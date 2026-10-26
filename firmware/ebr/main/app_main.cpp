/*
 * Spike, step 3 of notes/matter-device.md ("Plan"): the border router as a Matter-over-Thread device.
 *
 * Unpaired it advertises over Bluetooth (through the H2's BLE controller); Apple Home pairs it as a Thread device
 * and hands it the Thread dataset (Network Commissioning, Thread driver on endpoint 0); Matter then starts Thread
 * through the H2 RCP. Ethernet is the backbone of the border router. Matter never forms a network of its own:
 * Thread starts only with a dataset from pairing (or the Thread Border Router Management cluster).
 *
 * Based on esp-matter's examples/thread_border_router/main/app_main.cpp (Public Domain / CC0).
 */
#include <esp_err.h>
#include <esp_log.h>
#include <esp_netif.h>
#include <esp_openthread_border_router.h>
#include <esp_openthread_lock.h>
#include <esp_spiffs.h>
#include <mdns.h>
#include <nvs_flash.h>

#include <esp_matter.h>
#include <esp_matter_console.h>
#include <esp_matter_feature.h>

#include <esp_ot_config.h>
#include <esp_ot_rcp_update.h>
#include <esp_rcp_update.h>

#include <app/server/Server.h>
#include <platform/ESP32/OpenthreadLauncher.h>
#include <platform/KvsPersistentStorageDelegate.h>
#include <platform/OpenThread/GenericThreadBorderRouterDelegate.h>
#include <platform/ThreadStackManager.h>

#include <setup_payload/OnboardingCodesUtil.h>

#include "br_display.h"
#include "example_common_private.h"
#include "protocol_examples_common.h"

static const char *TAG = "ebr";

using namespace esp_matter;
using namespace esp_matter::endpoint;
using namespace chip::app::Clusters;
using chip::app::Clusters::ThreadBorderRouterManagement::GenericOpenThreadBorderRouterDelegate;

static void border_router_init_once(void)
{
    static bool done;
    if (done) {
        return;
    }
    esp_openthread_set_backbone_netif(get_example_netif());
    esp_openthread_lock_acquire(portMAX_DELAY);
    esp_err_t err = esp_openthread_border_router_init();
    esp_openthread_lock_release();
    ESP_LOGI(TAG, "Border router on the Ethernet backbone: %s", esp_err_to_name(err));
    br_display_attach(get_example_netif()); // from now on the display reads the Thread state
    done = true;
}

/*
 * The "home" fabric: the one that completed the first pairing (Apple Home). Apple adds a second, companion fabric
 * (VendorId 0x1384) and leaves it when the accessory is removed, so "last fabric gone" never happens; removing the
 * home fabric is what "removed from Home" means. Kept in NVS (namespace "ebr"); later pairings with other
 * controllers (multi-admin) do not replace it while it exists.
 */
#define EBR_NVS_NS "ebr"
#define EBR_NVS_HOME_FABRIC "home_fabric"

static bool fabric_exists(uint8_t index)
{
    return index != 0 && chip::Server::GetInstance().GetFabricTable().FindFabricWithIndex(index) != nullptr;
}

static uint8_t home_fabric_get(void)
{
    nvs_handle_t h;
    uint8_t index = 0;
    if (nvs_open(EBR_NVS_NS, NVS_READONLY, &h) == ESP_OK) {
        nvs_get_u8(h, EBR_NVS_HOME_FABRIC, &index);
        nvs_close(h);
    }
    return index;
}

static void home_fabric_remember(uint8_t index)
{
    if (fabric_exists(home_fabric_get())) {
        return; // a later commissioner (multi-admin) does not become "home"
    }
    nvs_handle_t h;
    if (nvs_open(EBR_NVS_NS, NVS_READWRITE, &h) == ESP_OK) {
        nvs_set_u8(h, EBR_NVS_HOME_FABRIC, index);
        nvs_commit(h);
        nvs_close(h);
        ESP_LOGI(TAG, "Home fabric: index %u", index);
    }
}

