#ifndef LV_PORT_DISP_H
#define LV_PORT_DISP_H

#include "lvgl.h"

/**
 * Initialize the LVGL display driver.
 * Sets up double-buffered L8 rendering with SSD1322 flush callback.
 * Must be called after lv_init() and ssd1322_init().
 */
void lv_port_disp_init(void);

#endif // LV_PORT_DISP_H
