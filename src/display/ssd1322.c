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
#include "hardware/structs/sio.h"

#include <string.h>
#include <stdio.h>

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

void ssd1322_fill(uint8_t pattern) {
    ssd1322_set_window(SSD1322_COL_START, SSD1322_COL_END,
                        SSD1322_ROW_START, SSD1322_ROW_END);
    ssd1322_write_cmd(SSD1322_CMD_WRITE_RAM);
    pio_wait_idle();
    gpio_put(PIN_DC, 1);  // Data mode for entire fill
    for (int i = 0; i < (SSD1322_WIDTH / 2) * SSD1322_HEIGHT; i++) {
        pio_put_byte(pattern);
    }
    pio_wait_idle();
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

    // Clock divider: 4.0 = PIO at 37.5 MHz (26.67 ns/cycle)
    // WR# low = 8 × 26.67 = 213 ns, high = 5 × 26.67 = 133 ns
    // Total cycle = 347 ns (SSD1322 min = 150 ns)
    float clk_div = 4.0f;

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

    // Display Enhancement A: enable internal VSL + enhanced low GS quality
    ssd1322_cmd_with_args(SSD1322_CMD_DISPLAY_ENHANCE_A, (uint8_t[]){0xA0, 0xFD}, 2);

    // Set phase length: [3:0] = phase 1 (reset), [7:4] = phase 2 (precharge)
    ssd1322_cmd_with_args(SSD1322_CMD_SET_PHASE_LENGTH, (uint8_t[]){0xE2}, 1);

    // Set contrast current
    ssd1322_cmd_with_args(SSD1322_CMD_SET_CONTRAST, (uint8_t[]){0x9F}, 1);

    // Set master contrast (0–15)
    ssd1322_cmd_with_args(SSD1322_CMD_MASTER_CONTRAST, (uint8_t[]){0x0F}, 1);

    // Use default linear grayscale table
    ssd1322_write_cmd(SSD1322_CMD_DEFAULT_GRAYSCALE);

    // Set pre-charge voltage level
    ssd1322_cmd_with_args(SSD1322_CMD_SET_PRECHARGE_VOLTAGE, (uint8_t[]){0x1F}, 1);

    // Set second pre-charge period
    ssd1322_cmd_with_args(SSD1322_CMD_SET_SECOND_PRECHARGE, (uint8_t[]){0x08}, 1);

    // Display Enhancement B
    ssd1322_cmd_with_args(SSD1322_CMD_DISPLAY_ENHANCE_B, (uint8_t[]){0xA2, 0x20}, 2);

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
    for (uint32_t i = 0; i < (SSD1322_WIDTH / 2) * SSD1322_HEIGHT; i++) {
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

// ==========================================================================
// GPIO Bit-Bang (bypasses PIO entirely for debugging)
// ==========================================================================

static bool bitbang_mode = false;

static void bitbang_gpio_setup(void) {
    if (bitbang_mode) return;

    // 8080 mode: WR# idles HIGH
    gpio_set_function(PIN_WR, GPIO_FUNC_SIO);
    gpio_set_dir(PIN_WR, GPIO_OUT);
    gpio_put(PIN_WR, 1);

    // Now set up data pins
    for (int i = 0; i < 8; i++) {
        gpio_set_function(PIN_DATA_BASE + i, GPIO_FUNC_SIO);
        gpio_set_dir(PIN_DATA_BASE + i, GPIO_OUT);
        gpio_put(PIN_DATA_BASE + i, 0);
    }

    bitbang_mode = true;
}

static void bitbang_write_byte(uint8_t byte, bool is_data) {
    gpio_put(PIN_DC, is_data ? 1 : 0);
    sleep_us(1);  // DC setup time

    // Set all 8 data pins atomically using masked write
    uint32_t data_mask = 0xFF << PIN_DATA_BASE;  // GPIO 0-7
    uint32_t data_value = ((uint32_t)byte) << PIN_DATA_BASE;
    gpio_put_masked(data_mask, data_value);

    sleep_us(1);  // Data setup time

    // 8080 mode: data latches on RISING edge of WR#
    gpio_put(PIN_WR, 0);  // WR# low
    sleep_us(1);           // WR# low pulse width
    gpio_put(PIN_WR, 1);  // WR# high — data latches
    sleep_us(1);           // Hold time
}

void ssd1322_bitbang_cmd(uint8_t cmd) {
    bitbang_gpio_setup();
    bitbang_write_byte(cmd, false);
}

void ssd1322_bitbang_data(uint8_t data) {
    bitbang_gpio_setup();
    bitbang_write_byte(data, true);
}

static void bitbang_cmd_with_args(uint8_t cmd, const uint8_t *args, uint8_t n) {
    bitbang_write_byte(cmd, false);
    for (uint8_t i = 0; i < n; i++) {
        bitbang_write_byte(args[i], true);
    }
}

void ssd1322_minimal_reset(void) {
    printf("  Setting up control GPIO (minimal)...\n");

    // Control pins (8080 mode)
    gpio_init(PIN_RD);
    gpio_set_dir(PIN_RD, GPIO_OUT);
    gpio_put(PIN_RD, 1);  // RD# high (not reading)

    gpio_init(PIN_DC);
    gpio_set_dir(PIN_DC, GPIO_OUT);
    gpio_put(PIN_DC, 1);

    gpio_init(PIN_RES);
    gpio_set_dir(PIN_RES, GPIO_OUT);
    gpio_put(PIN_RES, 1);

    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 0);  // CS# low (selected)

    // Data + WR pins
    bitbang_gpio_setup();

    // Hardware reset only
    printf("  Hardware reset...\n");
    gpio_put(PIN_RES, 1);
    sleep_ms(10);
    gpio_put(PIN_RES, 0);
    sleep_ms(10);
    gpio_put(PIN_RES, 1);
    sleep_ms(100);
    printf("  Minimal reset complete.\n");
}

void ssd1322_init_bitbang(void) {
    printf("  Setting up control GPIO (8080 mode)...\n");

    // Control pins (8080 mode)
    gpio_init(PIN_RD);
    gpio_set_dir(PIN_RD, GPIO_OUT);
    gpio_put(PIN_RD, 1);  // RD# high (not reading)

    gpio_init(PIN_DC);
    gpio_set_dir(PIN_DC, GPIO_OUT);
    gpio_put(PIN_DC, 1);

    gpio_init(PIN_RES);
    gpio_set_dir(PIN_RES, GPIO_OUT);
    gpio_put(PIN_RES, 1);

    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 0);  // CS# low (selected)

    // Data + WR pins
    bitbang_gpio_setup();

    // Hardware reset
    printf("  Hardware reset...\n");
    gpio_put(PIN_RES, 1);
    sleep_ms(10);
    gpio_put(PIN_RES, 0);
    sleep_ms(10);
    gpio_put(PIN_RES, 1);
    sleep_ms(50);

    // Full init sequence via bitbang
    printf("  Init sequence...\n");
    bitbang_cmd_with_args(0xFD, (uint8_t[]){0x12}, 1);          // Unlock
    bitbang_write_byte(0xAE, false);                              // Display OFF
    bitbang_cmd_with_args(0xB3, (uint8_t[]){0x91}, 1);          // Clock div
    bitbang_cmd_with_args(0xCA, (uint8_t[]){0x3F}, 1);          // Mux ratio 64
    bitbang_cmd_with_args(0xA2, (uint8_t[]){0x00}, 1);          // Display offset 0
    bitbang_cmd_with_args(0xA1, (uint8_t[]){0x00}, 1);          // Start line 0
    bitbang_cmd_with_args(0xA0, (uint8_t[]){0x14, 0x11}, 2);   // Remap
    bitbang_cmd_with_args(0xB5, (uint8_t[]){0x00}, 1);          // GPIO disable
    bitbang_cmd_with_args(0xAB, (uint8_t[]){0x01}, 1);          // Function select
    bitbang_cmd_with_args(0xB4, (uint8_t[]){0xA0, 0xFD}, 2);   // Display Enhancement A (internal VSL!)
    bitbang_cmd_with_args(0xB1, (uint8_t[]){0xE2}, 1);          // Phase length
    bitbang_cmd_with_args(0xC1, (uint8_t[]){0x9F}, 1);          // Contrast
    bitbang_cmd_with_args(0xC7, (uint8_t[]){0x0F}, 1);          // Master contrast
    bitbang_write_byte(0xB9, false);                              // Default grayscale
    bitbang_cmd_with_args(0xBB, (uint8_t[]){0x1F}, 1);          // Precharge voltage
    bitbang_cmd_with_args(0xB6, (uint8_t[]){0x08}, 1);          // 2nd precharge
    bitbang_cmd_with_args(0xD1, (uint8_t[]){0xA2, 0x20}, 2);   // Display Enhancement B
    bitbang_cmd_with_args(0xBE, (uint8_t[]){0x07}, 1);          // VCOMH
    bitbang_write_byte(0xA6, false);                              // Normal display
    bitbang_write_byte(0xA9, false);                              // Exit partial

    // Clear RAM
    printf("  Clearing RAM...\n");
    bitbang_cmd_with_args(0x15, (uint8_t[]){0x1C, 0x5B}, 2);   // Column range
    bitbang_cmd_with_args(0x75, (uint8_t[]){0x00, 0x3F}, 2);   // Row range 0-63
    bitbang_write_byte(0x5C, false);                              // Write RAM
    for (int i = 0; i < (256 / 2) * 64; i++) {
        bitbang_write_byte(0x00, true);
    }

    // Display ON
    bitbang_write_byte(0xAF, false);
    printf("  Init complete, display ON.\n");
}

