/*
 * The screens of design direction A (dark instrument panel, IBM Plex Sans Condensed / Mono), 320x240 landscape:
 * status, no dataset, neighbours. Design canvas: https://claude.ai/artifact/JS4Bp3QNGs2wz1DgyUVH4Y
 * Fixed layout with absolute positions; the display has one size.
 */
#include "br_ui.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

LV_FONT_DECLARE(br_font_sans_9);
LV_FONT_DECLARE(br_font_sans_11);
LV_FONT_DECLARE(br_font_sans_semi_10);
LV_FONT_DECLARE(br_font_sans_semi_12);
LV_FONT_DECLARE(br_font_sans_bold_18);
LV_FONT_DECLARE(br_font_sans_bold_26);
LV_FONT_DECLARE(br_font_mono_9);
LV_FONT_DECLARE(br_font_mono_11);
LV_FONT_DECLARE(br_font_mono_semi_14);

// Palette of direction A
#define C_SCREEN 0x0E1416
#define C_BAR 0x121B1E
#define C_LINE 0x1F2B2F
#define C_ROW_LINE 0x18232A
#define C_TILE 0x152024
#define C_TEXT 0xE6EDEF
#define C_BODY 0xC9D6DA
#define C_MUTED 0x9DB0B5
#define C_LABEL 0x8FA3A9
#define C_ACCENT 0x3FB8AF
#define C_LINK 0x7FD3CC
#define C_OK 0x7FE0A0
#define C_AMBER 0xF2B84B
#define C_AMBER_BG 0x3A2A0E
#define C_AMBER_TEXT 0xF6D79A
#define C_BAR_OFF 0x26343A

#define NEIGHBOUR_ROWS 5
#define PAGES 4 // status, neighbours, network, device
#define PAGE_NEIGHBOURS 1
#define PAGE_NETWORK 2
#define PAGE_DEVICE 3

// The four buttons sit under the display, evenly spaced; the bottom bar labels each one from left to right.
// Order fixed in notes/display-ui.md.
static const br_key_t KEY_ORDER[4] = {BR_KEY_BACK, BR_KEY_PREV, BR_KEY_NEXT, BR_KEY_SELECT};
#define SOFTKEY_W (BR_UI_WIDTH / 4)
#define SOFTKEY_BAR_H 20

typedef struct {
    uint32_t icon, bg, word;
} role_colors_t;

static const role_colors_t ROLE_GREY = {0x8FA3A9, 0x1A2427, 0xC9D6DA};
static const role_colors_t ROLE_CHILD = {0x7FE0A0, 0x123A26, 0xA8EFC0};
static const role_colors_t ROLE_ROUTER = {0x5AA9FF, 0x12304A, 0x8EC5FF};
static const role_colors_t ROLE_LEADER = {0xF2B84B, 0x3A2A0E, 0xF6D79A};

// The mesh glyph in the role circle: three nodes and their links, in a 26x26 box
static const lv_point_precise_t MESH_LINK_A[] = {{13, 8}, {6, 16}};
static const lv_point_precise_t MESH_LINK_B[] = {{13, 8}, {20, 16}};
static const lv_point_precise_t MESH_LINK_C[] = {{8, 19}, {18, 19}};

typedef struct {
    lv_obj_t *circle;
    lv_obj_t *nodes[3];
    lv_obj_t *links[3];
} mesh_icon_t;

typedef struct {
    lv_obj_t *label[4]; // indexed by br_key_t; NULL without buttons
} softkeys_t;

typedef struct {
    lv_obj_t *dot[PAGES];
} page_dots_t;

static struct {
    bool has_buttons;
    int page;
    lv_obj_t *shown;

    struct {
        lv_obj_t *screen;
        lv_obj_t *eth;
        mesh_icon_t icon;
        lv_obj_t *role;
        lv_obj_t *subtitle;
        lv_obj_t *tile_value[6];
        lv_obj_t *routers;
        lv_obj_t *radio_label;
        lv_obj_t *bt;
        lv_obj_t *lan;
        lv_obj_t *ipv6;
        page_dots_t dots;
        softkeys_t keys;
    } status;

    struct {
        lv_obj_t *screen;
        lv_obj_t *eth;
        lv_obj_t *info;
        softkeys_t keys;
    } nodataset;

    struct {
        lv_obj_t *screen;
        lv_obj_t *bt;
        lv_obj_t *qr;
        lv_obj_t *code;
        lv_obj_t *info;
        char shown_qr[96];
        softkeys_t keys;
    } pairing;

    struct {
        lv_obj_t *screen;
        lv_obj_t *summary;
        lv_obj_t *empty;
        page_dots_t dots;
        softkeys_t keys;
        struct {
            lv_obj_t *row;
            lv_obj_t *dot;
            lv_obj_t *role;
            lv_obj_t *rloc;
            lv_obj_t *bars[3];
            lv_obj_t *note;
            lv_obj_t *rssi;
        } rows[NEIGHBOUR_ROWS];
    } neighbours;

    struct {
        lv_obj_t *screen;
        lv_obj_t *eth;
        lv_obj_t *kind[1 + BR_STATUS_MAX_IPV6]; // row 0: IPv4
        lv_obj_t *addr[1 + BR_STATUS_MAX_IPV6];
        page_dots_t dots;
        softkeys_t keys;
    } network;

