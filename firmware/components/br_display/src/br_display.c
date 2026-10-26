#include "br_display.h"

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/spi_master.h"
#include "esp_check.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_ops.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_log.h"
#include "esp_app_desc.h"
#include "esp_rom_gpio.h"
#include "esp_lvgl_port.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/gpio_sig_map.h"
#include "soc/spi_periph.h"

#include <string.h>

#include "br_radio.h"
#include "br_status.h"
#include "br_ui.h"

#define TAG "br_display"

#define LCD_HOST SPI2_HOST
#define DRAW_LINES 40 // LVGL draws in bands of this many lines (double buffered, internal DMA memory)

#define TICK_MS 50
#define REFRESH_MS 1000

// Kconfig bools are undefined when off
#ifdef CONFIG_BR_DISPLAY_INVERT_COLORS
#define INVERT_COLORS true
#else
#define INVERT_COLORS false
#endif
#ifdef CONFIG_BR_DISPLAY_SWAP_XY
#define SWAP_XY true
#else
#define SWAP_XY false
#endif
#ifdef CONFIG_BR_DISPLAY_MIRROR_X
#define MIRROR_X true
#else
#define MIRROR_X false
#endif
#ifdef CONFIG_BR_DISPLAY_MIRROR_Y
#define MIRROR_Y true
#else
#define MIRROR_Y false
#endif
#ifdef CONFIG_BR_DISPLAY_BL_ACTIVE_LOW
#define BL_ACTIVE_LOW 1
#else
#define BL_ACTIVE_LOW 0
#endif

#ifdef CONFIG_BR_DISPLAY_PWR_ACTIVE_LOW
#define PWR_ON_LEVEL 0
#else
#define PWR_ON_LEVEL 1
#endif
#define PWR_SETTLE_MS 20 // module VCC up (its capacitors charged) before the ST7789 is reset

static esp_netif_t *volatile s_backbone;
static char s_pairing_qr[96];
static void (*s_reset_handler)(void);
static char s_pairing_code[24];
static esp_lcd_panel_handle_t s_panel;
static br_status_t s_status;
static bool s_on;           // backlight on, panel awake
static TickType_t s_on_since; // last boot, wake or button press

static esp_err_t backlight_init(void)
{
#if CONFIG_BR_DISPLAY_PIN_BL >= 0
    const ledc_timer_config_t timer = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 5000,
        .clk_cfg = LEDC_AUTO_CLK,
    };
    ESP_RETURN_ON_ERROR(ledc_timer_config(&timer), TAG, "backlight timer");
    const ledc_channel_config_t channel = {
        .gpio_num = CONFIG_BR_DISPLAY_PIN_BL,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .timer_sel = LEDC_TIMER_0,
        .duty = 0, // dark until the first screen is drawn
        .flags.output_invert = BL_ACTIVE_LOW,
    };
    ESP_RETURN_ON_ERROR(ledc_channel_config(&channel), TAG, "backlight channel");
#endif
    return ESP_OK;
}

static void backlight_set(bool on)
{
#if CONFIG_BR_DISPLAY_PIN_BL >= 0
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, on ? (1023 * CONFIG_BR_DISPLAY_BRIGHTNESS) / 100 : 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
#endif
}

/*
 * Module VCC through a high-side switch (modules without BLK). While it is off every signal line to the module is
 * driven low: a high line (CS idles high) would power the module through its protection diodes.
 */
#if CONFIG_BR_DISPLAY_PIN_PWR >= 0
static void power_set(bool on)
{
    gpio_set_level(CONFIG_BR_DISPLAY_PIN_PWR, on ? PWR_ON_LEVEL : !PWR_ON_LEVEL);
}

static void signal_lines_to_spi(bool spi)
{
    const struct {
        int gpio;
        uint32_t sig;
    } lines[] = {
        {CONFIG_BR_DISPLAY_PIN_SCLK, spi_periph_signal[LCD_HOST].spiclk_out},
        {CONFIG_BR_DISPLAY_PIN_MOSI, spi_periph_signal[LCD_HOST].spid_out},
        {CONFIG_BR_DISPLAY_PIN_CS, spi_periph_signal[LCD_HOST].spics_out[0]}, // the only device on the bus
    };
    for (size_t i = 0; i < sizeof(lines) / sizeof(lines[0]); i++) {
        if (lines[i].gpio < 0) {
            continue;
        }
        gpio_set_level(lines[i].gpio, 0);
        esp_rom_gpio_connect_out_signal(lines[i].gpio, spi ? lines[i].sig : SIG_GPIO_OUT_IDX, false, false);
    }
    if (!spi) {
        gpio_set_level(CONFIG_BR_DISPLAY_PIN_DC, 0);
        if (CONFIG_BR_DISPLAY_PIN_RST >= 0) {
            gpio_set_level(CONFIG_BR_DISPLAY_PIN_RST, 0);
        }
    }
}
#endif

