/**
 * @file main.c
 * bonanzaDisplay — Main entry point
 *
 * Bare-metal super loop driving SSD1322 OLED via LVGL on RPi Pico 2W.
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#include "lvgl.h"
#include "ssd1322.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "ui.h"

// ==========================================================================
// LVGL Tick (1 ms via repeating timer)
// ==========================================================================

static bool lvgl_tick_cb(struct repeating_timer *t) {
    (void)t;
    lv_tick_inc(1);
    return true;  // Keep repeating
}

// ==========================================================================
// Main
// ==========================================================================

int main(void) {
    // --- Platform init ---
    stdio_init_all();
    sleep_ms(100);  // Brief delay for USB CDC to enumerate

    printf("\n=== bonanzaDisplay ===\n");
    printf("SSD1322 256x64 OLED | LVGL 9.x | Pico 2W\n\n");

    // --- Display hardware init ---
    printf("Initializing SSD1322...\n");
    ssd1322_init();
    printf("SSD1322 initialized.\n");

    // --- LVGL init ---
    printf("Initializing LVGL...\n");
    lv_init();

    // Start LVGL tick timer (1 ms)
    struct repeating_timer tick_timer;
    add_repeating_timer_ms(-1, lvgl_tick_cb, NULL, &tick_timer);

    // --- Display driver port ---
    lv_port_disp_init();

    // --- Input device port ---
    lv_port_indev_init();

    // --- Create UI ---
    printf("Creating dashboard UI...\n");
    ui_dashboard_create();
    printf("Ready.\n");

    // =======================================================================
    // Super Loop
    // =======================================================================
    uint32_t last_ui_update = 0;
    const uint32_t UI_UPDATE_INTERVAL_MS = 1000;  // Update dashboard every 1s

    while (1) {
        // Run LVGL task handler (renders dirty areas, handles animations)
        lv_timer_handler();

        // Periodic dashboard data update
        uint32_t now = to_ms_since_boot(get_absolute_time());
        if (now - last_ui_update >= UI_UPDATE_INTERVAL_MS) {
            last_ui_update = now;
            ui_dashboard_update();
        }

        // Small sleep to yield CPU (prevents busy-wait, ~30 FPS budget)
        sleep_ms(5);
    }

    return 0;
}
