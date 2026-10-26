# Thread border router: hardware setup (ESP32-P4-ETH + ESP32-H2 + ST7789 display)

*Setup note, started 2026-10-17; the wiring below is the one running since 2026-10-20.*

## What goes where

| Part | Role | Notes |
| --- | --- | --- |
| **Waveshare ESP32-P4-ETH** (Amazon B0FY375LNH) | ebr: Matter device + OpenThread border router (Ethernet to the LAN) + the display | ESP32-P4NRW32, 32 MB PSRAM, 32 MB flash, 100 Mbit Ethernet (IP101GRI PHY), USB-C with a CH343P for flashing and the console, 2×20 header. The P4 has **no radio** |
| **ESP32-H2 board** (ESP32-H2-MINI-1 V1.2 devkit) | the radio for **Thread and Bluetooth**: `firmware/rcp_h2` (ot_rcp + BLE controller), flashed by the P4 | two USB-C: "UART" through a bridge chip to UART0 (= the Spinel line — not while wired), "USB" the H2's own USB (diagnostics) |
| **GMT020-02 v1.3** | status display | 2.0" TFT, **ST7789V**, 240×320, SPI, 8 pins **with CS** |
| 4 tactile buttons | BACK, PREV, NEXT, SELECT under the display | to GND, internal pull-ups |
| MuseLab nanoESP32-C6 v1.0 | spare; the dataset donor of 2026-10-20 | first planned as the radio |

The first plan was Espressif's documented default (esp-thread-br's `basic_thread_border_router`, "P4 + C6 Thread
radio"); on 2026-10-20 the wired radio turned out to be the H2 and stayed — and since ebr pairs over Bluetooth, the
H2 also carries the BLE controller. Whether the Waveshare board has an on-board C6 (the Amazon title says Wi-Fi 6)
was never checked; nothing needs it.

## Wiring

### The header (P1), from Waveshare's schematic (read 2026-10-20)

A Pico-style 2×20 header. From the schematic (`ESP32-P4-ETH-datasheet.pdf`, block "Interface"); every header GPIO
goes only to the P4 and the header — nothing else on the board uses them. Planned use in the right column.

| Pin | Signal | Planned | | Pin | Signal | Planned |
| --- | --- | --- | --- | --- | --- | --- |
| 1 | GPIO54 | | | 21 | GPIO48 | display DC |
| 2 | GPIO19 | | | 22 | GPIO47 | display RES |
| 3 | GND | button GND | | 23 | GND | display GND |
| 4 | GPIO18 | button BACK | | 24 | GPIO46 | display power switch (gate / base) |
| 5 | GPIO17 | button PREV | | 25 | GPIO33 | display SDA |
| 6 | GPIO16 | button NEXT | | 26 | GPIO32 | display SCL |
| 7 | GPIO15 | button SELECT | | 27 | GPIO27 | display CS |
| 8 | GND | button GND | | 28 | GND | |
| 9 | GPIO14 | | | 29 | GPIO26 | |
| 10 | GPIO6 | | | 30 | ESP_EN (reset of the P4) | — |
| 11 | GPIO5 | H2 RX (Spinel) | | 31 | GPIO23 | H2 "11" (HCI, H2 → P4) |
| 12 | GPIO4 | H2 TX (Spinel) | | 32 | GPIO22 | H2 "10" (HCI, P4 → H2) |
| 13 | GND | H2 GND | | 33 | GND | |
| 14 | GPIO3 | | | 34 | GPIO21 | H2 "9" (BOOT) |
| 15 | GPIO2 | | | 35 | GPIO20 | H2 RST |
| 16 | GPIO8 (I2C SCL) | — | | 36 | 3V3 | display VCC |
| 17 | GPIO7 (I2C SDA) | — | | 37 | 3V3_EN | — |
| 18 | GND | | | 38 | GND | |
| 19 | GPIO24 (USB D−) | — | | 39 | 5V | H2 5V |
| 20 | GPIO25 (USB D+) | — | | 40 | 5V | |

Free afterwards: GPIO2, 3, 6, 14, 19, 26, 54 (GPIO2–5 double as the P4's JTAG pins, unused with USB
debugging).

### P4 ↔ H2 (the radio link, since 2026-10-20)

The **ESP32-H2 board** (ESP32-H2-MINI-1 V1.2, pins `G TX RX 10 11 25 12 8 22 G 9 G 27 26 G`
/ `3V3 RST C 1 2 3 13/N 14/N 4 5 NC VBAT G 5V G`) is the radio; the P4 flashes it with
`ot_rcp` itself (verified 2026-10-20).

