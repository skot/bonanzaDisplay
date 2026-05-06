#ifndef DIAL_SWITCH_H
#define DIAL_SWITCH_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    DIAL_SWITCH_DIR_NONE = 0,
    DIAL_SWITCH_DIR_CW,
    DIAL_SWITCH_DIR_CCW,
} dial_switch_dir_t;

typedef struct {
    int32_t position;
    int8_t quadrature_accum;
    uint32_t cw_count;
    uint32_t ccw_count;
    uint32_t press_count;
    bool switch_pressed;
    bool cw_active;
    bool ccw_active;
    uint8_t phase;
    dial_switch_dir_t last_dir;
} dial_switch_state_t;

void dial_switch_init(void);
void dial_switch_update(void);
const dial_switch_state_t *dial_switch_get_state(void);
const char *dial_switch_dir_name(dial_switch_dir_t dir);

#endif // DIAL_SWITCH_H