void ssd1322_test_bitbang_fill(uint8_t pattern) {
    bitbang_gpio_setup();

    // Set window to visible range
    bitbang_cmd_with_args(0x15, (uint8_t[]){0x1C, 0x5B}, 2);   // Column 28-91
    bitbang_cmd_with_args(0x75, (uint8_t[]){0x00, 0x3F}, 2);   // Row 0-63
    bitbang_write_byte(0x5C, false);                              // Write RAM

    // Fill: 128 bytes/row × 64 rows = 8192 bytes
    int count = (256 / 2) * 64;
    printf("  Filling %d bytes with 0x%02X (cols 0x1C-0x5B)...\n", count, pattern);
    for (int i = 0; i < count; i++) {
        bitbang_write_byte(pattern, true);
    }
    printf("  Fill complete.\n");
}

void ssd1322_test_bitbang_fill_full(uint8_t pattern) {
    bitbang_gpio_setup();

    // Fill the ENTIRE SSD1322 RAM — all 120 columns, all 128 rows
    // This covers every possible display mapping
    bitbang_cmd_with_args(0x15, (uint8_t[]){0x00, 0x77}, 2);   // Column 0-119 (all)
    bitbang_cmd_with_args(0x75, (uint8_t[]){0x00, 0x7F}, 2);   // Row 0-127 (all)
    bitbang_write_byte(0x5C, false);                              // Write RAM

    // Fill: 120 columns × 2 bytes/col × 128 rows = 30720 bytes
    int count = 120 * 2 * 128;
    printf("  Filling %d bytes with 0x%02X (full RAM)...\n", count, pattern);
    for (int i = 0; i < count; i++) {
        bitbang_write_byte(pattern, true);
    }
    printf("  Fill complete.\n");
}

