#!/usr/bin/env bash
# bonanzaDisplay — Flash UF2 to Pico 2W
# Usage: ./tools/flash.sh [path/to/uf2]
#
# If no argument given, uses build/bonanzaDisplay.uf2
# Requires picotool or manual BOOTSEL + drag-and-drop

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_DIR="$(dirname "$SCRIPT_DIR")"
UF2_FILE="${1:-$PROJECT_DIR/build/bonanzaDisplay.uf2}"

if [ ! -f "$UF2_FILE" ]; then
    echo "Error: UF2 file not found: $UF2_FILE"
    echo "Run 'cd build && cmake -DPICO_BOARD=pico2_w .. && make -j' first."
    exit 1
fi

echo "Flashing: $UF2_FILE"

# Try picotool first
if command -v picotool &> /dev/null; then
    echo "Using picotool..."
    picotool load "$UF2_FILE" -f
    picotool reboot
    echo "Done. Device should reboot."
else
    # Fallback: look for mounted Pico drive
    PICO_MOUNT=""
    if [ -d "/Volumes/RPI-RP2" ]; then
        PICO_MOUNT="/Volumes/RPI-RP2"
    elif [ -d "/media/$USER/RPI-RP2" ]; then
        PICO_MOUNT="/media/$USER/RPI-RP2"
    fi

    if [ -n "$PICO_MOUNT" ]; then
        echo "Copying to $PICO_MOUNT ..."
        cp "$UF2_FILE" "$PICO_MOUNT/"
        echo "Done. Device should reboot automatically."
    else
        echo "Error: picotool not found and no RPI-RP2 drive mounted."
        echo "Hold BOOTSEL, plug in USB, then try again."
        exit 1
    fi
fi
