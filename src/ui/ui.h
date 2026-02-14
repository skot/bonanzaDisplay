#ifndef UI_H
#define UI_H

#include "lvgl.h"

/**
 * Create the dashboard screen UI.
 * Builds the main status display with labels, bars, etc.
 */
void ui_dashboard_create(void);

/**
 * Update dashboard with new data values.
 * Call periodically from the main loop or a timer callback.
 */
void ui_dashboard_update(void);

#endif // UI_H
