#include "bonanza_ui.h"

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
