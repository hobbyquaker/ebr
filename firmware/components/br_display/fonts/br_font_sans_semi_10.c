/*******************************************************************************
 * Size: 10 px
 * Bpp: 4
 * Opts: --no-compress --no-prefilter --bpp 4 --format lvgl --font IBMPlexSansCondensed-SemiBold.ttf --range 0x20-0x7E,0xB7,0x2013,0x2026,0x2212 --size 10 --lv-include lvgl.h --output br_font_sans_semi_10.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef BR_FONT_SANS_SEMI_10
#define BR_FONT_SANS_SEMI_10 1
#endif

#if BR_FONT_SANS_SEMI_10

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x3f, 0x13, 0xf0, 0x2f, 0x0, 0xd0, 0x6, 0x1,
    0x50, 0x3e, 0x10,

    /* U+0022 "\"" */
    0x5b, 0x6a, 0x5b, 0x6a, 0x59, 0x59,

    /* U+0023 "#" */
    0x2, 0xa0, 0xc0, 0x4, 0x70, 0xb0, 0x4d, 0xcb,
    0xd6, 0x9, 0x26, 0x60, 0x8e, 0xad, 0xb2, 0xc,
    0xb, 0x0, 0x1b, 0xc, 0x0,

    /* U+0024 "$" */
    0x0, 0x0, 0x0, 0x0, 0xc5, 0x0, 0x3e, 0xed,
    0x90, 0x7b, 0xa2, 0x0, 0x3e, 0xe7, 0x0, 0x0,
    0xbc, 0xc0, 0x12, 0xa4, 0xf0, 0x4e, 0xee, 0x80,
    0x0, 0xc4, 0x0,

    /* U+0025 "%" */
    0x2b, 0xb3, 0x5, 0xb0, 0x7, 0x86, 0x90, 0xd2,
    0x0, 0x69, 0x69, 0x97, 0x0, 0x1, 0xaa, 0x5d,
    0x5b, 0x80, 0x0, 0xc, 0x4d, 0x2d, 0x10, 0x6,
    0xa0, 0xe1, 0xd2, 0x1, 0xd1, 0x7, 0xaa, 0x0,

    /* U+0026 "&" */
    0x8, 0xed, 0x30, 0x0, 0xe3, 0x99, 0x0, 0x9,
    0xbd, 0x30, 0x0, 0xce, 0xa6, 0xf1, 0x6c, 0x1e,
    0xd6, 0x7, 0xd0, 0x7f, 0x40, 0x1c, 0xf9, 0x7e,
    0x10,

    /* U+0027 "'" */
    0x5b, 0x5b, 0x59,

    /* U+0028 "(" */
    0x6, 0xb0, 0x1e, 0x10, 0x5b, 0x0, 0x89, 0x0,
    0x98, 0x0, 0x7a, 0x0, 0x3e, 0x0, 0xb, 0x60,
    0x1, 0x60,

    /* U+0029 ")" */
    0xa, 0x70, 0x1, 0xe1, 0x0, 0xa6, 0x0, 0x88,
    0x0, 0x89, 0x0, 0x97, 0x0, 0xd3, 0x6, 0xb0,
    0x5, 0x10,

    /* U+002A "*" */
    0x0, 0xe0, 0x9, 0x9d, 0x8a, 0x6, 0xe8, 0x0,
    0xd2, 0xd1, 0x0, 0x0, 0x0,

    /* U+002B "+" */
    0x0, 0xd3, 0x0, 0xd, 0x30, 0x6e, 0xfe, 0xb0,
    0xd, 0x30, 0x0, 0x0, 0x0,

    /* U+002C "," */
    0x29, 0x3, 0xf0, 0x49, 0x0,

    /* U+002D "-" */
    0x7f, 0xf1, 0x12, 0x20,

    /* U+002E "." */
    0x16, 0x4, 0xe0,

    /* U+002F "/" */
    0x0, 0x78, 0x0, 0xc3, 0x1, 0xe0, 0x6, 0x90,
    0xb, 0x40, 0xe, 0x0, 0x5a, 0x0, 0xa5, 0x0,
    0x71, 0x0,

    /* U+0030 "0" */
    0xa, 0xfd, 0x20, 0x5d, 0x18, 0xb0, 0x8b, 0x4,
    0xf0, 0x9b, 0x4, 0xf0, 0x8b, 0x4, 0xf0, 0x5d,
    0x18, 0xb0, 0xa, 0xfd, 0x30,

    /* U+0031 "1" */
    0xb, 0xf9, 0x6, 0xca, 0x90, 0x1, 0xa9, 0x0,
    0xa, 0x90, 0x0, 0xa9, 0x0, 0xa, 0x90, 0x3f,
    0xff, 0xf0,

    /* U+0032 "2" */
    0xb, 0xfd, 0x35, 0xb0, 0xbb, 0x0, 0x9, 0xb0,
    0x2, 0xf4, 0x2, 0xe6, 0x2, 0xe6, 0x0, 0x7f,
    0xff, 0xe0,

    /* U+0033 "3" */
    0x1c, 0xfd, 0x23, 0x70, 0xc9, 0x0, 0xc, 0x80,
    0x3f, 0xd1, 0x0, 0xa, 0xa6, 0x60, 0xab, 0x3d,
    0xfc, 0x20,

    /* U+0034 "4" */
    0x0, 0x9f, 0x40, 0x1, 0xce, 0x40, 0x8, 0x5e,
    0x40, 0x1d, 0xe, 0x40, 0x77, 0xe, 0x40, 0xaf,
    0xff, 0xf1, 0x0, 0xe, 0x40,

    /* U+0035 "5" */
    0x2f, 0xff, 0xa0, 0x3d, 0x0, 0x0, 0x3c, 0x0,
    0x0, 0x4b, 0xce, 0x60, 0x15, 0x7, 0xf0, 0x27,
    0x6, 0xe0, 0x1b, 0xfe, 0x50,

    /* U+0036 "6" */
    0x1, 0xcc, 0x0, 0xb, 0xd0, 0x0, 0x3f, 0x30,
    0x0, 0x7d, 0xae, 0x70, 0x8d, 0x6, 0xf0, 0x6d,
    0x6, 0xf0, 0xa, 0xee, 0x50,

    /* U+0037 "7" */
    0x7f, 0xff, 0xe7, 0x90, 0x8b, 0x11, 0xd, 0x60,
    0x3, 0xf0, 0x0, 0x9a, 0x0, 0xe, 0x50, 0x5,
    0xf0, 0x0,

    /* U+0038 "8" */
    0xb, 0xfd, 0x40, 0x5d, 0x8, 0xc0, 0x4e, 0x8,
    0xa0, 0xb, 0xfe, 0x20, 0x7d, 0x7, 0xd0, 0x8d,
    0x6, 0xe0, 0x1c, 0xee, 0x50,

    /* U+0039 "9" */
    0xa, 0xfd, 0x37, 0xd0, 0x8c, 0x9a, 0x5, 0xf8,
    0xd0, 0x8e, 0x1c, 0xdb, 0x90, 0x2, 0xe2, 0x5,
    0xe4, 0x0,

    /* U+003A ":" */
    0x3e, 0x11, 0x60, 0x0, 0x1, 0x60, 0x3e, 0x10,

    /* U+003B ";" */
    0x3e, 0x11, 0x60, 0x0, 0x2, 0x90, 0x2f, 0x13,
    0x90,

    /* U+003C "<" */
    0x0, 0x0, 0x20, 0x3, 0xd7, 0x8, 0xe5, 0x1,
    0xf7, 0x0, 0x2, 0xbc, 0x20, 0x0, 0x67, 0x0,
    0x0, 0x0,

    /* U+003D "=" */
    0x6e, 0xee, 0xc0, 0x0, 0x0, 0x6e, 0xee, 0xc0,

    /* U+003E ">" */
    0x2, 0x0, 0x1, 0xe7, 0x0, 0x2, 0xbc, 0x20,
    0x3, 0xe6, 0x8, 0xe5, 0x1, 0xa1, 0x0, 0x0,
    0x0, 0x0,

    /* U+003F "?" */
    0x4e, 0xf9, 0x7, 0x53, 0xf2, 0x1, 0x7e, 0x0,
    0x8c, 0x20, 0x2, 0x30, 0x0, 0x33, 0x0, 0x9,
    0xb0, 0x0,

    /* U+0040 "@" */
    0x1, 0x9a, 0xaa, 0x30, 0xb, 0x20, 0x1, 0xc1,
    0x48, 0x4d, 0xaa, 0x57, 0x75, 0xa5, 0x5a, 0x39,
    0x76, 0xa5, 0x5a, 0x47, 0x39, 0x3c, 0x7b, 0xa1,
    0xa, 0x50, 0x0, 0x0, 0x0, 0x7a, 0xaa, 0x0,

    /* U+0041 "A" */
    0x0, 0xef, 0x0, 0x3, 0xdd, 0x30, 0x7, 0x99,
    0x80, 0xc, 0x55, 0xd0, 0x1f, 0xff, 0xf2, 0x5c,
    0x0, 0xb6, 0xa8, 0x0, 0x7b,

    /* U+0042 "B" */
    0x4f, 0xff, 0xc0, 0x4f, 0x1, 0xf4, 0x4f, 0x1,
    0xf3, 0x4f, 0xff, 0xb0, 0x4f, 0x0, 0xc7, 0x4f,
    0x0, 0xd8, 0x4f, 0xff, 0xd1,

    /* U+0043 "C" */
    0x5, 0xdf, 0xa0, 0x2f, 0x41, 0xc4, 0x7d, 0x0,
    0x0, 0x8c, 0x0, 0x0, 0x7d, 0x0, 0x0, 0x2f,
    0x31, 0xc4, 0x6, 0xef, 0xa0,

    /* U+0044 "D" */
    0x4f, 0xfe, 0x90, 0x4f, 0x1, 0xd6, 0x4f, 0x0,
    0x9b, 0x4f, 0x0, 0x8c, 0x4f, 0x0, 0x9b, 0x4f,
    0x1, 0xd6, 0x4f, 0xfe, 0x90,

    /* U+0045 "E" */
    0x4f, 0xff, 0xe4, 0xf0, 0x0, 0x4f, 0x0, 0x4,
    0xff, 0xf8, 0x4f, 0x0, 0x4, 0xf0, 0x0, 0x4f,
    0xff, 0xe0,

    /* U+0046 "F" */
    0x4f, 0xff, 0xd4, 0xf0, 0x0, 0x4f, 0x0, 0x4,
    0xff, 0xf7, 0x4f, 0x0, 0x4, 0xf0, 0x0, 0x4f,
    0x0, 0x0,

    /* U+0047 "G" */
    0x5, 0xdf, 0xb1, 0x2f, 0x41, 0xa5, 0x7d, 0x0,
    0x0, 0x8c, 0x9, 0xfc, 0x6d, 0x0, 0x6c, 0x2f,
    0x31, 0xbc, 0x6, 0xee, 0x8c,

    /* U+0048 "H" */
    0x4f, 0x0, 0x7c, 0x4f, 0x0, 0x7c, 0x4f, 0x0,
    0x7c, 0x4f, 0xff, 0xfc, 0x4f, 0x0, 0x7c, 0x4f,
    0x0, 0x7c, 0x4f, 0x0, 0x7c,

    /* U+0049 "I" */
    0x7f, 0xf5, 0xb, 0x90, 0xb, 0x90, 0xb, 0x90,
    0xb, 0x90, 0xb, 0x90, 0x7f, 0xf5,

    /* U+004A "J" */
    0xe, 0xff, 0x40, 0x0, 0xf4, 0x0, 0xf, 0x40,
    0x0, 0xf4, 0x0, 0xf, 0x48, 0x82, 0xf3, 0x3d,
    0xf9, 0x0,

    /* U+004B "K" */
    0x4f, 0x0, 0xd7, 0x4, 0xf0, 0x8c, 0x0, 0x4f,
    0x3f, 0x20, 0x4, 0xfc, 0xe0, 0x0, 0x4f, 0x7d,
    0x80, 0x4, 0xf0, 0x5f, 0x20, 0x4f, 0x0, 0xbb,
    0x0,

    /* U+004C "L" */
    0x4f, 0x0, 0x4, 0xf0, 0x0, 0x4f, 0x0, 0x4,
    0xf0, 0x0, 0x4f, 0x0, 0x4, 0xf0, 0x0, 0x4f,
    0xff, 0x70,

    /* U+004D "M" */
    0x4f, 0x50, 0xe, 0xa4, 0xfc, 0x6, 0xfa, 0x4e,
    0xb3, 0xd9, 0xa4, 0xe4, 0xca, 0x8a, 0x4e, 0xd,
    0x38, 0xa4, 0xe0, 0x20, 0x8a, 0x4e, 0x0, 0x8,
    0xa0,

    /* U+004E "N" */
    0x4f, 0x50, 0x6c, 0x4f, 0xd0, 0x6c, 0x4e, 0xb4,
    0x6c, 0x4e, 0x4c, 0x6c, 0x4e, 0xc, 0x9c, 0x4e,
    0x5, 0xfc, 0x4e, 0x0, 0xdc,

    /* U+004F "O" */
    0x6, 0xdf, 0xa0, 0x2f, 0x41, 0xc8, 0x6d, 0x0,
    0x6d, 0x8c, 0x0, 0x6e, 0x6d, 0x0, 0x6d, 0x2f,
    0x41, 0xc8, 0x6, 0xef, 0xa0,

    /* U+0050 "P" */
    0x4f, 0xff, 0xc0, 0x4f, 0x0, 0xe6, 0x4f, 0x0,
    0xe6, 0x4f, 0xef, 0xd1, 0x4f, 0x11, 0x0, 0x4f,
    0x0, 0x0, 0x4f, 0x0, 0x0,

    /* U+0051 "Q" */
    0x5, 0xdf, 0xa0, 0x2f, 0x41, 0xc8, 0x6d, 0x0,
    0x6d, 0x8c, 0x0, 0x6e, 0x7c, 0x0, 0x6d, 0x4f,
    0x10, 0x9a, 0xb, 0xed, 0xf3, 0x0, 0x7e, 0x10,
    0x0, 0x2e, 0xc0,

    /* U+0052 "R" */
    0x4f, 0xff, 0xc1, 0x4f, 0x0, 0xe6, 0x4f, 0x0,
    0xe6, 0x4f, 0xff, 0xc1, 0x4f, 0xb, 0x80, 0x4f,
    0x5, 0xe0, 0x4f, 0x0, 0xe5,

    /* U+0053 "S" */
    0xb, 0xfd, 0x70, 0x6e, 0x13, 0x60, 0x6e, 0x40,
    0x0, 0x9, 0xff, 0x70, 0x0, 0x6, 0xf0, 0x47,
    0x6, 0xf0, 0x2c, 0xfd, 0x50,

    /* U+0054 "T" */
    0xcf, 0xff, 0xf0, 0xf, 0x30, 0x0, 0xf3, 0x0,
    0xf, 0x30, 0x0, 0xf3, 0x0, 0xf, 0x30, 0x0,
    0xf3, 0x0,

    /* U+0055 "U" */
    0x5f, 0x0, 0xb9, 0x5f, 0x0, 0xb9, 0x5f, 0x0,
    0xb9, 0x5f, 0x0, 0xb9, 0x4f, 0x0, 0xb8, 0x2f,
    0x31, 0xe6, 0x8, 0xef, 0xa0,

    /* U+0056 "V" */
    0xb9, 0x0, 0xb8, 0x6d, 0x0, 0xf4, 0x2f, 0x13,
    0xf0, 0xd, 0x57, 0xa0, 0x8, 0x9b, 0x60, 0x4,
    0xce, 0x10, 0x0, 0xfd, 0x0,

    /* U+0057 "W" */
    0xa9, 0x7, 0xf2, 0xe, 0x47, 0xc0, 0xac, 0x51,
    0xf0, 0x3e, 0xe, 0x88, 0x4d, 0x0, 0xf3, 0xe4,
    0xc7, 0x90, 0xd, 0x8a, 0x1e, 0x96, 0x0, 0x9d,
    0x70, 0xdd, 0x30, 0x6, 0xf4, 0xa, 0xf0, 0x0,

    /* U+0058 "X" */
    0x7e, 0x0, 0xd7, 0x1f, 0x54, 0xe0, 0x8, 0xbb,
    0x70, 0x1, 0xfe, 0x0, 0x3, 0xff, 0x20, 0xd,
    0x69, 0xc0, 0x8c, 0x1, 0xe7,

    /* U+0059 "Y" */
    0xba, 0x0, 0xe5, 0x3f, 0x15, 0xd0, 0xc, 0x7c,
    0x60, 0x4, 0xee, 0x0, 0x0, 0xd8, 0x0, 0x0,
    0xc7, 0x0, 0x0, 0xc7, 0x0,

    /* U+005A "Z" */
    0x7f, 0xff, 0xf0, 0x0, 0xc, 0xa0, 0x0, 0x6e,
    0x10, 0x1, 0xf5, 0x0, 0xb, 0xb0, 0x0, 0x5f,
    0x20, 0x0, 0xaf, 0xff, 0xf1,

    /* U+005B "[" */
    0x4f, 0x64, 0xc0, 0x4c, 0x4, 0xc0, 0x4c, 0x4,
    0xc0, 0x4c, 0x3, 0xe6,

    /* U+005C "\\" */
    0x87, 0x0, 0x3c, 0x0, 0xe, 0x10, 0x9, 0x60,
    0x4, 0xb0, 0x0, 0xe0, 0x0, 0xa5, 0x0, 0x5a,
    0x0, 0x17,

    /* U+005D "]" */
    0x6f, 0x40, 0xc4, 0xc, 0x40, 0xc4, 0xc, 0x40,
    0xc4, 0xc, 0x46, 0xe3,

    /* U+005E "^" */
    0x2, 0xf8, 0x0, 0xa, 0x8e, 0x10, 0x3e, 0x9,
    0x90, 0x45, 0x1, 0x90,

    /* U+005F "_" */
    0xbf, 0xff, 0xb0,

    /* U+0060 "`" */
    0x14, 0x3, 0xe0, 0x5, 0x10,

    /* U+0061 "a" */
    0x2c, 0xeb, 0x1, 0x30, 0xf4, 0x2b, 0xbf, 0x5a,
    0x90, 0xe5, 0x5e, 0x9a, 0xc0,

    /* U+0062 "b" */
    0x5e, 0x0, 0x0, 0x5e, 0x0, 0x0, 0x5e, 0xbe,
    0x60, 0x5f, 0x6, 0xe0, 0x5e, 0x3, 0xf0, 0x5e,
    0x6, 0xe0, 0x5e, 0xaf, 0x60,

    /* U+0063 "c" */
    0x1b, 0xfc, 0x18, 0xc0, 0x61, 0xa9, 0x0, 0x8,
    0xb0, 0x61, 0x1c, 0xfc, 0x10,

    /* U+0064 "d" */
    0x0, 0x7, 0xc0, 0x0, 0x7c, 0x1c, 0xeb, 0xc7,
    0xd0, 0x8c, 0x9a, 0x7, 0xc7, 0xd0, 0x8c, 0x1c,
    0xe9, 0xc0,

    /* U+0065 "e" */
    0x1b, 0xec, 0x18, 0xb0, 0xa8, 0x9e, 0xbc, 0x97,
    0xb0, 0x31, 0xb, 0xec, 0x30,

    /* U+0066 "f" */
    0xc, 0xe1, 0x1f, 0x20, 0xbf, 0xe1, 0x1f, 0x20,
    0x1f, 0x20, 0x1f, 0x20, 0x1f, 0x20,

    /* U+0067 "g" */
    0x0, 0x8, 0x92, 0xdd, 0xe1, 0x7b, 0xd, 0x51,
    0xdd, 0xa0, 0x67, 0x0, 0x3, 0xff, 0xf8, 0x94,
    0x5, 0xe6, 0xdc, 0xd6,

    /* U+0068 "h" */
    0x5e, 0x0, 0x5, 0xe0, 0x0, 0x5e, 0xae, 0x45,
    0xf1, 0xaa, 0x5e, 0x7, 0xb5, 0xe0, 0x7b, 0x5e,
    0x7, 0xb0,

    /* U+0069 "i" */
    0x5d, 0x13, 0x5e, 0x5e, 0x5e, 0x5e, 0x5e,

    /* U+006A "j" */
    0x5, 0xe0, 0x1, 0x30, 0x5, 0xe0, 0x5, 0xe0,
    0x5, 0xe0, 0x5, 0xe0, 0x5, 0xe0, 0x5, 0xe0,
    0xe, 0xa0,

    /* U+006B "k" */
    0x5e, 0x0, 0x0, 0x5e, 0x0, 0x0, 0x5e, 0xc,
    0x80, 0x5d, 0x8b, 0x0, 0x5f, 0xf9, 0x0, 0x5e,
    0x2f, 0x20, 0x5e, 0x9, 0xc0,

    /* U+006C "l" */
    0x5e, 0x5, 0xe0, 0x5e, 0x5, 0xe0, 0x5e, 0x5,
    0xe0, 0x2e, 0x60,

    /* U+006D "m" */
    0x5e, 0x9e, 0x6c, 0xd1, 0x5e, 0xa, 0xb0, 0xe6,
    0x5e, 0x9, 0xa0, 0xc6, 0x5e, 0x9, 0xa0, 0xc6,
    0x5e, 0x9, 0xa0, 0xc6,

    /* U+006E "n" */
    0x5e, 0x9e, 0x45, 0xe0, 0x9a, 0x5e, 0x7, 0xb5,
    0xe0, 0x7b, 0x5e, 0x7, 0xb0,

    /* U+006F "o" */
    0x1b, 0xfc, 0x18, 0xc0, 0xb8, 0xa9, 0x8, 0xa8,
    0xb0, 0xb8, 0x1b, 0xec, 0x10,

    /* U+0070 "p" */
    0x5e, 0x8e, 0x60, 0x5e, 0x5, 0xe0, 0x5e, 0x3,
    0xf0, 0x5f, 0x6, 0xe0, 0x5e, 0xbe, 0x60, 0x5e,
    0x0, 0x0, 0x5e, 0x0, 0x0,

    /* U+0071 "q" */
    0x1c, 0xe9, 0xc7, 0xd0, 0x8c, 0x9a, 0x7, 0xc7,
    0xd0, 0x8c, 0x1c, 0xeb, 0xc0, 0x0, 0x7c, 0x0,
    0x7, 0xc0,

    /* U+0072 "r" */
    0x5e, 0xb6, 0x5f, 0x41, 0x5e, 0x0, 0x5e, 0x0,
    0x5e, 0x0,

    /* U+0073 "s" */
    0x3d, 0xea, 0x8, 0xb0, 0x20, 0x2c, 0xe9, 0x2,
    0x21, 0xf1, 0x4d, 0xea, 0x0,

    /* U+0074 "t" */
    0xf, 0x20, 0xbf, 0xe0, 0x1f, 0x20, 0x1f, 0x20,
    0x1f, 0x20, 0xd, 0xe0,

    /* U+0075 "u" */
    0x6d, 0x8, 0xa6, 0xd0, 0x8a, 0x6d, 0x8, 0xa5,
    0xe0, 0xaa, 0x1d, 0xda, 0xa0,

    /* U+0076 "v" */
    0xc6, 0xa, 0x87, 0xb0, 0xe3, 0x2f, 0x3e, 0x0,
    0xda, 0x90, 0x8, 0xf4, 0x0,

    /* U+0077 "w" */
    0xb7, 0xf, 0x70, 0xf1, 0x7a, 0x4b, 0xb3, 0xd0,
    0x3e, 0x76, 0xe6, 0x90, 0xe, 0xb2, 0xcb, 0x50,
    0xb, 0xe0, 0x8f, 0x10,

    /* U+0078 "x" */
    0x8b, 0xc, 0x71, 0xe6, 0xe0, 0x7, 0xf6, 0x0,
    0xce, 0xa0, 0x7b, 0xd, 0x60,

    /* U+0079 "y" */
    0xc7, 0x9, 0x97, 0xb0, 0xe3, 0x1f, 0x3e, 0x0,
    0xca, 0x90, 0x7, 0xf4, 0x0, 0x4e, 0x0, 0x6e,
    0x70, 0x0,

    /* U+007A "z" */
    0x8e, 0xef, 0x10, 0xb, 0xa0, 0x7, 0xd0, 0x3,
    0xf2, 0x0, 0xaf, 0xee, 0x20,

    /* U+007B "{" */
    0xc, 0xb0, 0xf2, 0xf, 0x21, 0xf1, 0xc8, 0x1,
    0xf1, 0xf, 0x20, 0xf2, 0xa, 0xa0,

    /* U+007C "|" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x51,

    /* U+007D "}" */
    0x7e, 0x10, 0xd, 0x30, 0xd, 0x30, 0xc, 0x50,
    0x4, 0xe1, 0xc, 0x50, 0xd, 0x30, 0xd, 0x30,
    0x7d, 0x10,

    /* U+007E "~" */
    0x3d, 0xa2, 0x31, 0x6, 0xe8,

    /* U+00B7 "·" */
    0x0, 0x1, 0xf4, 0x3, 0x0,

    /* U+2013 "–" */
    0xaf, 0xff, 0xe0,

    /* U+2026 "…" */
    0x16, 0x4, 0x30, 0x60, 0x4e, 0xa, 0x92, 0xe3,

    /* U+2212 "−" */
    0x4c, 0xcc, 0xb1, 0x33, 0x32
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 34, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 45, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 11, .adv_w = 69, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 17, .adv_w = 93, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 85, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 65, .adv_w = 139, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 103, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 38, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 125, .adv_w = 48, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 143, .adv_w = 48, .box_w = 4, .box_h = 9, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 161, .adv_w = 82, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 174, .adv_w = 86, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 44, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 192, .adv_w = 58, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 196, .adv_w = 44, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 64, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 217, .adv_w = 86, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 86, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 86, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 274, .adv_w = 86, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 86, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 86, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 86, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 355, .adv_w = 86, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 86, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 86, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 412, .adv_w = 45, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 420, .adv_w = 45, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 429, .adv_w = 86, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 447, .adv_w = 86, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 455, .adv_w = 86, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 473, .adv_w = 72, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 491, .adv_w = 130, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 523, .adv_w = 97, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 544, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 93, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 586, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 625, .adv_w = 84, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 103, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 104, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 62, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 79, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 98, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 742, .adv_w = 76, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 760, .adv_w = 118, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 785, .adv_w = 104, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 103, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 827, .adv_w = 93, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 848, .adv_w = 103, .box_w = 6, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 875, .adv_w = 96, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 896, .adv_w = 87, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 917, .adv_w = 84, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 935, .adv_w = 100, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 956, .adv_w = 93, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 977, .adv_w = 138, .box_w = 9, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1009, .adv_w = 95, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1030, .adv_w = 91, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1051, .adv_w = 86, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1072, .adv_w = 48, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1084, .adv_w = 64, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1102, .adv_w = 48, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1114, .adv_w = 86, .box_w = 6, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 1126, .adv_w = 80, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1129, .adv_w = 86, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 1134, .adv_w = 81, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1147, .adv_w = 87, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1168, .adv_w = 74, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1181, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1199, .adv_w = 81, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1212, .adv_w = 52, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1226, .adv_w = 79, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1246, .adv_w = 85, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1264, .adv_w = 40, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1271, .adv_w = 41, .box_w = 4, .box_h = 9, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 1289, .adv_w = 82, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1310, .adv_w = 43, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1321, .adv_w = 128, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1341, .adv_w = 85, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1354, .adv_w = 81, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1367, .adv_w = 87, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1388, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1406, .adv_w = 57, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1416, .adv_w = 72, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1429, .adv_w = 53, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1441, .adv_w = 85, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1454, .adv_w = 76, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1467, .adv_w = 118, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1487, .adv_w = 78, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1500, .adv_w = 77, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1518, .adv_w = 72, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1531, .adv_w = 53, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1545, .adv_w = 55, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1554, .adv_w = 53, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1572, .adv_w = 86, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1577, .adv_w = 51, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1582, .adv_w = 84, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1585, .adv_w = 126, .box_w = 8, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1593, .adv_w = 86, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x1f5c, 0x1f6f, 0x215b
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 183, .range_length = 8540, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 1, 0, 0, 2, 3,
    1, 4, 0, 1, 0, 5, 6, 5,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 8, 8, 0, 0, 0,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 0, 18, 19, 20, 21, 0, 0,
    22, 23, 22, 24, 25, 26, 27, 28,
    29, 30, 31, 32, 33, 0, 0, 0,
    34, 0, 35, 36, 37, 0, 38, 39,
    40, 41, 42, 43, 44, 45, 41, 41,
    46, 36, 47, 48, 49, 50, 51, 52,
    53, 54, 55, 56, 33, 0, 0, 0,
    0, 6, 5, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 2, 0, 0, 0, 3,
    2, 0, 4, 2, 0, 5, 6, 5,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 8, 8, 0, 0, 0,
    9, 10, 11, 0, 12, 0, 0, 0,
    12, 0, 13, 14, 0, 0, 0, 0,
    12, 0, 12, 0, 15, 16, 17, 18,
    19, 20, 21, 22, 0, 0, 23, 0,
    24, 0, 25, 26, 27, 28, 27, 29,
    30, 26, 31, 32, 26, 33, 34, 34,
    27, 35, 28, 34, 36, 37, 38, 39,
    40, 41, 42, 43, 0, 0, 23, 0,
    0, 6, 5, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, -14, 0, 0, 0,
    0, 0, -8, -2, 0, -6, 0, 3,
    0, 2, 3, 0, 1, 0, 0, 0,
    0, 0, -3, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 3,
    0, 3, 1, 0, -10, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, -1, -7, 0, -5,
    -3, 0, -9, -1, 0, 0, 1, 0,
    1, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -2, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 3, 3, 1, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 3, 0,
    10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -14, 0, 0,
    0, 0, 0, 0, -13, 0, 3, -7,
    0, 1, 0, -14, -6, -10, -7, 2,
    -14, 5, 0, 0, 1, 0, -3, -3,
    -3, 0, 0, 0, 0, 0, 0, 0,
    -4, -2, -10, -8, 0, -7, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 2, -5, -3, -3, -7, 0,
    -6, -3, -7, -10, -4, 0, 0, 0,
    0, 2, 2, 0, 0, 0, -1, 0,
    0, 0, 1, 0, 0, -1, 0, -6,
    -1, -3, 0, 0, 0, 0, 0, 0,
    -27, 0, 0, 0, -13, -5, 0, -5,
    -3, 3, 0, 2, 1, 0, 2, 0,
    0, 0, -7, 0, -6, -6, 0, -6,
    -1, -1, 0, -1, 0, -1, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, -4, -1,
    -2, -8, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -19, 0, 0, 0,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, 2, 3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -4, 0, -3,
    -3, -1, -5, 0, -5, -3, -6, -6,
    -2, 0, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, -3, -1, -1, 0, -8,
    -1, 0, 3, -3, 0, 0, -8, -3,
    1, -3, 0, 0, 0, -9, -3, -8,
    -4, 1, -11, 0, 0, 3, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, -4, -3, 0, -2,
    2, 0, 0, 0, 0, -3, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, -3, -1, -3, -3, 0, 0,
    -10, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, -2, -1, 0, 0, 0, -1, 0,
    0, -2, -2, 0, 0, -2, -1, -1,
    0, 0, 0, 0, 0, 0, 0, -3,
    -1, 0, 0, -8, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, -7, 2, -7, 0, 0,
    0, -5, 0, 0, -1, 0, -4, 0,
    -4, -3, -4, -5, -2, 0, -4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -2, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, -6,
    2, -16, 0, -12, 0, 0, -4, -11,
    -4, 0, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -22, -6, 0, -5,
    -5, -1, -7, 0, -2, 0, -4, -4,
    -4, -2, -4, -3, -2, -6, -3, -3,
    0, -2, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, 0, -4,
    0, -4, -2, -1, -6, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, 0, 0, 0, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, -1, 0,
    0, 0, 0, 0, 0, 0, -1, 0,
    0, -1, 0, 0, -1, 0, 0, 0,
    0, 0, -4, 0, -5, 0, 0, 0,
    -3, 0, 0, -1, 0, 0, 0, 0,
    0, -2, 0, 0, 0, -13, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, -4, 2, 2, -9, 0,
    0, 0, -5, 0, -5, 0, -3, -1,
    -4, 0, -3, -1, 0, -3, 0, 0,
    0, -1, 0, -4, -4, -3, -1, 0,
    0, -1, -2, -2, 0, -4, -3, -3,
    -3, -1, -3, 2, 0, -12, -1, 0,
    3, -6, 2, 0, -9, -2, 1, -6,
    0, 0, 0, -11, -3, -8, -6, 0,
    -13, 1, 0, 4, 1, 0, -1, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, -1, -6, -5, 2, -5, 2, 0,
    -2, -1, 0, -7, 2, -7, 0, 0,
    0, -3, 0, 0, -1, 0, -4, 0,
    -4, -3, -4, -6, -2, 0, -16, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, -5, 0, -17, 0,
    -13, 0, 1, -1, -10, 0, 0, -8,
    -1, 0, 0, 0, -1, -4, -3, -4,
    0, -24, -2, 0, -3, -3, 1, -4,
    0, 0, 0, -2, -2, -2, 1, 0,
    1, 0, 0, 1, 0, 0, 0, -4,
    0, -1, -3, -3, 0, 0, -3, 0,
    -1, 0, -2, 0, -2, -2, -2, -1,
    0, -4, 0, 0, 0, -2, 0, -1,
    -1, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, -1, 2, -5, 0,
    0, 0, 0, 0, 0, 0, -1, -2,
    0, -1, -1, 0, -2, 0, 0, -9,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 3, -5, 3, -14,
    -7, -15, -6, 2, -5, -9, -4, 0,
    -7, -2, 3, 0, 1, 1, 0, 2,
    0, 0, -13, -10, 0, -9, -9, -2,
    -11, 0, 0, 0, -7, -7, -10, 0,
    -7, -4, -6, -5, -4, -8, 0, 0,
    -1, 0, -6, 0, -6, 0, 0, 0,
    -3, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -11, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, -6, 3, -10, -6, -10,
    -4, 3, -5, -8, -4, 0, -6, -3,
    1, 0, 1, 0, 0, 1, -1, 0,
    -15, -5, 0, -5, -5, 0, -7, 0,
    -1, 0, -3, -3, -4, 0, -4, -2,
    -2, -2, -1, -2, 0, 3, -5, 3,
    -7, -3, -7, -1, 1, -3, -4, -3,
    0, -4, 0, 1, 0, 0, 0, 0,
    0, -1, 0, -11, -4, 0, -4, -4,
    0, -4, 0, -1, 0, -2, -1, -2,
    0, -1, 0, -1, -1, 0, -3, 0,
    0, -4, 1, 2, -7, 0, -2, -1,
    -5, 1, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 3, -1,
    0, -2, -2, 0, 0, 0, 0, 0,
    0, 0, -1, -3, -3, -2, -3, 0,
    -1, 2, 0, 1, -8, 3, -14, -10,
    -15, -8, 1, -6, -11, -6, 0, -6,
    -6, 1, 0, 0, 0, 0, 1, 0,
    0, -16, -9, -1, -8, -8, -3, -9,
    -2, -2, 0, -7, -8, -8, -3, -6,
    -4, -3, -6, -5, -7, 0, 1, -2,
    1, 4, -7, 0, 0, 0, -3, 0,
    -3, 0, -1, 0, 0, 0, -1, -1,
    0, -1, 0, 0, 3, 0, 0, -1,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 3, -16, 0,
    -7, -8, -13, -11, -15, -11, 3, -16,
    4, 0, 0, -5, 0, -10, -7, -4,
    6, 0, 9, -8, 0, 2, -6, -9,
    -6, -11, -7, 3, -1, 1, 0, -4,
    0, 0, 2, -1, 4, 0, 0, 0,
    2, 0, 0, 1, 0, -11, 0, -6,
    -3, 0, -9, 1, 0, 2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, -2, -1, 0, -1,
    0, 0, -3, 0, 0, -3, 2, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    -11, 0, -5, -4, -3, -9, -1, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, -2, -1, -1, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, 0,
    0, 1, 0, -7, 0, -4, -1, 0,
    -7, 1, 0, -6, 0, 0, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, -3, 2, 0, 0, 0,
    0, 0, 0, -1, 0, -2, -9, 0,
    -5, -3, -3, -9, -1, 0, -9, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, -2,
    -1, -1, 0, 5, -2, 4, -8, 0,
    -4, 0, 5, 0, -2, 2, 0, -4,
    0, 4, 0, 5, 4, 2, 5, 0,
    2, -9, 0, 0, -1, -1, 0, -1,
    2, 0, 0, 0, 0, 0, 0, 0,
    2, 0, 0, 2, 0, 0, 1, -1,
    4, 0, 0, 5, 0, 0, 0, 4,
    0, 0, -1, 0, 0, 0, -1, 0,
    1, -1, 2, 2, 9, 0, 0, -1,
    -1, 0, 2, 0, 4, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 1, 0,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -9,
    0, -5, -4, 0, -9, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, 0, -4,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -7, 0,
    0, 0, -2, 2, -2, 0, 0, -1,
    -4, 0, -3, -1, 0, -7, 3, 0,
    4, 0, 0, -1, -1, 0, 0, 0,
    0, 0, 0, 0, -1, -1, -2, -2,
    -1, 0, -1, 0, 0, 0, 0, 0,
    1, -2, 0, 0, 0, 0, 4, 0,
    0, 2, 0, -2, 0, -1, 0, 2,
    -2, 2, 0, 4, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    -1, 0, 0, 0, 0, -1, 1, 0,
    -3, 0, 0, -3, 2, 0, 0, 0,
    0, 0, 0, -1, 0, 0, -9, 0,
    -5, -4, -3, -9, -1, 0, -9, 0,
    0, 0, 0, -1, 0, 0, 0, 0,
    0, 0, 0, -1, 0, -1, -1, -2,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -1, 0, -4, -2, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 5, -4,
    0, -13, 0, -5, 0, 0, 0, -6,
    2, 0, -3, 1, -1, 0, 0, 1,
    -3, -3, -2, 0, -12, -1, 0, -1,
    0, 2, -1, 0, 0, 0, 0, 0,
    0, 1, 0, 2, 1, 0, 2, 0,
    0, -2, 0, 0, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -9,
    0, -5, 0, -3, -8, 0, 0, -7,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, 0, 0, -2, -1,
    -1, -1, -1, 0, 0, -1, 0, 0,
    -2, 0, 0, 0, 0, 2, 0, 0,
    0, 0, -4, 0, 0, 0, 0, -3,
    0, 0, 3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, -4,
    -1, 0, -8, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, -3, 0, -10, -1, -2,
    0, 0, 0, -4, 0, -1, -3, 0,
    -3, 0, -2, 0, 0, -2, 0, 0,
    -11, -1, 0, -1, -1, 1, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 3, -3, 0,
    -8, 0, 0, 0, 0, -1, -3, 0,
    0, -3, 0, -6, 0, -2, -1, 0,
    -5, 0, 0, -7, -2, 0, -1, -1,
    0, -3, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -4, 0, 0, -6, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, -6, 0,
    -2, -1, 0, -4, 0, 0, 3, 0,
    0, -2, -2, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 3, -5, 0, -10, -1,
    -2, 0, 0, -1, -5, 0, -1, -3,
    0, -4, 0, -2, 0, 0, 0, 0,
    0, -12, -2, 0, -1, -1, 1, -4,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 1, -1,
    0, 2, -3, 0, 0, 0, -1, 2,
    0, 0, 0, 0, -6, 0, -1, 0,
    2, -3, 0, 0, 1, 0, 0, -1,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 56,
    .right_class_cnt     = 43,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 4,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t br_font_sans_semi_10 = {
#else
lv_font_t br_font_sans_semi_10 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if BR_FONT_SANS_SEMI_10*/

