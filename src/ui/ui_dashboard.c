/**
 * @file ui_dashboard.c
 * Dashboard screen layout for SSD1322 256x64 OLED
 *
 * Displays a simple status screen with:
 *   - Title label
 *   - Status text
 *   - A progress/activity bar
 *
 * Customize this file for your application's dashboard content.
 */

#include "ui.h"
#include <stdio.h>

// ==========================================================================
// UI Element Handles
// ==========================================================================

static lv_obj_t *label_title;
static lv_obj_t *label_status;
static lv_obj_t *bar_activity;

// ==========================================================================
// Dashboard Creation
// ==========================================================================

void ui_dashboard_create(void) {
    // Get the active screen
    lv_obj_t *scr = lv_screen_active();

    // Set screen background to black
    lv_obj_set_style_bg_color(scr, lv_color_black(), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, LV_PART_MAIN);

    // --- Title Label (top) ---
    label_title = lv_label_create(scr);
    lv_label_set_text(label_title, "bonanzaDisplay");
    lv_obj_set_style_text_color(label_title, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(label_title, &lv_font_montserrat_14, LV_PART_MAIN);
    lv_obj_align(label_title, LV_ALIGN_TOP_MID, 0, 2);

    // --- Status Label (center) ---
    label_status = lv_label_create(scr);
    lv_label_set_text(label_status, "Initializing...");
    lv_obj_set_style_text_color(label_status, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_text_font(label_status, &lv_font_montserrat_10, LV_PART_MAIN);
    lv_obj_align(label_status, LV_ALIGN_CENTER, 0, 0);

    // --- Activity Bar (bottom) ---
    bar_activity = lv_bar_create(scr);
    lv_obj_set_size(bar_activity, 200, 10);
    lv_obj_align(bar_activity, LV_ALIGN_BOTTOM_MID, 0, -6);
    lv_bar_set_range(bar_activity, 0, 100);
    lv_bar_set_value(bar_activity, 0, LV_ANIM_OFF);

    // Style the bar for grayscale
    lv_obj_set_style_bg_color(bar_activity, lv_color_make(0x40, 0x40, 0x40), LV_PART_MAIN);
    lv_obj_set_style_bg_color(bar_activity, lv_color_white(), LV_PART_INDICATOR);
    lv_obj_set_style_radius(bar_activity, 3, LV_PART_MAIN);
    lv_obj_set_style_radius(bar_activity, 3, LV_PART_INDICATOR);
}

// ==========================================================================
// Dashboard Update
// ==========================================================================

static uint32_t update_counter = 0;

void ui_dashboard_update(void) {
    update_counter++;

    // Example: cycle bar value for demo purposes
    uint8_t bar_val = (update_counter * 2) % 101;
    lv_bar_set_value(bar_activity, bar_val, LV_ANIM_ON);

    // Update status text periodically
    if (update_counter % 30 == 0) {
        static char status_buf[64];
        snprintf(status_buf, sizeof(status_buf), "Uptime: %lu s", update_counter / 30);
        lv_label_set_text(label_status, status_buf);
    }
}