static esp_err_t power_init(void)
{
#if CONFIG_BR_DISPLAY_PIN_PWR >= 0
    const gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << CONFIG_BR_DISPLAY_PIN_PWR,
        .mode = GPIO_MODE_OUTPUT,
    };
    ESP_RETURN_ON_ERROR(gpio_config(&cfg), TAG, "power GPIO");
    power_set(true);
    vTaskDelay(pdMS_TO_TICKS(PWR_SETTLE_MS));
#endif
    return ESP_OK;
}

/** Reset and set up the ST7789 (after power-up); orientation comes back from the driver's saved MADCTL. */
static esp_err_t panel_setup(esp_lcd_panel_handle_t panel)
{
    ESP_RETURN_ON_ERROR(esp_lcd_panel_reset(panel), TAG, "panel reset");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_init(panel), TAG, "panel init");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_invert_color(panel, INVERT_COLORS), TAG, "panel invert");
    return ESP_OK;
}

static esp_err_t panel_init(esp_lcd_panel_io_handle_t *io_out, esp_lcd_panel_handle_t *panel_out)
{
    const spi_bus_config_t bus = {
        .sclk_io_num = CONFIG_BR_DISPLAY_PIN_SCLK,
        .mosi_io_num = CONFIG_BR_DISPLAY_PIN_MOSI,
        .miso_io_num = -1,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = BR_UI_WIDTH * DRAW_LINES * sizeof(uint16_t),
    };
    ESP_RETURN_ON_ERROR(spi_bus_initialize(LCD_HOST, &bus, SPI_DMA_CH_AUTO), TAG, "SPI bus");

    const esp_lcd_panel_io_spi_config_t io_cfg = {
        .cs_gpio_num = CONFIG_BR_DISPLAY_PIN_CS, // -1: tied to GND or no CS pin
        .dc_gpio_num = CONFIG_BR_DISPLAY_PIN_DC,
        .spi_mode = CONFIG_BR_DISPLAY_SPI_MODE,
        .pclk_hz = CONFIG_BR_DISPLAY_SPI_MHZ * 1000 * 1000,
        .trans_queue_depth = 10,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)LCD_HOST, &io_cfg, io_out), TAG,
                        "panel IO");

    const esp_lcd_panel_dev_config_t panel_cfg = {
        .reset_gpio_num = CONFIG_BR_DISPLAY_PIN_RST,
#if CONFIG_BR_DISPLAY_BGR
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_BGR,
#else
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
#endif
        .bits_per_pixel = 16,
    };
    ESP_RETURN_ON_ERROR(esp_lcd_new_panel_st7789(*io_out, &panel_cfg, panel_out), TAG, "ST7789");
    ESP_RETURN_ON_ERROR(panel_setup(*panel_out), TAG, "panel setup");
    ESP_RETURN_ON_ERROR(esp_lcd_panel_disp_on_off(*panel_out, true), TAG, "panel on");
    return ESP_OK;
}

#define NO_KEY (-1)

static const struct {
    int gpio;
    br_key_t key;
} BUTTONS[] = {
    {CONFIG_BR_DISPLAY_PIN_BTN_SELECT, BR_KEY_SELECT},
    {CONFIG_BR_DISPLAY_PIN_BTN_BACK, BR_KEY_BACK},
    {CONFIG_BR_DISPLAY_PIN_BTN_PREV, BR_KEY_PREV},
    {CONFIG_BR_DISPLAY_PIN_BTN_NEXT, BR_KEY_NEXT},
};
#define BUTTON_COUNT (sizeof(BUTTONS) / sizeof(BUTTONS[0]))

static esp_err_t buttons_init(void)
{
    for (size_t i = 0; i < BUTTON_COUNT; i++) {
        if (BUTTONS[i].gpio < 0) {
            continue;
        }
        const gpio_config_t cfg = {
            .pin_bit_mask = 1ULL << BUTTONS[i].gpio,
            .mode = GPIO_MODE_INPUT,
            .pull_up_en = GPIO_PULLUP_ENABLE,
        };
        ESP_RETURN_ON_ERROR(gpio_config(&cfg), TAG, "button GPIO%d", BUTTONS[i].gpio);
    }
    return ESP_OK;
}

