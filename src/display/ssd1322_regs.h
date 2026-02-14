#ifndef SSD1322_REGS_H
#define SSD1322_REGS_H

// ==========================================================================
// SSD1322 Command Register Definitions
// Solomon Systech SSD1322 OLED Driver IC
// ==========================================================================

// --- Fundamental Commands ---
#define SSD1322_CMD_SET_COLUMN_ADDR         0x15
#define SSD1322_CMD_WRITE_RAM               0x5C
#define SSD1322_CMD_READ_RAM                0x5D
#define SSD1322_CMD_SET_ROW_ADDR            0x75

// --- Display Configuration ---
#define SSD1322_CMD_SET_REMAP               0xA0
#define SSD1322_CMD_SET_START_LINE          0xA1
#define SSD1322_CMD_SET_DISPLAY_OFFSET      0xA2
#define SSD1322_CMD_DISPLAY_ALL_OFF         0xA4
#define SSD1322_CMD_DISPLAY_ALL_ON          0xA5
#define SSD1322_CMD_NORMAL_DISPLAY          0xA6
#define SSD1322_CMD_INVERSE_DISPLAY         0xA7
#define SSD1322_CMD_ENABLE_PARTIAL          0xA8
#define SSD1322_CMD_EXIT_PARTIAL            0xA9
#define SSD1322_CMD_FUNCTION_SELECT         0xAB
#define SSD1322_CMD_DISPLAY_OFF             0xAE
#define SSD1322_CMD_DISPLAY_ON              0xAF

// --- Timing & Driving ---
#define SSD1322_CMD_SET_PHASE_LENGTH        0xB1
#define SSD1322_CMD_SET_CLOCK_DIV           0xB3
#define SSD1322_CMD_SET_GPIO                0xB5
#define SSD1322_CMD_SET_SECOND_PRECHARGE    0xB6
#define SSD1322_CMD_SET_GRAYSCALE_TABLE     0xB8
#define SSD1322_CMD_DEFAULT_GRAYSCALE       0xB9
#define SSD1322_CMD_SET_PRECHARGE_VOLTAGE   0xBB
#define SSD1322_CMD_SET_VCOMH               0xBE

// --- Display Enhancement ---
#define SSD1322_CMD_DISPLAY_ENHANCE_A       0xB4
#define SSD1322_CMD_DISPLAY_ENHANCE_B       0xD1

// --- Contrast ---
#define SSD1322_CMD_SET_CONTRAST            0xC1
#define SSD1322_CMD_MASTER_CONTRAST         0xC7

// --- MUX ---
#define SSD1322_CMD_SET_MUX_RATIO           0xCA

// --- Command Lock ---
#define SSD1322_CMD_SET_COMMAND_LOCK        0xFD

// --- Display Geometry ---
#define SSD1322_WIDTH                       256
#define SSD1322_HEIGHT                      64

// Column address range for 256-pixel display (each addr = 4 pixels)
// 256 / 4 = 64 columns, offset by 0x1C for 256-wide panels
#define SSD1322_COL_START                   0x1C
#define SSD1322_COL_END                     0x5B
#define SSD1322_ROW_START                   0x00
#define SSD1322_ROW_END                     0x3F  // 64 - 1

#endif // SSD1322_REGS_H
