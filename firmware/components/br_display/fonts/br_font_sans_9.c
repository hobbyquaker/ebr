/*******************************************************************************
 * Size: 9 px
 * Bpp: 4
 * Opts: --no-compress --no-prefilter --bpp 4 --format lvgl --font IBMPlexSansCondensed-Regular.ttf --range 0x20-0x7E,0xB7,0x2013,0x2026,0x2212 --size 9 --lv-include lvgl.h --output br_font_sans_9.c
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef BR_FONT_SANS_9
#define BR_FONT_SANS_9 1
#endif

#if BR_FONT_SANS_9

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0x38, 0x38, 0x27, 0x16, 0x5, 0x0, 0x49,

    /* U+0022 "\"" */
    0x54, 0x95, 0x49, 0x32, 0x60,

    /* U+0023 "#" */
    0x0, 0x81, 0x60, 0x0, 0x73, 0x40, 0x19, 0xaa,
    0x91, 0x5, 0x37, 0x0, 0x4b, 0x8c, 0x70, 0x8,
    0x8, 0x0, 0x8, 0x8, 0x0,

    /* U+0024 "$" */
    0x1, 0xa0, 0x2, 0xbb, 0xb1, 0x55, 0x80, 0x1,
    0xbb, 0x10, 0x0, 0xab, 0x20, 0x8, 0x45, 0x4a,
    0xbb, 0x20, 0xa, 0x10,

    /* U+0025 "%" */
    0x28, 0x80, 0xa, 0x0, 0x72, 0x81, 0x73, 0x0,
    0x62, 0x81, 0x90, 0x0, 0x18, 0x68, 0x38, 0x50,
    0x0, 0x28, 0x81, 0x90, 0x0, 0x90, 0x80, 0x90,
    0x4, 0x60, 0x37, 0x70,

    /* U+0026 "&" */
    0x9, 0xa7, 0x0, 0xa, 0xa, 0x0, 0x9, 0x76,
    0x0, 0x9, 0xb0, 0xa2, 0x56, 0x39, 0x80, 0x55,
    0x9, 0x70, 0xa, 0x95, 0xb2,

    /* U+0027 "'" */
    0x54, 0x54, 0x32,

    /* U+0028 "(" */
    0x4, 0x50, 0x90, 0x27, 0x4, 0x50, 0x54, 0x3,
    0x50, 0x9, 0x0, 0x81, 0x0, 0x40,

    /* U+0029 ")" */
    0x9, 0x10, 0x1, 0x80, 0x0, 0x90, 0x0, 0x90,
    0x0, 0x90, 0x0, 0x90, 0x0, 0x90, 0x5, 0x40,
    0x5, 0x0,

    /* U+002A "*" */
    0x6, 0x20, 0x6b, 0x93, 0x18, 0x90, 0x0, 0x0,

    /* U+002B "+" */
    0x0, 0xa0, 0x0, 0xa, 0x0, 0x49, 0xd9, 0x20,
    0xa, 0x0, 0x0, 0x0, 0x0,

    /* U+002C "," */
    0x1, 0x49, 0x53,

    /* U+002D "-" */
    0x5c, 0x80,

    /* U+002E "." */
    0x0, 0x58,

    /* U+002F "/" */
    0x0, 0x90, 0x26, 0x6, 0x20, 0x90, 0x9, 0x2,
    0x60, 0x62, 0x9, 0x0, 0x40, 0x0,

    /* U+0030 "0" */
    0x9, 0xa8, 0x4, 0x60, 0x82, 0x73, 0x5, 0x58,
    0x30, 0x56, 0x73, 0x5, 0x54, 0x60, 0x82, 0xa,
    0xa8, 0x0,

    /* U+0031 "1" */
    0x8, 0xe0, 0x4, 0x5b, 0x0, 0x0, 0xb0, 0x0,
    0xb, 0x0, 0x0, 0xb0, 0x0, 0xb, 0x0, 0x2a,
    0xea, 0x40,

    /* U+0032 "2" */
    0xa, 0xa9, 0x3, 0x40, 0xb1, 0x0, 0xb, 0x0,
    0x2, 0xa0, 0x1, 0xb1, 0x0, 0xb2, 0x0, 0x6d,
    0xaa, 0x30,

    /* U+0033 "3" */
    0x1b, 0xb7, 0x1, 0x20, 0xc0, 0x0, 0xb, 0x0,
    0x5c, 0x50, 0x0, 0xb, 0x3, 0x0, 0xb0, 0x3b,
    0xb7, 0x0,

    /* U+0034 "4" */
    0x0, 0x8b, 0x0, 0x18, 0xb0, 0x7, 0x2b, 0x0,
    0x90, 0xb0, 0x64, 0xb, 0x8, 0xaa, 0xe5, 0x0,
    0xb, 0x0,

    /* U+0035 "5" */
    0xd, 0xaa, 0x1, 0x80, 0x0, 0x27, 0x0, 0x3,
    0x97, 0x80, 0x1, 0x8, 0x31, 0x20, 0x83, 0xa,
    0xaa, 0x0,

    /* U+0036 "6" */
    0x1, 0xb1, 0x0, 0xa3, 0x0, 0x2b, 0x0, 0x5,
    0x9a, 0x90, 0x76, 0x8, 0x45, 0x50, 0x74, 0x9,
    0xaa, 0x0,

    /* U+0037 "7" */
    0x7b, 0xad, 0x46, 0x20, 0xa0, 0x0, 0x1a, 0x0,
    0x6, 0x50, 0x0, 0xb0, 0x0, 0x1a, 0x0, 0x6,
    0x50, 0x0,

    /* U+0038 "8" */
    0xb, 0xaa, 0x5, 0x70, 0x92, 0x37, 0x9, 0x10,
    0xbb, 0x90, 0x65, 0x7, 0x47, 0x40, 0x75, 0x1b,
    0xaa, 0x0,

    /* U+0039 "9" */
    0xa, 0xa9, 0x5, 0x60, 0x82, 0x74, 0x6, 0x55,
    0x70, 0x93, 0x9, 0xaa, 0x0, 0x2, 0x80, 0x2,
    0xa0, 0x0,

    /* U+003A ":" */
    0x49, 0x0, 0x0, 0x0, 0x49,

    /* U+003B ";" */
    0x49, 0x0, 0x0, 0x0, 0x49, 0x36, 0x20,

    /* U+003C "<" */
    0x0, 0x0, 0x0, 0x3, 0xb0, 0x7, 0x80, 0x3,
    0xa0, 0x0, 0x4, 0xa2, 0x0, 0x1, 0xa1, 0x0,
    0x0, 0x0,

    /* U+003D "=" */
    0x49, 0x99, 0x20, 0x0, 0x0, 0x49, 0x99, 0x20,

    /* U+003E ">" */
    0x0, 0x0, 0x2, 0xa2, 0x0, 0x1, 0x96, 0x0,
    0x0, 0xc1, 0x3, 0xb3, 0x3, 0x90, 0x0, 0x0,
    0x0, 0x0,

    /* U+003F "?" */
    0x4b, 0xb2, 0x70, 0x38, 0x0, 0x47, 0x5, 0xa1,
    0x9, 0x10, 0x0, 0x0, 0xa, 0x30,

    /* U+0040 "@" */
    0x2, 0x98, 0x86, 0x0, 0x90, 0x0, 0x54, 0x44,
    0x89, 0xa0, 0x87, 0x1b, 0xa, 0x8, 0x61, 0xa0,
    0xb0, 0x84, 0x45, 0x87, 0x81, 0x9, 0x10, 0x0,
    0x0, 0x7, 0x88, 0x40,

    /* U+0041 "A" */
    0x0, 0xe2, 0x0, 0x4, 0x87, 0x0, 0x8, 0x1a,
    0x0, 0xa, 0x9, 0x0, 0x1d, 0xac, 0x40, 0x64,
    0x1, 0x90, 0xa0, 0x0, 0xb0,

    /* U+0042 "B" */
    0x4d, 0xac, 0x34, 0x70, 0x38, 0x47, 0x3, 0x74,
    0xda, 0xd2, 0x47, 0x1, 0xa4, 0x70, 0xb, 0x4d,
    0xac, 0x50,

    /* U+0043 "C" */
    0x8, 0xab, 0x23, 0x80, 0x6, 0x64, 0x0, 0x8,
    0x30, 0x0, 0x64, 0x0, 0x3, 0x80, 0x7, 0x8,
    0xab, 0x20,

    /* U+0044 "D" */
    0x4d, 0xab, 0x24, 0x70, 0x1a, 0x47, 0x0, 0xb4,
    0x70, 0xc, 0x47, 0x0, 0xb4, 0x70, 0x1a, 0x4d,
    0xab, 0x20,

    /* U+0045 "E" */
    0x4d, 0xaa, 0x24, 0x70, 0x0, 0x47, 0x0, 0x4,
    0xda, 0xa0, 0x47, 0x0, 0x4, 0x70, 0x0, 0x4d,
    0xaa, 0x20,

    /* U+0046 "F" */
    0x4d, 0xaa, 0x14, 0x70, 0x0, 0x47, 0x0, 0x4,
    0xda, 0x90, 0x47, 0x0, 0x4, 0x70, 0x0, 0x47,
    0x0, 0x0,

    /* U+0047 "G" */
    0x7, 0xab, 0x50, 0x38, 0x0, 0x70, 0x64, 0x0,
    0x0, 0x83, 0x9, 0xc0, 0x64, 0x0, 0xa1, 0x38,
    0x0, 0xd1, 0x8, 0xba, 0xa1,

    /* U+0048 "H" */
    0x47, 0x0, 0xb4, 0x70, 0xb, 0x47, 0x0, 0xb4,
    0xda, 0xae, 0x47, 0x0, 0xb4, 0x70, 0xb, 0x47,
    0x0, 0xb0,

    /* U+0049 "I" */
    0x5e, 0x70, 0xb0, 0xb, 0x0, 0xb0, 0xb, 0x0,
    0xb0, 0x5e, 0x70,

    /* U+004A "J" */
    0x1a, 0xb7, 0x0, 0x47, 0x0, 0x47, 0x0, 0x47,
    0x0, 0x47, 0x60, 0x56, 0x4b, 0xb1,

    /* U+004B "K" */
    0x47, 0x5, 0x74, 0x70, 0xb0, 0x47, 0x93, 0x4,
    0xad, 0x0, 0x4b, 0x48, 0x4, 0x70, 0xb2, 0x47,
    0x2, 0xa0,

    /* U+004C "L" */
    0x47, 0x0, 0x47, 0x0, 0x47, 0x0, 0x47, 0x0,
    0x47, 0x0, 0x47, 0x0, 0x4d, 0xa9,

    /* U+004D "M" */
    0x4e, 0x0, 0x5d, 0x4b, 0x50, 0xaa, 0x47, 0xa2,
    0x7b, 0x47, 0x79, 0x1b, 0x47, 0x19, 0xb, 0x47,
    0x0, 0xb, 0x47, 0x0, 0xb,

    /* U+004E "N" */
    0x4d, 0x0, 0xb4, 0xb4, 0xb, 0x47, 0xa0, 0xb4,
    0x77, 0x3b, 0x47, 0x1a, 0xb4, 0x70, 0x8b, 0x47,
    0x2, 0xf0,

    /* U+004F "O" */
    0x7, 0xab, 0x40, 0x38, 0x0, 0xb0, 0x64, 0x0,
    0x82, 0x83, 0x0, 0x84, 0x64, 0x0, 0x82, 0x38,
    0x0, 0xb0, 0x7, 0xab, 0x40,

    /* U+0050 "P" */
    0x4d, 0xab, 0x34, 0x70, 0x38, 0x47, 0x3, 0x84,
    0xda, 0xa2, 0x47, 0x0, 0x4, 0x70, 0x0, 0x47,
    0x0, 0x0,

    /* U+0051 "Q" */
    0x8, 0xab, 0x40, 0x38, 0x0, 0xb0, 0x74, 0x0,
    0x83, 0x73, 0x0, 0x83, 0x55, 0x0, 0x92, 0xb,
    0x45, 0xa0, 0x1, 0xa7, 0x0, 0x0, 0x3a, 0x10,

    /* U+0052 "R" */
    0x4d, 0xab, 0x34, 0x70, 0x38, 0x47, 0x3, 0x84,
    0xca, 0xc2, 0x47, 0xb, 0x4, 0x70, 0x92, 0x47,
    0x3, 0x90,

    /* U+0053 "S" */
    0x1a, 0xaa, 0x7, 0x40, 0x30, 0x58, 0x0, 0x0,
    0x7c, 0x80, 0x0, 0x8, 0x34, 0x10, 0x74, 0x2b,
    0xa9, 0x0,

    /* U+0054 "T" */
    0x8a, 0xea, 0x40, 0xb, 0x0, 0x0, 0xb0, 0x0,
    0xb, 0x0, 0x0, 0xb0, 0x0, 0xb, 0x0, 0x0,
    0xb0, 0x0,

    /* U+0055 "U" */
    0x46, 0x0, 0xb4, 0x60, 0xb, 0x46, 0x0, 0xb4,
    0x60, 0xb, 0x46, 0x0, 0xb2, 0x90, 0x1a, 0x9,
    0xab, 0x20,

    /* U+0056 "V" */
    0xa1, 0x1, 0xa6, 0x40, 0x55, 0x29, 0xa, 0x10,
    0xb0, 0xb0, 0xa, 0x39, 0x0, 0x69, 0x50, 0x1,
    0xf1, 0x0,

    /* U+0057 "W" */
    0xb0, 0xe, 0x30, 0xb0, 0x83, 0x2b, 0x60, 0xb0,
    0x56, 0x56, 0x91, 0x90, 0x29, 0x82, 0xa4, 0x60,
    0xb, 0xa0, 0xa7, 0x20, 0xa, 0x90, 0x8a, 0x0,
    0x8, 0x80, 0x5b, 0x0,

    /* U+0058 "X" */
    0x85, 0x4, 0x71, 0xb0, 0xb0, 0x8, 0x77, 0x0,
    0x1f, 0x10, 0x7, 0xa6, 0x1, 0xb0, 0xb0, 0x83,
    0x4, 0x80,

    /* U+0059 "Y" */
    0xa2, 0x4, 0x73, 0x80, 0xa1, 0xb, 0x29, 0x0,
    0x5d, 0x20, 0x0, 0xc0, 0x0, 0xb, 0x0, 0x0,
    0xb0, 0x0,

    /* U+005A "Z" */
    0x5a, 0xad, 0x40, 0x0, 0xb0, 0x0, 0x84, 0x0,
    0x1a, 0x0, 0xa, 0x20, 0x3, 0x80, 0x0, 0xab,
    0xaa, 0x40,

    /* U+005B "[" */
    0x4b, 0x4, 0x50, 0x45, 0x4, 0x50, 0x45, 0x4,
    0x50, 0x45, 0x4, 0x50, 0x3a, 0x0,

    /* U+005C "\\" */
    0x81, 0x0, 0x44, 0x0, 0x8, 0x0, 0x9, 0x0,
    0x8, 0x10, 0x4, 0x40, 0x0, 0x80, 0x0, 0x90,
    0x0, 0x40,

    /* U+005D "]" */
    0x4b, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9,
    0x49,

    /* U+005E "^" */
    0x1, 0xc0, 0x0, 0x84, 0x70, 0x19, 0xa, 0x6,
    0x20, 0x44,

    /* U+005F "_" */
    0x7a, 0xaa, 0x30,

    /* U+0060 "`" */
    0x11, 0x37, 0x3,

    /* U+0061 "a" */
    0x2b, 0xb4, 0x1, 0x1, 0x90, 0x28, 0x8a, 0x9,
    0x21, 0xa0, 0x5a, 0x6c, 0x10,

    /* U+0062 "b" */
    0x56, 0x0, 0x5, 0x60, 0x0, 0x5a, 0xa9, 0x5,
    0x60, 0x82, 0x56, 0x6, 0x45, 0x60, 0x82, 0x59,
    0x99, 0x0,

    /* U+0063 "c" */
    0x1a, 0xb5, 0x73, 0x3, 0x91, 0x0, 0x73, 0x3,
    0x1a, 0xa6,

    /* U+0064 "d" */
    0x0, 0xa, 0x0, 0x0, 0xa0, 0x1b, 0x9c, 0x7,
    0x30, 0xb0, 0x92, 0xa, 0x7, 0x30, 0xb0, 0x1b,
    0x8b, 0x0,

    /* U+0065 "e" */
    0x1a, 0xa6, 0x7, 0x30, 0xa0, 0x99, 0x8a, 0x7,
    0x20, 0x20, 0x1a, 0xa7, 0x0,

    /* U+0066 "f" */
    0xb, 0x41, 0x90, 0x8d, 0x41, 0x90, 0x19, 0x1,
    0x90, 0x19, 0x0,

    /* U+0067 "g" */
    0x0, 0xa, 0x1, 0xab, 0x60, 0x64, 0xa, 0x5,
    0x50, 0x90, 0xa, 0x92, 0x3, 0xca, 0x80, 0x81,
    0x8, 0x35, 0xa9, 0xa0,

    /* U+0068 "h" */
    0x56, 0x0, 0x56, 0x0, 0x59, 0xa8, 0x56, 0xb,
    0x56, 0xb, 0x56, 0xb, 0x56, 0xb,

    /* U+0069 "i" */
    0x45, 0x0, 0x56, 0x56, 0x56, 0x56, 0x56,

    /* U+006A "j" */
    0x45, 0x0, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56,
    0xb3,

    /* U+006B "k" */
    0x56, 0x0, 0x5, 0x60, 0x0, 0x56, 0x39, 0x5,
    0x6b, 0x0, 0x5c, 0xb0, 0x5, 0x67, 0x50, 0x56,
    0xb, 0x0,

    /* U+006C "l" */
    0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x3b,

    /* U+006D "m" */
    0x58, 0x87, 0x7b, 0x15, 0x60, 0xc0, 0x46, 0x56,
    0xb, 0x3, 0x75, 0x60, 0xb0, 0x37, 0x56, 0xb,
    0x3, 0x70,

    /* U+006E "n" */
    0x59, 0x88, 0x56, 0xb, 0x56, 0xb, 0x56, 0xb,
    0x56, 0xb,

    /* U+006F "o" */
    0x1a, 0xa6, 0x7, 0x30, 0xa0, 0x91, 0x9, 0x27,
    0x30, 0xa0, 0x1a, 0xa7, 0x0,

    /* U+0070 "p" */
    0x58, 0x79, 0x5, 0x60, 0x82, 0x56, 0x6, 0x45,
    0x60, 0x82, 0x5a, 0xa9, 0x5, 0x60, 0x0, 0x56,
    0x0, 0x0,

    /* U+0071 "q" */
    0x1b, 0x8b, 0x7, 0x30, 0xb0, 0x92, 0xa, 0x7,
    0x30, 0xb0, 0x1b, 0x9c, 0x0, 0x0, 0xa0, 0x0,
    0xa, 0x0,

    /* U+0072 "r" */
    0x5a, 0x95, 0x60, 0x56, 0x5, 0x60, 0x56, 0x0,

    /* U+0073 "s" */
    0x3b, 0xa2, 0x83, 0x0, 0x19, 0xa2, 0x10, 0x37,
    0x4a, 0xb3,

    /* U+0074 "t" */
    0x9, 0x8, 0xd5, 0x19, 0x1, 0x90, 0x19, 0x0,
    0xc4,

    /* U+0075 "u" */
    0x55, 0xb, 0x55, 0xb, 0x55, 0xb, 0x56, 0xb,
    0x1c, 0x8b,

    /* U+0076 "v" */
    0xa0, 0xa, 0x63, 0x36, 0x28, 0x72, 0x9, 0x90,
    0x8, 0x80,

    /* U+0077 "w" */
    0x90, 0x5a, 0xa, 0x6, 0x38, 0x80, 0x90, 0x36,
    0x97, 0x28, 0x0, 0x98, 0x49, 0x40, 0xb, 0x50,
    0xe1, 0x0,

    /* U+0078 "x" */
    0x74, 0x19, 0xa, 0x91, 0x7, 0x90, 0xa, 0xa1,
    0x83, 0x2a,

    /* U+0079 "y" */
    0xa0, 0xa, 0x63, 0x37, 0x28, 0x72, 0x9, 0x90,
    0x8, 0x80, 0x6, 0x40, 0x2b, 0x0,

    /* U+007A "z" */
    0x6a, 0xc6, 0x0, 0xb0, 0x8, 0x30, 0x29, 0x0,
    0xab, 0xa5,

    /* U+007B "{" */
    0xb, 0x20, 0x90, 0x9, 0x1, 0x80, 0xa2, 0x1,
    0x80, 0x9, 0x0, 0x90, 0x9, 0x20,

    /* U+007C "|" */
    0x99, 0x99, 0x99, 0x99, 0x40,

    /* U+007D "}" */
    0x4a, 0x0, 0x90, 0x9, 0x0, 0x90, 0x4, 0x80,
    0x90, 0x9, 0x0, 0x90, 0x48, 0x0,

    /* U+007E "~" */
    0x4a, 0x50, 0x11, 0x6, 0xa2,

    /* U+00B7 "·" */
    0x2b, 0x1,

    /* U+2013 "–" */
    0x8b, 0xbb, 0x50,

    /* U+2026 "…" */
    0x0, 0x0, 0x0, 0x58, 0x2b, 0xd,

    /* U+2212 "−" */
    0x69, 0x99, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 31, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 37, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 55, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 12, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 77, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 53, .adv_w = 121, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 90, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 32, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 105, .adv_w = 43, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 119, .adv_w = 43, .box_w = 4, .box_h = 9, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 137, .adv_w = 60, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 145, .adv_w = 78, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 36, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 161, .adv_w = 52, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 163, .adv_w = 36, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 50, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 179, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 251, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 37, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 37, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 371, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 389, .adv_w = 78, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 397, .adv_w = 78, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 415, .adv_w = 62, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 429, .adv_w = 116, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 457, .adv_w = 83, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 85, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 496, .adv_w = 81, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 514, .adv_w = 87, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 532, .adv_w = 76, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 550, .adv_w = 73, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 90, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 589, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 52, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 67, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 83, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 650, .adv_w = 65, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 664, .adv_w = 105, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 685, .adv_w = 92, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 703, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 724, .adv_w = 79, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 742, .adv_w = 92, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 766, .adv_w = 83, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 784, .adv_w = 76, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 802, .adv_w = 74, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 820, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 838, .adv_w = 79, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 856, .adv_w = 116, .box_w = 8, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 884, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 902, .adv_w = 77, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 920, .adv_w = 75, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 938, .adv_w = 41, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 952, .adv_w = 50, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 970, .adv_w = 41, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 979, .adv_w = 78, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 989, .adv_w = 73, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 992, .adv_w = 78, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 995, .adv_w = 70, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1008, .adv_w = 75, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1026, .adv_w = 65, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1036, .adv_w = 75, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1054, .adv_w = 71, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1067, .adv_w = 42, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1078, .adv_w = 69, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1098, .adv_w = 74, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1112, .adv_w = 33, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1119, .adv_w = 33, .box_w = 2, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1128, .adv_w = 69, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1146, .adv_w = 36, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1153, .adv_w = 113, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1171, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1181, .adv_w = 73, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1194, .adv_w = 75, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1212, .adv_w = 75, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1230, .adv_w = 48, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1238, .adv_w = 63, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1248, .adv_w = 46, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1257, .adv_w = 74, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1267, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1277, .adv_w = 101, .box_w = 7, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1295, .adv_w = 66, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1305, .adv_w = 65, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1319, .adv_w = 61, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1329, .adv_w = 45, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1343, .adv_w = 41, .box_w = 1, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1348, .adv_w = 45, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1362, .adv_w = 78, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1367, .adv_w = 43, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 1369, .adv_w = 76, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 1372, .adv_w = 105, .box_w = 6, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1378, .adv_w = 78, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 2}
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
    0, 0, 0, 0, -12, 0, 0, 0,
    0, 0, -7, -1, 0, -4, 1, 4,
    0, 2, 3, 0, 2, 1, 0, 0,
    0, 0, -3, -3, 0, -1, 0, 0,
    0, 0, 0, 0, 0, 0, 4, 4,
    1, 4, 1, 0, -9, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -7, 0, -4,
    -1, 0, -7, -1, 0, 0, 0, 0,
    1, 1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, -1, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 3, 2, 1, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 2, 0,
    7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, -12, 0, 0,
    0, 0, 0, 0, -11, 0, 3, -7,
    0, 2, 0, -13, -5, -9, -7, 2,
    -11, 4, 0, 0, 0, 0, -4, -4,
    -3, -1, 0, 0, 0, 0, 0, 0,
    -4, -2, -8, -6, 0, -6, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 2, -5, -4, -3, -7, 0,
    -5, -2, -7, -9, -5, 0, 0, 0,
    0, 1, 1, 0, -1, 0, -1, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    0, -3, 0, 0, 0, 0, 0, 0,
    -18, 0, 0, 0, -9, -3, 0, -4,
    -1, 4, 0, 2, 2, 0, 3, -1,
    0, 0, -5, -1, -6, -6, 0, -5,
    -2, -2, -1, -2, -1, -2, 0, -2,
    0, -1, -1, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -6, 0, -3, -1,
    -1, -6, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -17, 0, 0, 0,
    0, 0, -3, 1, 0, 0, 0, 1,
    0, 2, 5, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -2, 0, -2,
    -2, -1, -6, 0, -4, -2, -4, -6,
    -2, 0, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -1, -1, -1, 0, -7,
    0, 0, 3, -3, 1, 0, -6, -1,
    1, -2, 0, 2, 0, -8, -2, -6,
    -3, 1, -8, 0, 0, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, -3, -2, 1, -2,
    1, 0, 0, 0, 0, -3, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, -2, -1, -2, -3, 0, 0,
    -8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, -2, -1, 0, 0, 1, -1, 0,
    -1, -3, 0, 0, 0, -1, -1, -1,
    0, 0, 0, -1, 0, 0, 1, -1,
    -1, 0, 0, -6, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, -6, 2, -4, 0, 0,
    0, -4, 0, 0, -1, 0, -4, 0,
    -2, -1, -3, -4, -3, 0, -11, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    0, 0, 0, -1, 0, 0, 0, -1,
    0, 0, 0, -1, 0, 0, -1, 0,
    0, 0, 0, 0, -1, -1, 0, -1,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 1, -5,
    2, -14, 0, -7, 0, 1, -3, -8,
    -2, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -19, -5, 0, -4,
    -4, -1, -6, 0, -1, 0, -3, -3,
    -2, -1, -3, -2, -1, -4, -2, -2,
    0, -1, 0, 0, 0, 1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, -4,
    0, -2, -1, -1, -5, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, 0, 0,
    -5, 0, 0, 0, -2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, 0, 0, -1, -1, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -5, 0, -3, 0, 0, 0,
    -2, 0, 0, -1, 0, 0, 0, 0,
    0, -2, 0, 0, 0, -10, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 1, -3, 1, 1, -8, 1,
    0, 0, -4, 1, -3, 0, -1, -1,
    -3, 0, -2, -1, 0, -1, 1, 0,
    0, -1, 0, -2, -3, -2, -1, 0,
    0, 0, -1, -1, 0, -2, -1, -1,
    -1, -1, -1, 1, 0, -9, -1, 1,
    4, -6, 4, 1, -6, -2, 2, -4,
    0, 1, 0, -9, -3, -6, -4, 0,
    -10, 2, 0, 5, 1, 0, -1, -1,
    1, 1, 0, 1, 0, 0, 0, 0,
    -2, -1, -5, -4, 2, -4, 3, 0,
    -1, 0, 0, -7, 2, -4, 0, -1,
    0, -3, 0, 0, -1, 0, -3, 0,
    -3, -2, -3, -5, -1, 0, -13, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 3, -4, 0, -15, 0,
    -9, 0, 2, 0, -8, 0, 0, -5,
    1, 0, 0, 0, 1, -2, 0, -3,
    0, -20, -1, 0, -2, -2, 2, -3,
    0, 0, 0, -1, -2, -1, 2, 0,
    2, 1, 0, 2, 1, 0, 0, -4,
    0, -1, -3, -1, 0, 0, -3, 0,
    -1, 0, -1, 0, -2, -1, -2, -1,
    0, -3, 0, 0, 1, -1, 0, -1,
    -1, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -1, 0, -1, 2, -2, 0,
    0, 0, 0, 0, 0, 1, -1, -2,
    0, -1, -1, 0, -1, 0, 0, -6,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 4, -4, 3, -13,
    -7, -11, -6, 2, -6, -8, -3, 0,
    -4, -1, 3, 0, 1, 1, 0, 2,
    0, 0, -11, -9, 0, -9, -9, -2,
    -11, 0, 0, 0, -6, -6, -9, 0,
    -7, -5, -6, -6, -4, -7, 0, 0,
    -1, 0, -5, 0, -5, 0, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -9, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, -5, 3, -9, -5, -7,
    -3, 3, -4, -6, -3, 0, -4, -1,
    1, 0, 0, 0, 0, 1, 0, 0,
    -12, -5, 0, -5, -5, 0, -6, 0,
    0, 0, -3, -3, -4, 0, -3, -1,
    -1, -1, -1, -1, 0, 3, -4, 2,
    -7, -2, -4, -1, 3, -2, -3, -2,
    0, -2, 0, 1, 0, 0, 0, 0,
    0, 0, 0, -8, -3, 0, -2, -2,
    0, -3, 0, 0, 0, -1, -2, -2,
    1, -1, 0, 0, -1, 0, -1, 0,
    0, -2, 1, 2, -7, 0, -1, -1,
    -4, 0, -3, 0, 1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, -1,
    0, -2, -1, 0, 0, 0, 0, 0,
    0, 0, 0, -1, -1, -1, -2, 1,
    -1, 1, 0, 2, -6, 3, -11, -9,
    -11, -6, 1, -6, -8, -5, 0, -4,
    -3, 2, 0, 0, 0, 0, 0, 0,
    0, -11, -7, -1, -7, -7, -2, -8,
    -1, -2, 0, -6, -6, -6, -1, -5,
    -3, -2, -4, -4, -4, 0, 1, -1,
    1, 4, -6, 1, 0, 0, -3, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 3, 0, 0, -1,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, 3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 3, -13, 1,
    -3, -5, -11, -9, -12, -8, 4, -11,
    4, 0, 0, -5, 0, -9, -6, -2,
    6, 0, 9, -4, 0, 1, -4, -5,
    -5, -9, -5, 3, 1, 2, 0, -4,
    0, 0, 1, -1, 4, 0, 0, 0,
    3, 0, 0, 3, 0, -9, 0, -5,
    -1, 1, -7, 2, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -2, -1, 1, -1,
    1, 0, -3, 0, 0, -3, 1, 0,
    0, 0, 0, 0, 0, -1, 1, 0,
    -10, 0, -5, -2, -2, -7, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -1,
    0, -2, -1, -1, 0, 0, 0, 0,
    0, 0, 1, 0, 0, 0, 1, 0,
    0, 1, 0, -6, 0, -4, -1, 0,
    -5, 1, 0, -3, 0, 0, -1, -1,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -4, 0, 0, -3, 1, 1, 0, 0,
    0, 0, 0, -1, 0, -1, -8, 0,
    -4, -2, -2, -7, -1, 0, -7, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    -1, -1, 1, 4, -1, 4, -6, -1,
    -2, 0, 4, 0, -1, 2, 0, -3,
    1, 5, 0, 4, 4, 2, 4, 0,
    2, -7, 0, 0, -1, -1, 0, -1,
    1, 0, 0, 0, 0, 0, 0, 0,
    2, 0, 0, 1, 0, 0, 1, 0,
    4, 1, -1, 4, 0, 0, 0, 2,
    1, 0, 0, 0, -1, 0, -1, 1,
    1, -1, 2, 1, 7, 0, 0, -1,
    -1, 0, 1, 0, 2, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 1, 0,
    0, -3, 0, 0, 0, 0, 1, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    0, -4, -3, 0, -7, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -1, -1,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, 0, 0, 0, 0, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -3,
    -1, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 1, -6, 1,
    0, 0, -1, 2, -1, 0, 1, 0,
    -4, 0, -2, -1, 1, -5, 2, 0,
    4, -1, 0, -1, -1, 0, -1, 0,
    0, 0, 0, 0, -1, -1, -1, -2,
    -1, 0, -1, 1, 0, 0, 0, 0,
    1, -2, 1, 0, 0, 0, 3, 0,
    0, 2, 0, -3, 0, -1, 1, 2,
    -2, 2, 0, 4, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, 0, 0,
    -1, 0, -1, 0, 0, -1, 0, 0,
    -4, -1, 0, -3, 1, 0, 0, 0,
    0, 0, 0, -1, 0, 0, -9, 0,
    -5, -2, -2, -7, -1, 0, -8, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -1, -1, -2,
    -1, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -3, 0, -3, -1, 0, -5, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 4, -2,
    0, -11, -1, -3, 0, 0, 0, -4,
    1, 0, -2, 1, -1, 0, 1, 3,
    -1, -1, -1, 0, -10, -1, 0, 0,
    0, 2, -2, 0, 0, 0, 0, 0,
    0, 2, 0, 2, 2, 0, 2, 1,
    0, -1, -1, 0, -1, -1, 1, 0,
    0, 0, 0, 0, 0, 0, 0, -8,
    0, -4, 0, -2, -6, 0, 0, -5,
    0, 0, 0, 0, 0, -1, 0, 0,
    0, 0, 0, -1, 0, 0, -1, -1,
    -1, -2, -1, 0, 1, -1, 0, 1,
    -3, 0, 0, 1, -1, 2, 0, 0,
    1, 1, -4, 0, 0, 1, 1, -2,
    1, 1, 3, 0, 0, -1, -1, -1,
    -1, 0, 0, 0, 0, 0, 0, -1,
    0, 1, 0, 0, 1, 1, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -6, 0, -3,
    0, 0, -6, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, -1, 0, -8, 0, -1,
    0, 0, 0, -3, 0, 0, -1, 0,
    -4, 0, -1, 0, 0, -2, 0, 0,
    -9, -1, 0, -1, -1, 1, -2, 0,
    0, 0, 0, 0, 0, 1, 0, 0,
    0, 0, 0, 0, 0, 4, -3, 0,
    -6, 0, 0, 0, 0, 0, -2, 0,
    0, -2, 0, -6, 0, -1, 0, 0,
    -3, 0, 0, -5, -2, 0, -1, -1,
    1, -2, 0, 0, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 1, 0,
    1, -3, 0, 0, -5, 0, 0, 0,
    -1, 1, 0, 0, 1, 0, -6, 0,
    -1, -1, 1, -3, 0, 0, 3, 0,
    0, -2, -2, 0, 0, 0, 0, 0,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 4, -4, 0, -9, 0,
    -2, 0, 0, -1, -4, 0, 0, -3,
    0, -4, 0, -1, 0, 0, -1, 0,
    0, -10, -2, 0, -1, -1, 1, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, -1,
    0, 3, -3, 1, 0, 0, 0, 2,
    0, 0, 1, 0, -5, 0, -1, 1,
    2, -2, 1, 0, 3, 0, 0, -1,
    -1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 1, 1, 0, 1, 0
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
const lv_font_t br_font_sans_9 = {
#else
lv_font_t br_font_sans_9 = {
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



#endif /*#if BR_FONT_SANS_9*/