/** The key of a button that went down since the last call (polled every TICK_MS, which also debounces). */
static int button_pressed(void)
{
    static bool was_down[BUTTON_COUNT];
    int key = NO_KEY;
#if CONFIG_BR_DISPLAY_LOG_BUTTON_LEVELS
    static int last_levels = -1;
    int levels = 0;
    for (size_t i = 0; i < BUTTON_COUNT; i++) {
        if (BUTTONS[i].gpio >= 0) {
            levels |= gpio_get_level(BUTTONS[i].gpio) << i;
        }
    }
    if (levels != last_levels) {
        ESP_LOGI(TAG, "Button levels: SELECT(GPIO%d)=%d BACK(GPIO%d)=%d PREV(GPIO%d)=%d NEXT(GPIO%d)=%d",
                 BUTTONS[0].gpio, levels & 1, BUTTONS[1].gpio, (levels >> 1) & 1, BUTTONS[2].gpio,
                 (levels >> 2) & 1, BUTTONS[3].gpio, (levels >> 3) & 1);
        last_levels = levels;
    }
#endif
    for (size_t i = 0; i < BUTTON_COUNT; i++) {
        if (BUTTONS[i].gpio < 0) {
            continue;
        }
        bool down = gpio_get_level(BUTTONS[i].gpio) == 0;
        if (down && !was_down[i] && key == NO_KEY) {
            static const char *const NAMES[] = {"SELECT", "BACK", "PREV", "NEXT"};
            ESP_LOGI(TAG, "Button %s (GPIO%d)", NAMES[BUTTONS[i].key], BUTTONS[i].gpio);
            key = BUTTONS[i].key;
        }
        was_down[i] = down;
    }
    return key;
}

/** Collects the state, applies a key (or NO_KEY) and redraws. */
static void refresh(int key)
{
    // Collect outside the LVGL lock, so OpenThread is never waited for while LVGL is blocked.
    bool fresh = br_status_collect(s_backbone, &s_status);
    s_status.firmware = esp_app_get_description()->version;
    s_status.pairing_qr = s_pairing_qr[0] ? s_pairing_qr : NULL;
    s_status.pairing_code = s_pairing_code[0] ? s_pairing_code : NULL;
    if (lvgl_port_lock(0)) {
        if (key != NO_KEY) {
            br_ui_key((br_key_t)key);
        }
        if (fresh || key != NO_KEY) {
            br_ui_update(&s_status);
        }
        lvgl_port_unlock();
    }
}

static void display_sleep(void)
{
    backlight_set(false);
    esp_lcd_panel_disp_on_off(s_panel, false);
#if CONFIG_BR_DISPLAY_PIN_PWR >= 0
    // Under the LVGL lock no flush is running; stopped, LVGL sends nothing to the unpowered module
    if (lvgl_port_lock(0)) {
        lvgl_port_stop();
        lvgl_port_unlock();
    }
    signal_lines_to_spi(false);
    power_set(false);
#else
    esp_lcd_panel_disp_sleep(s_panel, true);
#endif
    s_on = false;
    ESP_LOGI(TAG, "Display off");
}

static void display_wake(void)
{
#if CONFIG_BR_DISPLAY_PIN_PWR >= 0
    power_set(true);
    vTaskDelay(pdMS_TO_TICKS(PWR_SETTLE_MS));
    signal_lines_to_spi(true);
    if (panel_setup(s_panel) != ESP_OK) {
        ESP_LOGE(TAG, "Panel setup after power-up failed");
    }
    lvgl_port_resume();
#else
    esp_lcd_panel_disp_sleep(s_panel, false); // waits the ST7789's sleep-out time
#endif
    refresh(NO_KEY);
    if (lvgl_port_lock(0)) {
        lv_obj_invalidate(lv_screen_active()); // the panel's memory is lost with its power
        lv_refr_now(NULL);
        lvgl_port_unlock();
    }
    esp_lcd_panel_disp_on_off(s_panel, true);
    backlight_set(true);
    s_on = true;
    s_on_since = xTaskGetTickCount();
    ESP_LOGI(TAG, "Display on");
}

static void hold_tick(TickType_t now);

static void display_task(void *ctx)
{
    TickType_t last_refresh = 0, last_page = xTaskGetTickCount();
    for (;;) {
        TickType_t now = xTaskGetTickCount();
        int key = button_pressed();

        if (!s_on) {
            if (key != NO_KEY) { // any button wakes the display; the press does nothing else
                display_wake();
                last_refresh = last_page = xTaskGetTickCount();
            }
            vTaskDelay(pdMS_TO_TICKS(TICK_MS));
            continue;
        }

        if (key != NO_KEY) {
            s_on_since = now; // each press restarts the timeout
        }
        hold_tick(now);
#if CONFIG_BR_DISPLAY_ON_SECONDS > 0
        if (now - s_on_since >= pdMS_TO_TICKS(CONFIG_BR_DISPLAY_ON_SECONDS * 1000)) {
            display_sleep();
            continue;
        }
#endif

#if !CONFIG_BR_DISPLAY_HAS_BUTTONS && CONFIG_BR_DISPLAY_PAGE_SECONDS > 0
        if (now - last_page >= pdMS_TO_TICKS(CONFIG_BR_DISPLAY_PAGE_SECONDS * 1000)) {
            key = BR_KEY_NEXT;
            last_page = now;
        }
#endif
        if (key != NO_KEY || now - last_refresh >= pdMS_TO_TICKS(REFRESH_MS)) {
            last_refresh = now;
            refresh(key);
        }
        vTaskDelay(pdMS_TO_TICKS(TICK_MS));
    }
}