| H2 board pin | P4 header pin | P4 GPIO | Purpose |
| --- | --- | --- | --- |
| TX (GPIO24) | 12 | GPIO4 | H2 sends → P4 receives |
| RX (GPIO23) | 11 | GPIO5 | P4 sends → H2 receives |
| RST | 35 | GPIO20 | P4 resets the H2 |
| 9 (boot strap) | 34 | GPIO21 | P4 puts the H2 into download mode for RCP updates |
| 10 | 32 | GPIO22 | Bluetooth HCI: P4 sends → H2 receives (UART1 RX) |
| 11 | 31 | GPIO23 | Bluetooth HCI: H2 sends → P4 receives (UART1 TX) |
| G | 13 | — | ground |
| 5V | 39 | — | the H2 board is powered by the P4 |

Spinel at 460800 baud (P4 UART1), HCI at 115200 (P4 UART2). Details and the reasons behind the settings (ACL buffer
100 × 1, the H2 reset at every start, no rx-on-when-idle) in [firmware/README.md](../firmware/README.md).

### P4 ↔ display (GMT020-02-7P, ST7789V)

The module at hand has a CS pin (2026-10-20) and **no BLK pin** (2026-10-24): `GND VCC SCL SDA RES DC CS`
(order on the silkscreen may differ); its backlight hangs on VCC. `SCL`/`SDA` are the SPI clock and data
(not I2C). CS goes to a GPIO (the driver selects the display per transfer, SPI mode 0); tied to GND instead it
saves a pin but usually needs SPI mode 3 (`BR_DISPLAY_PIN_CS` = −1).

| Display pin | ESP32-P4-ETH | Note |
| --- | --- | --- |
| GND | GND (pin 23) | |
| VCC | **3V3** (pin 36) **through the high-side switch** below | the ST7789 is a 3.3 V part; most such modules have no regulator — not 5 V |
| SCL | GPIO32 (pin 26) | SPI clock |
| SDA | GPIO33 (pin 25) | SPI MOSI |
| RES | GPIO47 (pin 22) | reset |
| DC | GPIO48 (pin 21) | data/command |
| CS | GPIO27 (pin 27) | chip select (`BR_DISPLAY_PIN_CS`) |
| — | GPIO46 (pin 24) → gate (or base) of the high-side switch | switches the module's VCC; low = on (`BR_DISPLAY_PIN_PWR`) |
| — | buttons BACK GPIO18 (pin 4), PREV GPIO17 (pin 5), NEXT GPIO16 (pin 6), SELECT GPIO15 (pin 7), each ↔ GND (pin 3 or 8) | internal pull-ups, no resistors; see "Buttons" below |

#### Display off by default (2026-10-18)

The display is **dark by default**: on at boot and on any button press, off again after **5 minutes**
(`BR_DISPLAY_ON_SECONDS` = 300); every press restarts the 5 minutes. The press that wakes the display does
nothing else.

The module has **no BLK pin** (2026-10-24): its backlight runs whenever VCC is there, so "off" means **cutting the
module's VCC** with a high-side switch between the header's 3V3 and the module's VCC, driven by GPIO46. The firmware
does the rest (`BR_DISPLAY_PIN_PWR` = 46, `BR_DISPLAY_PWR_ACTIVE_LOW`, 2026-10-24): before switching off it drives
SCL, SDA, CS, DC and RES **low** — a high line (CS idles high) would otherwise feed the module through its protection
diodes and let it glow — and after switching on it resets and sets up the ST7789 again and redraws the screen.
Off, the module draws nothing.

Measure the module's current once (multimeter in mA between 3V3 and VCC, backlight on): expect roughly 20–80 mA,
nearly all of it backlight. Every part below handles that with room to spare.

**The switch: a logic-level P-channel MOSFET** (best — no voltage loss). It must be fully on at a gate–source voltage
of **−2.5 V** (its datasheet gives R<sub>DS(on)</sub> at V<sub>GS</sub> = −2.5 V); 3.3 V of gate drive is all the
P4 has. Common ones:

| Part | Package | Note |
| --- | --- | --- |
| **AO3401A** (marking "A19T") | SOT-23 | the usual one in SMD kits; −30 V, ~0.06 Ω at −2.5 V |
| **Si2301** (CDS/DS, marking "A1SHB") | SOT-23 | −20 V, ~0.15 Ω at −2.5 V |
| **IRLML6402** | SOT-23 | −20 V, ~0.14 Ω at −2.5 V |
| **DMG2305UX** | SOT-23 | −20 V, ~0.1 Ω at −2.5 V |
| **NDP6020P** | TO-220 | through-hole, logic-level, −20 V |

