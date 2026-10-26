/*
 * SPDX-FileCopyrightText: 2021-2026 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 *
 * OpenThread Radio Co-Processor (RCP) Example
 *
 * This example code is in the Public Domain (or CC0-1.0 licensed, at your option.)
 *
 * Unless required by applicable law or agreed to in writing, this
 * software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
 * CONDITIONS OF ANY KIND, either express or implied.
 */

#include <stdio.h>
#include <unistd.h>

#include "esp_event.h"
#include "nvs_flash.h"
#include "esp_openthread.h"
#include "esp_ot_config.h"
#include "esp_vfs_eventfd.h"

#if CONFIG_ESP_COEX_EXTERNAL_COEXIST_ENABLE
#include "ot_examples_common.h"
#endif

#if !SOC_IEEE802154_SUPPORTED
#error "RCP is only supported for the SoCs which have IEEE 802.15.4 module"
#endif

#if CONFIG_OPENTHREAD_RCP_SPINEL_CONSOLE
#include "esp_console.h"
#if CONFIG_IEEE802154_DEBUG
#include "ieee802154_debug.h"
#endif
#if CONFIG_ESP_COEX_EXTERNAL_COEXIST_ENABLE
#include "ext_coex_cmd.h"
#endif
#endif

#define TAG "ot_esp_rcp"

#if CONFIG_BT_ENABLED
#include "esp_bt.h"

/*
 * Ours: the Bluetooth LE controller next to the RCP, its HCI on UART1 (BT_LE_HCI_INTERFACE_USE_UART), so the
 * border router's Matter stack on the P4 can pair over Bluetooth through this chip.
 */
static void ble_controller_start(void)
{
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
    ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));
}
#endif

extern void otAppNcpInit(otInstance *instance);

void app_main(void)
{
    // Used eventfds:
    // * ot task queue
    // * radio driver
    esp_vfs_eventfd_config_t eventfd_config = {
        .max_fds = 2,
    };

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_vfs_eventfd_register(&eventfd_config));

#if CONFIG_ESP_COEX_EXTERNAL_COEXIST_ENABLE
    ot_external_coexist_init();
#endif

    static esp_openthread_config_t config = {
        .netif_config = {0},
        .platform_config = {
            .radio_config = ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG(),
            .host_config = ESP_OPENTHREAD_DEFAULT_HOST_CONFIG(),
            .port_config = ESP_OPENTHREAD_DEFAULT_PORT_CONFIG(),
        },
    };

#if CONFIG_OPENTHREAD_RCP_SPINEL_CONSOLE
    esp_console_config_t console_config = ESP_CONSOLE_CONFIG_DEFAULT();
    esp_console_init(&console_config);
    esp_console_register_help_command();
#if CONFIG_IEEE802154_DEBUG
    register_ieee802154_debug_cmd();
#endif
#if CONFIG_ESP_COEX_EXTERNAL_COEXIST_ENABLE
    register_cmd_extcoex();
#endif
#endif

#if CONFIG_BT_ENABLED
    ble_controller_start();
#endif
    ESP_ERROR_CHECK(esp_openthread_start(&config));
}
