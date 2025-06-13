cmake_minimum_required(VERSION 3.20)

set(PICO_SDK_FETCH_FROM_GIT on)

include(include/pico_sdk_import.cmake)

project(PicoLED C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(PicoLED
  src/main.c
  include/lcd1602_i2c.c
)

target_link_libraries(PicoLED
  pico_stdlib
  pico_stdio_usb
  hardware_i2c
)

target_include_directories(PicoLED PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/include
)

pico_enable_stdio_usb(PicoLED 1)
pico_enable_stdio_uart(PicoLED 0)

pico_add_extra_outputs(PicoLED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
