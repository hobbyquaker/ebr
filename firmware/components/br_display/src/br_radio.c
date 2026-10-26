/*
 * The state of the radio co-processor for the display. esp-thread-br's RCP update (esp_rcp_update) and
 * OpenThread's Spinel driver report it only as log lines, so this watches the firmware's own log output for
 * them — every line is still passed on unchanged.
 */
#include "br_radio.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "esp_log.h"

static vprintf_like_t s_next;
static volatile br_radio_state_t s_state = BR_RADIO_STARTING;
static volatile int s_progress; // percent while flashing
static volatile br_bt_state_t s_bt = BR_BT_NONE;

static void scan(const char *line)
{
    const char *p;
    if (strstr(line, "RCP_UPDATE:")) {
        if ((p = strstr(line, "Progress: "))) {
            s_progress = atoi(p + 10);
            s_state = BR_RADIO_FLASHING;
        } else if (strstr(line, "Erasing flash") || strstr(line, "Start programming")) {
            s_progress = 0;
            s_state = BR_RADIO_FLASHING;
        } else if (strstr(line, "Failed to connect to RCP") || strstr(line, "Failed to update RCP")) {
            s_state = BR_RADIO_NO_ANSWER;
        }
    } else if (strstr(line, "Failed to reset co-processor")) {
        s_state = BR_RADIO_NO_ANSWER;
    } else if (strstr(line, "OpenThread enter mainloop") || strstr(line, "Running RCP Version")) {
        s_state = BR_RADIO_OK;
    }
}

static int log_hook(const char *fmt, va_list args)
{
    char line[160];
    va_list copy;
    va_copy(copy, args);
    vsnprintf(line, sizeof(line), fmt, copy);
    va_end(copy);
    scan(line);
    return s_next ? s_next(fmt, args) : vprintf(fmt, args);
}

void br_radio_watch_start(void)
{
    if (!s_next) {
        s_next = esp_log_set_vprintf(log_hook);
    }
}

br_radio_state_t br_radio_state(int *progress)
{
    if (progress) {
        *progress = s_progress;
    }
    return s_state;
}

void br_display_set_bt(br_bt_state_t state)
{
    s_bt = state;
}

br_bt_state_t br_radio_bt(void)
{
    return s_bt;
}

const char *br_radio_chip(void)
{
#if CONFIG_ESP_BR_H2_TARGET
    return "H2";
#elif CONFIG_ESP_BR_C6_TARGET
    return "C6";
#else
    return CONFIG_BR_DISPLAY_RADIO_CHIP; // projects without esp-thread-br's settings (the Matter firmware)
#endif
}
