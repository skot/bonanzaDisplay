#ifndef SSD1322_H
#define SSD1322_H

#include <stdint.h>
#include <stdbool.h>
#include "hardware/pio.h"

// ==========================================================================
// SSD1322 OLED Display Driver — Public API
// 8080 parallel interface via PIO + DMA
// ==========================================================================

/**
 * Initialize the SSD1322 display hardware.
 * Sets up GPIO, PIO state machine, DMA channel, and runs the
 * SSD1322 initialization sequence.
 */
void ssd1322_init(void);

/**
 * Send a command byte to the SSD1322.
 * Sets DC# low, sends byte via PIO.
 * @param cmd Command byte
 */
void ssd1322_write_cmd(uint8_t cmd);

/**
 * Send a data byte to the SSD1322.
 * Sets DC# high, sends byte via PIO.
 * @param data Data byte
 */
void ssd1322_write_data(uint8_t data);

/**
 * Send multiple data bytes to the SSD1322.
 * Sets DC# high, then pushes all bytes through PIO.
 * @param data Pointer to data buffer
 * @param len  Number of bytes
 */
void ssd1322_write_data_bulk(const uint8_t *data, uint16_t len);

/**
 * Set the column and row address window for subsequent RAM writes.
 * @param col_start Start column (each column = 4 pixels)
 * @param col_end   End column
 * @param row_start Start row
 * @param row_end   End row
 */
void ssd1322_set_window(uint8_t col_start, uint8_t col_end,
                         uint8_t row_start, uint8_t row_end);

/**
 * Send a framebuffer to the display via DMA.
 * The buffer must be in packed 4-bit grayscale format (2 pixels per byte).
 * Buffer size = (256 * 64) / 2 = 8192 bytes.
 *
 * @param buf       Pointer to packed 4bpp framebuffer
 * @param len       Buffer length in bytes
 * @param callback  Function called when DMA transfer completes (can be NULL)
 */
void ssd1322_flush_dma(const uint8_t *buf, uint16_t len, void (*callback)(void));

/**
 * Set display contrast (brightness).
 * @param contrast Contrast value 0–255
 */
void ssd1322_set_contrast(uint8_t contrast);

/**
 * Turn the display on or off.
 * @param on true = display on, false = display off (sleep)
 */
void ssd1322_set_display_on(bool on);

/**
 * Check if DMA transfer is currently in progress.
 * @return true if busy
 */
bool ssd1322_is_busy(void);

#endif // SSD1322_H
