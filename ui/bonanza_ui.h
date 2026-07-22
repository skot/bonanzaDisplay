#ifndef BONANZA_UI_H
#define BONANZA_UI_H

#include <stdbool.h>
#include <stdint.h>

#include "bonanza_ui_gen.h"

void bonanza_ui_init(const char *asset_path);
void bonanza_ui_set_dial_state(int32_t position, int32_t direction,
                               bool pressed, uint32_t cw, uint32_t ccw,
                               uint32_t presses, uint8_t phase);

#endif /* BONANZA_UI_H */
