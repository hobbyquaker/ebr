# The border router as a Matter device

*Note, 2026-10-17, on the question: can the device be a Thread border router and a Matter device at
once, how would Apple Home show it?* Research only; the points not verified are marked.

**Scope (2026-10-18): the relays are dropped.** v1 is a border router with display and four keys, no
other inputs or outputs. **Update 2026-10-20: Matter on the device is back — as the way to join** (plan below).
Before that it was not part of v1 either; it comes back with the v2 ideas
that need it — the virtual remote ([virtual-remote.md](virtual-remote.md), option A makes the router a Matter
switch) and possibly standalone mode ([standalone-mode.md](standalone-mode.md)). The relay sections below are
kept only as a record, marked *dropped*.

**State (end of 2026-10-20): built and verified** — `firmware/ebr` is this plan; the sections below keep the plan
and the findings of the way there. For how it works now, read [firmware/README.md](../firmware/README.md).

## Plan (2026-10-20): pair the router in Apple Home, get the dataset from the pairing

**Goal.** A new border router shows a Matter pairing QR on its display; the user scans it in the Home app; Apple
pairs it over **Bluetooth as a Matter-over-Thread device** and hands it the Thread dataset during pairing
(Network Commissioning cluster, `AddOrUpdateThreadNetwork`) — the same thing that happened with the C6 donor on
2026-10-20. The router then joins Apple's Thread network with that dataset and works as border router, **and stays
a Matter device** in Apple's fabric (shown in Home, shareable with she by multi-admin, OTA later).

**Removing it in Home = factory reset** (2026-10-20): when its last fabric is removed, the router
leaves the Thread network, erases the dataset (`otInstanceFactoryReset` / NVS) and shows the pairing QR again.

**Architecture — "A, concurrent" (agent proposal, to verify).** The P4 runs the Matter stack (esp-matter) as the
host of both radios on the H2:

| Part | Runs on | How |
| --- | --- | --- |
| Thread radio | H2, UART0 (as now) | `ot_rcp`, Spinel at 460800 |
| Bluetooth LE controller | **H2, UART1** (new: two more wires) | the H2 controller's HCI over UART (`BT_LE_HCI_INTERFACE_USE_UART`, port, pins, baud 115200…1M, optional RTS/CTS) |
| Bluetooth host | P4 | NimBLE host only (`BT_CONTROLLER_DISABLED`, `BT_NIMBLE_TRANSPORT_UART`) |
| Matter | P4 | esp-matter; Network Commissioning with the **Thread** driver on endpoint 0 (esp-matter's own `thread_border_router` example sets `THREAD_NETWORK_COMMISSIONING_DRIVER=n` — it pairs over Wi-Fi; we need the opposite) |
| Border router, display | P4 | our firmware as now; Ethernet as backbone |

One H2 firmware for both (its own project in this repository, from `ot_rcp` plus a few lines that start the BLE
controller, software coexistence on): the radio is time-shared between 802.15.4 and BLE, which Matter-over-Thread
devices on the H2 do all the time. Pairing then runs Matter's normal "concurrent" flow — Bluetooth stays up while
the router joins Thread — no switching under the fail-safe timer. **Fallback "A, switched"** if the combined H2
firmware does not work: the H2 boots a BLE-controller image while unpaired and the P4 swaps it for `ot_rcp` after
`ConnectNetwork` — needs Matter's non-concurrent commissioning (`SupportsConcurrentConnection` = false), whose
support in Apple Home is unknown.

Firmware rule: while unpaired the router must advertise as commissionable **over Bluetooth only, not on the LAN**
(no `_matterc._udp` on Ethernet) — on-network commissioning would skip the Thread credentials.

**Wiring (proposal, unchecked on the H2 board's labels):** H2 GPIO10 (labelled "10", default HCI RX) ← P4 GPIO22
(header pin 32); H2 GPIO11 (labelled "11", HCI TX, set in menuconfig) → P4 GPIO23 (header pin 31). Both P4 pins
are free (header table in [hardware-setup.md](hardware-setup.md)).

**Steps (each a spike that can fail early):**

*Progress:* step 1's firmware is `firmware/rcp_h2` (2026-10-20, 470 KB with the BLE controller; the P4 image
packs it and flashed it onto the H2 by itself). **Coexistence costs the RCP capability rx-on-when-idle**
(ESP-IDF: "not supported when SW coexistence is enabled"); the P4 required it, failed the RCP check and reflashed
the H2 in a loop — fixed by `CONFIG_OPENTHREAD_RX_ON_WHEN_IDLE=n` on the P4. The RCP runs with it (2026-10-20).
**Open:** does the router route well without it while BLE is idle? (Single-chip Matter devices with coexistence,
like the C6 donor, are Thread routers fine.) Check when it rejoins the network.
Step 2 code (2026-10-20): `components/br_ble` (removed in the cleanup of 2026-10-20, in git history) — NimBLE host on the P4 (`BT_CONTROLLER_DISABLED`, HCI over UART2,
TX GPIO22 → H2 "10", RX GPIO23 ← H2 "11", 460800 baud), a test advertiser "Thread-BR-test"
(`BR_BLE_TEST_ADVERTISER`), the state on the display's BT field. **Works (2026-10-20):** after the two wires were
in and a few rounds of probing (`BR_BLE_HCI_PROBE`: raw HCI Reset at several baud rates, the RX line level), the
H2 answered at 460800 (`04 10 01 01`, a hardware-error event from the probe's noise, then the host's reset went
through); NimBLE synced ("Controller answered over HCI", address 74:4d:bd:60:09:8c) and advertises
"Thread-BR-test" through the H2, next to the running Thread RCP. The earlier silence was the wiring/contact.
A diagnostic H2 build with its log on the board's "USB" port (`rcp_h2/sdkconfig.defaults.usblog`) did **not**
answer Spinel at all (cause unknown) — the P4 then reflashes it in a loop; don't use it without a plan to look
at why.

Step 3 spike (2026-10-20): `firmware/matter_br` (since the cleanup: `firmware/ebr`) — esp-matter (release/v1.6) on the P4: root node + Thread Border
Router endpoint, Thread Network Commissioning driver on endpoint 0, NimBLE host over HCI-UART to the H2, the H2 as
RCP, Ethernet via `protocol_examples_common`, border router init on the Ethernet IP. Needed: stub components for
`esp_hosted`/`esp_wifi_remote` (the Matter SDK pulls them in for every P4; `override_path`), `MBEDTLS_CMAC_C`,
the mdns component and a link dependency openthread → mdns. **Result:** boots, BLE advertises through the H2, no
commissionable mDNS on the LAN (good), the iPhone connects and sends PBKDFParamRequest — the 154-byte
PBKDFParamResponse never reaches it; after 15 s it gives up, the HCI link then times out and the P4 crashes
(`queue.c` assert). Same at 115200 baud as at 460800 (both sides now 115200). **Traps:** in the spike NimBLE starts
before the RCP update — garbage on the HCI line during an H2 update asserts NimBLE (`hci_h4.c:74`), the P4
restarts mid-update, the update never completes (USB of the H2 comes and goes); also a boot-time assert
`hci_h4.c:148` (bytes before the H4 parser is set up). Recovery: flash `firmware/` (updates the H2 before BLE).
**Next:** a calm test bench without Matter — P4 RCP auto-update off, the diagnostic H2 firmware flashed over the
H2's USB and read there, a connectable NimBLE GATT test with long notifications from `firmware/` (nRF Connect),
to find where large ACL packets get lost (UART RX on the H2? flow control? controller buffers?).

**2026-10-20, evening: plan A works — paired in Apple Home, dataset from the pairing.** The bench found the cause:
the H2's HCI UART (no-DMA mode) loses data when the host sends more than ~130 bytes in a row (its 128-byte FIFO):
indications up to 116 bytes passed, 120 failed even fragmented. Fix on the H2: `BT_LE_ACL_BUF_SIZE=100`,
`BT_LE_ACL_BUF_COUNT=1` — the host fragments to 100 and waits for Number of Completed Packets after each, so a
burst is at most 105 bytes (`rcp_h2/sdkconfig.defaults.esp32h2`). Further fixes in the spike:
- `USE_BLE_ONLY_FOR_COMMISSIONING=n` — shutting NimBLE down after pairing hangs the CHIP task forever (the UART
  transport's RX task never leaves its queue wait, `hal_uart: Waiting for uart task finish...`, watchdog).
- `esp_rcp_reset()` at every P4 start, before Thread and BLE: while the P4 resets, its HCI TX line floats, the H2's
  parser reads garbage ("parse rx data error") and may stay mute for a minute or for good.
- Own test pairing data (passcode 49582731, discriminator 0xA5C, verifier from `spake2p.py`): the default
  20202021/3840 is the C6 donor's too; the Home app refused at once.
- Don't keep nRF Connect connected while pairing — the router stops advertising during a BLE connection.
- The diagnostic H2 build (log on its USB) needs the RCP UART pins set (`OPENTHREAD_UART_PIN_MANUAL`, RX 23, TX 24):
  without a UART console nobody routes UART0 to its pins.

**Result:** the Home app paired it (uncertified accessory), Apple sent the Thread dataset over BLE, the router
joined the network (child → router), CASE over the LAN, CommissioningComplete, Apple's fabric (VendorId 0x1349) and
a second Apple fabric (0x1384) added, subscriptions from the iPhone and an Apple TV. **Open:** the boot-time assert
`hci_h4.c:148` on the first boot after flashing; how the device shows in Home; step 5 (merge with the display
firmware, the QR on the display, factory reset when removed from Home).

**Step 5, merge (2026-10-20, night):** `firmware/matter_br` (now `firmware/ebr`) includes `components/br_display` — display, keys,
radio/BLE state, and a **pairing screen** with the Matter QR (LVGL `lv_qrcode`) and the manual code while the router
has no Thread dataset (the codes come from `GetQRCode`/`GetManualPairingCode`, BLE rendezvous). BLE state on the
display follows CHIPoBLE events. **Last fabric removed → `esp_matter::factory_reset()`** (leaves the network,
erases the dataset, shows the QR again). esp-matter's device HAL is no longer in the build (its old `button`
component broke esp_lvgl_port). Shown in Home as "not supported", vendor "hobbyquaker", product "ebr".
Image 2.1 MB of 3.5 MB.

**Full cycle verified (2026-10-20, night):** QR on the display → paired in the Home app → status screen → removed
in the Home app → factory reset → QR again. Two fixes for it: **`mdns_init()`** (missing in the Matter firmware;
without it the border router's SRP advertising proxy and Matter's DNS-SD on Ethernet failed, and Apple could not
reach the router after a restart, so a removal only happened on Apple's side); and **the "home" fabric**: Apple
adds two fabrics (Apple Home, VendorId 0x1349, and a companion fabric, 0x1384) and removes only the first when the
accessory is deleted — so the reset triggers when the fabric that completed the first pairing is gone (index kept
in NVS namespace `ebr`; later multi-admin pairings do not replace it). NodeLabel is "ESP Border Router", but the Home
app names unsupported device types "Matter Accessory" regardless — rename it in the Home app if wanted.

1. **H2 combined firmware**: `ot_rcp` + BLE controller with HCI on UART1; the P4 border router keeps working
   (Spinel unchanged), and a NimBLE test on the P4 over UART sees the controller and advertises (visible in a
   phone's BLE scanner).
2. **NimBLE host on the P4 next to the border router** in our firmware (one more UART, memory).
3. **esp-matter on the P4**: a minimal Matter node (Ethernet up, Thread through the RCP, Thread Network
   Commissioning driver, BLE through the H2, commissionable over BLE only), first without our display code.
   Bigger app partitions (the flash is 32 MB).
4. **Pair in Apple Home** — the router factory-reset first (no dataset): does Apple accept the device type, send
   the dataset, finish over Thread? Which device type (Thread Border Router, or the Generic Switch of
   [virtual-remote.md](virtual-remote.md))?
5. Merge with our firmware: display shows the pairing QR on the No-dataset screen, "remove from Home" →
   factory reset, the role/fabric on the status screen.

Not needed any more for joining: the dataset donor stays as the manual way (hardware note, "Joining").

## Yes — Espressif ships the pieces

- **esp-matter `examples/thread_border_router`**: "a Matter Thread Border Router device using the ESP Matter data
  model" — the Matter *Thread Border Router* device type with the **Thread Border Router Management** cluster
  (Matter 1.4). Reference hardware: Espressif's border-router board (ESP32-S3 on Wi-Fi + ESP32-H2 RCP); the RCP
  is updated by the host through `esp_rcp_update`, as in esp-thread-br.
- *(dropped: relays)* esp-matter `examples/multiple_on_off_plugin_units` — several *On/Off Plug-in Unit*
  endpoints on one device. Matter devices may have any number of endpoints; the border router is endpoint 1,
  further endpoints (relays then, virtual switches in [virtual-remote.md](virtual-remote.md) now) 2…n.

## How the dataset gets in — and why this matters for Apple

In the example the Thread network is set **after commissioning, through the Matter cluster**:

```
chip-tool generalcommissioning arm-fail-safe 180 1 <node> 0
chip-tool threadborderroutermanagement set-active-dataset-request hex:<dataset tlvs> <node> 1
chip-tool generalcommissioning commissioning-complete <node> 0
```

A Matter controller has to send that command. **Whether Apple Home does** — i.e. configures a third-party Matter
border router with its own Thread network — was not found in this research (**not verified**; Apple has not
documented it). Two ways that do not depend on Apple:

- **she as the controller that sends it.** she's Matter controller (matter.js) can be commissioned into the same
  device as a second admin (multi-admin) and send `SetActiveDatasetRequest` with the dataset obtained some other
  way (a dataset donor, credential sharing). matter.js speaks arbitrary cluster commands; whether its
  cluster definitions include Thread Border Router Management is to check. This would be a she task, not one
  for this repository.
- Setting the dataset locally (console, credential sharing, the dataset QR) as in
  [hardware-setup.md](hardware-setup.md) — the Matter side then carries only the other endpoints.

The "dataset donor" trick (a Matter-over-Thread device receives the dataset during commissioning) does **not**
carry over: this device is reached over **Ethernet**, and a commissioner only configures the network a device is
being commissioned onto.

## Commissioning without Bluetooth *(superseded 2026-10-20 by the plan above)*

The ESP32-P4 has no radio, and the C6 runs only the 802.15.4 RCP — so no Bluetooth for pairing. Matter has
**on-network commissioning** for devices already on the IP network: the QR code's discovery bits say "on
network", and the controller finds the device by DNS-SD on the LAN. Apple Home commissions Ethernet devices this
way (Matter bridges on Ethernet are paired like that). Whether connectedhomeip's ESP32 platform runs the P4's
internal Ethernet as Matter's network interface is **not verified** — the example is Wi-Fi on an S3; Ethernet
support exists in the ESP32 platform layer, the P4 target is the open question.

## How Apple Home would show it (not verified on a device)

- *(dropped)* **Relays as On/Off Plug-in Units** appear as **outlets**; several endpoints of one device become one accessory
  with several outlets, which the Home app can show as one tile or as separate tiles ("Show as Separate Tiles").
  As *On/Off Light* endpoints they would be lights; as *On/Off Light Switch* … they are controllers, not targets —
  plug-in unit or light is the right type for a relay.
- **The border-router endpoint**: Apple Home shows device types it does not support as "not supported" or hides
  them; it is unlikely to offer anything for the Thread Border Router type. The outlets work regardless.
- Matter's multi-admin means the same endpoints can also be controlled from she directly.

## Relays on the P4 *(dropped 2026-10-18)*

- The P4's GPIOs are 3.3 V and weak: drive a **relay module whose input is 3.3 V-compatible** (transistor or
  optocoupler on board, separate 5 V coil supply) or a solid-state relay — never a bare relay coil from a GPIO.
- Free pins: the ones not taken in the hardware note (Ethernet, I2C, I2S, microSD, console, RCP link, display).
- Define the power-on state (Matter's *StartUpOnOff* attribute: off, on, previous) — relays must not flicker on boot.
- Mains switching belongs in a proper enclosure with certified relay modules; that part is to be
  built properly, not something to improvise on a breadboard.

## Effort and order

1. v1: the border router with display and keys, no Matter — `firmware/`.
2. Later (v2), if a v2 idea needs Matter on the device: a small esp-matter example on the P4 over Ethernet,
   commissioned into Apple Home on-network — this answers the open P4/Ethernet question with little at stake.
   Then merge with our firmware. The app slot (2 MB, 17 % free in v1) must grow; the flash has room.
3. The dataset through Matter from she (a she task) — or keep setting it locally.

## Sources

- esp-matter: [`examples/thread_border_router`](https://github.com/espressif/esp-matter/tree/main/examples/thread_border_router)
  (README: hardware, RCP update, the `set-active-dataset-request` sequence),
  [`examples/multiple_on_off_plugin_units`](https://github.com/espressif/esp-matter/tree/main/examples/multiple_on_off_plugin_units)
- connectedhomeip: [Thread Border Router Management server](https://gpl.boxmatrix.info/zzzz-none-000/packages/connectedhomeip/src/app/clusters/thread-border-router-management-server/thread-border-router-management-server.cpp),
  [ESP32 thread-br-app README](https://gpl.boxmatrix.info/zzzz-none-000/packages/connectedhomeip/examples/thread-br-app/esp32/README.md)
- SmartThings: [ThreadBorderRouterManagement cluster](https://developer.smartthings.com/docs/edge-device-drivers/matter/generated/clusters/ThreadBorderRouterManagement.html)