static void app_event_cb(const ChipDeviceEvent *event, intptr_t arg)
{
    using namespace chip::DeviceLayer;
    switch (event->Type) {
    case DeviceEventType::kESPSystemEvent:
        if (event->Platform.ESPSystemEvent.Base == IP_EVENT && event->Platform.ESPSystemEvent.Id == IP_EVENT_ETH_GOT_IP) {
            border_router_init_once();
        }
        break;
    case DeviceEventType::kCommissioningComplete:
        ESP_LOGI(TAG, "Commissioning complete (fabric index %u)", event->CommissioningComplete.fabricIndex);
        home_fabric_remember(event->CommissioningComplete.fabricIndex);
        break;
    case DeviceEventType::kThreadStateChange:
        ESP_LOGI(TAG, "Thread state changed");
        break;
    case DeviceEventType::kCHIPoBLEAdvertisingChange:
        br_display_set_bt(event->CHIPoBLEAdvertisingChange.Result == kActivity_Started ? BR_BT_ADVERTISING
                                                                                       : BR_BT_OFF);
        break;
    case DeviceEventType::kCHIPoBLEConnectionEstablished:
        ESP_LOGI(TAG, "BLE: commissioner connected");
        br_display_set_bt(BR_BT_CONNECTED);
        break;
    case DeviceEventType::kCHIPoBLEConnectionClosed:
        ESP_LOGI(TAG, "BLE: commissioner disconnected");
        br_display_set_bt(BR_BT_OFF);
        break;
    case DeviceEventType::kFabricRemoved:
        // Removed from Apple Home: when the home fabric (or every fabric) is gone, factory reset - leave the
        // Thread network, erase the dataset, show the pairing QR again (decided 2026-10-20)
        if (!fabric_exists(home_fabric_get()) || chip::Server::GetInstance().GetFabricTable().FabricCount() == 0) {
            ESP_LOGW(TAG, "Home fabric removed: factory reset");
            esp_matter::factory_reset();
        } else {
            ESP_LOGI(TAG, "Fabric removed, %u left, home fabric %u still there",
                     chip::Server::GetInstance().GetFabricTable().FabricCount(), home_fabric_get());
        }
        break;
    default:
        break;
    }
}

static void ethernet_task(void *arg)
{
    // Blocks until Ethernet has its addresses; the netif's key is "ETH_DEF", which the Matter stack recognises.
    ESP_ERROR_CHECK(example_ethernet_connect());
    vTaskDelete(NULL);
}

/* Factory reset from the display's device page (SELECT held until the bar is full) */
static void factory_reset_from_display(void)
{
    ESP_LOGW(TAG, "Factory reset from the device page");
    esp_matter::factory_reset();
}

/* The pairing codes for the display (BLE: the router is commissioned over Bluetooth only) */
static void show_pairing_codes(void)
{
    char qr[96], manual[24];
    chip::MutableCharSpan qr_span(qr, sizeof(qr) - 1), manual_span(manual, sizeof(manual) - 1);
    chip::RendezvousInformationFlags ble(chip::RendezvousInformationFlag::kBLE);
    if (GetQRCode(qr_span, ble) == CHIP_NO_ERROR && GetManualPairingCode(manual_span, ble) == CHIP_NO_ERROR) {
        qr[qr_span.size()] = '\0';
        manual[manual_span.size()] = '\0';
        br_display_set_pairing(qr, manual);
    }
}

