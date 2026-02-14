# bonanzaDisplay — Firmware Specification

## 1. Overview

**Project Name:** bonanzaDisplay  
**Purpose:** Microcontroller firmware for the Raspberry Pi Pico 2W driving a SSD1322-based 256×64 pixel OLED display via 8080 parallel interface, using the LVGL graphics library for a dashboard/status screen UI.

---

## 2. Hardware

### 2.1 Microcontroller

| Parameter       | Value                                      |
| --------------- | ------------------------------------------ |
| MCU             | RP2350 (Raspberry Pi Pico 2W)              |
| Architecture    | Dual-core Arm Cortex-M33 @ 150 MHz         |
| SRAM            | 520 KB                                     |
| Flash           | 4 MB (onboard QSPI)                        |
| Wireless        | CYW43439 — WiFi 4 (802.11n) + BLE 5.2     |

### 2.2 Display

| Parameter       | Value                                      |
| --------------- | ------------------------------------------ |
| Controller      | Solomon Systech SSD1322                     |
| Resolution      | 256 × 64 pixels                            |
| Color Depth     | 4-bit grayscale (16 shades)                |
| Technology      | OLED (passive matrix)                      |
| Interface Mode  | 8080 parallel (8-bit data bus)             |
| OLED VCC        | Onboard booster (module handles internally)|

### 2.3 Pin Mapping

| Display Pin | Signal   | Pico GPIO | Physical Pin | Notes                          |
| ----------- | -------- | --------- | ------------ | ------------------------------ |
| 1           | GND      | GND       | Any GND      | Ground                         |
| 2           | VCC_IN   | 3V3_OUT   | Pin 36       | 3.3V power supply              |
| 3           | NC       | —         | —            | Leave unconnected              |
| 4           | D0       | GPIO 0    | Pin 1        | Data bit 0 (LSB)              |
| 5           | D1       | GPIO 1    | Pin 2        | Data bit 1                     |
| 6           | D2       | GPIO 2    | Pin 4        | Data bit 2                     |
| 7           | D3       | GPIO 3    | Pin 5        | Data bit 3                     |
| 8           | D4       | GPIO 4    | Pin 6        | Data bit 4                     |
| 9           | D5       | GPIO 5    | Pin 7        | Data bit 5                     |
| 10          | D6       | GPIO 6    | Pin 9        | Data bit 6                     |
| 11          | D7       | GPIO 7    | Pin 10       | Data bit 7 (MSB)              |
| 12          | RD#      | GPIO 8    | Pin 11       | Read strobe (active low)       |
| 13          | WR#      | GPIO 9    | Pin 12       | Write strobe (active low)      |
| 14          | DC#      | GPIO 10   | Pin 13       | Data/Command select            |
| 15          | RES#     | GPIO 11   | Pin 15       | Hardware reset (active low)    |
| 16          | CS#      | GPIO 12   | Pin 16       | Chip select (active low)       |

> **PIO Note:** Data lines D0–D7 use consecutive GPIOs 0–7, which is optimal for PIO-based parallel output using a single `out pins, 8` instruction.

### 2.4 Input Devices

Physical buttons and/or rotary encoder — GPIO assignments **reserved, TBD**.  
Candidate GPIOs: 13–22 (free after display allocation).

---

## 3. Software Platform

### 3.1 SDK & Toolchain

| Component       | Choice                                     |
| --------------- | ------------------------------------------ |
| SDK             | Raspberry Pi Pico SDK (C/C++)              |
| Build System    | CMake                                      |
| Board Target    | `pico2_w` (RP2350, wireless-enabled)       |
| Compiler        | arm-none-eabi-gcc (via Pico SDK toolchain) |
| Architecture    | `riscv` or `arm` (Pico SDK selectable)     |

### 3.2 Graphics Library

| Component       | Choice                                     |
| --------------- | ------------------------------------------ |
| Library         | LVGL 9.x (latest stable)                   |
| Integration     | Git submodule or FetchContent via CMake     |
| Tick Source      | Pico SDK repeating timer (1 ms tick)       |

### 3.3 Execution Model

- **Bare-metal super loop** (no RTOS)
- Main loop: `lv_timer_handler()` called periodically
- LVGL tick driven by hardware timer interrupt

---

## 4. Display Driver Architecture

### 4.1 8080 Parallel Bus — PIO + DMA

The 8080 write cycle will be implemented using the RP2350's PIO (Programmable I/O) state machine with DMA for zero-CPU-overhead transfers.

#### PIO Program (conceptual)

