#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "esp_netif.h"

#include "br_radio.h"

#define BR_STATUS_MAX_NEIGHBOURS 8
#define BR_STATUS_MAX_IPV6 8

typedef enum {
    BR_ROLE_STARTING, // OpenThread stack not attached yet
    BR_ROLE_DISABLED,
    BR_ROLE_DETACHED,
    BR_ROLE_CHILD,
    BR_ROLE_ROUTER,
    BR_ROLE_LEADER,
} br_role_t;

/** IPv6 address kinds on the LAN, in the order the network page lists them */
typedef enum {
    BR_IP6_LINK_LOCAL, // fe80::/10
    BR_IP6_ULA,        // fc00::/7
    BR_IP6_GLOBAL,
    BR_IP6_OTHER,
} br_ip6_kind_t;

typedef struct {
    br_ip6_kind_t kind;
    char addr[40]; // without zone
} br_ip6_t;

typedef struct {
    uint16_t rloc16;
    int8_t avg_rssi;
    br_role_t role; // BR_ROLE_CHILD, BR_ROLE_ROUTER or BR_ROLE_LEADER
    bool is_border_router;
} br_neighbour_t;

/**
 * What the display shows, copied out of OpenThread and the netif in one go. Holds no secret: network name,
 * channel and PAN ID are in every Thread beacon; the dataset and network key are never read here.
 */
typedef struct {
    bool attached;    // br_display_attach() has been called
    bool has_dataset; // an active dataset is stored
    br_role_t role;
    char network_name[17];
    uint8_t channel;
    uint16_t pan_id;
    uint16_t rloc16;
    uint8_t neighbour_total;   // whole neighbour table
    uint8_t neighbour_routers; // of those, routers
    uint8_t neighbour_count;   // entries in neighbours[]
    uint8_t border_routers; // distinct border routers in the network data
    br_neighbour_t neighbours[BR_STATUS_MAX_NEIGHBOURS];

    const char *radio_chip; // "H2" / "C6"
    br_radio_state_t radio;
    int radio_progress; // percent while flashing
    br_bt_state_t bt;
    const char *firmware;     // firmware version (esp_app_get_description)
    const char *pairing_qr;   // Matter QR payload while unpaired, else NULL
    const char *pairing_code; // manual pairing code, 11 digits

    bool eth_up;
    char ipv4[16];
    br_ip6_t ipv6[BR_STATUS_MAX_IPV6]; // sorted by kind: link-local, ULA, global
    int ipv6_count;
    uint32_t uptime_s;
} br_status_t;

/** Fills *out. Takes the OpenThread lock briefly; returns false (and leaves the Thread part) if it is busy. */
bool br_status_collect(esp_netif_t *backbone, br_status_t *out);
