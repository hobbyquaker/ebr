# ebr firmware

**ebr** (esp border router): a Thread border router on the Waveshare ESP32-P4-ETH with an ESP32-H2 board as the
radio, a 2.0" ST7789 status display and four buttons. It is a **Matter device**: the display shows a pairing QR,
the Home app pairs it over Bluetooth, Apple hands it the Thread network's dataset during pairing, and from then on
it is a border router in that network. Removing it in the Home app factory-resets it.

## Layout

| Path | What |
| --- | --- |
| [`ebr/`](ebr) | the P4 firmware: esp-matter (release/v1.6) + OpenThread border router + display. Based on esp-matter's `examples/thread_border_router` |
| [`rcp_h2/`](rcp_h2) | the H2 firmware: ESP-IDF's `ot_rcp` (Thread radio, Spinel on UART0) **plus** the Bluetooth LE controller with HCI on UART1. The P4 packs it and flashes the H2 itself |
| [`components/br_display/`](components/br_display) | the ST7789 + LVGL display, the buttons, the status/neighbours/pairing screens, the radio and BLE state |
| [`tools/ui_preview/`](tools/ui_preview) | renders the screens on the PC (host gcc + the LVGL that `ebr` fetched) |

## How the pieces talk

| Link | P4 | H2 | |
| --- | --- | --- | --- |
| Thread (Spinel) | UART1, RX GPIO4, TX GPIO5 | UART0, TX 24, RX 23 | 460800 baud |
| Bluetooth (HCI H4) | UART2, TX GPIO22, RX GPIO23 | UART1, RX 10, TX 11 | 115200 baud, ACL buffer **100 bytes × 1** on the H2 |
| RCP reset / boot | GPIO20 / GPIO21 | RST / IO9 | the P4 resets the H2 at every start and flashes it when its firmware differs |

The NimBLE **host** runs on the P4 (`BT_CONTROLLER_DISABLED`, `BT_NIMBLE_TRANSPORT_UART`), the **controller** on the
H2 (`BT_LE_HCI_INTERFACE_USE_UART`). The H2 shares its radio between 802.15.4 and BLE (software coexistence) and
therefore cannot offer the RCP capability rx-on-when-idle; the P4 does not require it
(`OPENTHREAD_RX_ON_WHEN_IDLE=n`). The H2's HCI UART loses bursts over ~130 bytes (its FIFO) — hence one 100-byte
ACL buffer, so the host waits after every packet.

## Build

```sh
. ~/esp/esp-idf/export.sh             # ESP-IDF v5.5.6
. ~/esp/esp-matter/export.sh          # esp-matter release/v1.6 (ESP_MATTER_PATH)
(cd firmware/rcp_h2 && idf.py set-target esp32h2 && idf.py build)   # first: the H2 image
cd firmware/ebr
idf.py set-target esp32p4             # applies sdkconfig.defaults
idf.py build
idf.py -p /dev/ttyACM0 flash          # first time: erase-flash flash
```

`ebr` packs `../rcp_h2/build` into its `rcp_fw` partition (`CONFIG_RCP_SRC_DIR` via `BR_RCP_BUILD_DIR`). After a
change to the H2 firmware, rebuild `rcp_h2` first, then `ebr`; on boot the P4 updates the H2. After moving the
project, delete `dependencies.lock` and `managed_components` (they hold absolute paths).

The Matter SDK pulls `esp_hosted` and `esp_wifi_remote` into every P4 build; `ebr/stubs/` replaces them with empty
components (`override_path`) — there is no Wi-Fi co-processor, and esp_hosted would claim GPIO14–19 (the buttons).

Pairing data are **test values** (`ENABLE_TEST_SETUP_PARAMS`, test vendor ID 0xFFF1, Espressif's test DAC):
passcode 49582731, discriminator 0xA5C, verifier from connectedhomeip's `spake2p.py` — see `ebr/CMakeLists.txt`.
Apple Home adds it as an "uncertified accessory" and lists it as **"Matter Accessory", not supported** (fine).
Basic Information: vendor "hobbyquaker", product "ebr", node label "ESP Border Router".

## Behaviour

- **Unpaired:** Thread off, BLE advertising, the display shows "ADD TO APPLE HOME" with the QR and the setup code.
- **Paired:** Thread on with the dataset from the pairing; border router on Ethernet (SRP server, advertising
  proxy, mDNS hostname `ebr`); the status screen (role, network, channel, PAN ID, neighbours, RLOC16, radio + BT
  state, border routers, IPv4 + one IPv6 address); PREV/NEXT page through Status → Neighbours → Network (all
  IPv6 addresses) → Device, BACK goes home.
- **Factory reset on the device:** Device page, hold SELECT until the bar is full (5 s; releasing cancels) →
  `esp_matter::factory_reset()`, restart unpaired with the pairing QR. Remove the stale entry in the Home app.
- **Removed in the Home app** (the fabric that completed the first pairing is gone — Apple leaves a second,
  companion fabric behind): factory reset → unpaired.
- **Matter console** on the P4's UART (115200): `matter onboardingcodes ble`, `matter device factoryreset`,
  `matter esp ot_cli <command>`.
- The display goes dark after 5 min; any button wakes it.
- **No web server** — esp-thread-br's REST API has no authentication (`notes/rest-api.md`).

## Known issues

- **Start-up assert** `hci_h4.c:148` on the first boot after a flash (bytes on the HCI line before NimBLE's parser
  is ready); the P4 restarts once and then runs.
- Opening the P4's or the H2's USB serial port resets the board (CH343 / USB-Serial-JTAG reset lines).
- Never keep a BLE app (nRF Connect) connected while pairing: the router stops advertising during a connection.

## Diagnostics

- `rcp_h2/sdkconfig.defaults.usblog`: the H2's log on its own USB port (the board's "USB" socket); build into
  `build_diag` and flash over that port — see `notes/matter-device.md`.
- `BR_DISPLAY_LOG_BUTTON_LEVELS`: logs the raw button levels.
- `tools/ui_preview/build.sh <dir>`: the screens as PNGs.
