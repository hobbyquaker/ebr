# Future (v2 or later): standalone border router for Apple Home without an Apple hub

*Filed 2026-10-18 on the question: can someone without an Apple TV or HomePod set up this border
router and then pair Matter-over-Thread devices with the Home app? Only worth doing if the Home app works
with it. Status: **plausible, not proven** — the deciding step is undocumented and needs a test. Nothing built.*

## What Apple says (support pages, read 2026-10-18)

- **Matter without a hub is allowed since iOS 18:** "If you have an iPhone using iOS 18 or later … you can add
  Matter accessories to and control Matter accessories from the Home app without a home hub" (HT213441). An
  older page (102557) still says a hub is required — the newer statement is the iOS 18 one.
- **Thread accessories need a Thread border router:** "Thread-based accessories require a Thread-enabled home hub
  such as Apple TV 4K, HomePod (2nd generation), HomePod mini, … **or a compatible third-party Thread border
  router**" (HT213441, 102557). Apple names no list of compatible ones.
- **iPhone 15 Pro and later** have a Thread radio: "you can control thread-based accessories without a home hub"
  (HT213441). A developer reports commissioning a Matter-over-Thread bulb in the Home app on iOS 18 with an
  iPhone 15 Pro and no hub at all; Apple DTS says the iPhone's radio "does not expose itself as a border
  router" — it talks Thread itself but routes nothing for others.

## What it would take

The border router side is not the problem: an OpenThread border router (ours) does what Apple's do — routes
between Wi-Fi/Ethernet and Thread, advertises itself by mDNS (`_meshcop._udp`), serves SRP. The open question is
the **iPhone side: the Home app must know our network's credentials** (the active dataset) to hand them to a
new device during commissioning. Apple border routers put theirs into the iCloud keychain; a third-party router
needs another way in:

1. **An iOS app storing the credentials** with `THClient.storeCredentials(forBorderAgent:activeOperationalDataSet:)`
   (ThreadNetwork framework). Needs the entitlement `com.apple.developer.networking.manage-thread-network-credentials`,
   which Apple grants on request — the same problem an own iOS app for
   reading Apple's dataset would have. Eve, Nanoleaf and the Home Assistant companion app do this. Whether the Home app then uses a
   *non-Apple* network from the keychain when no Apple one exists is **not documented**; reports conflict.
2. **Thread 1.4 credential sharing (ePSKc)**, which our router gets anyway ([credential-sharing.md](credential-sharing.md)):
   the user types the passcode from our display into the iPhone. Apple moved to Thread 1.4 in its 2025/26
   releases, but whether iOS offers a UI to *import* a third-party network this way is not documented either.
3. **Let the iPhone form the network?** An iPhone 15 Pro commissions Thread devices alone; whether it then has a
   network our router could join (as a router, giving range and LAN access) is unknown.

Limits even if it works: without an Apple hub there is no remote access and no automations in Apple Home — the
iPhone is the controller and must be at home. Our router would add Thread range and the IP route to the LAN,
not a hub.

## What the firmware would need

- **Forming a network, deliberately.** Today the firmware refuses to start Thread without a stored dataset —
  right for a house where Apple's network exists. Standalone mode needs the opposite, guarded: a
  "Create network" action on the No dataset screen (SELECT, with a confirm), which first scans (`discover`) and
  refuses if a Thread network is already in range — then `otDatasetCreateNewNetwork`.
- **Getting the credentials to the iPhone**: whichever of 1–3 works; for 2, the Share network screen of
  [display-ui.md](display-ui.md) is that path.
- Optional: the router as a Matter device itself ([matter-device.md](matter-device.md)), so it shows up in Home.

## Test before building anything

With the P4 router forming a **test network away from the Apple TV's range** (or with the Apple TV unplugged —
the production network must not see a second one), an iPhone 15 Pro or later on the current iOS, and a
Matter-over-Thread test device:

1. A test Home without hubs; try to add the device → which error ("Thread Border Router Required" / "Needs Thread
   Network")?
2. Put the test network's credentials into the iPhone keychain through the Home Assistant companion app (it holds
   the entitlement) → retry. Works → path 1 is real.
3. Once our router has ePSKc: look for an iOS import flow → path 2.

Result decides whether standalone mode goes on the roadmap. Pick it up after v1 (border router in Apple's
network, display, credential sharing).

## Sources

- Apple: [Pair and manage your Matter accessories (HT213441)](https://support.apple.com/en-us/HT213441),
  [Set up a home hub (102557)](https://support.apple.com/en-us/102557),
  ["Thread Border Router Required" alert (102078)](https://support.apple.com/en-tm/102078)
- [Apple developer forum: commissioning Matter Thread device without hub](https://developer.apple.com/forums/thread/766729)
- [Espressif: Thread network credentials sharing](https://developer.espressif.com/blog/2026/01/thread-credential-sharing/)
- [Home Assistant: Thread integration](https://www.home-assistant.io/integrations/thread/),
  [community: standalone Thread/Matter](https://community.home-assistant.io/t/standalone-thread-matter/739798)