SOT-23 parts: solder onto a SOT-23 adapter board or straight onto three wires. All of these have the same SOT-23
pinout: 1 = gate, 2 = source, 3 = drain (check the datasheet of the one you take).

**Not suitable** — they are not logic-level, barely conduct at 3.3 V: IRF9540(N), IRF9Z34N, IRF4905, FQP27P06,
BS250. Also no **N-MOSFET or NPN in the ground line** (2N7000, AO3400, BC547): with its GND cut the module would
power itself through the signal lines.

```
 3V3 (pin 36) ───┬───────────────┐
                 │               │ S
              100 kΩ          ┌──┴──┐
                 │          G │  P  │   AO3401A / Si2301 / IRLML6402 / DMG2305UX / NDP6020P
                 ├────────────┤ FET │
                 │            └──┬──┘
               1 kΩ              │ D
                 │               │
 GPIO46 (pin 24) ┘               └──── VCC (display)
```

- **100 kΩ gate–source pull-up**: keeps the switch **off** while the P4 is in reset or being flashed (GPIO46
  floating) — the display stays dark until the firmware switches it on.
- **1 kΩ** in the gate line: limits the gate charging current; anything from 100 Ω to 1 kΩ is fine.
- GPIO46 **low = display powered**.

**Without a suitable MOSFET: a PNP transistor**, same position. **BC327** (−25/−40; 800 mA) is the best of the
common ones, **BC557 / BC558 / BC307, 2N4403, S8550, 2N3906** work too (100 mA or more; BC337, BC548 and
2N4401 are NPN — not usable). Base resistor 1 kΩ (≈ 2.6 mA base current, enough to saturate it
at up to ~80 mA), 10 kΩ base–emitter pull-up; emitter at 3V3, collector to the display's VCC. The module then gets
~3.1–3.2 V instead of 3.3 V (V<sub>CE(sat)</sub> 0.1–0.2 V), which the ST7789 does not mind. Pinouts differ:
BC327/BC557/BC558/BC307 are C-B-E, 2N3906, 2N4403 and S8550 E-B-C (flat side facing you) — check the
datasheet.

```
 3V3 (pin 36) ───┬───────────────┐
                 │               │ E
               10 kΩ          ┌──┴──┐
                 │          B │ PNP │   BC557 / BC327 / 2N4403 / …   
                 ├────────────┤     │
                 │            └──┬──┘
               1 kΩ              │ C
                 │               │
 GPIO46 (pin 24) ┘               └──── VCC (display)
```

Not changed by either switch: GND, SCL, SDA, RES, DC and CS stay wired as in the table above.

#### Buttons (2026-10-18: four, "select, back, prev, next", under the display, evenly spaced)

