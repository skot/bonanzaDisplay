/**
 * @file main.c
 * bonanzaDisplay — Main entry point
 *
 * Bare-metal super loop driving SSD1322 OLED via LVGL on RPi Pico 2W.
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "pico/time.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"

#include "lvgl.h"
#include "ssd1322.h"
#include "ssd1322_regs.h"
#include "lv_port_disp.h"
#include "pin_config.h"

// ==========================================================================
// LVGL Tick — Pico SDK monotonic ms clock
// ==========================================================================

static uint32_t pico_tick_get_cb(void) {
    return to_ms_since_boot(get_absolute_time());
}

// ==========================================================================
// Main
// ==========================================================================

int main(void) {
    // --- Platform init ---
    stdio_init_all();
    sleep_ms(500);

    printf("\n=== bonanzaDisplay (LVGL + PIO + DMA) ===\n");
    printf("System clock: %lu MHz\n\n", clock_get_hz(clk_sys) / 1000000);

    // --- Display hardware init (PIO + DMA) ---
    printf("Init SSD1322 (PIO 8080 mode)...\n");
    ssd1322_init();
    printf("SSD1322 initialized.\n");

    // Quick blink to confirm display alive
    ssd1322_write_cmd(0xA5);  // ALL_ON
    sleep_ms(200);
    ssd1322_write_cmd(0xA6);  // Normal mode
    sleep_ms(100);

    // --- LVGL init ---
    printf("Init LVGL...\n");
    lv_init();
    lv_tick_set_cb(pico_tick_get_cb);
    lv_port_disp_init();
    printf("LVGL ready.\n");

    // --- Create a simple demo UI ---
    lv_obj_t *scr = lv_screen_active();

    // Style: white text on black background
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    // Title label — large, centered near top
    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "bonanzaDisplay");
    lv_obj_set_style_text_color(title, lv_color_white(), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_14, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 4);

    // Info label — smaller, centered below
    lv_obj_t *info = lv_label_create(scr);
    lv_label_set_text(info, "LVGL + PIO + DMA");
    lv_obj_set_style_text_color(info, lv_color_white(), 0);
    lv_obj_set_style_text_font(info, &lv_font_montserrat_10, 0);
    lv_obj_align(info, LV_ALIGN_CENTER, 0, 4);

    // Counter label — bottom, updates every frame
    lv_obj_t *counter = lv_label_create(scr);
    lv_label_set_text(counter, "Frame: 0");
    lv_obj_set_style_text_color(counter, lv_color_white(), 0);
    lv_obj_set_style_text_font(counter, &lv_font_montserrat_10, 0);
    lv_obj_align(counter, LV_ALIGN_BOTTOM_MID, 0, -4);

    printf("Entering LVGL main loop...\n");

    // --- Main loop ---
    uint32_t frame = 0;
    char buf[32];
    while (1) {
        lv_timer_handler();  // Run LVGL tasks (render, animations, etc.)
        sleep_ms(5);         // ~200 Hz poll rate, LVGL handles its own timing

        // Update counter every 30 frames (~150ms)
        if (frame % 30 == 0) {
            snprintf(buf, sizeof(buf), "Frame: %lu", (unsigned long)frame);
            lv_label_set_text(counter, buf);
        }
        frame++;
    }

    return 0;
}
