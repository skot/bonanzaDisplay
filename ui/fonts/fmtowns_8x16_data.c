/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --font /fonts/Px437_FMTowns_re_8x16.ttf -o /fonts/fmtowns_8x16_data.c --no-compress --size 16 --bpp 1 --format lvgl --range 0x20-0x7e
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef FMTOWNS_8X16_DATA
#define FMTOWNS_8X16_DATA 1
#endif

#if FMTOWNS_8X16_DATA

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0x98,

    /* U+0022 "\"" */
    0x99, 0x99,

    /* U+0023 "#" */
    0x49, 0x24, 0xbf, 0x49, 0x24, 0x92, 0x4b, 0xf4,
    0x92, 0x48,

    /* U+0024 "$" */
    0x10, 0x79, 0x5a, 0x85, 0xa, 0xe, 0xa, 0x14,
    0x2b, 0x53, 0xc1, 0x0,

    /* U+0025 "%" */
    0x66, 0x9a, 0xb2, 0x10, 0x42, 0x8, 0x4d, 0x59,
    0x66,

    /* U+0026 "&" */
    0x71, 0x12, 0x24, 0x45, 0x6, 0x12, 0x45, 0x85,
    0xa, 0x13, 0xd0,

    /* U+0027 "'" */
    0x2a, 0x0,

    /* U+0028 "(" */
    0x29, 0x49, 0x24, 0x91, 0x22,

    /* U+0029 ")" */
    0x89, 0x12, 0x49, 0x25, 0x28,

    /* U+002A "*" */
    0x11, 0x25, 0x51, 0xc3, 0x9f, 0xce, 0x1c, 0x55,
    0x24, 0x40,

    /* U+002B "+" */
    0x21, 0x8, 0x4f, 0x90, 0x84, 0x20,

    /* U+002C "," */
    0xf5, 0x80,

    /* U+002D "-" */
    0xf8,

    /* U+002E "." */
    0xf0,

    /* U+002F "/" */
    0x2, 0x4, 0x10, 0x40, 0x82, 0x4, 0x10, 0x20,
    0x82, 0x4, 0x0,

    /* U+0030 "0" */
    0x31, 0x24, 0xa1, 0x86, 0x18, 0x61, 0x86, 0x14,
    0x92, 0x30,

    /* U+0031 "1" */
    0x23, 0x28, 0x42, 0x10, 0x84, 0x21, 0x8, 0x4f,
    0x80,

    /* U+0032 "2" */
    0x7a, 0x18, 0x61, 0x4, 0x21, 0x8, 0x41, 0x8,
    0x20, 0xfc,

    /* U+0033 "3" */
    0x7a, 0x18, 0x41, 0x4, 0x13, 0x81, 0x4, 0x18,
    0x61, 0x78,

    /* U+0034 "4" */
    0x8, 0x61, 0x8a, 0x29, 0x24, 0xa2, 0x8a, 0x2f,
    0xc2, 0x8,

    /* U+0035 "5" */
    0xfe, 0x8, 0x20, 0x83, 0xe0, 0x41, 0x4, 0x18,
    0x61, 0x78,

    /* U+0036 "6" */
    0x7a, 0x18, 0x60, 0x83, 0xe8, 0x61, 0x86, 0x18,
    0x61, 0x78,

    /* U+0037 "7" */
    0xfe, 0x18, 0x61, 0x8, 0x20, 0x82, 0x10, 0x41,
    0x4, 0x10,

    /* U+0038 "8" */
    0x7a, 0x18, 0x61, 0x85, 0xe8, 0x61, 0x86, 0x18,
    0x61, 0x78,

    /* U+0039 "9" */
    0x7a, 0x18, 0x61, 0x86, 0x18, 0x5f, 0x4, 0x18,
    0x61, 0x78,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0x6c, 0x0, 0x1b, 0x2a, 0x0,

    /* U+003C "<" */
    0x4, 0x21, 0x8, 0x42, 0x4, 0x8, 0x10, 0x20,
    0x40,

    /* U+003D "=" */
    0xf0, 0xf,

    /* U+003E ">" */
    0x81, 0x2, 0x4, 0x8, 0x10, 0x84, 0x21, 0x8,
    0x0,

    /* U+003F "?" */
    0x7a, 0x18, 0x61, 0x4, 0x21, 0x4, 0x10, 0x0,
    0x4, 0x10,

    /* U+0040 "@" */
    0x3c, 0x8a, 0xc, 0x9a, 0xb5, 0x6a, 0xd5, 0xab,
    0x5e, 0x5a, 0x3, 0xe0,

    /* U+0041 "A" */
    0x31, 0x28, 0x61, 0x86, 0x18, 0x7f, 0x86, 0x18,
    0x61, 0x84,

    /* U+0042 "B" */
    0xf9, 0x14, 0x51, 0x45, 0x17, 0x91, 0x45, 0x14,
    0x51, 0xf8,

    /* U+0043 "C" */
    0x39, 0x18, 0x60, 0x82, 0x8, 0x20, 0x82, 0x8,
    0x51, 0x38,

    /* U+0044 "D" */
    0xf1, 0x24, 0x51, 0x45, 0x14, 0x51, 0x45, 0x14,
    0x52, 0xf0,

    /* U+0045 "E" */
    0xfe, 0x8, 0x20, 0x82, 0xf, 0xa0, 0x82, 0x8,
    0x20, 0xfc,

    /* U+0046 "F" */
    0xfe, 0x8, 0x20, 0x82, 0xf, 0xa0, 0x82, 0x8,
    0x20, 0x80,

    /* U+0047 "G" */
    0x39, 0x18, 0x60, 0x82, 0x8, 0x27, 0x86, 0x18,
    0x51, 0x38,

    /* U+0048 "H" */
    0x86, 0x18, 0x61, 0x86, 0x1f, 0xe1, 0x86, 0x18,
    0x61, 0x84,

    /* U+0049 "I" */
    0xe9, 0x24, 0x92, 0x49, 0x2e,

    /* U+004A "J" */
    0x1c, 0x20, 0x82, 0x8, 0x20, 0x82, 0xa, 0x28,
    0xa2, 0x70,

    /* U+004B "K" */
    0x86, 0x18, 0xa2, 0x92, 0x8a, 0x34, 0x92, 0x28,
    0xa1, 0x84,

    /* U+004C "L" */
    0x82, 0x8, 0x20, 0x82, 0x8, 0x20, 0x82, 0x8,
    0x20, 0xfc,

    /* U+004D "M" */
    0x83, 0x8f, 0x1d, 0x5a, 0xb2, 0x64, 0xc1, 0x83,
    0x6, 0xc, 0x18, 0x20,

    /* U+004E "N" */
    0x86, 0x1c, 0x71, 0xa6, 0x99, 0x65, 0x8e, 0x38,
    0x61, 0x84,

    /* U+004F "O" */
    0x7a, 0x18, 0x61, 0x86, 0x18, 0x61, 0x86, 0x18,
    0x61, 0x78,

    /* U+0050 "P" */
    0xf2, 0x28, 0x61, 0x86, 0x2f, 0x20, 0x82, 0x8,
    0x20, 0x80,

    /* U+0051 "Q" */
    0x7a, 0x18, 0x61, 0x86, 0x18, 0x61, 0xa6, 0x58,
    0xa2, 0x74,

    /* U+0052 "R" */
    0xfa, 0x18, 0x61, 0x86, 0x1f, 0xa4, 0x92, 0x28,
    0xa1, 0x84,

    /* U+0053 "S" */
    0x7a, 0x18, 0x60, 0x82, 0x7, 0x81, 0x4, 0x18,
    0x61, 0x78,

    /* U+0054 "T" */
    0xfe, 0x20, 0x40, 0x81, 0x2, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x81, 0x0,

    /* U+0055 "U" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x61, 0x86, 0x18,
    0x61, 0x78,

    /* U+0056 "V" */
    0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xa2, 0x44,
    0x88, 0xa1, 0xc1, 0x0,

    /* U+0057 "W" */
    0x83, 0x6, 0xc, 0x19, 0x32, 0x64, 0xc9, 0xab,
    0x56, 0xaa, 0x24, 0x40,

    /* U+0058 "X" */
    0x83, 0x5, 0x13, 0x62, 0x82, 0x4, 0x8, 0x28,
    0xd9, 0x14, 0x18, 0x20,

    /* U+0059 "Y" */
    0x83, 0x5, 0x12, 0x22, 0x85, 0x4, 0x8, 0x10,
    0x20, 0x40, 0x81, 0x0,

    /* U+005A "Z" */
    0xfc, 0x10, 0x42, 0x8, 0x43, 0x8, 0x41, 0x8,
    0x20, 0xfc,

    /* U+005B "[" */
    0xf2, 0x49, 0x24, 0x92, 0x4e,

    /* U+005C "\\" */
    0x81, 0x1, 0x1, 0x2, 0x2, 0x4, 0x4, 0x8,
    0x8, 0x8, 0x10,

    /* U+005D "]" */
    0xe4, 0x92, 0x49, 0x24, 0x9e,

    /* U+005E "^" */
    0x22, 0xa2,

    /* U+005F "_" */
    0xfc,

    /* U+0060 "`" */
    0x88, 0x80,

    /* U+0061 "a" */
    0x72, 0x20, 0x9e, 0x8a, 0x28, 0xa4, 0x6c,

    /* U+0062 "b" */
    0x82, 0x8, 0x20, 0xbb, 0x18, 0x61, 0x86, 0x18,
    0x71, 0xb8,

    /* U+0063 "c" */
    0x7a, 0x18, 0x20, 0x82, 0x8, 0x21, 0x78,

    /* U+0064 "d" */
    0x4, 0x10, 0x41, 0x76, 0x38, 0x61, 0x86, 0x18,
    0x63, 0x74,

    /* U+0065 "e" */
    0x7a, 0x18, 0x61, 0xfe, 0x8, 0x21, 0x78,

    /* U+0066 "f" */
    0x18, 0x92, 0x8, 0xf8, 0x82, 0x8, 0x20, 0x82,
    0x8, 0x70,

    /* U+0067 "g" */
    0x76, 0x38, 0x61, 0x86, 0x18, 0xdd, 0x4, 0x17,
    0x80,

    /* U+0068 "h" */
    0x82, 0x8, 0x20, 0xbb, 0x18, 0x61, 0x86, 0x18,
    0x61, 0x84,

    /* U+0069 "i" */
    0x48, 0xc, 0x92, 0x49, 0x2e,

    /* U+006A "j" */
    0x11, 0x0, 0x31, 0x11, 0x11, 0x11, 0x19, 0x60,

    /* U+006B "k" */
    0x82, 0x8, 0x20, 0x86, 0x29, 0x28, 0xc2, 0x89,
    0x22, 0x84,

    /* U+006C "l" */
    0xc9, 0x24, 0x92, 0x49, 0x2e,

    /* U+006D "m" */
    0xa5, 0xb6, 0x4c, 0x99, 0x32, 0x64, 0xc9, 0x92,

    /* U+006E "n" */
    0xbb, 0x18, 0x61, 0x86, 0x18, 0x61, 0x84,

    /* U+006F "o" */
    0x7a, 0x18, 0x61, 0x86, 0x18, 0x61, 0x78,

    /* U+0070 "p" */
    0xbb, 0x18, 0x61, 0x86, 0x18, 0x71, 0xba, 0x8,
    0x0,

    /* U+0071 "q" */
    0x76, 0x38, 0x61, 0x86, 0x18, 0x63, 0x74, 0x10,
    0x40,

    /* U+0072 "r" */
    0xb6, 0x61, 0x8, 0x42, 0x10, 0x80,

    /* U+0073 "s" */
    0x7a, 0x18, 0x20, 0x78, 0x10, 0x61, 0x78,

    /* U+0074 "t" */
    0x20, 0x82, 0x8, 0xf8, 0x82, 0x8, 0x20, 0x82,
    0x9, 0x18,

    /* U+0075 "u" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0x63, 0x74,

    /* U+0076 "v" */
    0x83, 0x6, 0xc, 0x14, 0x48, 0x8a, 0x14, 0x10,

    /* U+0077 "w" */
    0x93, 0x26, 0x4c, 0x99, 0x32, 0x64, 0xc9, 0x6c,

    /* U+0078 "x" */
    0x86, 0x1c, 0xd2, 0x31, 0x2c, 0xe1, 0x84,

    /* U+0079 "y" */
    0x86, 0x18, 0x61, 0x86, 0x18, 0xdd, 0x4, 0x17,
    0x80,

    /* U+007A "z" */
    0xfc, 0x10, 0x82, 0x31, 0x4, 0x20, 0xfc,

    /* U+007B "{" */
    0x29, 0x24, 0xa2, 0x49, 0x22,

    /* U+007C "|" */
    0xff, 0xe0,

    /* U+007D "}" */
    0x89, 0x24, 0x8a, 0x49, 0x28,

    /* U+007E "~" */
    0x66, 0x60
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 128, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 128, .box_w = 1, .box_h = 13, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 128, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 5, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 128, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 36, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 49, .adv_w = 128, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 128, .box_w = 3, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 128, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 69, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 75, .adv_w = 128, .box_w = 2, .box_h = 5, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 77, .adv_w = 128, .box_w = 5, .box_h = 1, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 78, .adv_w = 128, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 1},
    {.bitmap_index = 79, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 128, .box_w = 5, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 128, .box_w = 2, .box_h = 8, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 191, .adv_w = 128, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 205, .adv_w = 128, .box_w = 4, .box_h = 4, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 207, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 216, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 258, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 278, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 128, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 343, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 365, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 375, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 425, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 437, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 459, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 483, .adv_w = 128, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 505, .adv_w = 128, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 128, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 521, .adv_w = 128, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 526, .adv_w = 128, .box_w = 5, .box_h = 3, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 528, .adv_w = 128, .box_w = 6, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 128, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = 10},
    {.bitmap_index = 531, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 538, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 548, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 555, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 565, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 572, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 582, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 591, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 601, .adv_w = 128, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 606, .adv_w = 128, .box_w = 4, .box_h = 15, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 614, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 624, .adv_w = 128, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 629, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 637, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 651, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 660, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 669, .adv_w = 128, .box_w = 5, .box_h = 9, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 675, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 682, .adv_w = 128, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 692, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 699, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 707, .adv_w = 128, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 715, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 722, .adv_w = 128, .box_w = 6, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 731, .adv_w = 128, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 738, .adv_w = 128, .box_w = 3, .box_h = 13, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 743, .adv_w = 128, .box_w = 1, .box_h = 11, .ofs_x = 4, .ofs_y = 1},
    {.bitmap_index = 745, .adv_w = 128, .box_w = 3, .box_h = 13, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 750, .adv_w = 128, .box_w = 6, .box_h = 2, .ofs_x = 1, .ofs_y = 11}
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
const lv_font_t fmtowns_8x16_data = {
#else
lv_font_t fmtowns_8x16_data = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if FMTOWNS_8X16_DATA*/

