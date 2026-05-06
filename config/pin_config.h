#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// ==========================================================================
// bonanzaDisplay — GPIO Pin Configuration
// SSD1322 OLED via 8080 8-bit parallel interface
// ==========================================================================

// --- 8080 Data Bus ---
// The SSD1322 data bus is wired bit-reversed on the RP2350:
//   Display D0..D7 -> GPIO7..GPIO0
// The PIO still drives the contiguous GPIO0..GPIO7 block; bytes are
// bit-reversed in the display driver before being written to PIO.
#define PIN_DB0             7
#define PIN_DB1             6
#define PIN_DB2             5
#define PIN_DB3             4
#define PIN_DB4             3
#define PIN_DB5             2
#define PIN_DB6             1
#define PIN_DB7             0
#define PIN_DATA_BASE       0         // Base GPIO for PIO out block
#define PIN_DATA_COUNT      8         // Number of data pins
#define PIN_DATA_BIT_REVERSE 1

// --- 8080 Control Signals ---
#define PIN_RD              8         // Read strobe (active low, directly to 3V3 if unused)
#define PIN_WR              9         // Write strobe (active low, pulsed for each byte)
#define PIN_DC              10        // Data/Command select (0=command, 1=data)
#define PIN_CS              11        // Chip select (active low)
#define PIN_RES             12        // Reset (active low)

// --- Dial Switch (active low to COM/GND) ---
#define PIN_DIAL_CCW        13        // Counterclockwise contact
#define PIN_DIAL_CW         14        // Clockwise contact
#define PIN_DIAL_SW         15        // Push switch contact

#endif // PIN_CONFIG_H
