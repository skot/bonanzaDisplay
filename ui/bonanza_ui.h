#ifndef BONANZA_UI_H
#define BONANZA_UI_H

#include <stdbool.h>
#include <stdint.h>

#include "bonanza_ui_gen.h"

void bonanza_ui_init(const char *asset_path);
void bonanza_ui_set_dial_state(int32_t position, int32_t direction,
                               bool pressed, uint32_t cw, uint32_t ccw,
                               uint32_t presses, uint8_t phase);
void bonanza_ui_set_metrics(const char *device_family, const char *device_model,
                            const char *device_name, const char *ip_address,
                            const char *best_share, uint32_t hashrate,
                            uint32_t temperature, uint32_t power,
                            uint32_t frequency, uint32_t fan);

#endif /* BONANZA_UI_H */