esp_err_t br_display_start(void)
{
    br_radio_watch_start(); // before the OpenThread stack, so the RCP update is seen
    ESP_RETURN_ON_ERROR(backlight_init(), TAG, "backlight");
    ESP_RETURN_ON_ERROR(power_init(), TAG, "module power");

    esp_lcd_panel_io_handle_t io;
    ESP_RETURN_ON_ERROR(panel_init(&io, &s_panel), TAG, "panel");

    const lvgl_port_cfg_t port_cfg = ESP_LVGL_PORT_INIT_CONFIG();
    ESP_RETURN_ON_ERROR(lvgl_port_init(&port_cfg), TAG, "LVGL port");

    const lvgl_port_display_cfg_t disp_cfg = {
        .io_handle = io,
        .panel_handle = s_panel,
        .buffer_size = BR_UI_WIDTH * DRAW_LINES,
        .double_buffer = true,
        .hres = BR_UI_WIDTH,
        .vres = BR_UI_HEIGHT,
        .monochrome = false,
        .color_format = LV_COLOR_FORMAT_RGB565,
        .rotation =
            {
                .swap_xy = SWAP_XY,
                .mirror_x = MIRROR_X,
                .mirror_y = MIRROR_Y,
            },
        .flags =
            {
                .buff_dma = true,
                .swap_bytes = true, // RGB565 goes out big-endian over SPI
            },
    };
    lv_display_t *disp = lvgl_port_add_disp(&disp_cfg);
    ESP_RETURN_ON_FALSE(disp, ESP_FAIL, TAG, "LVGL display");

    ESP_RETURN_ON_ERROR(buttons_init(), TAG, "buttons");

    ESP_RETURN_ON_FALSE(lvgl_port_lock(0), ESP_FAIL, TAG, "LVGL lock");
#ifdef CONFIG_BR_DISPLAY_HAS_BUTTONS
    br_ui_create(true);
#else
    br_ui_create(false);
#endif
    lv_refr_now(disp);
    lvgl_port_unlock();
    // On at boot; the timeout runs from here
    backlight_set(true);
    s_on = true;
    s_on_since = xTaskGetTickCount();

    ESP_RETURN_ON_FALSE(xTaskCreate(display_task, "br_display", 4096, NULL, 2, NULL) == pdPASS, ESP_ERR_NO_MEM, TAG,
                        "display task");
    ESP_LOGI(TAG, "Display up: ST7789 %dx%d, SPI %d MHz, on for %d s", BR_UI_WIDTH, BR_UI_HEIGHT,
             CONFIG_BR_DISPLAY_SPI_MHZ, CONFIG_BR_DISPLAY_ON_SECONDS);
    return ESP_OK;
}

void br_display_set_factory_reset_handler(void (*handler)(void))
{
    s_reset_handler = handler;
}

/*
 * Holding SELECT on the device page fills the bar; full = factory reset (once). Releasing before resets the bar.
 * Polled every tick while the display is on.
 */
static void hold_tick(TickType_t now)
{
#if CONFIG_BR_DISPLAY_PIN_BTN_SELECT >= 0
    static TickType_t since;
    static bool fired;
    static int shown = -1;
    bool down = gpio_get_level(CONFIG_BR_DISPLAY_PIN_BTN_SELECT) == 0;
    int percent = 0;
    if (down && br_ui_on_device_page() && !fired) {
        if (since == 0) {
            since = now ? now : 1;
        }
        percent = (int)((now - since) * portTICK_PERIOD_MS * 100 / CONFIG_BR_DISPLAY_RESET_HOLD_MS);
        if (percent > 100) {
            percent = 100;
        }
    } else if (!fired) {
        since = 0;
    } else {
        percent = 100;
    }
    if (percent != shown && lvgl_port_lock(0)) {
        br_ui_set_hold(percent);
        lvgl_port_unlock();
        shown = percent;
    }
    if (percent >= 100 && !fired) {
        fired = true;
        ESP_LOGW(TAG, "Factory reset confirmed on the device page");
        if (s_reset_handler) {
            s_reset_handler();
        }
    }
#endif
}

void br_display_set_pairing(const char *qr_payload, const char *manual_code)
{
    strlcpy(s_pairing_qr, qr_payload ? qr_payload : "", sizeof(s_pairing_qr));
    strlcpy(s_pairing_code, manual_code ? manual_code : "", sizeof(s_pairing_code));
}

void br_display_attach(esp_netif_t *backbone)
{
    s_backbone = backbone;
}
