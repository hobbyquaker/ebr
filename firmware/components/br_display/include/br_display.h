#pragma once

#include "esp_err.h"
#include "esp_netif.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BR_BT_NONE,        // no Bluetooth host on the P4
    BR_BT_OFF,         // host up (controller answered), not advertising
    BR_BT_ADVERTISING, // advertising (open for Matter pairing, or the test advertiser)
    BR_BT_CONNECTED,   // a central (commissioner) is connected
} br_bt_state_t;

/** The Bluetooth host reports its state for the display. */
void br_display_set_bt(br_bt_state_t state);

/**
 * The Matter pairing codes (QR payload "MT:…" and the manual code). While the router has no Thread dataset the
 * display shows them instead of the "No Thread dataset yet" screen. NULL clears them.
 */
void br_display_set_pairing(const char *qr_payload, const char *manual_code);

/**
 * The factory reset behind the device page: called once when SELECT has been held until the bar is full
 * (BR_DISPLAY_RESET_HOLD_MS). Without a handler the page shows the bar but nothing happens.
 */
void br_display_set_factory_reset_handler(void (*handler)(void));

/**
 * Brings up the ST7789 and LVGL and shows the start-up screen. Call once, early; independent of OpenThread.
 */
esp_err_t br_display_start(void);

/**
 * From now on the display reads the Thread state (OpenThread stack and border router initialised) and the
 * backbone interface. Call once, after esp_openthread_border_router_init().
 */
void br_display_attach(esp_netif_t *backbone);

#ifdef __cplusplus
}
#endif
