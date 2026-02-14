cmake_minimum_required(VERSION 3.13)

# Pull in Pico SDK (must be before project())
include(pico_sdk_import.cmake)

project(bonanzaDisplay C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# --------------------------------------------------------------------------
# LVGL
# --------------------------------------------------------------------------
set(LV_BUILD_CONF_DIR "${CMAKE_CURRENT_SOURCE_DIR}/config" CACHE STRING "" FORCE)
set(LV_CONF_BUILD_DISABLE_EXAMPLES ON CACHE BOOL "" FORCE)
set(LV_CONF_BUILD_DISABLE_DEMOS ON CACHE BOOL "" FORCE)
set(LV_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(LV_BUILD_DEMOS OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/lvgl)

# Remove Helium (ARMv8.1-M MVE) assembly — not supported on RP2350 Cortex-M33
get_target_property(LVGL_SOURCES lvgl SOURCES)
list(FILTER LVGL_SOURCES EXCLUDE REGEX ".*helium.*\\.S$")
set_target_properties(lvgl PROPERTIES SOURCES "${LVGL_SOURCES}")

# --------------------------------------------------------------------------
# Main executable
# --------------------------------------------------------------------------
add_executable(${PROJECT_NAME}
    src/main.c
    src/display/ssd1322.c
    src/lvgl_port/lv_port_disp.c
    src/lvgl_port/lv_port_indev.c
    src/ui/ui_dashboard.c
)

# --------------------------------------------------------------------------
# PIO program (must be after add_executable)
# --------------------------------------------------------------------------
pico_generate_pio_header(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/display/parallel_8080.pio
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/display
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lvgl_port
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/config
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_gpio
    hardware_pio
    hardware_dma
    hardware_timer
    lvgl
)

# USB output for printf debugging, disable UART
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Generate UF2 output
pico_add_extra_outputs(${PROJECT_NAME})