```
; 8080 write cycle: pull data from FIFO, assert on pins, strobe WR#
.wrap_target
    pull block            ; wait for data from DMA/FIFO
    out pins, 8           ; put 8 bits on GPIO 0-7
    set pins, 0           ; WR# low (begin write strobe)
    nop            [T]    ; hold time (T cycles configurable)
    set pins, 1           ; WR# high (latch data)
.wrap
```

#### Signal Control

| Signal | Control Method                                |
| ------ | --------------------------------------------- |
| D0–D7  | PIO `out pins` (GPIO 0–7)                     |
| WR#    | PIO `set pins` (GPIO 9)                       |
| RD#    | GPIO output, held HIGH (read not used)         |
| DC#    | GPIO output, toggled by CPU before DMA burst   |
| CS#    | GPIO output, held LOW during transfers          |
| RES#   | GPIO output, pulsed LOW during init             |

#### DMA Configuration

- DMA channel transfers framebuffer data → PIO TX FIFO
- Transfer size: 8-bit
- IRQ on completion for LVGL flush-ready callback (`lv_display_flush_ready()`)

### 4.2 Color Pipeline

```
LVGL renders (L8, 8bpp)  →  Flush callback  →  Pack to 4bpp  →  DMA to PIO  →  SSD1322
     256×64×1 byte            2 pixels/byte        256×64/2         8080 bus
```

1. LVGL renders into an L8 (8-bit luminance) buffer
2. The flush callback converts L8 → 4-bit grayscale by taking the upper nibble of each byte
3. Two adjacent pixels are packed into one byte (high nibble = left pixel, low nibble = right pixel) matching SSD1322 native format
4. Packed buffer is DMA'd through PIO to the display

### 4.3 Framebuffer Strategy

| Parameter         | Value                  |
| ----------------- | ---------------------- |
| Buffering         | Double buffer          |
| LVGL buffer size  | 256 × 64 = 16,384 B each (L8) |
| Total LVGL RAM    | 32,768 B (32 KB)      |
| Packed buffer     | 8,192 B (for 4bpp DMA output) |
| Total display RAM | ~41 KB                 |
| Available SRAM    | 520 KB (plenty of headroom) |

---

## 5. SSD1322 Initialization

Key commands for the SSD1322 init sequence:

| Step | Command          | Hex    | Purpose                                    |
| ---- | ---------------- | ------ | ------------------------------------------ |
| 1    | Set Command Lock | 0xFD   | Unlock OLED driver IC                      |
| 2    | Display Off      | 0xAE   | Turn off during setup                      |
| 3    | Set Clock Div    | 0xB3   | Set oscillator frequency & divide ratio    |
| 4    | Set Mux Ratio    | 0xCA   | Set to 63 (64 rows - 1)                    |
| 5    | Set Display Offset| 0xA2  | Set vertical offset (typically 0)          |
| 6    | Set Start Line   | 0xA1   | Set start line to 0                        |
| 7    | Set Remap        | 0xA0   | Configure scan direction, COM split, nibble remap |
| 8    | Set GPIO         | 0xB5   | Disable GPIO pins                          |
| 9    | Function Select  | 0xAB   | Enable internal VDD regulator              |
| 10   | Set Phase Length  | 0xB1   | Set precharge/discharge periods            |
| 11   | Set VCOMH         | 0xBE   | Set VCOMH voltage level                    |
| 12   | Set Contrast     | 0xC1   | Set contrast current (brightness)          |
| 13   | Master Contrast  | 0xC7   | Set master contrast (1–15)                 |
| 14   | Set Precharge V  | 0xBB   | Set precharge voltage                      |
| 15   | Normal Display   | 0xA6   | Normal (not inverted) display mode         |
| 16   | Exit Partial     | 0xA9   | Exit partial display mode                  |
| 17   | Display On       | 0xAF   | Turn display on                            |

Column address range for 256 pixels: 0x1C – 0x5B (each column address = 4 pixels in 4bpp mode).

---

## 6. LVGL Configuration

### 6.1 Core Settings (`lv_conf.h` highlights)

| Setting                        | Value       | Rationale                          |
| ------------------------------ | ----------- | ---------------------------------- |
| `LV_COLOR_DEPTH`              | 8           | L8 grayscale rendering             |
| `LV_HOR_RES_MAX`             | 256         | Display width                      |
| `LV_VER_RES_MAX`             | 64          | Display height                     |
| `LV_USE_OS`                  | `LV_OS_NONE`| Bare-metal                         |
| `LV_TICK_CUSTOM`             | 1           | Use Pico SDK timer for tick        |
| `LV_DEF_REFR_PERIOD`         | 33          | ~30 FPS target                     |
| `LV_USE_LOG`                 | 1           | Enable during development          |
| `LV_LOG_LEVEL`               | `LV_LOG_LEVEL_WARN` | Moderate logging          |
| `LV_FONT_MONTSERRAT_14`      | 1           | Default built-in font              |

