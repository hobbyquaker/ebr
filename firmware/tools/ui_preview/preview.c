/*
 * Renders the display's screens (components/br_display/src/br_ui.c, unchanged) on the workstation into PPM
 * files, with sample states. The values are made up; nothing here comes from a real network.
 */
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "lvgl.h"

#include "br_ui.h"

static uint16_t s_frame[BR_UI_WIDTH * BR_UI_HEIGHT];
static uint8_t s_draw_buf[BR_UI_WIDTH * BR_UI_HEIGHT * 2];

static uint32_t tick_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

static void flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px)
{
    const uint16_t *src = (const uint16_t *)px;
    for (int y = area->y1; y <= area->y2; y++) {
        for (int x = area->x1; x <= area->x2; x++) {
            s_frame[y * BR_UI_WIDTH + x] = *src++;
        }
    }
    lv_display_flush_ready(disp);
}

static void save(lv_display_t *disp, const char *path)
{
    lv_obj_invalidate(lv_screen_active());
    lv_refr_now(disp);
    FILE *f = fopen(path, "wb");
    fprintf(f, "P6\n%d %d\n255\n", BR_UI_WIDTH, BR_UI_HEIGHT);
    for (int i = 0; i < BR_UI_WIDTH * BR_UI_HEIGHT; i++) {
        uint16_t c = s_frame[i];
        uint8_t rgb[3] = {(uint8_t)(((c >> 11) & 0x1f) * 255 / 31), (uint8_t)(((c >> 5) & 0x3f) * 255 / 63),
                          (uint8_t)((c & 0x1f) * 255 / 31)};
        fwrite(rgb, 1, 3, f);
    }
    fclose(f);
    printf("wrote %s\n", path);
}

int main(int argc, char **argv)
{
    const char *out = argc > 1 ? argv[1] : ".";
    char path[512];

    lv_init();
    lv_tick_set_cb(tick_ms);
    lv_display_t *disp = lv_display_create(BR_UI_WIDTH, BR_UI_HEIGHT);
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_RGB565);
    lv_display_set_buffers(disp, s_draw_buf, NULL, sizeof(s_draw_buf), LV_DISPLAY_RENDER_MODE_FULL);
    lv_display_set_flush_cb(disp, flush);

    br_ui_create(true);
    snprintf(path, sizeof(path), "%s/1-starting.ppm", out);
    save(disp, path);

    br_status_t flashing = {.role = BR_ROLE_STARTING, .radio_chip = "H2", .radio = BR_RADIO_FLASHING,
                            .radio_progress = 42};
    br_ui_update(&flashing);
    snprintf(path, sizeof(path), "%s/1b-flashing-radio.ppm", out);
    save(disp, path);

    br_status_t st = {
        .attached = true,
        .has_dataset = false,
        .role = BR_ROLE_DISABLED,
        .eth_up = true,
        .ipv4 = "192.168.1.40",
        .radio_chip = "H2",
        .radio = BR_RADIO_OK,
        .uptime_s = 42,
    };
    br_ui_update(&st);
    snprintf(path, sizeof(path), "%s/2-no-dataset.ppm", out);
    save(disp, path);

    st.pairing_qr = "MT:Y.K90-C714BEB61V110"; // the ebr spike's test pairing code, not a secret
    st.pairing_code = "23751530266";
    st.bt = BR_BT_ADVERTISING;
    br_ui_update(&st);
    snprintf(path, sizeof(path), "%s/2b-pairing.ppm", out);
    save(disp, path);
    st.pairing_qr = NULL;
    st.pairing_code = NULL;

    st.has_dataset = true;
    st.role = BR_ROLE_ROUTER;
    strcpy(st.network_name, "MyHome1A2B");
    st.ipv6[0] = (br_ip6_t){BR_IP6_LINK_LOCAL, "fe80::eaf6:aff:fee8:275"};
    st.ipv6[1] = (br_ip6_t){BR_IP6_ULA, "fd12:3456:789a:1:eaf6:aff:fee8:275"};
    st.ipv6[2] = (br_ip6_t){BR_IP6_GLOBAL, "2001:db8:1234:5678:eaf6:aff:fee8:275"};
    st.ipv6[3] = (br_ip6_t){BR_IP6_GLOBAL, "2001:db8:1234:5678:9c3e:41ff:2b07:e1d4"};
    st.ipv6_count = 4;
    st.channel = 15;
    st.pan_id = 0x1a2b;
    st.rloc16 = 0x5800;
    st.border_routers = 2;
    st.uptime_s = 3 * 86400 + 4 * 3600;
    st.neighbour_total = 4;
    st.neighbour_routers = 2;
    st.neighbour_count = 4;
    st.neighbours[0] = (br_neighbour_t){0x2400, -58, BR_ROLE_LEADER, true};
    st.neighbours[1] = (br_neighbour_t){0x9c00, -71, BR_ROLE_ROUTER, false};
    st.neighbours[2] = (br_neighbour_t){0x5801, -64, BR_ROLE_CHILD, false};
    st.neighbours[3] = (br_neighbour_t){0x5802, -83, BR_ROLE_CHILD, false};
    br_ui_update(&st);
    snprintf(path, sizeof(path), "%s/3-status-router.ppm", out);
    save(disp, path);

    br_ui_key(BR_KEY_NEXT);
    br_ui_update(&st);
    snprintf(path, sizeof(path), "%s/4-neighbours.ppm", out);
    save(disp, path);

    br_ui_key(BR_KEY_NEXT);
    br_ui_update(&st);
    snprintf(path, sizeof(path), "%s/4a-network.ppm", out);
    save(disp, path);

    br_ui_key(BR_KEY_NEXT);
    st.firmware = "2327062";
    br_ui_update(&st);
    snprintf(path, sizeof(path), "%s/4b-device.ppm", out);
    save(disp, path);
    br_ui_set_hold(40);
    snprintf(path, sizeof(path), "%s/4c-device-holding.ppm", out);
    save(disp, path);
    br_ui_set_hold(0);

    br_ui_key(BR_KEY_NEXT);
    st.role = BR_ROLE_DETACHED;
    st.neighbour_total = st.neighbour_routers = st.neighbour_count = 0;
    br_ui_update(&st);
    snprintf(path, sizeof(path), "%s/5-status-detached.ppm", out);
    save(disp, path);
    return 0;
}
