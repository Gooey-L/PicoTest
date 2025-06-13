#include "pico/stdlib.h"

#define LED_PIN    15
#define BUTTON_PIN 12

int main() {
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    while (1) {
        if (gpio_get(BUTTON_PIN)) {
            gpio_put(LED_PIN, 1);  // Button pressed => LED ON
        } else {
            gpio_put(LED_PIN, 0);  // Button released => LED OFF
        }
        sleep_ms(10);  // Small debounce delay
    }

    return 0;
}
