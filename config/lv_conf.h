/**
 * @file lv_conf.h
 * LVGL configuration for bonanzaDisplay
 * SSD1322 256x64 OLED, 4-bit grayscale, Pico 2W (RP2350)
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

// ==========================================================================
// Color Settings
// ==========================================================================
#define LV_COLOR_DEPTH                  8       // L8 grayscale rendering

// ==========================================================================
// Memory
// ==========================================================================
#define LV_MEM_CUSTOM                   0       // Use LVGL's built-in memory manager
#define LV_MEM_SIZE                     (48 * 1024) // 48 KB for LVGL internal use

// ==========================================================================
// Display
// ==========================================================================
#define LV_DEF_REFR_PERIOD             33      // ~30 FPS

// ==========================================================================
// OS / Threading
// ==========================================================================
#define LV_USE_OS                       LV_OS_NONE

// ==========================================================================
// Tick — handled via lv_tick_set_cb() in main.c
// ==========================================================================

// ==========================================================================
// Logging
// ==========================================================================
#define LV_USE_LOG                      1
#define LV_LOG_LEVEL                    LV_LOG_LEVEL_WARN
#define LV_LOG_PRINTF                   1       // Use printf for log output

// ==========================================================================
// Asserts
// ==========================================================================
#define LV_USE_ASSERT_NULL              1
#define LV_USE_ASSERT_MALLOC            1
#define LV_USE_ASSERT_STYLE             0
#define LV_USE_ASSERT_MEM_INTEGRITY     0
#define LV_USE_ASSERT_OBJ               0

// ==========================================================================
// Built-in Fonts
// ==========================================================================
#define LV_FONT_MONTSERRAT_8            0
#define LV_FONT_MONTSERRAT_10           0
#define LV_FONT_MONTSERRAT_12           0
#define LV_FONT_MONTSERRAT_14           1
#define LV_FONT_MONTSERRAT_16           0
#define LV_FONT_MONTSERRAT_18           0
#define LV_FONT_MONTSERRAT_20           0
#define LV_FONT_MONTSERRAT_22           0
#define LV_FONT_MONTSERRAT_24           0
#define LV_FONT_MONTSERRAT_26           0
#define LV_FONT_MONTSERRAT_28           0
#define LV_FONT_MONTSERRAT_30           0
#define LV_FONT_MONTSERRAT_32           0
#define LV_FONT_MONTSERRAT_34           0
#define LV_FONT_MONTSERRAT_36           0
#define LV_FONT_MONTSERRAT_38           0
#define LV_FONT_MONTSERRAT_40           0
#define LV_FONT_MONTSERRAT_42           0
#define LV_FONT_MONTSERRAT_44           0
#define LV_FONT_MONTSERRAT_46           0
#define LV_FONT_MONTSERRAT_48           0

#define LV_FONT_DEFAULT                 &lv_font_montserrat_14

// ==========================================================================
// Widgets (enable only what's needed for dashboard)
// ==========================================================================
#define LV_USE_ARC                      1
#define LV_USE_BAR                      1
#define LV_USE_BUTTON                   1
#define LV_USE_BUTTONMATRIX             0
#define LV_USE_CANVAS                   0
#define LV_USE_CHECKBOX                 0
#define LV_USE_DROPDOWN                 0
#define LV_USE_IMAGE                    1
#define LV_USE_LABEL                    1
#define LV_USE_LINE                     1
#define LV_USE_ROLLER                   0
#define LV_USE_SCALE                    0
#define LV_USE_SLIDER                   0
#define LV_USE_SWITCH                   0
#define LV_USE_TABLE                    0
#define LV_USE_TEXTAREA                 0

// ==========================================================================
// Extra Widgets
// ==========================================================================
#define LV_USE_ANIMIMG                  0
#define LV_USE_CALENDAR                 0
#define LV_USE_CHART                    0
#define LV_USE_COLORWHEEL              0
#define LV_USE_IMGBTN                   0
#define LV_USE_KEYBOARD                 0
#define LV_USE_LED                      1
#define LV_USE_LIST                     0
#define LV_USE_MENU                     0
#define LV_USE_METER                    0
#define LV_USE_MSGBOX                   0
#define LV_USE_SPAN                     0
#define LV_USE_SPINBOX                  0
#define LV_USE_SPINNER                  1
#define LV_USE_TABVIEW                  0
#define LV_USE_TILEVIEW                 0
#define LV_USE_WIN                      0

// ==========================================================================
// Layouts
// ==========================================================================
#define LV_USE_FLEX                     1
#define LV_USE_GRID                     0

// ==========================================================================
// Draw
// ==========================================================================
#define LV_USE_DRAW_SW                  1

// ==========================================================================
// Demos & Examples (disabled)
// ==========================================================================
#define LV_BUILD_EXAMPLES               0

#endif // LV_CONF_H
