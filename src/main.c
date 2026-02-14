/**
 * @file main.c
 * bonanzaDisplay — Main entry point
 *
 * Bare-metal super loop driving SSD1322 OLED via LVGL on RPi Pico 2W.
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "hardware/structs/sio.h"

#include "lvgl.h"
#include "ssd1322.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"
#include "ui.h"
#include "pin_config.h"

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
    sleep_ms(500);  // Brief settle, don't wait for USB

    printf("\n=== bonanzaDisplay ===\n");
    printf("System clock: %lu MHz\n\n", clock_get_hz(clk_sys) / 1000000);

    // --- Display hardware init ---
    printf("Init SSD1322 (8080 mode)...\n");
    ssd1322_init_bitbang();
    printf("SSD1322 initialized.\n");

    // Quick blink
    ssd1322_bitbang_cmd(0xA5);  // ALL_ON
    sleep_ms(300);
    ssd1322_bitbang_cmd(0xA6);  // Normal mode
    sleep_ms(200);

    // Fill white
    printf("Fill white...\n");
    ssd1322_test_bitbang_fill(0xFF);
    sleep_ms(2000);

    // Fill black
    printf("Fill black...\n");
    ssd1322_test_bitbang_fill(0x00);
    sleep_ms(1000);

    // Draw test pattern: 4 horizontal bands
    printf("Drawing test pattern...\n");
    ssd1322_bitbang_cmd(0x15);
    ssd1322_bitbang_data(0x1C);
    ssd1322_bitbang_data(0x5B);
    ssd1322_bitbang_cmd(0x75);
    ssd1322_bitbang_data(0x00);
    ssd1322_bitbang_data(0x3F);
    ssd1322_bitbang_cmd(0x5C);

    for (int row = 0; row < 64; row++) {
        for (int col = 0; col < 128; col++) {  // 128 bytes/row = 256 pixels
            if (row < 16) {
                ssd1322_bitbang_data(0xFF);                         // White
            } else if (row < 32) {
                ssd1322_bitbang_data((col % 2 == 0) ? 0xFF : 0x00); // Vertical stripes
            } else if (row < 48) {
                uint8_t g = (col * 15) / 128;
                ssd1322_bitbang_data((g << 4) | g);                 // Gradient
            } else {
                ssd1322_bitbang_data(0x00);                         // Black
            }
        }
    }
    printf("Test pattern done:\n");
    printf("  Top 1/4: solid white\n");
    printf("  2nd 1/4: vertical stripes\n");
    printf("  3rd 1/4: gradient (dark->bright)\n");
    printf("  Bottom 1/4: black\n");

    // Stay forever
    uint32_t count = 0;
    while (1) {
        printf("[%lu] display test active\n", count++);
        sleep_ms(2000);
    }

    return 0;
}
