/**
 * @file ssd1322.c
 * SSD1322 OLED display driver — 8080 parallel via PIO + DMA
 */

#include "ssd1322.h"
#include "ssd1322_regs.h"
#include "pin_config.h"
#include "parallel_8080.pio.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pio.h"
#include "hardware/dma.h"
#include "hardware/clocks.h"

#include <string.h>

// ==========================================================================
// Internal State
// ==========================================================================

static PIO     pio_inst    = pio0;
static uint    pio_sm      = 0;
static uint    pio_offset  = 0;
static int     dma_channel = -1;
static volatile bool dma_busy = false;
static void    (*dma_complete_callback)(void) = NULL;

// ==========================================================================
// DMA IRQ Handler
// ==========================================================================

static void dma_irq_handler(void) {
    if (dma_channel_get_irq0_status(dma_channel)) {
        dma_channel_acknowledge_irq0(dma_channel);
        dma_busy = false;
        if (dma_complete_callback) {
            dma_complete_callback();
            dma_complete_callback = NULL;
        }
    }
}

// ==========================================================================
// Low-level Write Helpers
// ==========================================================================

/**
 * Wait for PIO TX FIFO to drain (all data shifted out).
 */
static inline void pio_wait_idle(void) {
    // Wait until TX FIFO is empty and state machine is idle
    while (!pio_sm_is_tx_fifo_empty(pio_inst, pio_sm)) {
        tight_loop_contents();
    }
    // Small delay for last byte to clock out
    sleep_us(1);
}

/**
 * Push a single byte into PIO TX FIFO.
 */
static inline void pio_put_byte(uint8_t byte) {
    pio_sm_put_blocking(pio_inst, pio_sm, (uint32_t)byte);
}

// ==========================================================================
// Public API
// ==========================================================================

void ssd1322_write_cmd(uint8_t cmd) {
    pio_wait_idle();
    gpio_put(PIN_DC, 0);    // DC# low = command
    pio_put_byte(cmd);
    pio_wait_idle();
}

void ssd1322_write_data(uint8_t data) {
    pio_wait_idle();
    gpio_put(PIN_DC, 1);    // DC# high = data
    pio_put_byte(data);
}

void ssd1322_write_data_bulk(const uint8_t *data, uint16_t len) {
    pio_wait_idle();
    gpio_put(PIN_DC, 1);    // DC# high = data
    for (uint16_t i = 0; i < len; i++) {
        pio_put_byte(data[i]);
    }
}

/**
 * Send a command followed by data argument bytes.
 */
static void ssd1322_cmd_with_args(uint8_t cmd, const uint8_t *args, uint8_t num_args) {
    ssd1322_write_cmd(cmd);
    for (uint8_t i = 0; i < num_args; i++) {
        ssd1322_write_data(args[i]);
    }
}

void ssd1322_set_window(uint8_t col_start, uint8_t col_end,
                         uint8_t row_start, uint8_t row_end) {
    uint8_t col_args[2] = { col_start, col_end };
    uint8_t row_args[2] = { row_start, row_end };

    ssd1322_cmd_with_args(SSD1322_CMD_SET_COLUMN_ADDR, col_args, 2);
    ssd1322_cmd_with_args(SSD1322_CMD_SET_ROW_ADDR, row_args, 2);
}

void ssd1322_set_contrast(uint8_t contrast) {
    uint8_t args[1] = { contrast };
    ssd1322_cmd_with_args(SSD1322_CMD_SET_CONTRAST, args, 1);
}

void ssd1322_set_display_on(bool on) {
    ssd1322_write_cmd(on ? SSD1322_CMD_DISPLAY_ON : SSD1322_CMD_DISPLAY_OFF);
}

bool ssd1322_is_busy(void) {
    return dma_busy;
}

// ==========================================================================
// DMA Flush
// ==========================================================================

