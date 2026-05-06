# bonanzaDisplay-fw

Firmware for driving a **SSD1322-based 256×64 OLED display** from a **RP2350** on the bitaxeBonanza display board using the **LVGL** graphics library.

The display is connected via an **8080 8-bit parallel interface**, driven by the RP2350's PIO state machine with DMA for zero-CPU-overhead framebuffer transfers.

## Features

- **SSD1322 256×64 OLED** — 4-bit grayscale (16 shades)
- **8080 parallel bus** via PIO hardware — ~2.9 MHz byte rate
- **DMA** transfers framebuffer to PIO TX FIFO with no CPU involvement
- **LVGL 9.x** rendering — L8 (8bpp) with automatic 4bpp packing
- **Double-buffered** full-screen render mode
- **Pixel Emulator** custom bitmap font (8px, 12px, 16px)

## Hardware

### Components

The [bonanzaDisplay](https://github.com/bitaxeorg/bonanzaDisplay) hardware is attached to the [bitaxeBonanza-1002x](https://github.com/bitaxeorg/bitaxeBonanza/tree/1002x) via a 10 pin FPC that delivers 12VDC power, I2C and GPIO. The bonanzaDisplay is controlled by a RP2350 microcontroller.

### Wiring — RP2350 to SSD1322 Display

| RP2350 | GPIO   | Signal | Display Pin | Description |
|------- |--------|--------|-------------|-------------|
| Pin 10 | GPIO7  | D0     | 13 (D0/CLK) | Data bit 0 |
| Pin 9  | GPIO6  | D1     | 12 (D1/DIN) | Data bit 1 |
| Pin 8  | GPIO5  | D2     | 11 (D2)     | Data bit 2 |
| Pin 7  | GPIO4  | D3     | 10 (D3)     | Data bit 3 |
| Pin 5  | GPIO3  | D4     | 9 (D4)      | Data bit 4 |
| Pin 4  | GPIO2  | D5     | 8 (D5)      | Data bit 5 |
| Pin 3  | GPIO1  | D6     | 7 (D6)      | Data bit 6 |
| Pin 2  | GPIO0  | D7     | 6 (D7)      | Data bit 7 |
| Pin 12 | GPIO8  | RD#    | 14 (E/RD#)  | Read strobe (active low) |
| Pin 13 | GPIO9  | WR#    | 15 (R/W#)   | Write strobe (active low) |
| Pin 14 | GPIO10 | DC#    | 18 (D/C#)   | Data/Command select |
| Pin 16 | GPIO12 | RES#   | 20 (RES#)   | Reset (active low) |
| Pin 15 | GPIO11 | CS#    | 19 (CS#)    | Chip select (active low) |

> **Note:** The display is configured for **8080 parallel mode**

### Dial Switch
The bonanzaDisplay has a SIQ-02FVS3 push-button jog wheel on it for interacting with the display. It is connected to the RP2350:

| Dial Switch Pin  | Function     | RP2350 | GPIO   |
|------------------|--------------|--------|--------|
| Counterclockwise | Quadrature A | Pin 17 | GPIO13 |
| Clockwise        | Quadrature B | Pin 18 | GPIO14 |
| Switch           | Push switch  | Pin 19 | GPIO15 |

The Counterclockwise and Clockwise pins are active-low quadrature phases. Both phase pins use pull-ups and connect to COM/GND through the dial contacts as the wheel rotates. Direction is decoded from the A/B phase sequence across a full detent. The Switch pin is also active-low and connects to COM/GND while the dial is pressed.

## Building

### Prerequisites

- [Pico SDK 2.x](https://github.com/raspberrypi/pico-sdk) installed at `~/pico-sdk` (or set `PICO_SDK_PATH`)
- `arm-none-eabi-gcc` toolchain
- `cmake` and `make`
- [picotool](https://github.com/raspberrypi/picotool) for flashing

### Build

```bash
mkdir build && cd build
cmake -DPICO_BOARD=pico2_w ..
make -j
```

### Flash

```bash
picotool load build/bonanzaDisplay.uf2 -f && picotool reboot
```

Or hold BOOTSEL while connecting USB, then drag `build/bonanzaDisplay.uf2` to the mounted drive.

## Project Structure

```
bonanzaDisplay/
├── CMakeLists.txt              # Top-level build configuration
├── config/
│   ├── lv_conf.h               # LVGL configuration
│   └── pin_config.h            # GPIO pin assignments
├── src/
│   ├── main.c                  # Entry point and LVGL main loop
│   ├── display/
│   │   ├── ssd1322.c           # SSD1322 driver (PIO + DMA + bitbang)
│   │   ├── ssd1322.h           # Driver public API
│   │   ├── ssd1322_regs.h      # Register definitions and geometry
│   │   └── parallel_8080.pio   # PIO program for 8080 bus
│   ├── fonts/
│   │   ├── fonts.h             # Font declarations
│   │   ├── font_pixel_8.c      # Pixel Emulator 8px
│   │   ├── font_pixel_12.c     # Pixel Emulator 12px
│   │   └── font_pixel_16.c     # Pixel Emulator 16px
│   ├── lvgl_port/
│   │   ├── lv_port_disp.c      # LVGL display driver (L8 → 4bpp → DMA)
│   │   └── lv_port_disp.h
│   └── ui/
│       ├── ui.h                # UI public API
│       └── ui_dashboard.c      # Dashboard screen layout
└── lib/
    └── lvgl/                   # LVGL 9.x (git submodule)
```

## Architecture

```
┌─────────────┐    ┌──────────────┐    ┌───────────┐    ┌──────────┐
│  LVGL 9.x   │───►│ L8 → 4bpp    │───►│    DMA    │───►│   PIO    │
│  (render)   │    │  (packing)   │    │ (transfer)│    │ (8080)   │
└─────────────┘    └──────────────┘    └───────────┘    └────┬─────┘
                                                             │ 8-bit
                                                             ▼ parallel
                                                        ┌──────────┐
                                                        │ SSD1322  │
                                                        │  OLED    │
                                                        └──────────┘
```

1. **LVGL** renders to an L8 (8-bit grayscale) double buffer
2. **Flush callback** packs L8 → 4bpp (upper nibble of each byte → two 4-bit pixels per byte)
3. **DMA** transfers the packed buffer to PIO TX FIFO
4. **PIO** clocks out each byte with hardware-timed WR# strobes on the 8080 bus

## Font

The project uses **Pixel Emulator** (`.otf`) converted to LVGL format with `lv_font_conv`:

```bash
lv_font_conv --font "Pixel Emulator.otf" --size 16 --bpp 1 \
  --range 0x20-0x7E --format lvgl --no-compress \
  -o src/fonts/font_pixel_16.c --lv-include "lvgl.h"
```

Available sizes: 8px, 12px, 16px — all at 1bpp for crisp pixel rendering.

## License

GPL v3 -- FOSS || GTFO