extern "C" void app_main()
{
    nvs_flash_init();
    if (br_display_start() != ESP_OK) {
        ESP_LOGE(TAG, "Display start failed, continuing without it");
    }
    br_display_set_factory_reset_handler(factory_reset_from_display);

    node::config_t node_config;
    // NodeLabel: the name the device suggests for itself; the Home app showed "Matter Test" (test vendor ID)
    strlcpy(node_config.root_node.basic_information.node_label, "ESP Border Router",
            sizeof(node_config.root_node.basic_information.node_label));
    node_t *node = node::create(&node_config, NULL, NULL);
    static chip::KvsPersistentStorageDelegate tbr_storage_delegate;
    LogErrorOnFailure(tbr_storage_delegate.Init(&chip::DeviceLayer::PersistedStorage::KeyValueStoreMgr()));
    GenericOpenThreadBorderRouterDelegate *delegate =
        chip::Platform::New<GenericOpenThreadBorderRouterDelegate>(&tbr_storage_delegate);
    if (!node || !delegate) {
        ESP_LOGE(TAG, "Failed to create the data model");
        return;
    }
    static char br_name[] = "ebr";
    delegate->SetThreadBorderRouterName(chip::CharSpan(br_name));
    thread_border_router::config_t tbr_config;
    tbr_config.thread_border_router_management.delegate = delegate;
    endpoint_t *tbr_endpoint = thread_border_router::create(node, &tbr_config, ENDPOINT_FLAG_NONE, NULL);
    if (!tbr_endpoint) {
        ESP_LOGE(TAG, "Failed to create the border router endpoint");
        return;
    }

    // RCP update from the rcp_fw partition (the H2 firmware of firmware/rcp_h2)
    esp_vfs_spiffs_conf_t rcp_fw_conf = {
        .base_path = "/rcp_fw", .partition_label = "rcp_fw", .max_files = 10, .format_if_mount_failed = false};
    ESP_ERROR_CHECK(esp_vfs_spiffs_register(&rcp_fw_conf));
    esp_rcp_update_config_t rcp_update_config = ESP_OPENTHREAD_RCP_UPDATE_CONFIG();
    esp_rcp_update_init(&rcp_update_config);
    esp_ot_register_rcp_handler();
    // Reset the H2 through its RST wire before Thread and BLE start: while the P4 itself resets, its HCI TX line
    // floats, the H2's HCI parser reads garbage and can stay unresponsive for a minute or for good ("HCI wait for
    // ack"). A fresh H2 on a quiet line syncs at once.
    esp_rcp_reset();
    vTaskDelay(pdMS_TO_TICKS(500));

    esp_openthread_platform_config_t ot_config = {
        .radio_config = ESP_OPENTHREAD_DEFAULT_RADIO_CONFIG(),
        .host_config = ESP_OPENTHREAD_DEFAULT_HOST_CONFIG(),
        .port_config = ESP_OPENTHREAD_DEFAULT_PORT_CONFIG(),
    };
    set_openthread_platform_config(&ot_config);

    esp_err_t err = esp_matter::start(app_event_cb);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Matter start failed: %d", err);
        return;
    }

    {
        // Update the H2 if its firmware differs from the one in rcp_fw (Thread paused meanwhile)
        esp_matter::lock::ScopedChipStackLock lock(portMAX_DELAY);
        using namespace chip::DeviceLayer;
        bool thread_was_enabled = ThreadStackMgr().IsThreadEnabled();
        if (thread_was_enabled) {
            ThreadStackMgr().SetThreadEnabled(false);
        }
        esp_ot_update_rcp_if_different();
        if (thread_was_enabled) {
            ThreadStackMgr().SetThreadEnabled(true);
        }
    }

    // mDNS for Matter's own DNS-SD on Ethernet and for the border router: its SRP advertising proxy publishes the
    // Thread devices' services (ours included, when it registers with our SRP server) on the LAN. Without it Apple
    // did not find the router again after a restart (2026-10-20). Needs the default event loop esp_matter::start made.
    ESP_ERROR_CHECK(mdns_init());
    mdns_hostname_set("ebr");

    show_pairing_codes();
    xTaskCreate(ethernet_task, "ethernet", 4096, NULL, 5, NULL);

#if CONFIG_ENABLE_CHIP_SHELL
    esp_matter::console::diagnostics_register_commands();
    esp_matter::console::factoryreset_register_commands();
#if CONFIG_OPENTHREAD_CLI
    esp_matter::console::otcli_register_commands();
#endif
    esp_matter::console::init();
#endif
}
