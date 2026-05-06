/**
 * @file main.c
 * bonanzaDisplay — Main entry point
 *
 * Bare-metal super loop driving SSD1322 OLED via LVGL on RPi Pico 2W.
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
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
#include "fonts.h"
#include "dial_switch.h"

// ==========================================================================
// LVGL Tick — Pico SDK monotonic ms clock
// ==========================================================================

static uint32_t pico_tick_get_cb(void) {
    return to_ms_since_boot(get_absolute_time());
}

// ==========================================================================
// Debug Logging
// ==========================================================================

static void debug_log(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    stdio_flush();
}

static void wait_for_usb_serial(void) {
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }

    // Give the host-side terminal a moment to finish configuring the port.
    sleep_ms(250);
}

#if BONANZA_DISPLAY_BRINGUP_TEST
static void run_display_bringup_test(void) {
    debug_log("\n=== bonanzaDisplay SSD1322 bring-up test ===\n");
    debug_log("Boot ms: %lu\n", (unsigned long)to_ms_since_boot(get_absolute_time()));
    debug_log("System clock: %lu MHz\n", clock_get_hz(clk_sys) / 1000000);
    debug_log("Data bus: D0=GPIO%d D1=GPIO%d D2=GPIO%d D3=GPIO%d D4=GPIO%d D5=GPIO%d D6=GPIO%d D7=GPIO%d\n",
              PIN_DB0, PIN_DB1, PIN_DB2, PIN_DB3, PIN_DB4, PIN_DB5, PIN_DB6, PIN_DB7);
    debug_log("Control: RD#=GPIO%d WR#=GPIO%d DC#=GPIO%d CS#=GPIO%d RES#=GPIO%d\n",
              PIN_RD, PIN_WR, PIN_DC, PIN_CS, PIN_RES);

    debug_log("Initializing SSD1322 with GPIO bit-bang path...\n");
    ssd1322_init_bitbang();
    stdio_flush();
    debug_log("Bit-bang init returned.\n");

    ssd1322_debug_gpio_state();
    stdio_flush();

    uint32_t cycle = 0;
    const uint8_t patterns[] = {
        0xFF,  // all white
        0x00,  // all black
        0xF0,  // alternating bright/dark pixels
        0x0F,  // alternating dark/bright pixels
        0xAA,  // checker-ish nibble pattern
        0x55
    };

    while (1) {
        debug_log("Cycle %lu: SSD1322 all-on command (0xA5)\n", (unsigned long)cycle);
        ssd1322_bitbang_cmd(0xA5);
        sleep_ms(1000);

        debug_log("Cycle %lu: normal display command (0xA6)\n", (unsigned long)cycle);
        ssd1322_bitbang_cmd(0xA6);
        sleep_ms(250);

        for (uint32_t i = 0; i < sizeof(patterns); i++) {
            debug_log("Cycle %lu: visible-window fill pattern 0x%02X\n",
                      (unsigned long)cycle, patterns[i]);
            ssd1322_test_bitbang_fill(patterns[i]);
            stdio_flush();
            sleep_ms(1000);
        }

        debug_log("Cycle %lu complete.\n", (unsigned long)cycle);
        cycle++;
    }
}
#endif

// ==========================================================================
// Main
// ==========================================================================

int main(void) {
    // --- Platform init ---
    stdio_init_all();

#if BONANZA_DISPLAY_BRINGUP_TEST
    wait_for_usb_serial();
    run_display_bringup_test();
#else
    sleep_ms(500);

    debug_log("\n=== bonanzaDisplay (LVGL + PIO + DMA) ===\n");
    debug_log("Boot ms: %lu\n", (unsigned long)to_ms_since_boot(get_absolute_time()));
    debug_log("System clock: %lu MHz\n\n", clock_get_hz(clk_sys) / 1000000);

    // --- Display hardware init (PIO + DMA) ---
    debug_log("Init SSD1322 (PIO 8080 mode)...\n");
    ssd1322_init();
    debug_log("SSD1322 initialized.\n");

    // --- Dial switch init ---
    debug_log("Init dial switch...\n");
    dial_switch_init();
    debug_log("Dial switch ready: CCW=GPIO%d CW=GPIO%d SW=GPIO%d\n",
              PIN_DIAL_CCW, PIN_DIAL_CW, PIN_DIAL_SW);

    // Quick blink to confirm display alive
    debug_log("SSD1322 all-on blink...\n");
    ssd1322_write_cmd(0xA5);  // ALL_ON
    sleep_ms(200);
    ssd1322_write_cmd(0xA6);  // Normal mode
    sleep_ms(100);
    debug_log("SSD1322 blink complete.\n");

    // --- LVGL init ---
    debug_log("Init LVGL...\n");
    lv_init();
    lv_tick_set_cb(pico_tick_get_cb);
    lv_port_disp_init();
    debug_log("LVGL ready.\n");

    // --- Create a simple demo UI ---
    lv_obj_t *scr = lv_screen_active();

    // Style: white text on black background
    lv_obj_set_style_bg_color(scr, lv_color_black(), 0);
    lv_obj_set_style_bg_opa(scr, LV_OPA_COVER, 0);

    // Title label — large, centered near top
    lv_obj_t *title = lv_label_create(scr);
    lv_label_set_text(title, "Dial Switch");
    lv_obj_set_style_text_color(title, lv_color_white(), 0);
    lv_obj_set_style_text_font(title, &lv_font_portfolio_6x8, 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 4);

    lv_obj_t *position_label = lv_label_create(scr);
    lv_label_set_text(position_label, "POS +0");
    lv_obj_set_style_text_color(position_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(position_label, &lv_font_portfolio_6x8, 0);
    lv_obj_align(position_label, LV_ALIGN_LEFT_MID, 6, -8);

    lv_obj_t *direction_label = lv_label_create(scr);
    lv_label_set_text(direction_label, "DIR --");
    lv_obj_set_style_text_color(direction_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(direction_label, &lv_font_portfolio_6x8, 0);
    lv_obj_align(direction_label, LV_ALIGN_RIGHT_MID, -8, -8);

    lv_obj_t *switch_label = lv_label_create(scr);
    lv_label_set_text(switch_label, "SW UP");
    lv_obj_set_style_text_color(switch_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(switch_label, &lv_font_portfolio_6x8, 0);
    lv_obj_align(switch_label, LV_ALIGN_LEFT_MID, 6, 10);

    lv_obj_t *counts_label = lv_label_create(scr);
    lv_label_set_text(counts_label, "CW 0  CCW 0  P 0");
    lv_obj_set_style_text_color(counts_label, lv_color_white(), 0);
    lv_obj_set_style_text_font(counts_label, &lv_font_portfolio_6x8, 0);
    lv_obj_align(counts_label, LV_ALIGN_BOTTOM_MID, 0, -4);

    debug_log("Entering LVGL main loop...\n");

    // --- Main loop ---
    uint32_t frame = 0;
    uint32_t last_heartbeat_ms = to_ms_since_boot(get_absolute_time());
    int32_t shown_position = INT32_MIN;
    uint32_t shown_cw_count = UINT32_MAX;
    uint32_t shown_ccw_count = UINT32_MAX;
    uint32_t shown_press_count = UINT32_MAX;
    uint8_t shown_phase = UINT8_MAX;
    int8_t shown_quadrature_accum = INT8_MAX;
    bool shown_switch_pressed = false;
    dial_switch_dir_t shown_dir = DIAL_SWITCH_DIR_NONE;
    char buf[40];
    while (1) {
        dial_switch_update();
        lv_timer_handler();  // Run LVGL tasks (render, animations, etc.)
        sleep_ms(5);         // ~200 Hz poll rate, LVGL handles its own timing

        const dial_switch_state_t *dial = dial_switch_get_state();
        if (dial->position != shown_position) {
            snprintf(buf, sizeof(buf), "POS %+ld", (long)dial->position);
            lv_label_set_text(position_label, buf);
            shown_position = dial->position;
        }

        if (dial->last_dir != shown_dir) {
            snprintf(buf, sizeof(buf), "DIR %s", dial_switch_dir_name(dial->last_dir));
            lv_label_set_text(direction_label, buf);
            shown_dir = dial->last_dir;
        }

        if (dial->switch_pressed != shown_switch_pressed) {
            lv_label_set_text(switch_label, dial->switch_pressed ? "SW DOWN" : "SW UP");
            shown_switch_pressed = dial->switch_pressed;
        }

        if (dial->cw_count != shown_cw_count ||
            dial->ccw_count != shown_ccw_count ||
            dial->press_count != shown_press_count ||
            dial->phase != shown_phase ||
            dial->quadrature_accum != shown_quadrature_accum) {
            snprintf(buf, sizeof(buf), "CW %lu CCW %lu P %lu PH %u%u",
                     (unsigned long)dial->cw_count,
                     (unsigned long)dial->ccw_count,
                     (unsigned long)dial->press_count,
                     (unsigned)((dial->phase >> 1) & 1u),
                     (unsigned)(dial->phase & 1u));
            lv_label_set_text(counts_label, buf);
            shown_cw_count = dial->cw_count;
            shown_ccw_count = dial->ccw_count;
            shown_press_count = dial->press_count;
            shown_phase = dial->phase;
            shown_quadrature_accum = dial->quadrature_accum;
        }

        uint32_t now_ms = to_ms_since_boot(get_absolute_time());
        if (now_ms - last_heartbeat_ms >= 1000) {
            debug_log("Heartbeat: frame=%lu uptime_ms=%lu\n",
                      (unsigned long)frame, (unsigned long)now_ms);
            last_heartbeat_ms = now_ms;
        }
        frame++;
    }
#endif

    return 0;
}
