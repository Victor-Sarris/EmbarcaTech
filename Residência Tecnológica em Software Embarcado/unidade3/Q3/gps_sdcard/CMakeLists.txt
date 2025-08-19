cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(gps_lcd C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(gps_lcd
    main.c
)

target_link_libraries(gps_lcd
    pico_stdlib
    hardware_uart
    hardware_spi
    hardware_gpio
)

pico_enable_stdio_usb(gps_lcd 1)
pico_enable_stdio_uart(gps_lcd 0)

pico_add_extra_outputs(gps_lcd)
