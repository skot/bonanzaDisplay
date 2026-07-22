# bonanzaDisplay-fw

Firmware for driving a **SSD1322-based 256×64 OLED display** from a **RP2350** on the bitaxeBonanza display board using the **LVGL** graphics library.

The `ui` directory is an **LVGL Editor / LVGL Pro project**. Its XML files are
the source of truth for screen layout, styles, fonts, and data bindings; the
exported C is compiled directly into the Pico firmware.

The display is connected via an **8080 8-bit parallel interface**, driven by the RP2350's PIO state machine with DMA for zero-CPU-overhead framebuffer transfers.

## Features

- **SSD1322 256×64 OLED** — 4-bit grayscale (16 shades)
- **8080 parallel bus** via PIO hardware — ~2.9 MHz byte rate
- **DMA** transfers framebuffer to PIO TX FIFO with no CPU involvement
- **LVGL 9.x** rendering — L8 (8bpp) with automatic 4bpp packing
- **Double-buffered** full-screen render mode
- **Px437 FMTowns and Portfolio** 1bpp bitmap fonts shared with `bitaxe-lcd`

## Hardware

### Components

The [bonanzaDisplay](https://github.com/bitaxeorg/bonanzaDisplay) v2 hardware is attached to the [bitaxeBonanza-1002x](https://github.com/bitaxeorg/bitaxeBonanza/tree/1002x) via a 10 pin FPC that delivers 12VDC power, I2C and GPIO. The bonanzaDisplay is controlled by a RP2350 microcontroller.

### Wiring — RP2350 to SSD1322 Display

| RP2350 | GPIO   | Signal | Display Pin | Description |
|------- |--------|--------|-------------|-------------|
| Pin 2  | GPIO0  | D0     | 13 (D0)     | Data bit 0 |
| Pin 3  | GPIO1  | D1     | 12 (D1)     | Data bit 1 |
| Pin 4  | GPIO2  | D2     | 11 (D2)     | Data bit 2 |
| Pin 5  | GPIO3  | D3     | 10 (D3)     | Data bit 3 |
| Pin 7  | GPIO4  | D4     | 9 (D4)      | Data bit 4 |
| Pin 8  | GPIO5  | D5     | 8 (D5)      | Data bit 5 |
| Pin 9  | GPIO6  | D6     | 7 (D6)      | Data bit 6 |
| Pin 10 | GPIO7  | D7     | 6 (D7)      | Data bit 7 |
| Pin 12 | GPIO8  | RES#   | 20 (RES#)   | Reset (active low) |
| Pin 13 | GPIO9  | CS#    | 19 (CS#)    | Chip select (active low) |
| Pin 14 | GPIO10 | DC#    | 18 (D/C#)   | Data/Command select |
| Pin 15 | GPIO11 | R/W#   | 15 (R/W#)   | Write strobe (active low) |
| Pin 16 | GPIO12 | E/RD#  | 14 (E/RD#)  | Read strobe (active low) |

> **Note:** The display is configured for **8080 parallel mode**

### Dial Switch
The bonanzaDisplay has a SIQ-02FVS3 push-button jog wheel on it for interacting with the display. It is connected to the RP2350:

| Dial Switch Pin  | Function     | RP2350 | GPIO   |
|------------------|--------------|--------|--------|
| Counterclockwise | Quadrature A | Pin 19 | GPIO15 |
| Clockwise        | Quadrature B | Pin 17 | GPIO13 |
| Switch           | Push switch  | Pin 18 | GPIO14 |

The Counterclockwise and Clockwise pins are active-low quadrature phases. Both phase pins use pull-ups and connect to COM/GND through the dial contacts as the wheel rotates. Direction is decoded from the A/B phase sequence across a full detent. The Switch pin is also active-low and connects to COM/GND while the dial is pressed.

## Building

### Prerequisites

- [Pico SDK 2.x](https://github.com/raspberrypi/pico-sdk) installed at `~/pico-sdk` (or set `PICO_SDK_PATH`)
- `arm-none-eabi-gcc` toolchain
- `cmake` and `make`
- [picotool](https://github.com/raspberrypi/picotool) for flashing

### Build

```bash
export PICO_SDK_PATH=/path/to/pico-sdk
cmake -S . -B build -DPICO_BOARD=pico2_w
cmake --build build -j
```

### Flash

```bash
picotool load build/bonanzaDisplay.uf2 -f && picotool reboot
```

Or hold BOOTSEL while connecting USB, then drag `build/bonanzaDisplay.uf2` to the mounted drive.

## Edit the UI with LVGL Editor

1. Install LVGL Editor (LVGL Pro Editor 1.2 or newer, or the official VS Code
   extension).
2. Open `bonanzaDisplay-fw.code-workspace`. Its first workspace folder is
   `ui`, which puts `globals.xml` and `project.xml` at the root expected by the
   editor. Opening the `ui` directory by itself also works.
3. If the extension was already running, use **Developer: Reload Window** once.
4. Open LVGL Editor and select the `pico2w_ssd1322` target. The preview is
   configured for the physical **256×64 L8 grayscale** display.
5. Edit `ui/screens/main_screen.xml` in Design or XML mode.
6. Choose **Compile and export code**, then rebuild the firmware.

Keep the `ui/fonts` and `ui/images` directories present. LVGL Editor's
containerized resource converter mounts both directories even when a project
currently has no images.

The UI uses the same Px437 FMTowns 8×16 and Portfolio 6×8 fonts as
`bitaxe-lcd`. With LVGL Editor 1.0.x, asset filenames must not contain spaces
because its resource-converter command does not quote font paths.

Files ending in `_gen.c` or `_gen.h`, plus `file_list_gen.cmake`, are owned by
LVGL Editor and may be overwritten. Put persistent C code in `bonanza_ui.c`,
`bonanza_ui.h`, or add extra sources in `user_config.cmake`.

The screen uses LVGL subjects for live firmware data. Application code updates
them through `bonanza_ui_set_dial_state()`; labels bound in the XML repaint
automatically. Keep LVGL calls on the same core/thread as `lv_timer_handler()`
unless synchronization is added.

## Project Structure

```
bonanzaDisplay/
├── bonanzaDisplay-fw.code-workspace # Opens UI at the LVGL Editor project root
├── CMakeLists.txt              # Top-level build configuration
├── config/
│   ├── lv_conf.h               # LVGL configuration
│   └── pin_config.h            # GPIO pin assignments
├── src/
│   ├── main.c                  # Entry point, hardware init, and live UI data
│   ├── display/
│   │   ├── ssd1322.c           # SSD1322 driver (PIO + DMA + bitbang)
│   │   ├── ssd1322.h           # Driver public API
│   │   ├── ssd1322_regs.h      # Register definitions and geometry
│   │   └── parallel_8080.pio   # PIO program for 8080 bus
│   ├── fonts/
│   │   └── lv_font_portfolio_6x8.c # LVGL default/fallback font
│   ├── lvgl_port/
│   │   ├── lv_port_disp.c      # LVGL display driver (L8 → 4bpp → DMA)
│   │   └── lv_port_disp.h
├── ui/                         # LVGL Editor / LVGL Pro project
│   ├── project.xml             # 256×64 L8 target definition
│   ├── globals.xml             # Fonts and observable subjects
│   ├── screens/
│   │   ├── main_screen.xml     # Editable screen source
│   │   └── main_screen_gen.c   # Editor-generated firmware source
│   ├── bonanza_ui.c            # Persistent application-facing UI hooks
│   └── CMakeLists.txt          # Builds exported UI as lib-ui
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

1. **LVGL Editor** exports the XML UI as C and LVGL renders it to an L8
   (8-bit grayscale) double buffer
2. **Flush callback** packs L8 → 4bpp (upper nibble of each byte → two 4-bit pixels per byte)
3. **DMA** transfers the packed buffer to PIO TX FIFO
4. **PIO** clocks out each byte with hardware-timed WR# strobes on the 8080 bus

## Fonts

The editable UI uses the same 1bpp Px437 FMTowns 8×16 and Portfolio 6×8
fonts as `bitaxe-lcd`. Their source `.ttf` files and editor-generated C data
live in `ui/fonts`.

## License

GPL v3 -- FOSS || GTFO
