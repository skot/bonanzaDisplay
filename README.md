# bonanzaDisplay

Firmware for driving a **SSD1322-based 256×64 OLED display** from a **Raspberry Pi Pico 2W** using the **LVGL** graphics library.

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

| Component | Description |
|-----------|-------------|
| Raspberry Pi Pico 2W | RP2350, dual Cortex-M33 @ 150 MHz, 520 KB SRAM, 4 MB flash |
| SSD1322 OLED module | 256×64 pixels, 4-bit grayscale, 8080/6800 parallel interface |

### Wiring — Pico 2W to SSD1322 Display Module

| Pico 2W Pin | GPIO | Signal | Display Pin | Description |
|-------------|------|--------|-------------|-------------|
| Pin 1 | GP0 | D0 | 4 (D0/CLK) | Data bit 0 |
| Pin 2 | GP1 | D1 | 5 (D1/DIN) | Data bit 1 |
| Pin 4 | GP2 | D2 | 6 (D2) | Data bit 2 |
| Pin 5 | GP3 | D3 | 7 (D3) | Data bit 3 |
| Pin 6 | GP4 | D4 | 8 (D4) | Data bit 4 |
| Pin 7 | GP5 | D5 | 9 (D5) | Data bit 5 |
| Pin 9 | GP6 | D6 | 10 (D6) | Data bit 6 |
| Pin 10 | GP7 | D7 | 11 (D7) | Data bit 7 |
| Pin 11 | GP8 | RD# | 12 (E/RD#) | Read strobe (active low) |
| Pin 12 | GP9 | WR# | 13 (R/W#) | Write strobe (active low) |
| Pin 14 | GP10 | DC# | 14 (D/C#) | Data/Command select |
| Pin 15 | GP11 | RES# | 15 (RES#) | Reset (active low) |
| Pin 16 | GP12 | CS# | 16 (CS#) | Chip select (active low) |
| Pin 36 | 3V3 OUT | 3V3 | 2 (VCC_IN) | Power supply |
| Pin 38 | GND | GND | 1 (GND) | Ground |

> **Note:** The display module must be configured for **8080 parallel mode** (BS0/BS1 resistors). Pin 3 (NC) is not connected.

### Pin Map Diagram

```
         Pico 2W                    SSD1322 Module
        ┌────────┐                  ┌────────────┐
   GP0  │ 1    40│ VBUS        GND  │ 1          │
   GP1  │ 2    39│ VSYS     VCC_IN  │ 2          │
   GND  │ 3    38│ GND          NC  │ 3          │
   GP2  │ 4    37│ 3V3_EN   D0/CLK  │ 4          │
   GP3  │ 5    36│ 3V3 ────────────►│ 2 (VCC)    │
   GP4  │ 6    35│ ADC_VREF D1/DIN  │ 5          │
   GP5  │ 7    34│ GP28        D2   │ 6          │
   GND  │ 8    33│ GND ───────────►│ 1 (GND)    │
   GP6  │ 9    32│ GP27        D3   │ 7          │
   GP7  │10    31│ GP26        D4   │ 8          │
   GP8  │11    30│ RUN         D5   │ 9          │
   GP9  │12    29│ GP22        D6   │ 10         │
   GND  │13    28│ GND         D7   │ 11         │
  GP10  │14    27│ GP21     E/RD#   │ 12         │
  GP11  │15    26│ GP20     R/W#    │ 13         │
  GP12  │16    25│ GP19     D/C#    │ 14         │
  GP13  │17    24│ GP18     RES#    │ 15         │
   GND  │18    23│ GND      CS#     │ 16         │
  GP14  │19    22│ GP17             └────────────┘
  GP15  │20    21│ GP16
        └────────┘
```

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
│  LVGL 9.x   │───►│ L8 → 4bpp   │───►│    DMA    │───►│   PIO    │
│  (render)   │    │  (packing)   │    │ (transfer) │    │ (8080)   │
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

TBD
