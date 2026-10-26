# Thread 1.4 credential sharing (ePSKc) on our border router

*Plan, 2026-10-18: "Thread 1.4 credential sharing sounds great, i want that" (after
[prior-art.md](prior-art.md)). Nothing built; the hardware has not arrived.*

## What it gives us

Thread 1.4 lets a border router share its network's credentials with an external commissioner without anyone
copying a network key by hand: the border router shows a **one-time passcode** (on its screen or in an app), the
commissioner derives the **ePSKc** (ephemeral pre-shared key for the commissioner) from it, finds the router by mDNS
(`_meshcop-e._udp`), opens a DTLS session (EC-JPAKE) and reads the active dataset. The passcode is valid for one
session and a few minutes.

Two directions, and only one is available today:

| Direction | Status |
| --- | --- |
| **Apple TV → us** (fetch Apple's dataset with a code shown by Apple) | **not possible yet**: the Apple TV advertises Thread 1.4 since tvOS 26, but no sharing control has appeared in tvOS/iOS (as of the June 2026 betas). If Apple adds it, this replaces every other way of getting the dataset in [thread-research.md](thread-research.md). Watch tvOS releases. |
| **Our border router → anyone** (we show the code, a commissioner fetches the dataset) | **possible**: esp-thread-br implements it; Espressif's M5Stack border router shows the code and its QR on its screen |

The second direction makes our border router the **standard entry point to the home's Thread network**: once it
holds Apple's dataset (from the donor device, the HA iOS app or a dataset QR — once), any Thread 1.4 commissioner
can get the network from it with a code on our display — Google Home on Android, SmartThings, Home Assistant
(**not verified** which HA version supports it), a future she feature, ESP RainMaker. Our dataset QR screen
(network key in plain text in a QR code) becomes the fallback; the passcode screen is the safer default, because
the passcode is short-lived and useless after the session.

## How Espressif does it (reference to copy)

- **esp-thread-br `examples/m5stack_thread_border_router`** (needs **ESP-IDF v5.5.5**) with the shared UI code in
  `examples/common/thread_border_router_m5stack/`; the passcode page is
  `src/br_m5stack_epskc_page.c`:
  - OpenThread's border-agent API: `otBorderAgentEphemeralKeyStart()` / `otBorderAgentEphemeralKeyStop()` (the
    stop is called when the user leaves the page; the session also ends on its own after the lifetime);
  - the passcode as text and as a QR code: Espressif's `qrcode` component (`esp_qrcode_generate`), drawn into an
    LVGL image at scale 3;
  - the web GUI's REST API can start and stop it too (`esp_br_web_epskc_set_active_tap`), so a web page or
    another program can trigger "share now".
  - The menuconfig of the example sets "Lifetime and port of the Ephemeral Key".
- The OpenThread CLI has the same as `ba ephemeralkey …` commands — useful on the console while testing (exact
  syntax to check in the OpenThread version esp-idf 5.5 ships).
- Espressif's blog post on Thread credential sharing describes the flow with SmartThings as the commissioner.

## What changes in our plan

1. **ESP-IDF 5.5.x instead of 5.4.2.** The M5Stack example needs v5.5.5; that also covers the newer ESP32-P4 chip
   revision v3, which 5.4 does not support. The hardware note is updated accordingly; check that
   esp-thread-br's `basic_thread_border_router` P4 example builds with 5.5.x (its README recommended 5.4.2).
2. **A "Share network" screen** on the ST7789: the passcode in large digits, its QR code, a countdown, a
   "B · stop" hint; started by a button (or from the web page). Drawn as screen A6 on the design canvas.
3. **Thread 1.4 on the border router.** The ePSKc feature is part of OpenThread's border agent as built for
   esp-thread-br 1.4-capable releases; take the options from the M5Stack example's `sdkconfig.defaults` and the
   `components/` it uses rather than guessing names.
4. **Security:** the passcode only appears on a button press, the session lifetime stays short (the example's
   default), the REST trigger needs the same token as the dataset endpoint, and every started session is logged.

## A commissioner of our own (later, optional)

To test without a phone ecosystem, a small commissioner on the workstation: OpenThread's `ot-commissioner` (check
ePSKc support in its current release), or Swift [ThreadCommissionerKit](https://github.com/phil-margetson/ThreadCommissionerKit)
on a Mac. A Node.js one for she would need EC-JPAKE over DTLS, which OpenSSL does not offer (mbedTLS does) — a
she task of its own, not part of this repository.

## Sources

- Espressif: [Thread credential sharing (blog, 2026-01)](https://developer.espressif.com/blog/2026/01/thread-credential-sharing/);
  [esp-thread-br](https://github.com/espressif/esp-thread-br) — `examples/m5stack_thread_border_router/README.md`
  (ESP-IDF v5.5.5, ePSKc on the touchscreen), `examples/m5stack_thread_border_router/sdkconfig.defaults`,
  `examples/common/thread_border_router_m5stack/src/br_m5stack_epskc_page.c`
- Apple status: [Matter Alpha (tvOS 26 beta)](https://www.matteralpha.com/news/apple-tv-upgrades-to-thread-1-4-with-tvos-26-beta),
  [10jqka report (June 2026)](https://stock.10jqka.com.cn/20260611/c677376492.shtml)
- Google: [border router device guide](https://developers.home.google.com/apis/ios/device/border-router)
