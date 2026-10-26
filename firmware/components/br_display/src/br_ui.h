#pragma once

#include "lvgl.h"

#include "br_status.h"

#define BR_UI_WIDTH 320
#define BR_UI_HEIGHT 240

typedef enum {
    BR_KEY_SELECT, // the screen's action (none of the current screens has one yet)
    BR_KEY_BACK,   // back to the status screen
    BR_KEY_PREV,   // previous screen
    BR_KEY_NEXT,   // next screen
} br_key_t;

/** Builds all screens and shows the start-up state. Call with the LVGL lock held. */
void br_ui_create(bool has_buttons);

/** Shows the screen that fits the state and fills it. Call with the LVGL lock held. */
void br_ui_update(const br_status_t *status);

/** A button press; br_ui_update() shows the result. Call with the LVGL lock held. */
void br_ui_key(br_key_t key);

/** True while the device page (with the factory reset) is shown. */
bool br_ui_on_device_page(void);

/**
 * Progress of holding SELECT on the device page, 0..100 (0 = not held). 100 shows "Resetting…".
 * Call with the LVGL lock held.
 */
void br_ui_set_hold(int percent);
