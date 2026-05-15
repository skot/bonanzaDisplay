#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// ==========================================================================
// bonanzaDisplay — GPIO Pin Configuration
// SSD1322 OLED via 8080 8-bit parallel interface
// ==========================================================================

// --- 8080 Data Bus ---
// rev2 wires the SSD1322 data bus straight through:
//   Display D0..D7 -> GPIO0..GPIO7
// The PIO drives this contiguous GPIO0..GPIO7 block directly.
#define PIN_DB0             0
#define PIN_DB1             1
#define PIN_DB2             2
#define PIN_DB3             3
#define PIN_DB4             4
#define PIN_DB5             5
#define PIN_DB6             6
#define PIN_DB7             7
#define PIN_DATA_BASE       0         // Base GPIO for PIO out block
#define PIN_DATA_COUNT      8         // Number of data pins
#define PIN_DATA_BIT_REVERSE 0

// --- 8080 Control Signals ---
#define PIN_RES             8         // Reset (active low)
#define PIN_CS              9         // Chip select (active low)
#define PIN_DC              10        // Data/Command select (0=command, 1=data)
#define PIN_WR              11        // Write strobe (active low, pulsed for each byte)
#define PIN_RD              12        // Read strobe (active low, directly to 3V3 if unused)

// --- Dial Switch (active low to COM/GND) ---
#define PIN_DIAL_CCW        15        // Counterclockwise contact / quadrature A
#define PIN_DIAL_CW         13        // Clockwise contact / quadrature B
#define PIN_DIAL_SW         14        // Push switch contact

#endif // PIN_CONFIG_H
