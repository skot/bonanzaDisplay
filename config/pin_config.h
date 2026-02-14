#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// ==========================================================================
// bonanzaDisplay — GPIO Pin Configuration
// SSD1322 OLED via 8080 8-bit parallel interface
// ==========================================================================

// --- 8080 Data Bus (consecutive GPIOs for PIO) ---
#define PIN_DB0             0
#define PIN_DB1             1
#define PIN_DB2             2
#define PIN_DB3             3
#define PIN_DB4             4
#define PIN_DB5             5
#define PIN_DB6             6
#define PIN_DB7             7
#define PIN_DATA_BASE       PIN_DB0   // Base pin for PIO out
#define PIN_DATA_COUNT      8         // Number of data pins

// --- 8080 Control Signals ---
#define PIN_RD              8         // Read strobe (active low, directly to 3V3 if unused)
#define PIN_WR              9         // Write strobe (active low, directly from PIO)
#define PIN_DC              10        // Data/Command select (0=command, 1=data)
#define PIN_RES             11        // Reset (active low)
#define PIN_CS              12        // Chip select (active low)

// --- Input Devices (TBD — reserved range) ---
// #define PIN_ENC_A        13        // Rotary encoder A
// #define PIN_ENC_B        14        // Rotary encoder B
// #define PIN_ENC_SW       15        // Rotary encoder switch
// #define PIN_BTN_1        16        // Button 1
// #define PIN_BTN_2        17        // Button 2

#endif // PIN_CONFIG_H
