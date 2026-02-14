/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Opts: --font Pixel Emulator.otf --size 8 --bpp 1 --range 0x20-0x7E --format lvgl --no-compress -o src/fonts/font_pixel_8.c --lv-include lvgl.h
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_PIXEL_8
#define FONT_PIXEL_8 1
#endif

#if FONT_PIXEL_8

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x8, 0x84, 0x40, 0x40,

    /* U+0022 "\"" */
    0xc0,

    /* U+0023 "#" */
    0x6f, 0xf6,

    /* U+0024 "$" */
    0x23, 0xfe, 0x57, 0x90,

    /* U+0025 "%" */
    0xcc, 0x61, 0x8, 0x63, 0x30,

    /* U+0026 "&" */
    0x63, 0x46, 0x19, 0xd9, 0xf0,

    /* U+0027 "'" */
    0x80,

    /* U+0028 "(" */
    0x7e, 0x31, 0x8c, 0x3c,

    /* U+0029 ")" */
    0xf0, 0xc6, 0x31, 0xf8,

    /* U+002A "*" */
    0x9f, 0x69,

    /* U+002B "+" */
    0x27, 0xc8, 0x40,

    /* U+002C "," */
    0x80,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0xc, 0x63, 0x8, 0x43, 0x0,

    /* U+0030 "0" */
    0x71, 0x6c, 0xf3, 0x49, 0xc0,

    /* U+0031 "1" */
    0x31, 0xc3, 0xc, 0x33, 0xf0,

    /* U+0032 "2" */
    0x7b, 0x33, 0x98, 0xc3, 0xf0,

    /* U+0033 "3" */
    0x7c, 0xe3, 0x82, 0xcd, 0xe0,

    /* U+0034 "4" */
    0x39, 0x6d, 0xbf, 0x18, 0x60,

    /* U+0035 "5" */
    0xfb, 0xf, 0x83, 0xcd, 0xe0,

    /* U+0036 "6" */
    0x3b, 0x8f, 0xb2, 0xcd, 0xe0,

    /* U+0037 "7" */
    0xfe, 0x10, 0x84, 0x30, 0xc0,

    /* U+0038 "8" */
    0x73, 0x27, 0x2c, 0x8d, 0xe0,

    /* U+0039 "9" */
    0x7b, 0x37, 0xc3, 0x19, 0xc0,

    /* U+003A ":" */
    0x90,

    /* U+003B ";" */
    0xb0,

    /* U+003C "<" */
    0x3f, 0x8, 0x70,

    /* U+003D "=" */
    0xf0, 0xf0,

    /* U+003E ">" */
    0xc1, 0xc9, 0x80,

    /* U+003F "?" */
    0x7b, 0x33, 0x88, 0x1, 0x0,

    /* U+0040 "@" */
    0x7b, 0x3e, 0xfe, 0xc1, 0xe0,

    /* U+0041 "A" */
    0x31, 0xec, 0xff, 0xcf, 0x30,

    /* U+0042 "B" */
    0xfb, 0x3f, 0xb2, 0xcf, 0xe0,

    /* U+0043 "C" */
    0x39, 0xbc, 0x30, 0x6c, 0xe0,

    /* U+0044 "D" */
    0xf3, 0x6c, 0xf3, 0xdb, 0xc0,

    /* U+0045 "E" */
    0xfe, 0x3f, 0x8c, 0x7c,

    /* U+0046 "F" */
    0xfe, 0x3f, 0x8c, 0x60,

    /* U+0047 "G" */
    0x3d, 0x8d, 0xf3, 0x6c, 0xf0,

    /* U+0048 "H" */
    0xcf, 0x3f, 0xf3, 0xcf, 0x30,

    /* U+0049 "I" */
    0xfc, 0xc3, 0xc, 0x33, 0xf0,

    /* U+004A "J" */
    0xc, 0x30, 0xc3, 0xcd, 0xe0,

    /* U+004B "K" */
    0xcf, 0x6d, 0x3c, 0xdb, 0x30,

    /* U+004C "L" */
    0xc6, 0x31, 0x8c, 0x7c,

    /* U+004D "M" */
    0xcf, 0xfe, 0xf3, 0xcf, 0x30,

    /* U+004E "N" */
    0xcf, 0xbe, 0xf7, 0xdf, 0x30,

    /* U+004F "O" */
    0x7b, 0x3c, 0xf3, 0xcd, 0xe0,

    /* U+0050 "P" */
    0xfb, 0x3c, 0xfe, 0xc3, 0x0,

    /* U+0051 "Q" */
    0x7b, 0x3c, 0xf7, 0xd9, 0xd0,

    /* U+0052 "R" */
    0xfb, 0x3d, 0xfc, 0xdb, 0x70,

    /* U+0053 "S" */
    0x73, 0x67, 0x82, 0xcd, 0xe0,

    /* U+0054 "T" */
    0xfc, 0xc3, 0xc, 0x30, 0xc0,

    /* U+0055 "U" */
    0xcf, 0x3c, 0xf3, 0xcd, 0xe0,

    /* U+0056 "V" */
    0xcf, 0x3c, 0xff, 0x78, 0x80,

    /* U+0057 "W" */
    0xcf, 0x3c, 0xfb, 0xff, 0x30,

    /* U+0058 "X" */
    0xcd, 0x63, 0xc, 0x5b, 0x30,

    /* U+0059 "Y" */
    0xcf, 0x37, 0x88, 0x20, 0x80,

    /* U+005A "Z" */
    0xfc, 0x73, 0x98, 0xc3, 0xf0,

    /* U+005B "[" */
    0xfe, 0x31, 0x8c, 0x7c,

    /* U+005C "\\" */
    0xc1, 0x2, 0xc, 0x18, 0x30,

    /* U+005D "]" */
    0xf8, 0xc6, 0x31, 0xfc,

    /* U+005E "^" */
    0x54,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0xcc,

    /* U+0061 "a" */
    0x31, 0xec, 0xff, 0xcf, 0x30,

    /* U+0062 "b" */
    0xfb, 0x3f, 0xb2, 0xcf, 0xe0,

    /* U+0063 "c" */
    0x39, 0xbc, 0x30, 0x6c, 0xe0,

    /* U+0064 "d" */
    0xf3, 0x6c, 0xf3, 0xdb, 0xc0,

    /* U+0065 "e" */
    0xfe, 0x3f, 0x8c, 0x7c,

    /* U+0066 "f" */
    0xfe, 0x3f, 0x8c, 0x60,

    /* U+0067 "g" */
    0x3d, 0x8d, 0xf3, 0x6c, 0xf0,

    /* U+0068 "h" */
    0xcf, 0x3f, 0xf3, 0xcf, 0x30,

    /* U+0069 "i" */
    0xfc, 0xc3, 0xc, 0x33, 0xf0,

    /* U+006A "j" */
    0xc, 0x30, 0xc3, 0xcd, 0xe0,

    /* U+006B "k" */
    0xcf, 0x6d, 0x3c, 0xdb, 0x30,

    /* U+006C "l" */
    0xc6, 0x31, 0x8c, 0x7c,

    /* U+006D "m" */
    0xcf, 0xfe, 0xf3, 0xcf, 0x30,

    /* U+006E "n" */
    0xcf, 0xbe, 0xf7, 0xdf, 0x30,

    /* U+006F "o" */
    0x7b, 0x3c, 0xf3, 0xcd, 0xe0,

    /* U+0070 "p" */
    0xfb, 0x3c, 0xfe, 0xc3, 0x0,

    /* U+0071 "q" */
    0x7b, 0x3c, 0xf7, 0xd9, 0xd0,

    /* U+0072 "r" */
    0xfb, 0x3d, 0xfc, 0xdb, 0x70,

    /* U+0073 "s" */
    0x73, 0x67, 0x82, 0xcd, 0xe0,

    /* U+0074 "t" */
    0xfc, 0xc3, 0xc, 0x30, 0xc0,

    /* U+0075 "u" */
    0xcf, 0x3c, 0xf3, 0xcd, 0xe0,

    /* U+0076 "v" */
    0xcf, 0x3c, 0xff, 0x78, 0x80,

    /* U+0077 "w" */
    0xcf, 0x3c, 0xfb, 0xff, 0x30,

    /* U+0078 "x" */
    0xcd, 0x63, 0xc, 0x5b, 0x30,

    /* U+0079 "y" */
    0xcf, 0x37, 0x88, 0x20, 0x80,

    /* U+007A "z" */
    0xfc, 0x73, 0x98, 0xc3, 0xf0,

    /* U+007B "{" */
    0x3b, 0x30, 0xc6, 0x1c,

    /* U+007C "|" */
    0xfc,

    /* U+007D "}" */
    0xe1, 0x86, 0x63, 0x70,

    /* U+007E "~" */
    0x4d, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 101, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 50, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 6, .adv_w = 75, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 8, .adv_w = 100, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 22, .adv_w = 25, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 23, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 75, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 33, .adv_w = 75, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 36, .adv_w = 25, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 75, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 38, .adv_w = 25, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 88, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 25, .box_w = 1, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 25, .box_w = 1, .box_h = 4, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 96, .adv_w = 88, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 99, .adv_w = 75, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 101, .adv_w = 88, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 104, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 101, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 88, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 88, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 88, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 241, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 254, .adv_w = 63, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 255, .adv_w = 100, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 256, .adv_w = 63, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 257, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 267, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 88, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 324, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 334, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 349, .adv_w = 88, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 369, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 88, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 379, .adv_w = 100, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 388, .adv_w = 25, .box_w = 1, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 393, .adv_w = 88, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 7}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
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
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
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
const lv_font_t font_pixel_8 = {
#else
lv_font_t font_pixel_8 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
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



#endif /*#if FONT_PIXEL_8*/