void ssd1322_debug_gpio_state(void) {
    // Read GPIO output register to verify pin states
    uint32_t gpio_out = sio_hw->gpio_out;
    printf("  GPIO output register: 0x%08lX\n", (unsigned long)gpio_out);
    printf("  D0-D7: 0x%02lX\n", (unsigned long)(gpio_out & 0xFF));
    printf("  RD# (GPIO%d): %d\n", PIN_RD, (gpio_out >> PIN_RD) & 1);
    printf("  WR# (GPIO%d): %d\n", PIN_WR, (gpio_out >> PIN_WR) & 1);
    printf("  DC#  (GPIO%d): %d\n", PIN_DC, (gpio_out >> PIN_DC) & 1);
    printf("  RES# (GPIO%d): %d\n", PIN_RES, (gpio_out >> PIN_RES) & 1);
    printf("  CS#  (GPIO%d): %d\n", PIN_CS, (gpio_out >> PIN_CS) & 1);

    // Test DC# toggle
    printf("  Testing DC# toggle:\n");
    gpio_put(PIN_DC, 0);
    sleep_us(10);
    uint32_t dc_low = (sio_hw->gpio_out >> PIN_DC) & 1;
    gpio_put(PIN_DC, 1);
    sleep_us(10);
    uint32_t dc_high = (sio_hw->gpio_out >> PIN_DC) & 1;
    printf("    DC# set LOW → read %lu, set HIGH → read %lu\n",
           (unsigned long)dc_low, (unsigned long)dc_high);
    if (dc_low == 0 && dc_high == 1) {
        printf("    DC# toggles correctly.\n");
    } else {
        printf("    *** DC# TOGGLE FAILURE! ***\n");
    }
}
