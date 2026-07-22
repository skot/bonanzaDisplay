/**
 * @file main_screen_gen.c
 * @brief Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/

#include "main_screen_gen.h"
#include "bonanza_ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * main_screen_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t screen_style;
    static lv_style_t divider_style;
    static lv_style_t metric_style;
    static lv_style_t caption_style;
    static lv_style_t logo_style;
    static lv_style_t name_style;

    static bool style_inited = false;

    if (!style_inited) {
        lv_style_init(&screen_style);
        lv_style_set_bg_color(&screen_style, lv_color_hex(0x080a0d));
        lv_style_set_bg_opa(&screen_style, (255 * 100 / 100));
        lv_style_set_border_width(&screen_style, 0);
        lv_style_set_pad_all(&screen_style, 0);

        lv_style_init(&divider_style);
        lv_style_set_bg_color(&divider_style, lv_color_hex(0x252a31));
        lv_style_set_bg_opa(&divider_style, (255 * 100 / 100));
        lv_style_set_border_width(&divider_style, 0);
        lv_style_set_radius(&divider_style, 0);

        lv_style_init(&metric_style);
        lv_style_set_text_color(&metric_style, lv_color_hex(0xFFFFFF));
        lv_style_set_text_font(&metric_style, fmtowns_8x16);

        lv_style_init(&caption_style);
        lv_style_set_text_color(&caption_style, lv_color_hex(0x333333));
        lv_style_set_text_font(&caption_style, portfolio_6x8);

        lv_style_init(&logo_style);
        lv_style_set_image_recolor(&logo_style, lv_color_hex(0x888888));
        lv_style_set_image_recolor_opa(&logo_style, (255 * 100 / 100));

        lv_style_init(&name_style);
        lv_style_set_text_color(&name_style, lv_color_hex(0xAAAAAA));
        lv_style_set_text_font(&name_style, portfolio_6x8);

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    lv_obj_set_name_static(lv_obj_0, "main_screen_#");

    lv_obj_add_style(lv_obj_0, &screen_style, 0);
    lv_obj_t * lv_image_0 = lv_image_create(lv_obj_0);
    lv_obj_set_x(lv_image_0, 10);
    lv_obj_set_y(lv_image_0, 0);
    lv_image_set_src(lv_image_0, bitaxe_logo);
    lv_obj_add_style(lv_image_0, &logo_style, 0);
    
    lv_obj_t * lv_label_0 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_0, 17);
    lv_obj_set_y(lv_label_0, 31);
    lv_label_bind_text(lv_label_0, &device_identity, NULL);
    lv_obj_add_style(lv_label_0, &caption_style, 0);
    
    lv_obj_t * lv_label_1 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_1, 10);
    lv_obj_set_y(lv_label_1, 45);
    lv_label_bind_text(lv_label_1, &device_name_text, NULL);
    lv_obj_add_style(lv_label_1, &name_style, 0);
    
    lv_obj_t * lv_label_2 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_2, 10);
    lv_obj_set_y(lv_label_2, 54);
    lv_label_bind_text(lv_label_2, &ip_address_text, NULL);
    lv_obj_add_style(lv_label_2, &name_style, 0);
    
    lv_obj_t * lv_label_3 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_3, 112);
    lv_obj_set_y(lv_label_3, 0);
    lv_label_bind_text(lv_label_3, &hashrate_ghs, "%dGH/s");
    lv_obj_add_style(lv_label_3, &metric_style, 0);
    
    lv_obj_t * lv_label_4 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_4, 120);
    lv_obj_set_y(lv_label_4, 13);
    lv_label_set_text(lv_label_4, "HASHRATE");
    lv_obj_add_style(lv_label_4, &caption_style, 0);
    
    lv_obj_t * lv_label_5 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_5, 112);
    lv_obj_set_y(lv_label_5, 21);
    lv_label_bind_text(lv_label_5, &best_share_text, NULL);
    lv_obj_add_style(lv_label_5, &metric_style, 0);
    
    lv_obj_t * lv_label_6 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_6, 120);
    lv_obj_set_y(lv_label_6, 34);
    lv_label_set_text(lv_label_6, "BESTSHARE");
    lv_obj_add_style(lv_label_6, &caption_style, 0);
    
    lv_obj_t * lv_label_7 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_7, 112);
    lv_obj_set_y(lv_label_7, 42);
    lv_label_bind_text(lv_label_7, &asic_temp_c, "%dC");
    lv_obj_add_style(lv_label_7, &metric_style, 0);
    
    lv_obj_t * lv_label_8 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_8, 120);
    lv_obj_set_y(lv_label_8, 55);
    lv_label_set_text(lv_label_8, "TEMP");
    lv_obj_add_style(lv_label_8, &caption_style, 0);
    
    lv_obj_t * lv_label_9 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_9, 191);
    lv_obj_set_y(lv_label_9, 0);
    lv_label_bind_text(lv_label_9, &power_w, "%dW");
    lv_obj_add_style(lv_label_9, &metric_style, 0);
    
    lv_obj_t * lv_label_10 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_10, 199);
    lv_obj_set_y(lv_label_10, 13);
    lv_label_set_text(lv_label_10, "POWER");
    lv_obj_add_style(lv_label_10, &caption_style, 0);
    
    lv_obj_t * lv_label_11 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_11, 191);
    lv_obj_set_y(lv_label_11, 21);
    lv_label_bind_text(lv_label_11, &frequency_mhz, "%dMHz");
    lv_obj_add_style(lv_label_11, &metric_style, 0);
    
    lv_obj_t * lv_label_12 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_12, 199);
    lv_obj_set_y(lv_label_12, 34);
    lv_label_set_text(lv_label_12, "FREQUENCY");
    lv_obj_add_style(lv_label_12, &caption_style, 0);
    
    lv_obj_t * lv_label_13 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_13, 191);
    lv_obj_set_y(lv_label_13, 42);
    lv_label_bind_text(lv_label_13, &fan_percent, "%d%%");
    lv_obj_add_style(lv_label_13, &metric_style, 0);
    
    lv_obj_t * lv_label_14 = lv_label_create(lv_obj_0);
    lv_obj_set_x(lv_label_14, 199);
    lv_obj_set_y(lv_label_14, 55);
    lv_label_set_text(lv_label_14, "FAN");
    lv_obj_add_style(lv_label_14, &caption_style, 0);

    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
