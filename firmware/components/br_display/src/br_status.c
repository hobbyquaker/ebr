#include "br_status.h"

#include <string.h>

#include "esp_openthread.h"
#include "esp_openthread_lock.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "lwip/ip6_addr.h"
#include "openthread/dataset.h"
#include "openthread/link.h"
#include "openthread/netdata.h"
#include "openthread/thread.h"
#include "openthread/thread_ftd.h"

#define MAX_BORDER_ROUTERS 16

static br_role_t map_role(otDeviceRole role)
{
    switch (role) {
    case OT_DEVICE_ROLE_DETACHED:
        return BR_ROLE_DETACHED;
    case OT_DEVICE_ROLE_CHILD:
        return BR_ROLE_CHILD;
    case OT_DEVICE_ROLE_ROUTER:
        return BR_ROLE_ROUTER;
    case OT_DEVICE_ROLE_LEADER:
        return BR_ROLE_LEADER;
    case OT_DEVICE_ROLE_DISABLED:
    default:
        return BR_ROLE_DISABLED;
    }
}

static bool add_unique(uint16_t *set, uint8_t *count, uint16_t rloc16)
{
    for (uint8_t i = 0; i < *count; i++) {
        if (set[i] == rloc16) {
            return false;
        }
    }
    if (*count < MAX_BORDER_ROUTERS) {
        set[(*count)++] = rloc16;
    }
    return true;
}

static bool contains(const uint16_t *set, uint8_t count, uint16_t rloc16)
{
    for (uint8_t i = 0; i < count; i++) {
        if (set[i] == rloc16) {
            return true;
        }
    }
    return false;
}

static void collect_thread(otInstance *instance, br_status_t *out)
{
    out->has_dataset = otDatasetIsCommissioned(instance);
    out->role = map_role(otThreadGetDeviceRole(instance));
    strlcpy(out->network_name, otThreadGetNetworkName(instance), sizeof(out->network_name));
    out->channel = otLinkGetChannel(instance);
    out->pan_id = otLinkGetPanId(instance);
    out->rloc16 = otThreadGetRloc16(instance);

    // Border routers: every RLOC16 that publishes an on-mesh prefix or an external route
    uint16_t brs[MAX_BORDER_ROUTERS];
    uint8_t br_count = 0;
    otNetworkDataIterator it = OT_NETWORK_DATA_ITERATOR_INIT;
    otBorderRouterConfig prefix;
    while (otNetDataGetNextOnMeshPrefix(instance, &it, &prefix) == OT_ERROR_NONE) {
        add_unique(brs, &br_count, prefix.mRloc16);
    }
    it = OT_NETWORK_DATA_ITERATOR_INIT;
    otExternalRouteConfig route;
    while (otNetDataGetNextRoute(instance, &it, &route) == OT_ERROR_NONE) {
        add_unique(brs, &br_count, route.mRloc16);
    }
    out->border_routers = br_count;

    bool attached = out->role >= BR_ROLE_CHILD;
    uint16_t leader_rloc16 = attached ? (uint16_t)(otThreadGetLeaderRouterId(instance) << 10) : 0xfffe;

    out->neighbour_count = 0;
    out->neighbour_routers = 0;
    otNeighborInfoIterator nit = OT_NEIGHBOR_INFO_ITERATOR_INIT;
    otNeighborInfo info;
    uint8_t total = 0;
    while (otThreadGetNextNeighborInfo(instance, &nit, &info) == OT_ERROR_NONE) {
        total++;
        if (!info.mIsChild) {
            out->neighbour_routers++;
        }
        if (out->neighbour_count < BR_STATUS_MAX_NEIGHBOURS) {
            br_neighbour_t *n = &out->neighbours[out->neighbour_count++];
            n->rloc16 = info.mRloc16;
            n->avg_rssi = info.mAverageRssi;
            n->role = info.mIsChild ? BR_ROLE_CHILD : (info.mRloc16 == leader_rloc16 ? BR_ROLE_LEADER : BR_ROLE_ROUTER);
            n->is_border_router = contains(brs, br_count, info.mRloc16);
        }
    }
    out->neighbour_total = total;
}

static br_ip6_kind_t ip6_kind(const esp_ip6_addr_t *a)
{
    switch (esp_netif_ip6_get_addr_type((esp_ip6_addr_t *)a)) {
    case ESP_IP6_ADDR_IS_LINK_LOCAL:
        return BR_IP6_LINK_LOCAL;
    case ESP_IP6_ADDR_IS_UNIQUE_LOCAL:
        return BR_IP6_ULA;
    case ESP_IP6_ADDR_IS_GLOBAL:
        return BR_IP6_GLOBAL;
    default:
        return BR_IP6_OTHER;
    }
}

static void collect_netif(esp_netif_t *netif, br_status_t *out)
{
    out->eth_up = esp_netif_is_netif_up(netif);
    out->ipv4[0] = '\0';
    out->ipv6_count = 0;

    esp_netif_ip_info_t ip;
    if (esp_netif_get_ip_info(netif, &ip) == ESP_OK && ip.ip.addr != 0) {
        snprintf(out->ipv4, sizeof(out->ipv4), IPSTR, IP2STR(&ip.ip));
    }

    // All addresses, sorted by kind (stable insertion: link-local, ULA, global, other)
    esp_ip6_addr_t addrs[CONFIG_LWIP_IPV6_NUM_ADDRESSES];
    int n = esp_netif_get_all_ip6(netif, addrs);
    for (int i = 0; i < n && out->ipv6_count < BR_STATUS_MAX_IPV6; i++) {
        br_ip6_kind_t kind = ip6_kind(&addrs[i]);
        int pos = out->ipv6_count;
        while (pos > 0 && out->ipv6[pos - 1].kind > kind) {
            out->ipv6[pos] = out->ipv6[pos - 1];
            pos--;
        }
        ip6_addr_t a;
        memcpy(a.addr, addrs[i].addr, sizeof(a.addr));
        ip6_addr_clear_zone(&a);
        out->ipv6[pos].kind = kind;
        ip6addr_ntoa_r(&a, out->ipv6[pos].addr, sizeof(out->ipv6[pos].addr));
        out->ipv6_count++;
    }
}

bool br_status_collect(esp_netif_t *backbone, br_status_t *out)
{
    out->uptime_s = (uint32_t)(esp_timer_get_time() / 1000000);
    out->radio_chip = br_radio_chip();
    out->radio = br_radio_state(&out->radio_progress);
    out->bt = br_radio_bt();
    out->attached = backbone != NULL;
    if (!out->attached) {
        out->role = BR_ROLE_STARTING;
        return true;
    }

    collect_netif(backbone, out);

    if (!esp_openthread_lock_acquire(pdMS_TO_TICKS(100))) {
        return false;
    }
    collect_thread(esp_openthread_get_instance(), out);
    esp_openthread_lock_release();
    return true;
}
