/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: --font Pixel Emulator.otf --size 12 --bpp 1 --range 0x20-0x7E --format lvgl --no-compress -o src/fonts/font_pixel_12.c --lv-include lvgl.h
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef FONT_PIXEL_12
#define FONT_PIXEL_12 1
#endif

#if FONT_PIXEL_12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0x6, 0x1c, 0x30, 0x43, 0x4, 0x0, 0x40,

    /* U+0022 "\"" */
    0xb4,

    /* U+0023 "#" */
    0xfd, 0x45, 0x3f, 0x50,

    /* U+0024 "$" */
    0x8, 0x7e, 0xc8, 0x7e, 0xa, 0xb, 0x7e, 0x8,

    /* U+0025 "%" */
    0xc3, 0xc7, 0x1e, 0x1c, 0x38, 0x60, 0xe3, 0xc3,

    /* U+0026 "&" */
    0x78, 0xc4, 0xf4, 0x78, 0x49, 0xcd, 0xc6, 0x7f,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x7f, 0x83, 0x6, 0xc, 0x18, 0x10, 0x3f,

    /* U+0029 ")" */
    0xfc, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x7e,

    /* U+002A "*" */
    0x86, 0x24, 0xbf, 0x4a, 0x10,

    /* U+002B "+" */
    0x20, 0x8f, 0xc8, 0x20,

    /* U+002C "," */
    0xc0,

    /* U+002D "-" */
    0xfc,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x3, 0x7, 0x1e, 0x1c, 0x38, 0x60, 0xe0, 0xc0,

    /* U+0030 "0" */
    0x3c, 0x46, 0xc3, 0xc3, 0xc3, 0x42, 0x24, 0x3c,

    /* U+0031 "1" */
    0x18, 0xf0, 0x60, 0xc1, 0x83, 0x6, 0x7f,

    /* U+0032 "2" */
    0x7e, 0xc3, 0x3, 0x3e, 0x78, 0x70, 0xf0, 0xff,

    /* U+0033 "3" */
    0x7f, 0x6, 0xc, 0x3e, 0x2, 0x3, 0xc3, 0x7e,

    /* U+0034 "4" */
    0x1c, 0x79, 0xb2, 0x6c, 0xdf, 0xc3, 0x6,

    /* U+0035 "5" */
    0xfe, 0xc0, 0xfe, 0x2, 0x3, 0x3, 0xc3, 0x7e,

    /* U+0036 "6" */
    0x3e, 0x60, 0x40, 0xfe, 0xc2, 0xc3, 0xc3, 0x7e,

    /* U+0037 "7" */
    0xff, 0x83, 0x6, 0x6, 0x8, 0x18, 0x18, 0x18,

    /* U+0038 "8" */
    0x7c, 0xc2, 0xe2, 0x64, 0x9c, 0x9f, 0x83, 0x7e,

    /* U+0039 "9" */
    0x7e, 0xc3, 0xc3, 0x7f, 0x3, 0x2, 0x6, 0x7c,

    /* U+003A ":" */
    0x88,

    /* U+003B ";" */
    0x8c,

    /* U+003C "<" */
    0xe, 0x10, 0x47, 0x81, 0x81, 0xc0,

    /* U+003D "=" */
    0xfc, 0xf, 0xc0,

    /* U+003E ">" */
    0xf0, 0x20, 0x20, 0x71, 0x9e, 0x0,

    /* U+003F "?" */
    0x7e, 0xc3, 0x3, 0x1e, 0x10, 0x30, 0x0, 0x20,

    /* U+0040 "@" */
    0x7e, 0xc3, 0xcb, 0xcb, 0xca, 0xce, 0x40, 0x7e,

    /* U+0041 "A" */
    0x3c, 0x24, 0x42, 0xc3, 0xc3, 0xff, 0xc3, 0xc3,

    /* U+0042 "B" */
    0xfe, 0xc3, 0xc3, 0xfe, 0xc2, 0xc3, 0xc3, 0xfe,

    /* U+0043 "C" */
    0x3e, 0x63, 0xc0, 0xc0, 0xc0, 0x40, 0x63, 0x3e,

    /* U+0044 "D" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc2, 0xc4, 0xfc,

    /* U+0045 "E" */
    0xff, 0x83, 0x7, 0xfc, 0x18, 0x30, 0x7f,

    /* U+0046 "F" */
    0xff, 0x83, 0x7, 0xfc, 0x18, 0x30, 0x60,

    /* U+0047 "G" */
    0x3f, 0x60, 0xc0, 0xcf, 0xc3, 0x43, 0x23, 0x3f,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xfe, 0x30, 0x60, 0xc1, 0x83, 0x6, 0x7f,

    /* U+004A "J" */
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xc3, 0x7e,

    /* U+004B "K" */
    0xc3, 0xc6, 0xc4, 0xc8, 0xf8, 0xfc, 0xce, 0xc7,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x7f,

    /* U+004D "M" */
    0xc3, 0xf7, 0xff, 0xcb, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+004E "N" */
    0xc3, 0xe3, 0xfb, 0xfb, 0xdf, 0xc7, 0xc7, 0xc3,

    /* U+004F "O" */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x42, 0x7e,

    /* U+0050 "P" */
    0xfe, 0xc3, 0xc3, 0xc3, 0xc2, 0xfe, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xdf, 0x46, 0x7d,

    /* U+0052 "R" */
    0xfe, 0xc3, 0xc3, 0xcf, 0xcc, 0xfc, 0xde, 0xcf,

    /* U+0053 "S" */
    0x7c, 0xc6, 0xc0, 0x7e, 0x2, 0x3, 0xc3, 0x7e,

    /* U+0054 "T" */
    0xfe, 0x30, 0x60, 0xc1, 0x83, 0x6, 0xc,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x7e,

    /* U+0056 "V" */
    0xc3, 0xc3, 0xc3, 0xc3, 0x76, 0x3c, 0x3c, 0x8,

    /* U+0057 "W" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xcb, 0xff, 0xf7, 0xc3,

    /* U+0058 "X" */
    0xc3, 0xe7, 0x7e, 0x3c, 0x3c, 0x66, 0xc3, 0xc3,

    /* U+0059 "Y" */
    0xc7, 0x8f, 0x1a, 0x23, 0x83, 0x6, 0xc,

    /* U+005A "Z" */
    0xff, 0x7, 0xe, 0x3c, 0x78, 0x70, 0xf0, 0xff,

    /* U+005B "[" */
    0xff, 0x83, 0x6, 0xc, 0x18, 0x30, 0x7f,

    /* U+005C "\\" */
    0xc0, 0xe0, 0x78, 0x38, 0x1c, 0x6, 0x7, 0x3,

    /* U+005D "]" */
    0xfe, 0xc, 0x18, 0x30, 0x60, 0xc1, 0xff,

    /* U+005E "^" */
    0x64, 0xc0,

    /* U+005F "_" */
    0xff, 0x80,

    /* U+0060 "`" */
    0xc3, 0xc0,

    /* U+0061 "a" */
    0x3c, 0x24, 0x42, 0xc3, 0xc3, 0xff, 0xc3, 0xc3,

    /* U+0062 "b" */
    0xfe, 0xc3, 0xc3, 0xfe, 0xc2, 0xc3, 0xc3, 0xfe,

    /* U+0063 "c" */
    0x3e, 0x63, 0xc0, 0xc0, 0xc0, 0x40, 0x63, 0x3e,

    /* U+0064 "d" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc2, 0xc4, 0xfc,

    /* U+0065 "e" */
    0xff, 0x83, 0x7, 0xfc, 0x18, 0x30, 0x7f,

    /* U+0066 "f" */
    0xff, 0x83, 0x7, 0xfc, 0x18, 0x30, 0x60,

    /* U+0067 "g" */
    0x3f, 0x60, 0xc0, 0xcf, 0xc3, 0x43, 0x23, 0x3f,

    /* U+0068 "h" */
    0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+0069 "i" */
    0xfe, 0x30, 0x60, 0xc1, 0x83, 0x6, 0x7f,

    /* U+006A "j" */
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xc3, 0x7e,

    /* U+006B "k" */
    0xc3, 0xc6, 0xc4, 0xc8, 0xf8, 0xfc, 0xce, 0xc7,

    /* U+006C "l" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x7f,

    /* U+006D "m" */
    0xc3, 0xf7, 0xff, 0xcb, 0xc3, 0xc3, 0xc3, 0xc3,

    /* U+006E "n" */
    0xc3, 0xe3, 0xfb, 0xfb, 0xdf, 0xc7, 0xc7, 0xc3,

    /* U+006F "o" */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x42, 0x7e,

    /* U+0070 "p" */
    0xfe, 0xc3, 0xc3, 0xc3, 0xc2, 0xfe, 0xc0, 0xc0,

    /* U+0071 "q" */
    0x7e, 0xc3, 0xc3, 0xc3, 0xc3, 0xdf, 0x46, 0x7d,

    /* U+0072 "r" */
    0xfe, 0xc3, 0xc3, 0xcf, 0xcc, 0xfc, 0xde, 0xcf,

    /* U+0073 "s" */
    0x7c, 0xc6, 0xc0, 0x7e, 0x2, 0x3, 0xc3, 0x7e,

    /* U+0074 "t" */
    0xfe, 0x30, 0x60, 0xc1, 0x83, 0x6, 0xc,

    /* U+0075 "u" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0x7e,

    /* U+0076 "v" */
    0xc3, 0xc3, 0xc3, 0xc3, 0x76, 0x3c, 0x3c, 0x8,

    /* U+0077 "w" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xcb, 0xff, 0xf7, 0xc3,

    /* U+0078 "x" */
    0xc3, 0xe7, 0x7e, 0x3c, 0x3c, 0x66, 0xc3, 0xc3,

    /* U+0079 "y" */
    0xc7, 0x8f, 0x1a, 0x23, 0x83, 0x6, 0xc,

    /* U+007A "z" */
    0xff, 0x7, 0xe, 0x3c, 0x78, 0x70, 0xf0, 0xff,

    /* U+007B "{" */
    0x3e, 0xc1, 0x86, 0x6, 0xc, 0x8, 0x1f,

    /* U+007C "|" */
    0xff,

    /* U+007D "}" */
    0xf8, 0x18, 0x30, 0x30, 0xc1, 0x82, 0x7c,

    /* U+007E "~" */
    0x63, 0x38
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 151, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 8, .adv_w = 75, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 9, .adv_w = 113, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 13, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 29, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 38, .box_w = 1, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 38, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 113, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 57, .adv_w = 113, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 61, .adv_w = 38, .box_w = 1, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 62, .adv_w = 113, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 63, .adv_w = 38, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 64, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 150, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 126, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 134, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 38, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 38, .box_w = 1, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 152, .adv_w = 131, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 158, .adv_w = 113, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 161, .adv_w = 131, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 167, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 151, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 215, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 237, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 260, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 283, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 307, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 331, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 346, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 370, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 377, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 392, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 407, .adv_w = 94, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 409, .adv_w = 150, .box_w = 9, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 411, .adv_w = 94, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 413, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 429, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 445, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 490, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 498, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 513, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 537, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 545, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 553, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 561, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 568, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 576, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 600, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 150, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 615, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 622, .adv_w = 38, .box_w = 1, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 131, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 630, .adv_w = 131, .box_w = 7, .box_h = 2, .ofs_x = 0, .ofs_y = 9}
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
const lv_font_t font_pixel_12 = {
#else
lv_font_t font_pixel_12 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 12,          /*The maximum line height required by the font*/
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



#endif /*#if FONT_PIXEL_12*/

