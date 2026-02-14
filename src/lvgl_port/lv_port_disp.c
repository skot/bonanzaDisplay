/**
 * @file lv_port_disp.c
 * LVGL display port for SSD1322 256x64 OLED
 *
 * Renders in L8 (8-bit grayscale), packs to 4bpp in flush callback,
 * then DMA's the packed buffer to the display via PIO.
 */

#include "lv_port_disp.h"
#include "ssd1322.h"
#include "ssd1322_regs.h"

#include <string.h>

// ==========================================================================
// Framebuffers
// ==========================================================================

#define DISP_HOR_RES    SSD1322_WIDTH   // 256
#define DISP_VER_RES    SSD1322_HEIGHT  // 64
#define DISP_BUF_SIZE   (DISP_HOR_RES * DISP_VER_RES)  // 16384 bytes (L8)

// Double buffers for LVGL (L8 format, 1 byte per pixel)
static uint8_t buf1[DISP_BUF_SIZE];
static uint8_t buf2[DISP_BUF_SIZE];

// Packed 4bpp buffer for DMA output (2 pixels per byte)
static uint8_t packed_buf[DISP_BUF_SIZE / 2];

// Display handle
static lv_display_t *disp;

// ==========================================================================
// L8 → 4bpp Packing
// ==========================================================================

/**
 * Convert L8 buffer (8bpp) to packed 4-bit grayscale (4bpp).
 * Takes the upper nibble of each L8 byte as the 4-bit grayscale value.
 * Two adjacent pixels are packed into one byte:
 *   byte = (left_pixel_4bit << 4) | right_pixel_4bit
 *
 * @param src     L8 source buffer (DISP_BUF_SIZE bytes)
 * @param dst     Packed 4bpp destination (DISP_BUF_SIZE/2 bytes)
 * @param num_px  Number of pixels (must be even)
 */
static void pack_l8_to_4bpp(const uint8_t *src, uint8_t *dst, uint32_t num_px) {
    for (uint32_t i = 0; i < num_px; i += 2) {
        uint8_t hi = (src[i]     >> 4) & 0x0F;  // Left pixel: upper nibble
        uint8_t lo = (src[i + 1] >> 4) & 0x0F;  // Right pixel: upper nibble
        dst[i / 2] = (hi << 4) | lo;
    }
}

// ==========================================================================
// DMA Complete Callback
// ==========================================================================

static void flush_complete_cb(void) {
    lv_display_flush_ready(disp);
}

// ==========================================================================
// LVGL Flush Callback
// ==========================================================================

static void ssd1322_flush_cb(lv_display_t *display, const lv_area_t *area, uint8_t *px_map) {
    // Calculate the number of pixels in the area
    uint32_t w = lv_area_get_width(area);
    uint32_t h = lv_area_get_height(area);
    uint32_t num_px = w * h;

    // For full-screen rendering mode, we always flush the entire screen
    // Pack L8 → 4bpp
    pack_l8_to_4bpp(px_map, packed_buf, num_px);

    // DMA the packed buffer to the display
    ssd1322_flush_dma(packed_buf, num_px / 2, flush_complete_cb);
}

// ==========================================================================
// Public API
// ==========================================================================

void lv_port_disp_init(void) {
    // Create display (LVGL 9.x API)
    disp = lv_display_create(DISP_HOR_RES, DISP_VER_RES);

    // Set color format to L8 (8-bit luminance/grayscale)
    lv_display_set_color_format(disp, LV_COLOR_FORMAT_L8);

    // Set flush callback
    lv_display_set_flush_cb(disp, ssd1322_flush_cb);

    // Set double buffers, full-screen render mode
    lv_display_set_buffers(disp, buf1, buf2, sizeof(buf1),
                           LV_DISPLAY_RENDER_MODE_FULL);
}
