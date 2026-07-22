#include "bonanza_ui.h"

#include <limits.h>
#include <stdio.h>

static int32_t subject_value(uint32_t value) {
    return value > INT32_MAX ? INT32_MAX : (int32_t)value;
}

void bonanza_ui_init(const char *asset_path) {
    bonanza_ui_init_gen(asset_path);
}

void bonanza_ui_set_dial_state(int32_t position, int32_t direction,
                               bool pressed, uint32_t cw, uint32_t ccw,
                               uint32_t presses, uint8_t phase) {
    lv_subject_set_int(&dial_position, position);
    lv_subject_set_int(&dial_direction, direction);
    lv_subject_set_int(&switch_pressed, pressed ? 1 : 0);
    lv_subject_set_int(&cw_count, (int32_t)cw);
    lv_subject_set_int(&ccw_count, (int32_t)ccw);
    lv_subject_set_int(&press_count, (int32_t)presses);
    lv_subject_set_int(&dial_phase, phase);
}

void bonanza_ui_set_metrics(const char *device_family, const char *device_model,
                            const char *device_name, const char *ip_address,
                            const char *best_share, uint32_t hashrate,
                            uint32_t temperature, uint32_t power,
                            uint32_t frequency, uint32_t fan) {
    char identity[UI_SUBJECT_STRING_LENGTH];
    snprintf(identity, sizeof(identity), "%s %s", device_family, device_model);

    lv_subject_copy_string(&device_identity, identity);
    lv_subject_copy_string(&device_name_text, device_name);
    lv_subject_copy_string(&ip_address_text, ip_address);
    lv_subject_copy_string(&best_share_text, best_share);
    lv_subject_set_int(&hashrate_ghs, subject_value(hashrate));
    lv_subject_set_int(&asic_temp_c, subject_value(temperature));
    lv_subject_set_int(&power_w, subject_value(power));
    lv_subject_set_int(&frequency_mhz, subject_value(frequency));
    lv_subject_set_int(&fan_percent, subject_value(fan));
}