void ssd1322_flush_dma(const uint8_t *buf, uint16_t len, void (*callback)(void)) {
    // Wait for any previous DMA transfer to complete
    while (dma_busy) {
        tight_loop_contents();
    }

    // Set up the display window for full screen
    ssd1322_set_window(SSD1322_COL_START, SSD1322_COL_END,
                        SSD1322_ROW_START, SSD1322_ROW_END);

    // Begin RAM write
    ssd1322_write_cmd(SSD1322_CMD_WRITE_RAM);

    // Switch to data mode
    pio_wait_idle();
    gpio_put(PIN_DC, 1);

    // Configure DMA transfer
    dma_complete_callback = callback;
    dma_busy = true;

    dma_channel_config cfg = dma_channel_get_default_config(dma_channel);
    channel_config_set_transfer_data_size(&cfg, DMA_SIZE_8);
    channel_config_set_read_increment(&cfg, true);
    channel_config_set_write_increment(&cfg, false);
    channel_config_set_dreq(&cfg, pio_get_dreq(pio_inst, pio_sm, true));

    dma_channel_configure(
        dma_channel,
        &cfg,
        &pio_inst->txf[pio_sm],  // Write to PIO TX FIFO
        buf,                      // Read from framebuffer
        len,                      // Transfer count
        true                      // Start immediately
    );
}

// ==========================================================================
// Initialization
// ==========================================================================

/**
 * Initialize GPIO pins for control signals (DC#, RES#, CS#, RD#).
 */
static void gpio_init_control_pins(void) {
    // RD# — held high (read not used)
    gpio_init(PIN_RD);
    gpio_set_dir(PIN_RD, GPIO_OUT);
    gpio_put(PIN_RD, 1);

    // DC# — data/command select
    gpio_init(PIN_DC);
    gpio_set_dir(PIN_DC, GPIO_OUT);
    gpio_put(PIN_DC, 1);

    // RES# — reset (active low)
    gpio_init(PIN_RES);
    gpio_set_dir(PIN_RES, GPIO_OUT);
    gpio_put(PIN_RES, 1);

    // CS# — chip select (active low, hold low for entire session)
    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 0);
}

/**
 * Hardware reset pulse on RES# pin.
 */
static void ssd1322_hw_reset(void) {
    gpio_put(PIN_RES, 1);
    sleep_ms(10);
    gpio_put(PIN_RES, 0);
    sleep_ms(10);
    gpio_put(PIN_RES, 1);
    sleep_ms(50);   // Wait for reset to complete
}

/**
 * Initialize PIO state machine for 8080 parallel output.
 */
static void pio_init_8080(void) {
    pio_offset = pio_add_program(pio_inst, &parallel_8080_program);

    // Clock divider: 1.0 = run at system clock (150 MHz)
    // Each PIO write cycle ~12 instructions = ~80 ns per byte
    float clk_div = 1.0f;

    parallel_8080_program_init(pio_inst, pio_sm, pio_offset,
                                PIN_DATA_BASE, PIN_WR, clk_div);
}

/**
 * Initialize DMA channel for PIO transfers.
 */
static void dma_init_channel(void) {
    dma_channel = dma_claim_unused_channel(true);

    // Enable DMA IRQ
    dma_channel_set_irq0_enabled(dma_channel, true);
    irq_set_exclusive_handler(DMA_IRQ_0, dma_irq_handler);
    irq_set_enabled(DMA_IRQ_0, true);
}

/**
 * SSD1322 display initialization command sequence.
 */