Mounted in a row under the display, one under each quarter of its width (80 px of the 320 px screen, about
10 mm apart on the 2.0" panel's ~41 mm active width), left to right **BACK, PREV, NEXT, SELECT**; the bottom bar
of every screen labels them. Screens and what each button does: [display-ui.md](display-ui.md).

| Button | Kconfig | Does (firmware 2026-10-18) |
| --- | --- | --- |
| SELECT | `BR_DISPLAY_PIN_BTN_SELECT` | the screen's action — reserved: dataset QR, credential-sharing passcode, Matter pairing window |
| BACK | `BR_DISPLAY_PIN_BTN_BACK` | back to the status screen (later: close a QR / leave an action) |
| PREV | `BR_DISPLAY_PIN_BTN_PREV` | previous screen |
| NEXT | `BR_DISPLAY_PIN_BTN_NEXT` | next screen |

Each a momentary push button (the usual 6×6 mm tactile switch) between its GPIO and **GND**; the P4's internal
pull-ups are enough, and the firmware polls every 50 ms, which debounces. Not the BOOT key (GPIO35 is an Ethernet
pin on this board). Any button that is left at −1 is simply absent.

**Verified 2026-10-20:** all four buttons reach their GPIOs (NEXT needed a wiring fix);
`BR_DISPLAY_LOG_BUTTON_LEVELS` logs the raw levels for such checks.

**Pins.** Display (6 with CS), RCP link (4) and buttons (4): **14 GPIOs** — the header has 23 usable ones, so
they fit (see the header table). The fallbacks below are only needed if pins are wanted for something else:

1. Tie the display's **RES to 3V3** and set `BR_DISPLAY_PIN_RST` = −1 (the driver resets the ST7789 by command)
   — frees GPIO47.
2. **All four buttons on one ADC pin** with a resistor ladder (each button pulls a divider to a different voltage):
   one GPIO instead of four; needs an ADC-capable header pin *(check which — the P4's ADC channels sit on
   GPIO16–23 and 49–54 as far as known)* and a small firmware change (not written yet).
3. An I2C port expander (e.g. PCF8574) on the board's I2C bus (GPIO7/8) — no extra GPIO at all, if one is in the
   lab.

ESP-IDF has the ST7789 driver built in (`esp_lcd_new_panel_st7789`); LVGL is optional. The display belongs on the
P4 — the H2 only runs the radio firmware. 240×320 is roomier than the 160×128 module the first note assumed:
the dataset QR code (version 8–9) gets 4 px per module.

## Software on the workstation (WSL)

- **usbipd-win** on Windows passes the boards into WSL (installed 2026-10-18; `bind` once per device in an admin
  terminal, `attach --wsl --busid <id>` after every replug). The CH343 and the H2's native
  USB appear as `/dev/ttyACM*`; the WSL user is in `dialout`.
- **ESP-IDF v5.5.6** (`~/esp/esp-idf`, `./install.sh esp32p4,esp32c6,esp32h2`) and **esp-matter release/v1.6**
  (`~/esp/esp-matter`, its submodules for esp32 only, `./install.sh`). Debian packages: `git wget flex bison gperf
  python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0`.
- ESP-IDF 5.5 builds the P4 for **chip revision ≥ v3.1** by default; our P4 is v3.2. Use ESP-IDF's esptool
  (`python -m esptool`), not the system 4.7.0, which loses the serial stream with this chip.

## Build and flash

See [firmware/README.md](../firmware/README.md): build `firmware/rcp_h2` (H2), then `firmware/ebr` (P4), flash the P4
over its CH343 USB-C; on boot the P4 resets the H2 and flashes it when its firmware differs — the H2 needs no
flashing of its own. First flash with `erase-flash`.

History: the first firmware (2026-10-18) was esp-thread-br's example with our start logic, because the example's
auto start creates a **random network** when no dataset is stored, and its default PHY reset GPIO40 is a microSD pin
on this board; it also needed a patch to build its web server on a P4 without Wi-Fi. All gone with ebr (in git
history).

## Joining the Apple TV's Thread network

**Pair ebr in the Home app** from the QR on its display: Apple hands it the dataset over Bluetooth, it joins as a
child and becomes a router (2026-10-20). Removing it in the Home app factory-resets it.

The manual way (used once on 2026-10-20, before ebr was a Matter device): a dataset donor — any Matter-over-Thread
device whose console can print the dataset, here the C6 with esp-matter's `light` example — and a small script
that carried the dataset to the router's console without printing it. On a plain OpenThread console the steps are `dataset set active <tlvs>`, `ifconfig up`, `thread start`; `state` must become
`child` or `router` — `leader` alone means a new partition (wrong dataset or out of reach: stop it).

## Open points

- The display power switch (2026-10-24): firmware ready, not yet soldered or tested on the board.
- Physical layout: enclosure, button cap spacing (~10 mm), cable lengths.

## Sources

- Espressif: [esp-thread-br](https://github.com/espressif/esp-thread-br) — `examples/basic_thread_border_router/README_esp32p4.md`
  (Espressif's P4 + C6 default, ESP-IDF v5.4.2, build steps), `README_standalone_RCP.md`, `sdkconfig.defaults.esp32p4`,
  `components/esp_rcp_update/Kconfig` (reset/boot pins), `examples/common/thread_border_router/Kconfig.projbuild`
  (RCP UART pins), `main/esp_ot_config.h`; ESP-IDF [`ot_rcp`](https://github.com/espressif/esp-idf/tree/v5.4.2/examples/openthread/ot_rcp)
  (UART0, 460800 baud); [ESP-Hosted OpenThread border router example](https://components.espressif.com/components/espressif/esp_hosted/versions/3.0.1/examples/openthread/border_router/esp_host)
- Waveshare: [ESP32-P4-ETH wiki](https://www.waveshare.com/wiki/ESP32-P4-ETH); pin assignments of the board family
  from the [espp/esp32-p4-wifi6-poe-eth BSP](https://components.espressif.com/components/espp/esp32-p4-wifi6-poe-eth/versions/1.3.8/readme)
  (states the Ethernet pinout is identical to the ESP32-P4-ETH)
- MuseLab: [nanoESP32-C6](https://github.com/wuxx/nanoESP32-C6) (two USB-C: CH343 and native USB)
- Display: [GoldenMorning ST7789V 2.0" 240×320 listing](https://st.robu.in/product/goldenmorning-st7789v-7p-240x320-spi-2-0-inch-tft-display-module)
  (GMT020-02, 7 pins, ST7789V)
- [usbipd-win](https://github.com/dorssel/usbipd-win)
