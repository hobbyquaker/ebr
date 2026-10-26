#pragma once

typedef enum {
    BR_RADIO_STARTING,  // not heard from yet
    BR_RADIO_FLASHING,  // the P4 is writing the RCP firmware onto it
    BR_RADIO_OK,        // the OpenThread stack talks to it
    BR_RADIO_NO_ANSWER, // reset or update failed (wiring, power, wrong chip)
} br_radio_state_t;

#include "br_display.h" // br_bt_state_t

/** Starts watching the log for the radio's state. Call before the OpenThread stack starts. */
void br_radio_watch_start(void);

/** The radio's state; *progress gets the flashing progress in percent. */
br_radio_state_t br_radio_state(int *progress);

/** The Bluetooth state last reported through br_display_set_bt(). */
br_bt_state_t br_radio_bt(void);

/** "H2" or "C6", from the border router's RCP target setting. */
const char *br_radio_chip(void);