static void ssd1322_init_sequence(void) {
    // Unlock command interface
    ssd1322_cmd_with_args(SSD1322_CMD_SET_COMMAND_LOCK, (uint8_t[]){0x12}, 1);

    // Display OFF during setup
    ssd1322_write_cmd(SSD1322_CMD_DISPLAY_OFF);

    // Set clock divide ratio / oscillator frequency
    // [7:4] = oscillator freq, [3:0] = divide ratio
    ssd1322_cmd_with_args(SSD1322_CMD_SET_CLOCK_DIV, (uint8_t[]){0x91}, 1);

    // Set MUX ratio to 64 (N-1 = 63 = 0x3F)
    ssd1322_cmd_with_args(SSD1322_CMD_SET_MUX_RATIO, (uint8_t[]){0x3F}, 1);

    // Set display offset to 0
    ssd1322_cmd_with_args(SSD1322_CMD_SET_DISPLAY_OFFSET, (uint8_t[]){0x00}, 1);

    // Set start line to 0
    ssd1322_cmd_with_args(SSD1322_CMD_SET_START_LINE, (uint8_t[]){0x00}, 1);

    // Set re-map and dual COM line mode
    // Byte 0: [0] = column address remap, [1] = nibble remap,
    //         [2] = horizontal address increment, [4] = COM remap
    // Byte 1: [4] = COM split odd/even, [0] = dual COM mode
    ssd1322_cmd_with_args(SSD1322_CMD_SET_REMAP, (uint8_t[]){0x14, 0x11}, 2);

    // Set GPIO (disable)
    ssd1322_cmd_with_args(SSD1322_CMD_SET_GPIO, (uint8_t[]){0x00}, 1);

    // Function select: enable internal VDD regulator
    ssd1322_cmd_with_args(SSD1322_CMD_FUNCTION_SELECT, (uint8_t[]){0x01}, 1);

    // Set phase length: [3:0] = phase 1 (reset), [7:4] = phase 2 (precharge)
    ssd1322_cmd_with_args(SSD1322_CMD_SET_PHASE_LENGTH, (uint8_t[]){0xE2}, 1);

    // Set contrast current
    ssd1322_cmd_with_args(SSD1322_CMD_SET_CONTRAST, (uint8_t[]){0x9F}, 1);

    // Set master contrast (0–15)
    ssd1322_cmd_with_args(SSD1322_CMD_MASTER_CONTRAST, (uint8_t[]){0x0F}, 1);

    // Use default linear grayscale table
    ssd1322_write_cmd(SSD1322_CMD_DEFAULT_GRAYSCALE);

    // Set pre-charge voltage level
    ssd1322_cmd_with_args(SSD1322_CMD_SET_PRECHARGE_VOLTAGE, (uint8_t[]){0x17}, 1);

    // Set second pre-charge period
    ssd1322_cmd_with_args(SSD1322_CMD_SET_SECOND_PRECHARGE, (uint8_t[]){0x08}, 1);

    // Set VCOMH deselect level
    ssd1322_cmd_with_args(SSD1322_CMD_SET_VCOMH, (uint8_t[]){0x07}, 1);

    // Normal display mode (not inverted, not all-on)
    ssd1322_write_cmd(SSD1322_CMD_NORMAL_DISPLAY);

    // Exit partial display mode
    ssd1322_write_cmd(SSD1322_CMD_EXIT_PARTIAL);

    // Clear display RAM
    ssd1322_set_window(SSD1322_COL_START, SSD1322_COL_END,
                        SSD1322_ROW_START, SSD1322_ROW_END);
    ssd1322_write_cmd(SSD1322_CMD_WRITE_RAM);
    for (uint16_t i = 0; i < (SSD1322_WIDTH / 2) * SSD1322_HEIGHT; i++) {
        ssd1322_write_data(0x00);
    }

    // Display ON
    ssd1322_write_cmd(SSD1322_CMD_DISPLAY_ON);
}

void ssd1322_init(void) {
    // 1. Initialize control GPIO pins
    gpio_init_control_pins();

    // 2. Hardware reset
    ssd1322_hw_reset();

    // 3. Initialize PIO for 8080 parallel bus
    pio_init_8080();

    // 4. Initialize DMA
    dma_init_channel();

    // 5. Run SSD1322 initialization command sequence
    ssd1322_init_sequence();
}