### 6.2 Display Driver Registration (LVGL 9.x API)

```c
lv_display_t *disp = lv_display_create(256, 64);
lv_display_set_color_format(disp, LV_COLOR_FORMAT_L8);
lv_display_set_flush_cb(disp, ssd1322_flush_cb);
lv_display_set_buffers(disp, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_FULL);
```

### 6.3 Input Device (placeholder)

```c
lv_indev_t *indev = lv_indev_create();
lv_indev_set_type(indev, LV_INDEV_TYPE_ENCODER);  // or LV_INDEV_TYPE_BUTTON
lv_indev_set_read_cb(indev, input_read_cb);
```

---

## 7. Project Structure

```
bonanzaDisplay/
├── CMakeLists.txt              # Top-level CMake configuration
├── pico_sdk_import.cmake       # Pico SDK CMake helper
├── SPECIFICATION.md            # This document
├── src/
│   ├── main.c                  # Entry point, super loop
│   ├── display/
│   │   ├── ssd1322.h           # SSD1322 driver public API
│   │   ├── ssd1322.c           # SSD1322 init, command, flush
│   │   ├── ssd1322_regs.h      # SSD1322 register/command defines
│   │   └── parallel_8080.pio   # PIO program for 8080 bus
│   ├── lvgl_port/
│   │   ├── lv_port_disp.h      # LVGL display port header
│   │   ├── lv_port_disp.c      # LVGL display driver glue
│   │   ├── lv_port_indev.h     # LVGL input device port header
│   │   └── lv_port_indev.c     # LVGL input device glue
│   └── ui/
│       ├── ui.h                # UI screen declarations
│       └── ui_dashboard.c      # Dashboard screen layout
├── config/
│   ├── lv_conf.h               # LVGL configuration
│   └── pin_config.h            # GPIO pin assignments
├── lib/
│   └── lvgl/                   # LVGL 9.x (git submodule)
└── tools/
    └── flash.sh                # Helper script for UF2 flashing
```

---

## 8. Build & Flash

### 8.1 Build Commands

```bash
mkdir build && cd build
cmake -DPICO_BOARD=pico2_w ..
make -j$(nproc)
```

### 8.2 Flash

- Hold BOOTSEL, connect USB → mass storage appears
- Copy `bonanzaDisplay.uf2` to the mounted drive
- Or use `picotool load bonanzaDisplay.uf2`

---

## 9. Performance Budget

| Metric                      | Target     | Notes                               |
| --------------------------- | ---------- | ----------------------------------- |
| Frame rate                  | 30 FPS     | 33 ms per frame                     |
| LVGL render (256×64 L8)     | < 5 ms     | Small area, simple widgets          |
| L8→4bpp packing             | < 0.5 ms   | 8 KB output, tight loop or DMA      |
| PIO+DMA transfer (8 KB)     | < 2 ms     | PIO clock ≥ 10 MHz = ~0.8 ms       |
| Total frame pipeline        | < 10 ms    | Well within 33 ms budget            |
| CPU utilization (display)   | < 30%      | DMA offloads bulk of transfer       |

---

## 10. Future Considerations

- **WiFi connectivity:** Pico 2W wireless is available but not enabled initially. Can be added for fetching dashboard data from network sources.
- **BLE:** Available for potential mobile app connectivity.
- **Custom fonts:** Bitmap fonts optimized for 4-bit grayscale at small sizes.
- **Power management:** SSD1322 sleep mode + Pico dormant mode for battery operation.
- **Brightness control:** Expose SSD1322 contrast register (0xC1) via UI or API.
- **Input device finalization:** GPIO assignments for buttons/encoder TBD.

---

## 11. Dependencies

| Dependency      | Version   | Source                                          |
| --------------- | --------- | ----------------------------------------------- |
| Pico SDK        | ≥ 2.0     | https://github.com/raspberrypi/pico-sdk         |
| LVGL            | 9.x       | https://github.com/lvgl/lvgl (submodule)        |
| ARM Toolchain   | 13.x+     | arm-none-eabi-gcc                               |
| CMake           | ≥ 3.13    | System package                                  |
| picotool        | latest    | https://github.com/raspberrypi/picotool          |

---

*Document created: 2026-02-13*  
*Status: Draft — Ready for implementation*
