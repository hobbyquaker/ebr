# Similar projects (prior art)

*Search of 2026-10-17 on GitHub and the web, on the question: are there border routers or Thread/Matter
devices with a colour TFT already? Star counts and dates as of that day.*

## Border routers built on ESP32

| Project | What it is | Useful for us |
| --- | --- | --- |
| [espressif/esp-thread-br](https://github.com/espressif/esp-thread-br) ★236 | Espressif's border-router SDK; the base of the hardware note | the P4 + C6 example, RCP update, web GUI, REST API |
| esp-thread-br `examples/m5stack_thread_border_router` | border router on the **M5Stack CoreS3** (ESP32-S3 with a 2" 320×240 IPS **touchscreen**), sold as "M5Stack Thread Border Router"; the screen generates the **Thread 1.4 ephemeral key (ePSKc)** for credential sharing; needs ESP-IDF v5.5.5 | **the closest thing to our idea** — a border router with a colour screen from Espressif; its UI code is the reference for drawing on the display next to the BR stack |
| [andylee830914/esp-thread-br-probe](https://github.com/andylee830914/esp-thread-br-probe) | built on esp-matter's `thread_border_router`: Matter-managed border router (Thread Border Router Management cluster) **plus a fake Matter-over-Thread On/Off Light**, W5500 Ethernet, Espressif's web UI, a topology/telemetry REST API, RCP auto-update; target the ESP Thread BR board (S3 + H2) | **the closest to the Matter-device note** — border router and Matter accessory in one firmware, as a working example |
| [mcuw/esp32-thread-br](https://github.com/mcuw/esp32-thread-br) | border router on a single **ESP32-S31** (ESP-IDF master/preview) with **Gigabit Ethernet**, REST API with setup-token auth (dataset, neighbours, commissioner, OTA), Astro/Qwik web front end, OTA from GitHub releases | the token-protected REST API (dataset, neighbours) is the shape our web page should have |
| [tostmann/THBR](https://github.com/tostmann/THBR) | the whole border router on one **ESP32-C6 USB stick**, the host sees it as a network interface over USB; also lends its Bluetooth to the Matter server; Home Assistant add-on or Docker | an alternative architecture (no Spinel link to a host process) |
| [mozolin/esp-thread-br](https://github.com/mozolin/esp-thread-br) | esp-thread-br 1.2 with a reworked web page (themes, password, OTA page, mDNS names) | web UI ideas |
| [make2explore/Open-Thread-Border-Router-On-ESP32](https://github.com/make2explore/Open-Thread-Border-Router-On-ESP32) | tutorial with videos for a two-chip ESP32 OTBR | beginner reference |
| [openthread/ot-br-posix](https://github.com/openthread/ot-br-posix) ★577 | the Linux OTBR (option C on a Pi) | — |

**Not found:** a border router or a Thread/Matter device that shows the **Matter pairing QR code** or the
**dataset as a QR code** on a colour TFT, and none with relays. The M5Stack example is the nearest (a screen,
credential sharing); esp-thread-br-probe the nearest for "border router + Matter accessory". The combination
planned here — P4 on Ethernet, C6 RCP, ST7789 status/QR screens, four keys (relay outlets dropped
2026-10-18) — seems new.

## Thread devices with a display (hardware)

Several ESP32-C6 boards come with a small colour LCD (e.g. Waveshare's ESP32-C6-LCD and -Touch-LCD series), and
ESPHome's `openthread` component runs on the C6 — so "a Thread router with a status screen" is an ESPHome YAML away
on such a board; not checked which projects do it.

## Thread network management outside Home Assistant

*Added on the follow-up: is Home Assistant's Thread management available as a standalone project?* Home Assistant's
part is two integrations: **`otbr`** (talks to an OpenThread border router through the Python library
[python-otbr-api](https://github.com/home-assistant-libs/python-otbr-api), its REST client) and **`thread`** (the
store of known datasets, the "preferred network", the credential exchange with the companion apps, the
visualisation). The pieces exist standalone as follows — **the dataset store and phone sync do not**:

| Piece | Standalone | Notes |
| --- | --- | --- |
| Border router web UI | **ot-br-posix's own web GUI** (`src/web`, `otbr-web`): status, form/join a network, topology; **esp-thread-br's web GUI**: discovery, forming, status, topology | comes with the border router; this is what our P4 would serve |
| REST API | ot-br-posix `src/rest`: node state, active/pending dataset, and a JSON:API for devices, diagnostics and commissioning (`/api/devices` …); esp-thread-br has a REST API too | what HA's `otbr` integration uses |
| REST client library | [python-otbr-api](https://github.com/home-assistant-libs/python-otbr-api) (HA's, usable on its own) | Python; read/set datasets, state, channel |
| Topology view | [fpb/Thread-Network-Visualizer](https://github.com/fpb/Thread-Network-Visualizer) — a static web page (vanilla JS) that crawls an OTBR's REST API hop by hop, or imports `ot-ctl meshdiag topology` output; [cputoaster/matter_graph](https://github.com/cputoaster/matter_graph) — a graph from python-matter-server's data (neighbour and route tables, roles, RSSI/LQI), optionally names from HA | the first works against our border router directly |
| Matter controller with Thread | [python-matter-server](https://github.com/home-assistant-libs/python-matter-server) runs without HA (a WebSocket server) and commissions Thread devices with a dataset you give it | she has its own controller (matter.js) |
| External commissioner | OpenThread's `ot-commissioner` (CLI) | joining devices, reading datasets with the PSKc |
| **Dataset store, preferred network, iOS/Android credential sync** | **not found standalone** | the part only HA offers; a natural she feature (store datasets as secrets, show networks and border routers, hand a dataset to an OTBR) |

So for our border router: its own web GUI and REST API cover status, dataset and topology; the visualiser above can
point at it unchanged; what HA adds on top — keeping several networks' datasets and pushing the right one to each
border router — would be the she side.

## Thread 1.4 credential sharing (ePSKc) — a fourth way to the dataset, later

Thread 1.4 lets a border router hand its dataset to an external commissioner after the user reads an **ephemeral
key (ePSKc)** off the border router's screen or app: mDNS service `_meshcop-e._udp`, EC-JPAKE, DTLS, then the
commissioner reads the active dataset. Implementations: Espressif's M5Stack example (border-router side, with the
key on the screen), [phil-margetson/ThreadCommissionerKit](https://github.com/phil-margetson/ThreadCommissionerKit)
(Swift, commissioner side — reads a dataset given the code; no Apple entitlement involved). Google's TV Streamer
offers "share Thread credentials" with a QR code and a code (Google's developer guide describes the ePSKc
flow). **Apple:** the Apple TV advertises Thread 1.4 in its mDNS records since tvOS 26, but no credential-sharing
control in iOS/tvOS has been seen (as of the June 2026 betas, per a news report) — so not usable with the Apple TV
yet. Worth watching: once Apple offers it, an own commissioner (a small Python/Go tool, or she) gets the dataset
without any app or donor device. And our own border router could offer ePSKc itself (esp-thread-br has it), so
other ecosystems can join *our* network the standard way.

Sources: [Espressif blog: Thread credential sharing](https://developer.espressif.com/blog/2026/01/thread-credential-sharing/),
[Matter Alpha: Apple TV Thread 1.4 in tvOS 26 beta](https://www.matteralpha.com/news/apple-tv-upgrades-to-thread-1-4-with-tvos-26-beta),
[10jqka report (June 2026)](https://stock.10jqka.com.cn/20260611/c677376492.shtml),
[TechGenyz on Google TV Streamer](https://techgenyz.com/?p=331887),
[Google: border router device guide](https://developers.home.google.com/apis/ios/device/border-router),
[fixoryhq guide](https://fixoryhq.com/?p=1312).
