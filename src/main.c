#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/stdio_usb.h"

#include "../include/lcd1602_ic2.h"

#define LED_PIN 10
#define BUTTON_PIN 8

int main() {
    stdio_init_all();

    LCD mylcd;
    lcd_init(&mylcd, 0x27, 4, 5, i2c0);

    char message[] = "Hello, world";
    lcd_string(&mylcd, message);

    return 0;
}
