/**
 * @file bonanza_ui_gen.h
 */

#ifndef BONANZA_UI_GEN_H
#define BONANZA_UI_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/*-------------------
 * Permanent screens
 *------------------*/

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Fonts
 *----------------*/

extern lv_font_t * fmtowns_8x16;

extern lv_font_t * portfolio_6x8;

/*----------------
 * Images
 *----------------*/

extern const void * bitaxe_logo;

/*----------------
 * Subjects
 *----------------*/

extern lv_subject_t dial_position;
extern lv_subject_t dial_direction;
extern lv_subject_t switch_pressed;
extern lv_subject_t cw_count;
extern lv_subject_t ccw_count;
extern lv_subject_t press_count;
extern lv_subject_t dial_phase;
extern lv_subject_t hashrate_ghs;
extern lv_subject_t asic_temp_c;
extern lv_subject_t power_w;
extern lv_subject_t frequency_mhz;
extern lv_subject_t fan_percent;
extern lv_subject_t device_identity;
extern lv_subject_t device_name_text;
extern lv_subject_t ip_address_text;
extern lv_subject_t best_share_text;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/*----------------
 * Event Callbacks
 *----------------*/

/**
 * Initialize the component library
 */

void bonanza_ui_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

/**********************
 *   POST INCLUDES
 **********************/

/*Include all the widget and components of this library*/
#include "screens/main_screen_gen.h"

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*BONANZA_UI_GEN_H*/
