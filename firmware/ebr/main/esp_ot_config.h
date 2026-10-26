/*
 * The H2 as RCP on the Waveshare ESP32-P4-ETH: Spinel on P4 UART1 (RX GPIO4 ← H2 TX, TX GPIO5 → H2 RX), the
 * H2's RST on GPIO20 and boot strap (IO9) on GPIO21 for RCP updates — the same wiring as firmware/ (header table in
 * notes/hardware-setup.md). The H2's BLE controller is on UART2 (BT_NIMBLE_* in sdkconfig.defaults).
 */
#pragma once

#include "sdkconfig.h"
#include "esp_openthread_types.h"
#include "esp_rcp_update.h"

#define ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG()              \
    {                                                      \
        .radio_mode = RADIO_MODE_UART_RCP,                 \
        .radio_uart_config = {                             \
            .port = UART_NUM_1,                            \
            .uart_config =                                 \
                {                                          \
                    .baud_rate = 460800,                   \
                    .data_bits = UART_DATA_8_BITS,         \
                    .parity = UART_PARITY_DISABLE,         \
                    .stop_bits = UART_STOP_BITS_1,         \
                    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, \
                    .rx_flow_ctrl_thresh = 0,              \
                    .source_clk = UART_SCLK_DEFAULT,       \
                },                                         \
            .rx_pin = GPIO_NUM_4,                          \
            .tx_pin = GPIO_NUM_5,                          \
        },                                                 \
    }

#define ESP_OPENTHREAD_DEFAULT_HOST_CONFIG()               \
    {                                                      \
        .host_connection_mode = HOST_CONNECTION_MODE_NONE, \
    }

#define ESP_OPENTHREAD_DEFAULT_PORT_CONFIG()                                            \
    {                                                                                   \
        .storage_partition_name = "nvs", .netif_queue_size = 10, .task_queue_size = 10, \
    }

#define ESP_OPENTHREAD_RCP_UPDATE_CONFIG()                                                                   \
    {                                                                                                        \
        .rcp_type = RCP_TYPE_UART, .uart_rx_pin = GPIO_NUM_4, .uart_tx_pin = GPIO_NUM_5, .uart_port = 1,     \
        .uart_baudrate = 115200, .reset_pin = GPIO_NUM_20, .boot_pin = GPIO_NUM_21, .update_baudrate = 460800, \
        .firmware_dir = "/rcp_fw/ot_rcp", .target_chip = ESP32H2_CHIP                                         \
    }
