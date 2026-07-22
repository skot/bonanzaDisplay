/**
 * @file bonanza_ui_gen.c
 */

/*********************
 *      INCLUDES
 *********************/

#include "bonanza_ui_gen.h"

#if LV_USE_XML
#endif /* LV_USE_XML */

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/*----------------
 * Translations
 *----------------*/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Fonts
 *----------------*/

lv_font_t * fmtowns_8x16;
extern lv_font_t fmtowns_8x16_data;
lv_font_t * portfolio_6x8;
extern lv_font_t portfolio_6x8_data;

/*----------------
 * Images
 *----------------*/

const void * bitaxe_logo;
extern const void * bitaxe_logo_data;

/*----------------
 * Subjects
 *----------------*/

lv_subject_t dial_position;
lv_subject_t dial_direction;
lv_subject_t switch_pressed;
lv_subject_t cw_count;
lv_subject_t ccw_count;
lv_subject_t press_count;
lv_subject_t dial_phase;
lv_subject_t hashrate_ghs;
lv_subject_t asic_temp_c;
lv_subject_t power_w;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void bonanza_ui_init_gen(const char * asset_path)
{
    char buf[256];

    /*----------------
     * Global styles
     *----------------*/

    /*----------------
     * Fonts
     *----------------*/

    /* get font 'fmtowns_8x16' from a C array */
    fmtowns_8x16 = &fmtowns_8x16_data;
    /* get font 'portfolio_6x8' from a C array */
    portfolio_6x8 = &portfolio_6x8_data;


    /*----------------
     * Images
     *----------------*/
    bitaxe_logo = &bitaxe_logo_data;

    /*----------------
     * Subjects
     *----------------*/
    lv_subject_init_int(&dial_position, 0);
    lv_subject_init_int(&dial_direction, 0);
    lv_subject_init_int(&switch_pressed, 0);
    lv_subject_init_int(&cw_count, 0);
    lv_subject_init_int(&ccw_count, 0);
    lv_subject_init_int(&press_count, 0);
    lv_subject_init_int(&dial_phase, 0);
    lv_subject_init_int(&hashrate_ghs, 1200);
    lv_subject_init_int(&asic_temp_c, 58);
    lv_subject_init_int(&power_w, 17);

    /*----------------
     * Translations
     *----------------*/

#if LV_USE_XML
    /* Register widgets */

    /* Register fonts */
    lv_xml_register_font(NULL, "fmtowns_8x16", fmtowns_8x16);
    lv_xml_register_font(NULL, "portfolio_6x8", portfolio_6x8);

    /* Register subjects */
    lv_xml_register_subject(NULL, "dial_position", &dial_position);
    lv_xml_register_subject(NULL, "dial_direction", &dial_direction);
    lv_xml_register_subject(NULL, "switch_pressed", &switch_pressed);
    lv_xml_register_subject(NULL, "cw_count", &cw_count);
    lv_xml_register_subject(NULL, "ccw_count", &ccw_count);
    lv_xml_register_subject(NULL, "press_count", &press_count);
    lv_xml_register_subject(NULL, "dial_phase", &dial_phase);
    lv_xml_register_subject(NULL, "hashrate_ghs", &hashrate_ghs);
    lv_xml_register_subject(NULL, "asic_temp_c", &asic_temp_c);
    lv_xml_register_subject(NULL, "power_w", &power_w);

    /* Register callbacks */
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if LV_USE_XML && !defined(LV_EDITOR_PREVIEW)
    /* Register images */
    lv_xml_register_image(NULL, "bitaxe_logo", bitaxe_logo);
#endif

#if LV_USE_XML == 0
    /*--------------------
     *  Permanent screens
     *-------------------*/
    /* If XML is enabled it's assumed that the permanent screens are created
     * manaully from XML using lv_xml_create() */
#endif
}

/* Callbacks */

/**********************
 *   STATIC FUNCTIONS
 **********************/