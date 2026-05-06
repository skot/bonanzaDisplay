#include "dial_switch.h"
#include "pin_config.h"

#include "hardware/gpio.h"
#include "pico/time.h"

#define SWITCH_DEBOUNCE_MS 20u
#define QUADRATURE_STEPS_PER_DETENT 4

typedef struct {
    uint pin;
    bool was_active;
    uint32_t last_edge_ms;
} dial_contact_t;

static dial_contact_t contact_sw = { PIN_DIAL_SW, false, 0 };
static dial_switch_state_t state;
static uint8_t last_phase;

static void init_contact(uint pin) {
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
    gpio_pull_up(pin);
}

static uint8_t read_phase(void) {
    bool phase_a = !gpio_get(PIN_DIAL_CCW);
    bool phase_b = !gpio_get(PIN_DIAL_CW);
    return (phase_a ? 2u : 0u) | (phase_b ? 1u : 0u);
}

static bool update_contact(dial_contact_t *contact, uint32_t now_ms) {
    bool active = !gpio_get(contact->pin);
    bool pressed_edge = false;

    if (active != contact->was_active &&
        now_ms - contact->last_edge_ms >= SWITCH_DEBOUNCE_MS) {
        contact->was_active = active;
        contact->last_edge_ms = now_ms;
        pressed_edge = active;
    }

    return pressed_edge;
}

static int8_t decode_quadrature_step(uint8_t previous, uint8_t current) {
    static const int8_t transition_table[16] = {
        0,  1, -1,  0,
       -1,  0,  0,  1,
        1,  0,  0, -1,
        0, -1,  1,  0,
    };

    return transition_table[((previous & 0x3u) << 2) | (current & 0x3u)];
}

void dial_switch_init(void) {
    init_contact(PIN_DIAL_CW);
    init_contact(PIN_DIAL_CCW);
    init_contact(PIN_DIAL_SW);

    state = (dial_switch_state_t) {
        .last_dir = DIAL_SWITCH_DIR_NONE,
    };

    last_phase = read_phase();
    state.phase = last_phase;
    state.cw_active = (last_phase & 0x1u) != 0;
    state.ccw_active = (last_phase & 0x2u) != 0;
    contact_sw.was_active = !gpio_get(PIN_DIAL_SW);
    uint32_t now_ms = to_ms_since_boot(get_absolute_time());
    contact_sw.last_edge_ms = now_ms;
}

void dial_switch_update(void) {
    uint32_t now_ms = to_ms_since_boot(get_absolute_time());
    uint8_t phase = read_phase();

    if (phase != last_phase) {
        state.quadrature_accum += decode_quadrature_step(last_phase, phase);
        last_phase = phase;
    }

    if (state.quadrature_accum >= QUADRATURE_STEPS_PER_DETENT) {
        state.position++;
        state.cw_count++;
        state.last_dir = DIAL_SWITCH_DIR_CW;
        state.quadrature_accum = 0;
    }

    if (state.quadrature_accum <= -QUADRATURE_STEPS_PER_DETENT) {
        state.position--;
        state.ccw_count++;
        state.last_dir = DIAL_SWITCH_DIR_CCW;
        state.quadrature_accum = 0;
    }

    if (update_contact(&contact_sw, now_ms)) {
        state.press_count++;
    }

    state.phase = phase;
    state.cw_active = (phase & 0x1u) != 0;
    state.ccw_active = (phase & 0x2u) != 0;
    state.switch_pressed = contact_sw.was_active;
}

const dial_switch_state_t *dial_switch_get_state(void) {
    return &state;
}

const char *dial_switch_dir_name(dial_switch_dir_t dir) {
    switch (dir) {
    case DIAL_SWITCH_DIR_CW:
        return "CW";
    case DIAL_SWITCH_DIR_CCW:
        return "CCW";
    default:
        return "--";
    }
}
