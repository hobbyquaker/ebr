# Future (v2 or later): a virtual remote on the display

*Filed 2026-10-18 on the idea: click through a menu on our display with the four keys and switch
other Matter devices — a Thread light, but also Matter devices on Wi-Fi/Ethernet and bridged devices. Research
only, nothing built; v1 stays a border router with display and keys
([matter-device.md](matter-device.md), scope).*

## What the remote should do

A **Remote** page in the page ring of [display-ui.md](display-ui.md): a list of entries ("Kitchen light",
"Hall plug", "All off" …), PREV/NEXT move the cursor once inside, SELECT switches, BACK leaves. Nice to have:
the current state (on/off, brightness) next to each entry.

Our router is a good place for this: it sits on **both** networks — Thread through the C6 and the LAN through
Ethernet — so it reaches Thread devices directly and Wi-Fi/Ethernet devices over IP, without Apple's border
router in between.

## Four ways to build it

### A. The router as a Matter switch in Apple Home — Apple Home does the switching

The router becomes a Matter device with several **Generic Switch** endpoints (momentary buttons; Apple Home calls
them stateless programmable switches). Each remote entry is one button: SELECT sends its press event. In the
Home app every button gets an automation: "when *Remote 3* is pressed → turn the hall light on / toggle it".

- **Reaches everything Apple Home controls**: Matter on Thread, Wi-Fi and Ethernet, bridged devices, and plain
  HomeKit devices too — Apple Home does the work, our device only reports button presses.
- **No state on our display**: the router does not know whether the light is on; it can only say "sent".
  Names of the entries live on our device; Apple Home reportedly ignores Matter's label clusters for button
  names, so they are named twice (on the device and in the Home app).
- **Automations run on the home hub** — the Apple TV is there. (For [standalone-mode.md](standalone-mode.md)
  without a hub this option falls away.)
- **Reports of quirks**: Apple's developer forum has a 12-button Matter switch whose button order in the Home
  app did not match the device and changed after factory resets; an ST forum post has a button that stopped
  triggering automations after a restart. Single/double/long press per button are vendor claims, unverified for
  Apple Home.
- **Effort: medium.** esp-matter on the P4 over Ethernet with on-network commissioning (the open point of
  [matter-device.md](matter-device.md)), plus Generic Switch endpoints and the Remote page. Espressif's Arduino
  docs show a Generic Switch endpoint triggering Apple Home automations.

### B. The router as its own Matter controller — it switches the devices itself

esp-matter's **controller** (commissioner) runs on the device and builds its **own fabric**. Per Espressif's
docs it can commission (`onnetwork`, by setup code, BLE variants only on the ESP32-S3), **invoke** commands,
**read/write** attributes, **subscribe** to attributes and events, and manage **groups**.

- **Adding a device**: multi-admin. In Apple Home, the device's settings → "Turn On Pairing Mode" gives a setup
  code; our router commissions the device into its fabric on-network (the device is already on Thread or the
  LAN). Entering an 11-digit code with four keys is tedious: better through the console, a (then authenticated)
  web page, or she.
- **Live state**: subscriptions keep on/off and brightness current on the display — the "real remote".
- **Reaches**: Matter devices on Thread (through our own border router — independent of Apple's) and on
  Wi-Fi/Ethernet, and **bridged devices** (a Matter bridge is one node with many endpoints; each endpoint is an
  entry). **Not** plain HomeKit devices: Apple Home is no Matter bridge.
- **Groups**: one group command switches several lights at once ("All off"), as a single multicast.
- **Limits**: each device needs a free fabric slot (Matter devices must offer at least 5: Apple, Google, she,
  ours …). The controller must check device attestation against the PAA trust store (esp-matter has an
  attestation trust store option, the DCL's PAA certificates must be on the device). Espressif's example root
  certificate is "for testing only and must not be used in production" — for a private device an own CA in
  NVS is fine, for a published product it is a real piece of work.
- **Effort: high.** Commissioner, node storage, attestation, device/endpoint discovery (Descriptor cluster), the
  Remote UI with a cursor and state, and a bigger app slot: esp-matter's controller plus the border router will
  not fit the 2 MB slot of v1 (the flash has room). A user report has the esp-matter commissioner crashing
  with some third-party devices (on an S3 with BLE) — test with the actual devices.

### C. Through she (or Home Assistant): the display as a front-end

she already controls these devices (its matter.js controller has them by multi-admin). The Remote page would
fetch a list of entries from she and send "toggle" over she's API (REST or MQTT), with state from she.

- **Small on the firmware side**: an HTTP or MQTT client and a list on the display; no Matter on the router.
- **Reaches whatever she reaches**, with state.
- **Depends on she running**; and it is work for she's roadmap (an endpoint for such a remote), not
  this repository's. For other users Home Assistant's REST/WebSocket API would be the same idea.
- **Effort: low here, the rest in she.**

### D. Bindings — the router talks to the devices directly, configured by someone else

The router as an *On/Off Light Switch* with a Binding cluster: it sends On/Off commands straight to the target
devices, as wall switches do. Someone must write the bindings into our device **and** the matching ACL entries
into every target — only an admin of that fabric can. Apple Home offers no binding setup (no UI found, **not
verified**); she could do it as a second admin. Fragile and hard to explain — **not recommended**.

## Comparison

| | A: Matter switch → Apple automations | B: own controller | C: via she | D: bindings |
| --- | --- | --- | --- | --- |
| Thread Matter devices | yes | yes | yes | yes |
| Wi-Fi/Ethernet Matter | yes | yes | yes | yes |
| Bridged devices | yes | yes (Matter bridges) | yes | depends |
| Plain HomeKit devices | **yes** | no | if she has them | no |
| State on our display | no | **yes** | yes | no |
| Needs | Apple home hub | free fabric slot per device | she running | a fabric admin |
| Firmware effort | medium | high | low (+ she work) | medium |

## Recommendation (agent, 2026-10-18)

1. **A first** — the most useful per effort: every device in Apple Home, the automations already
   in use, and the Matter work it needs (esp-matter on the P4 over Ethernet) is the same first step every Matter
   idea here needs.
2. **B** only if the state on the display turns out to matter — it makes the router an independent controller,
   a much bigger job.
3. **C** as a quick path for a house with she, if she gets the endpoint anyway.

Watch: Matter 1.4's *Joint Fabric* (sharing devices between ecosystems without commissioning each one again) —
if Apple adopts it, B's per-device multi-admin step could go away (**not verified**).

## Sources

- Espressif: [esp-matter Matter Controller](https://docs.espressif.com/projects/esp-matter/en/latest/esp32/controller.html)
  (features, pairing methods, test root certificate), [Arduino Matter Generic Switch endpoint](https://docs.espressif.com/projects/arduino-esp32/en/latest/matter/ep_generic_switch.html)
- Apple developer forum: [Matter switch buttons vs. the Home app](https://developer.apple.com/forums/thread/788551)
- [ST community: Generic Switch button stops after restart](https://community.st.com/t5/stm32-mcus-wireless/generic-switch-app-after-restarting-the-device-button-2-cannot/td-p/755141)
- [esp32.com: ESP32 border router / commissioner crash with Aqara and IKEA devices](https://esp32.com/viewtopic.php?p=154825)
