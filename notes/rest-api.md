# The border router's REST API (and the Thread Network Visualizer)

**ebr (since 2026-10-20) runs no web server at all** — it is built on esp-matter, not on esp-thread-br's example,
and has no REST API; the questions below matter again only if a web page comes back.

*Note, 2026-10-18, on the question: the Thread Network Visualizer uses the OTBR REST API — can our
ESP32-P4 border router offer that API?* Read from the sources on GitHub; nothing run.

## Short answer

Partly. esp-thread-br's web server (`components/esp_ot_br_server`, enabled with `CONFIG_OPENTHREAD_BR_START_WEB`,
port 80) implements the **classic OTBR REST API** — the one ot-br-posix has had for years — but **not the newer
JSON:API** (`/api/devices`, `/api/actions`, `/api/diagnostics/{id}`) that the visualizer's crawl uses.

## What esp-thread-br serves (its `openapi.yaml`)

| Path | Methods | Content |
| --- | --- | --- |
| `/.well-known/thread/esp-br-rest` | GET | API version and entry points (RFC 8288 links) |
| `/node` | GET, DELETE | node state; **DELETE = factory reset** |
| `/node/ba-id`, `/rloc`, `/rloc16`, `/ext-address`, `/state`, `/network-name`, `/leader-data`, `/ext-panid`, `/num-of-router` | GET | single node values |
| `/node/dataset/active`, `/node/dataset/pending` | GET, PUT | the datasets as JSON — **GET includes `NetworkKey`**; PUT sets one (refused while Thread is active) |
| `/node/ba-epskc/state`, `/node/ba-epskc/key` | GET, POST, DELETE | Thread 1.4 credential sharing: status, start an ephemeral key (optional lifetime and port), stop it — the REST side of [credential-sharing.md](credential-sharing.md) |
| `/diagnostics` | GET | network diagnostics of the mesh (the classic OTBR form: one request, all nodes) |
| `/`, `/index.html` | GET | the web GUI |

## What the visualizer calls (`fpb/Thread-Network-Visualizer`, `app.js`)

1. `GET /node` — **served** by esp-thread-br.
2. `POST /api/actions` with a `getNetworkDiagnosticTask` (destination, types `routerNeighbors`, `childTable`,
   `rloc16`, `extAddress`, `ipv6Addresses`), then polling `GET /api/actions/{id}` until `completed`, then
   `GET /api/diagnostics/{resultId}` — hop by hop, one node at a time. **Not served** (ot-br-posix's JSON:API from
   `src/rest/README.md`, "REST JSON:API for Commissioner and Diagnostics").

The visualizer also runs from another origin (a static page on a PC); a browser then needs CORS headers, and
`esp_br_web.c` sets none (searched for `Access-Control`) — so even matching paths would be blocked unless the page
is served by the border router itself.

## Ways to get there

| Way | Effort | Notes |
| --- | --- | --- |
| **A. Adapt the visualizer to the classic `/diagnostics`** and serve it **from the border router** (static files next to the web GUI) | small: the crawl becomes one GET plus the same graph code; no CORS issue | a fork of a small vanilla-JS page; the visualizer can already import `ot-ctl meshdiag topology` output, which is close to what `/diagnostics` returns. Best first step. |
| **B. Implement the JSON:API on the ESP** (`/api/devices`, `/api/actions`, `/api/diagnostics`) | larger: port of ot-br-posix's `src/rest` actions and diagnostics (C++), on top of esp-thread-br's server | any tool written for ot-br-posix's JSON:API then works unchanged; a candidate for an upstream contribution to esp-thread-br (they keep `openapi.yaml` and a version check, so additions are expected to go through review) |
| **C. A small proxy** (in she, or a script) that turns `/api/actions` into calls to `/diagnostics`, adds CORS and authentication | medium | useful only if something else needs the proxy anyway (e.g. she managing border routers) |

Recommendation: A now (it also gives a topology view on our own web page), B later if it proves useful, as an
upstream pull request.

## Security finding — before the border router goes on the LAN

The esp-thread-br REST API has **no authentication** (the OpenAPI file declares no security scheme; "token",
"Authorization" do not occur): anyone on the LAN can **read the network key** (`GET /node/dataset/active`),
**factory-reset** the border router (`DELETE /node`) and start a credential-sharing session. ot-br-posix's REST API
is the same by design ("local network access control"). For a border router in Apple's production network that
is too open:

- add a token check to the write paths and to the dataset GET (setup token as in `mcuw/esp32-thread-br`, which
  has "REST-API with Setup-Token-Auth"), or
- build without the dataset GET and the DELETE, keeping the read-only status paths open for the visualizer.

To decide when the code is written.

## Sources

- esp-thread-br: `components/esp_ot_br_server/src/openapi.yaml`, `src/esp_br_web.c`,
  `private_include/esp_br_web_api.h`, `tools/ci/check_rest_api_version_sync.py` in
  [espressif/esp-thread-br](https://github.com/espressif/esp-thread-br)
- ot-br-posix: [`src/rest/README.md`](https://github.com/openthread/ot-br-posix/blob/main/src/rest/README.md)
  (JSON:API for devices, actions, diagnostics)
- [fpb/Thread-Network-Visualizer](https://github.com/fpb/Thread-Network-Visualizer) `app.js`
- [mcuw/esp32-thread-br](https://github.com/mcuw/esp32-thread-br) (setup-token auth on its REST API)
