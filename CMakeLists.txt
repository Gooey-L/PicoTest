cmake_minimum_required(VERSION 3.20)

set(PICO_SDK_FETCH_FROM_GIT on)

include(include/pico_sdk_import.cmake)

project(PicoLED)

pico_sdk_init()

add_executable(PicoLED
  src/main.c
)

target_link_libraries(PicoLED
  pico_stdlib
  pico_stdio_usb
)

pico_add_extra_outputs(PicoLED)
