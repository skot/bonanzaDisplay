/**
 * @file lv_port_indev.c
 * LVGL input device port — placeholder
 *
 * GPIO assignments for buttons/encoder are TBD.
 * This file provides the skeleton for when input hardware is finalized.
 */

#include "lv_port_indev.h"
#include "pin_config.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"

// ==========================================================================
// Input Read Callback (placeholder)
// ==========================================================================

#if 0  // Enable when input hardware is wired up

static void encoder_read_cb(lv_indev_t *indev, lv_indev_data_t *data) {
    // TODO: Read rotary encoder state
    // data->enc_diff = encoder_get_diff();
    // data->state = gpio_get(PIN_ENC_SW) ? LV_INDEV_STATE_RELEASED : LV_INDEV_STATE_PRESSED;
    (void)indev;
    data->enc_diff = 0;
    data->state = LV_INDEV_STATE_RELEASED;
}

#endif

// ==========================================================================
// Public API
// ==========================================================================

void lv_port_indev_init(void) {
    // Input device initialization — uncomment and configure when ready

    /*
    // --- Rotary encoder ---
    gpio_init(PIN_ENC_A);
    gpio_set_dir(PIN_ENC_A, GPIO_IN);
    gpio_pull_up(PIN_ENC_A);

    gpio_init(PIN_ENC_B);
    gpio_set_dir(PIN_ENC_B, GPIO_IN);
    gpio_pull_up(PIN_ENC_B);

    gpio_init(PIN_ENC_SW);
    gpio_set_dir(PIN_ENC_SW, GPIO_IN);
    gpio_pull_up(PIN_ENC_SW);

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_ENCODER);
    lv_indev_set_read_cb(indev, encoder_read_cb);
    */
}