    struct {
        lv_obj_t *screen;
        lv_obj_t *eth;
        lv_obj_t *firmware;
        lv_obj_t *paired;
        lv_obj_t *radio;
        lv_obj_t *uptime;
        lv_obj_t *bar;
        lv_obj_t *hint;
        page_dots_t dots;
        softkeys_t keys;
    } device;
} s_ui;

/* ---- building blocks ---- */

static lv_obj_t *box(lv_obj_t *parent, int x, int y, int w, int h, uint32_t color)
{
    lv_obj_t *o = lv_obj_create(parent);
    lv_obj_remove_style_all(o);
    lv_obj_remove_flag(o, LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_pos(o, x, y);
    lv_obj_set_size(o, w, h);
    lv_obj_set_style_bg_color(o, lv_color_hex(color), 0);
    lv_obj_set_style_bg_opa(o, LV_OPA_COVER, 0);
    return o;
}

static lv_obj_t *circle(lv_obj_t *parent, int x, int y, int d, uint32_t color)
{
    lv_obj_t *o = box(parent, x, y, d, d, color);
    lv_obj_set_style_radius(o, LV_RADIUS_CIRCLE, 0);
    return o;
}

static lv_obj_t *ring(lv_obj_t *parent, int x, int y, int d, uint32_t color)
{
    lv_obj_t *o = circle(parent, x, y, d, 0);
    lv_obj_set_style_bg_opa(o, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(o, 1, 0);
    lv_obj_set_style_border_color(o, lv_color_hex(color), 0);
    return o;
}

static lv_obj_t *label(lv_obj_t *parent, const lv_font_t *font, uint32_t color, int x, int y, const char *text)
{
    lv_obj_t *l = lv_label_create(parent);
    lv_obj_set_style_text_font(l, font, 0);
    lv_obj_set_style_text_color(l, lv_color_hex(color), 0);
    lv_obj_set_pos(l, x, y);
    lv_label_set_text(l, text);
    return l;
}

static lv_obj_t *label_right(lv_obj_t *parent, const lv_font_t *font, uint32_t color, int right, int y, int w,
                             const char *text)
{
    lv_obj_t *l = label(parent, font, color, right - w, y, text);
    lv_obj_set_width(l, w);
    lv_obj_set_style_text_align(l, LV_TEXT_ALIGN_RIGHT, 0);
    lv_label_set_long_mode(l, LV_LABEL_LONG_CLIP);
    return l;
}

static lv_obj_t *new_screen(void)
{
    lv_obj_t *scr = lv_obj_create(NULL);
    lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(scr, lv_color_hex(C_SCREEN), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);
    return scr;
}

/** The 22 px bar on top; returns the right-hand label. */
static lv_obj_t *header(lv_obj_t *scr, const char *title, bool live)
{
    lv_obj_t *bar = box(scr, 0, 0, BR_UI_WIDTH, 22, C_BAR);
    lv_obj_set_style_border_side(bar, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_border_width(bar, 1, 0);
    lv_obj_set_style_border_color(bar, lv_color_hex(C_LINE), 0);

    ring(bar, 10, 6, 10, live ? C_ACCENT : C_LABEL);
    if (live) {
        circle(bar, 13, 9, 4, C_ACCENT);
    }
    lv_obj_t *t = label(bar, &br_font_sans_semi_10, C_MUTED, 26, 5, title);
    lv_obj_set_style_text_letter_space(t, 1, 0);

    lv_obj_t *right = label_right(bar, &br_font_sans_semi_10, C_MUTED, BR_UI_WIDTH - 10, 5, 170, "");
    lv_obj_set_style_text_letter_space(right, 1, 0);
    return right;
}

/**
 * The 20 px bar at the bottom: one cell per button, each label right above its button. Without buttons the bar
 * stays empty.
 */
static void softkeys_create(lv_obj_t *scr, softkeys_t *keys)
{
    lv_obj_t *bar = box(scr, 0, BR_UI_HEIGHT - SOFTKEY_BAR_H, BR_UI_WIDTH, SOFTKEY_BAR_H, C_SCREEN);
    lv_obj_set_style_border_side(bar, LV_BORDER_SIDE_TOP, 0);
    lv_obj_set_style_border_width(bar, 1, 0);
    lv_obj_set_style_border_color(bar, lv_color_hex(C_LINE), 0);
    if (!s_ui.has_buttons) {
        return;
    }
    for (int cell = 0; cell < 4; cell++) {
        if (cell > 0) {
            box(bar, cell * SOFTKEY_W, 5, 1, SOFTKEY_BAR_H - 10, C_LINE);
        }
        lv_obj_t *l = label(bar, &br_font_sans_semi_10, C_LABEL, cell * SOFTKEY_W, 4, "");
        lv_obj_set_width(l, SOFTKEY_W);
        lv_obj_set_style_text_align(l, LV_TEXT_ALIGN_CENTER, 0);
        lv_obj_set_style_text_letter_space(l, 1, 0);
        keys->label[KEY_ORDER[cell]] = l;
    }
}

/** Labels by br_key_t: SELECT, BACK, PREV, NEXT; "" for a button without a function on this screen. */
static void softkeys_set(softkeys_t *keys, const char *select, const char *back, const char *prev, const char *next)
{
    const char *text[4] = {[BR_KEY_SELECT] = select, [BR_KEY_BACK] = back, [BR_KEY_PREV] = prev, [BR_KEY_NEXT] = next};
    for (int k = 0; k < 4; k++) {
        if (keys->label[k]) {
            lv_label_set_text(keys->label[k], text[k]);
        }
    }
}

/** A row of small dots, one per page, centred just above the bottom bar. */
static void page_dots_create(lv_obj_t *scr, page_dots_t *dots)
{
    const int d = 5, gap = 6, w = PAGES * d + (PAGES - 1) * gap;
    for (int i = 0; i < PAGES; i++) {
        dots->dot[i] = circle(scr, (BR_UI_WIDTH - w) / 2 + i * (d + gap), BR_UI_HEIGHT - SOFTKEY_BAR_H - 10, d,
                              C_BAR_OFF);
    }
}

static void page_dots_set(page_dots_t *dots)
{
    for (int i = 0; i < PAGES; i++) {
        lv_obj_set_style_bg_color(dots->dot[i], lv_color_hex(i == s_ui.page ? C_ACCENT : C_BAR_OFF), 0);
    }
}

static void mesh_icon_create(mesh_icon_t *icon, lv_obj_t *parent, int x, int y, int d)
{
    icon->circle = circle(parent, x, y, d, ROLE_GREY.bg);
    int off = (d - 26) / 2;
    static const int NODE[3][2] = {{13, 5}, {5, 19}, {21, 19}};
    for (int i = 0; i < 3; i++) {
        icon->nodes[i] = circle(icon->circle, off + NODE[i][0] - 3, off + NODE[i][1] - 3, 6, ROLE_GREY.icon);
    }
    const lv_point_precise_t *links[3] = {MESH_LINK_A, MESH_LINK_B, MESH_LINK_C};
    for (int i = 0; i < 3; i++) {
        lv_obj_t *l = lv_line_create(icon->circle);
        lv_line_set_points(l, links[i], 2);
        lv_obj_set_pos(l, off, off);
        lv_obj_set_style_line_width(l, 2, 0);
        icon->links[i] = l;
    }
}

static void mesh_icon_set(mesh_icon_t *icon, const role_colors_t *c)
{
    lv_obj_set_style_bg_color(icon->circle, lv_color_hex(c->bg), 0);
    for (int i = 0; i < 3; i++) {
        lv_obj_set_style_bg_color(icon->nodes[i], lv_color_hex(c->icon), 0);
        lv_obj_set_style_line_color(icon->links[i], lv_color_hex(c->icon), 0);
    }
}

/* ---- the screens ---- */

static void create_status(void)
{
    lv_obj_t *scr = s_ui.status.screen = new_screen();
    s_ui.status.eth = header(scr, "THREAD BORDER ROUTER", true);

    mesh_icon_create(&s_ui.status.icon, scr, 12, 34, 46);
    s_ui.status.role = label(scr, &br_font_sans_bold_26, ROLE_GREY.word, 70, 32, "STARTING");
    lv_obj_set_style_text_letter_space(s_ui.status.role, 1, 0);
    s_ui.status.subtitle = label(scr, &br_font_sans_11, C_MUTED, 70, 64, "");
    lv_obj_set_width(s_ui.status.subtitle, BR_UI_WIDTH - 70 - 12);
    lv_label_set_long_mode(s_ui.status.subtitle, LV_LABEL_LONG_DOT);

    static const char *const TILE_LABELS[6] = {"CHANNEL", "PAN ID", "NEIGHBOURS", "RLOC16", "RADIO",
                                               "BORDER ROUTERS"};
    const int tile_w = (BR_UI_WIDTH - 24 - 8) / 3, tile_h = 34;
    for (int i = 0; i < 6; i++) {
        int x = 12 + (i % 3) * (tile_w + 4), y = 90 + (i / 3) * (tile_h + 4);
        lv_obj_t *tile = box(scr, x, y, tile_w, tile_h, C_TILE);
        lv_obj_set_style_radius(tile, 4, 0);
        lv_obj_t *l = label(tile, &br_font_sans_9, C_LABEL, 7, 4, TILE_LABELS[i]);
        lv_obj_set_style_text_letter_space(l, 1, 0);
        if (i == 4) {
            s_ui.status.radio_label = l;
        }
        s_ui.status.tile_value[i] = label(tile, &br_font_mono_semi_14, C_TEXT, 7, 15, "-");
    }
    // Bluetooth next to the radio state
    s_ui.status.bt = label(lv_obj_get_parent(s_ui.status.tile_value[4]), &br_font_sans_9, C_LABEL, 0, 4, "");
    lv_obj_set_width(s_ui.status.bt, tile_w - 7);
    lv_obj_set_style_text_align(s_ui.status.bt, LV_TEXT_ALIGN_RIGHT, 0);
    // "of those, routers" next to the neighbour count
    s_ui.status.routers = label(lv_obj_get_parent(s_ui.status.tile_value[2]), &br_font_sans_9, C_LABEL, 40, 19, "");

    s_ui.status.lan = label(scr, &br_font_mono_9, C_MUTED, 12, 172, "");
    s_ui.status.ipv6 = label(scr, &br_font_mono_9, C_MUTED, 12, 184, "");
    lv_obj_set_width(s_ui.status.ipv6, BR_UI_WIDTH - 24);
    lv_label_set_long_mode(s_ui.status.ipv6, LV_LABEL_LONG_DOT);

    page_dots_create(scr, &s_ui.status.dots);
    softkeys_create(scr, &s_ui.status.keys);
    softkeys_set(&s_ui.status.keys, "", "", "< PREV", "NEXT >");
}

static void create_nodataset(void)
{
    lv_obj_t *scr = s_ui.nodataset.screen = new_screen();
    s_ui.nodataset.eth = header(scr, "THREAD BORDER ROUTER", false);

    lv_obj_t *c = circle(scr, 12, 36, 44, C_AMBER_BG);
    static const int NODE[3][2] = {{12, 4}, {4, 18}, {20, 18}};
    for (int i = 0; i < 3; i++) {
        ring(c, 10 + NODE[i][0] - 3, 10 + NODE[i][1] - 3, 6, C_AMBER);
    }

    label(scr, &br_font_sans_bold_18, C_AMBER_TEXT, 68, 34, "No Thread dataset yet");
    lv_obj_t *t = label(scr, &br_font_sans_11, C_BODY, 68, 60,
                        "Thread stays off, so no second network appears next to the existing one. "
                        "Give the router that network's dataset first:");
    lv_obj_set_width(t, BR_UI_WIDTH - 68 - 12);
    lv_label_set_long_mode(t, LV_LABEL_LONG_WRAP);

    label(scr, &br_font_mono_11, C_AMBER, 68, 112, "1");
    label(scr, &br_font_sans_11, C_TEXT, 80, 112, "Serial console:");
    label(scr, &br_font_mono_11, C_LINK, 80, 126, "dataset set active <tlvs>");
    label(scr, &br_font_mono_11, C_AMBER, 68, 146, "2");
    label(scr, &br_font_sans_11, C_TEXT, 80, 146, "then:");
    label(scr, &br_font_mono_11, C_LINK, 80, 160, "ifconfig up · thread start");
    label(scr, &br_font_sans_9, C_LABEL, 68, 182, "The web UI stays off until it has authentication.");

    s_ui.nodataset.info = label(scr, &br_font_mono_9, C_MUTED, 68, 200, "");
    softkeys_create(scr, &s_ui.nodataset.keys); // no functions while there is no dataset
}

/* Unpaired: the Matter QR code for the Home app, and the manual code */
static void create_pairing(void)
{
    lv_obj_t *scr = s_ui.pairing.screen = new_screen();
    s_ui.pairing.bt = header(scr, "ADD TO APPLE HOME", false);

    lv_obj_t *field = box(scr, 10, 28, 180, 180, 0xFFFFFF);
    lv_obj_set_style_radius(field, 4, 0);
    s_ui.pairing.qr = lv_qrcode_create(field);
    lv_qrcode_set_size(s_ui.pairing.qr, 164);
    lv_qrcode_set_dark_color(s_ui.pairing.qr, lv_color_hex(0x0B0F10));
    lv_qrcode_set_light_color(s_ui.pairing.qr, lv_color_hex(0xFFFFFF));
    lv_obj_center(s_ui.pairing.qr);

    const int x = 200, w = BR_UI_WIDTH - x - 8;
    label(scr, &br_font_sans_bold_18, C_TEXT, x, 28, "Home app");
    lv_obj_t *t = label(scr, &br_font_sans_11, C_BODY, x, 52,
                        "Tap + and Add Accessory, then scan the code. The router gets the Thread network from the pairing.");
    lv_obj_set_width(t, w);
    lv_label_set_long_mode(t, LV_LABEL_LONG_WRAP);
    lv_obj_t *l = label(scr, &br_font_sans_9, C_LABEL, x, 136, "SETUP CODE");
    lv_obj_set_style_text_letter_space(l, 1, 0);
    s_ui.pairing.code = label(scr, &br_font_mono_semi_14, C_TEXT, x, 148, "");
    s_ui.pairing.info = label(scr, &br_font_mono_9, C_MUTED, x, 176, "");
    lv_obj_set_width(s_ui.pairing.info, w);
    lv_label_set_long_mode(s_ui.pairing.info, LV_LABEL_LONG_WRAP);

    softkeys_create(scr, &s_ui.pairing.keys); // no functions while unpaired
}

static void create_neighbours(void)
{
    lv_obj_t *scr = s_ui.neighbours.screen = new_screen();
    s_ui.neighbours.summary = header(scr, "NEIGHBOURS", true);

    static const char *const COLS[] = {"ROLE", "RLOC16", "LINK"};
    static const int COL_X[] = {10, 68, 140};
    for (int i = 0; i < 3; i++) {
        lv_obj_t *l = label(scr, &br_font_sans_9, C_LABEL, COL_X[i], 27, COLS[i]);
        lv_obj_set_style_text_letter_space(l, 1, 0);
    }
    label_right(scr, &br_font_sans_9, C_LABEL, BR_UI_WIDTH - 10, 27, 50, "RSSI");

    for (int i = 0; i < NEIGHBOUR_ROWS; i++) {
        lv_obj_t *row = box(scr, 0, 40 + i * 29, BR_UI_WIDTH, 29, C_SCREEN);
        lv_obj_set_style_border_side(row, LV_BORDER_SIDE_TOP, 0);
        lv_obj_set_style_border_width(row, 1, 0);
        lv_obj_set_style_border_color(row, lv_color_hex(C_ROW_LINE), 0);
        s_ui.neighbours.rows[i].row = row;
        s_ui.neighbours.rows[i].dot = circle(row, 10, 11, 7, ROLE_GREY.icon);
        s_ui.neighbours.rows[i].role = label(row, &br_font_sans_semi_12, C_TEXT, 21, 6, "");
        s_ui.neighbours.rows[i].rloc = label(row, &br_font_mono_11, C_TEXT, 68, 7, "");
        static const int BAR_H[3] = {4, 7, 10};
        for (int b = 0; b < 3; b++) {
            s_ui.neighbours.rows[i].bars[b] = box(row, 140 + b * 6, 19 - BAR_H[b], 4, BAR_H[b], C_BAR_OFF);
        }
        s_ui.neighbours.rows[i].note = label(row, &br_font_sans_9, C_MUTED, 164, 8, "");
        s_ui.neighbours.rows[i].rssi = label_right(row, &br_font_mono_11, C_BODY, BR_UI_WIDTH - 10, 7, 50, "");
    }
    s_ui.neighbours.empty = label(scr, &br_font_sans_11, C_MUTED, 10, 50, "No neighbours yet.");

    page_dots_create(scr, &s_ui.neighbours.dots);
    softkeys_create(scr, &s_ui.neighbours.keys);
    softkeys_set(&s_ui.neighbours.keys, "", "HOME", "< PREV", "NEXT >");
}

/* ---- filling them ---- */

static const role_colors_t *role_colors(br_role_t role)
{
    switch (role) {
    case BR_ROLE_CHILD:
        return &ROLE_CHILD;
    case BR_ROLE_ROUTER:
        return &ROLE_ROUTER;
    case BR_ROLE_LEADER:
        return &ROLE_LEADER;
    default:
        return &ROLE_GREY;
    }
}

static const char *role_word(br_role_t role)
{
    static const char *const WORDS[] = {"STARTING", "OFF", "DETACHED", "CHILD", "ROUTER", "LEADER"};
    return WORDS[role];
}

static const char *radio_text(br_radio_state_t r)
{
    static const char *const TEXT[] = {"starting", "flashing", "ok", "no answer"};
    return TEXT[r];
}

static uint32_t radio_color(br_radio_state_t r)
{
    return r == BR_RADIO_OK ? C_OK : r == BR_RADIO_NO_ANSWER || r == BR_RADIO_FLASHING ? C_AMBER : C_LABEL;
}

static const char *bt_text(br_bt_state_t b)
{
    static const char *const TEXT[] = {"-", "off", "adv", "conn"};
    return TEXT[b];
}

static void format_uptime(char *buf, size_t len, uint32_t s)
{
    uint32_t d = s / 86400, h = (s / 3600) % 24, m = (s / 60) % 60;
    if (d > 0) {
        snprintf(buf, len, "%" PRIu32 "d %" PRIu32 "h", d, h);
    } else if (h > 0) {
        snprintf(buf, len, "%" PRIu32 "h %" PRIu32 "m", h, m);
    } else {
        snprintf(buf, len, "%" PRIu32 "m", m);
    }
}

static void set_eth_label(lv_obj_t *l, const br_status_t *st, bool with_thread)
{
    char up[16];
    format_uptime(up, sizeof(up), st->uptime_s);
    if (!st->attached) {
        lv_label_set_text_fmt(l, "ETH … · %s", up);
    } else if (with_thread) {
        lv_label_set_text_fmt(l, "ETH %s · THREAD OFF", st->eth_up ? "UP" : "DOWN");
    } else {
        lv_label_set_text_fmt(l, "ETH %s · %s", st->eth_up ? "UP" : "DOWN", up);
    }
}

static void update_status(const br_status_t *st)
{
    set_eth_label(s_ui.status.eth, st, false);

    const role_colors_t *c = role_colors(st->role);
    mesh_icon_set(&s_ui.status.icon, c);
    lv_label_set_text(s_ui.status.role, role_word(st->role));
    lv_obj_set_style_text_color(s_ui.status.role, lv_color_hex(c->word), 0);

    switch (st->role) {
    case BR_ROLE_STARTING:
        if (st->radio == BR_RADIO_FLASHING) {
            lv_label_set_text_fmt(s_ui.status.subtitle, "updating the %s radio firmware · %d %%", st->radio_chip,
                                  st->radio_progress);
        } else if (st->radio == BR_RADIO_NO_ANSWER) {
            lv_label_set_text_fmt(s_ui.status.subtitle, "the %s radio does not answer", st->radio_chip);
        } else {
            lv_label_set_text(s_ui.status.subtitle, "waiting for Ethernet and the radio");
        }
        break;
    case BR_ROLE_DISABLED:
        lv_label_set_text_fmt(s_ui.status.subtitle, "Thread stopped · dataset of %s stored", st->network_name);
        break;
    case BR_ROLE_DETACHED:
        lv_label_set_text_fmt(s_ui.status.subtitle, "looking for %s", st->network_name);
        break;
    default:
        lv_label_set_text_fmt(s_ui.status.subtitle, "in %s", st->network_name);
        break;
    }

    bool on = st->role >= BR_ROLE_DETACHED;
    bool joined = st->role >= BR_ROLE_CHILD;
    if (on) {
        lv_label_set_text_fmt(s_ui.status.tile_value[0], "%u", st->channel);
        lv_label_set_text_fmt(s_ui.status.tile_value[1], "0x%04X", st->pan_id);
    } else {
        lv_label_set_text(s_ui.status.tile_value[0], "-");
        lv_label_set_text(s_ui.status.tile_value[1], "-");
    }
    if (joined) {
        lv_label_set_text_fmt(s_ui.status.tile_value[2], "%u", st->neighbour_total);
        lv_label_set_text_fmt(s_ui.status.routers, "%u R", st->neighbour_routers);
        lv_label_set_text_fmt(s_ui.status.tile_value[3], "0x%04x", st->rloc16);
        lv_label_set_text_fmt(s_ui.status.tile_value[5], "%u", st->border_routers);
    } else {
        lv_label_set_text(s_ui.status.tile_value[2], "-");
        lv_label_set_text(s_ui.status.routers, "");
        lv_label_set_text(s_ui.status.tile_value[3], "-");
        lv_label_set_text(s_ui.status.tile_value[5], "-");
    }

    lv_label_set_text_fmt(s_ui.status.radio_label, "RADIO (%s)", st->radio_chip ? st->radio_chip : "?");
    lv_obj_t *rcp = s_ui.status.tile_value[4];
    lv_obj_set_style_text_font(rcp, &br_font_sans_semi_12, 0);
    lv_obj_set_style_text_color(rcp, lv_color_hex(radio_color(st->radio)), 0);
    if (st->radio == BR_RADIO_FLASHING) {
        lv_label_set_text_fmt(rcp, "flashing %d%%", st->radio_progress);
    } else {
        lv_label_set_text(rcp, radio_text(st->radio));
    }
    lv_label_set_text_fmt(s_ui.status.bt, "BT %s", bt_text(st->bt));

    lv_label_set_text_fmt(s_ui.status.lan, "IPv4  %s", st->ipv4[0] ? st->ipv4 : "-");
    // The widest-reaching address; all of them are on the network page
    const br_ip6_t *best = NULL;
    for (int i = 0; i < st->ipv6_count; i++) {
        if (st->ipv6[i].kind != BR_IP6_OTHER && (!best || st->ipv6[i].kind > best->kind)) {
            best = &st->ipv6[i];
        }
    }
    if (!best) {
        lv_label_set_text(s_ui.status.ipv6, "IPv6  -");
    } else if (st->ipv6_count > 1) {
        lv_label_set_text_fmt(s_ui.status.ipv6, "IPv6  %s  +%d", best->addr, st->ipv6_count - 1);
    } else {
        lv_label_set_text_fmt(s_ui.status.ipv6, "IPv6  %s", best->addr);
    }
    page_dots_set(&s_ui.status.dots);
}

static void update_nodataset(const br_status_t *st)
{
    set_eth_label(s_ui.nodataset.eth, st, true);
    lv_label_set_text_fmt(s_ui.nodataset.info, "IPv4 %s · %s %s · BT %s", st->ipv4[0] ? st->ipv4 : "-",
                          st->radio_chip ? st->radio_chip : "radio", radio_text(st->radio), bt_text(st->bt));
}

static void update_pairing(const br_status_t *st)
{
    lv_label_set_text_fmt(s_ui.pairing.bt, "BT %s", bt_text(st->bt));
    if (strcmp(s_ui.pairing.shown_qr, st->pairing_qr) != 0) {
        lv_qrcode_update(s_ui.pairing.qr, st->pairing_qr, strlen(st->pairing_qr));
        strlcpy(s_ui.pairing.shown_qr, st->pairing_qr, sizeof(s_ui.pairing.shown_qr));
    }
    const char *c = st->pairing_code ? st->pairing_code : "";
    if (strlen(c) == 11) {
        lv_label_set_text_fmt(s_ui.pairing.code, "%.4s-%.3s-%.4s", c, c + 4, c + 7);
    } else {
        lv_label_set_text(s_ui.pairing.code, c);
    }
    lv_label_set_text_fmt(s_ui.pairing.info, "IPv4 %s\n%s %s", st->ipv4[0] ? st->ipv4 : "-",
                          st->radio_chip ? st->radio_chip : "radio", radio_text(st->radio));
}

static void update_neighbours(const br_status_t *st)
{
    lv_label_set_text_fmt(s_ui.neighbours.summary, "%u SEEN · %u ROUTERS", st->neighbour_total,
                          st->neighbour_routers);
    static const char *const SHORT[] = {"", "", "", "CHLD", "ROUT", "LEAD"};

    for (int i = 0; i < NEIGHBOUR_ROWS; i++) {
        typeof(s_ui.neighbours.rows[0]) *r = &s_ui.neighbours.rows[i];
        if (i >= st->neighbour_count) {
            lv_obj_add_flag(r->row, LV_OBJ_FLAG_HIDDEN);
            continue;
        }
        const br_neighbour_t *n = &st->neighbours[i];
        lv_obj_remove_flag(r->row, LV_OBJ_FLAG_HIDDEN);
        const role_colors_t *c = role_colors(n->role);
        lv_obj_set_style_bg_color(r->dot, lv_color_hex(c->icon), 0);
        lv_label_set_text(r->role, SHORT[n->role]);
        lv_obj_set_style_text_color(r->role, lv_color_hex(c->icon), 0);
        lv_label_set_text_fmt(r->rloc, "0x%04x", n->rloc16);
        int bars = n->avg_rssi >= -65 ? 3 : n->avg_rssi >= -80 ? 2 : 1;
        for (int b = 0; b < 3; b++) {
            lv_obj_set_style_bg_color(r->bars[b], lv_color_hex(b < bars ? C_LINK : C_BAR_OFF), 0);
        }
        lv_label_set_text(r->note, n->is_border_router ? "border router" : "");
        lv_label_set_text_fmt(r->rssi, "%d", n->avg_rssi);
    }
    if (st->neighbour_count == 0) {
        lv_obj_remove_flag(s_ui.neighbours.empty, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_add_flag(s_ui.neighbours.empty, LV_OBJ_FLAG_HIDDEN);
    }
    page_dots_set(&s_ui.neighbours.dots);
}

/* Network page: the LAN addresses, IPv4 and every IPv6 address with its kind */
static void create_network(void)
{
    lv_obj_t *scr = s_ui.network.screen = new_screen();
    s_ui.network.eth = header(scr, "NETWORK", true);
    for (int i = 0; i < 1 + BR_STATUS_MAX_IPV6; i++) {
        int y = 30 + i * 15 + (i > 0 ? 6 : 0); // a little gap between IPv4 and the IPv6 list
        s_ui.network.kind[i] = label(scr, &br_font_sans_9, C_LABEL, 12, y + 1, "");
        lv_obj_set_style_text_letter_space(s_ui.network.kind[i], 1, 0);
        s_ui.network.addr[i] = label(scr, &br_font_mono_9, C_TEXT, 62, y, "");
        lv_obj_set_width(s_ui.network.addr[i], BR_UI_WIDTH - 62 - 12);
        lv_label_set_long_mode(s_ui.network.addr[i], LV_LABEL_LONG_DOT);
    }
    lv_label_set_text(s_ui.network.kind[0], "IPv4");

    page_dots_create(scr, &s_ui.network.dots);
    softkeys_create(scr, &s_ui.network.keys);
    softkeys_set(&s_ui.network.keys, "", "HOME", "< PREV", "NEXT >");
}

static void update_network(const br_status_t *st)
{
    static const char *const KIND[] = {[BR_IP6_LINK_LOCAL] = "LINK", [BR_IP6_ULA] = "ULA",
                                       [BR_IP6_GLOBAL] = "GLOBAL", [BR_IP6_OTHER] = "IPv6"};
    set_eth_label(s_ui.network.eth, st, false);
    lv_label_set_text(s_ui.network.addr[0], st->ipv4[0] ? st->ipv4 : "-");
    for (int i = 0; i < BR_STATUS_MAX_IPV6; i++) {
        lv_obj_t *k = s_ui.network.kind[1 + i], *a = s_ui.network.addr[1 + i];
        if (i < st->ipv6_count) {
            lv_label_set_text(k, KIND[st->ipv6[i].kind]);
            lv_label_set_text(a, st->ipv6[i].addr);
        } else if (i == 0) {
            lv_label_set_text(k, "IPv6");
            lv_label_set_text(a, "-");
        } else {
            lv_label_set_text(k, "");
            lv_label_set_text(a, "");
        }
    }
    page_dots_set(&s_ui.network.dots);
}

/* Device page: what runs, and the factory reset by holding SELECT until the bar is full */
static lv_obj_t *info_row(lv_obj_t *scr, int y, const char *name)
{
    lv_obj_t *l = label(scr, &br_font_sans_9, C_LABEL, 12, y + 2, name);
    lv_obj_set_style_text_letter_space(l, 1, 0);
    lv_obj_t *v = label(scr, &br_font_mono_11, C_TEXT, 92, y, "");
    lv_obj_set_width(v, BR_UI_WIDTH - 92 - 12);
    lv_label_set_long_mode(v, LV_LABEL_LONG_DOT);
    return v;
}

#define HOLD_HINT "Hold SELECT until the bar is full: ebr leaves the Thread network and forgets its pairing. Remove it in the Home app too."

static void create_device(void)
{
    lv_obj_t *scr = s_ui.device.screen = new_screen();
    s_ui.device.eth = header(scr, "DEVICE", true);
    s_ui.device.firmware = info_row(scr, 30, "FIRMWARE");
    s_ui.device.paired = info_row(scr, 48, "PAIRED");
    s_ui.device.radio = info_row(scr, 66, "RADIO");
    s_ui.device.uptime = info_row(scr, 84, "UPTIME");

    box(scr, 12, 106, BR_UI_WIDTH - 24, 1, C_LINE);
    lv_obj_t *t = label(scr, &br_font_sans_semi_10, C_AMBER, 12, 114, "FACTORY RESET");
    lv_obj_set_style_text_letter_space(t, 1, 0);
    s_ui.device.hint = label(scr, &br_font_sans_11, C_BODY, 12, 130, HOLD_HINT);
    lv_obj_set_width(s_ui.device.hint, BR_UI_WIDTH - 24);
    lv_label_set_long_mode(s_ui.device.hint, LV_LABEL_LONG_WRAP);

    s_ui.device.bar = lv_bar_create(scr);
    lv_obj_set_pos(s_ui.device.bar, 12, 182);
    lv_obj_set_size(s_ui.device.bar, BR_UI_WIDTH - 24, 10);
    lv_bar_set_range(s_ui.device.bar, 0, 100);
    lv_obj_set_style_radius(s_ui.device.bar, 3, 0);
    lv_obj_set_style_bg_color(s_ui.device.bar, lv_color_hex(C_BAR_OFF), 0);
    lv_obj_set_style_bg_opa(s_ui.device.bar, LV_OPA_COVER, 0);
    lv_obj_set_style_radius(s_ui.device.bar, 3, LV_PART_INDICATOR);
    lv_obj_set_style_bg_color(s_ui.device.bar, lv_color_hex(C_AMBER), LV_PART_INDICATOR);

    page_dots_create(scr, &s_ui.device.dots);
    softkeys_create(scr, &s_ui.device.keys);
    softkeys_set(&s_ui.device.keys, "HOLD", "HOME", "< PREV", "NEXT >");
}

static void update_device(const br_status_t *st)
{
    set_eth_label(s_ui.device.eth, st, false);
    lv_label_set_text_fmt(s_ui.device.firmware, "ebr %s", st->firmware ? st->firmware : "-");
    if (st->has_dataset) {
        lv_label_set_text_fmt(s_ui.device.paired, "yes \xc2\xb7 %s", st->network_name);
    } else {
        lv_label_set_text(s_ui.device.paired, "no");
    }
    lv_label_set_text_fmt(s_ui.device.radio, "%s %s \xc2\xb7 BT %s", st->radio_chip ? st->radio_chip : "radio",
                          radio_text(st->radio), bt_text(st->bt));
    char up[16];
    format_uptime(up, sizeof(up), st->uptime_s);
    lv_label_set_text(s_ui.device.uptime, up);
    page_dots_set(&s_ui.device.dots);
}

bool br_ui_on_device_page(void)
{
    return s_ui.page == PAGE_DEVICE && s_ui.shown == s_ui.device.screen;
}

void br_ui_set_hold(int percent)
{
    if (!s_ui.device.bar) {
        return;
    }
    lv_bar_set_value(s_ui.device.bar, percent, LV_ANIM_OFF);
    if (percent >= 100) {
        lv_label_set_text(s_ui.device.hint, "Resetting \xe2\x80\xa6 ebr restarts and shows the pairing code.");
    } else if (percent > 0) {
        lv_label_set_text(s_ui.device.hint, "Keep holding \xe2\x80\xa6 release to cancel.");
    } else {
        lv_label_set_text(s_ui.device.hint, HOLD_HINT);
    }
}

static void show(lv_obj_t *screen)
{
    if (s_ui.shown != screen) {
        lv_screen_load(screen);
        s_ui.shown = screen;
    }
}

void br_ui_create(bool has_buttons)
{
    s_ui.has_buttons = has_buttons;
    create_status();
    create_nodataset();
    create_pairing();
    create_neighbours();
    create_network();
    create_device();
    br_status_t starting = {.role = BR_ROLE_STARTING};
    br_ui_update(&starting);
}

void br_ui_update(const br_status_t *st)
{
    if (st->attached && !st->has_dataset && st->pairing_qr) {
        update_pairing(st);
        show(s_ui.pairing.screen);
    } else if (st->attached && !st->has_dataset) {
        update_nodataset(st);
        show(s_ui.nodataset.screen);
    } else if (st->attached && s_ui.page == PAGE_NEIGHBOURS) {
        update_neighbours(st);
        show(s_ui.neighbours.screen);
    } else if (st->attached && s_ui.page == PAGE_NETWORK) {
        update_network(st);
        show(s_ui.network.screen);
    } else if (st->attached && s_ui.page == PAGE_DEVICE) {
        update_device(st);
        show(s_ui.device.screen);
    } else {
        update_status(st);
        show(s_ui.status.screen);
    }
}

void br_ui_key(br_key_t key)
{
    switch (key) {
    case BR_KEY_NEXT:
        s_ui.page = (s_ui.page + 1) % PAGES;
        break;
    case BR_KEY_PREV:
        s_ui.page = (s_ui.page + PAGES - 1) % PAGES;
        break;
    case BR_KEY_BACK:
        s_ui.page = 0;
        break;
    case BR_KEY_SELECT:
        // Screen actions: the device page's factory reset is a hold, polled in br_display.c (hold_tick); later dataset QR, credential sharing, Matter pairing window
        break;
    }
}
