#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "lcd1602_i2c.h"

#define BUTTON_PIN 10
#define SDA_PIN 4
#define SCL_PIN 5
#define DEBOUNCE_MS 20

int main() {
  stdio_init_all();

  gpio_init(BUTTON_PIN);
  gpio_set_dir(BUTTON_PIN, GPIO_IN);

  bool last_state = true;
  absolute_time_t last_debounce_time = get_absolute_time();

  LCD lcd;
  lcd_init(&lcd, 0x27, SDA_PIN, SCL_PIN, i2c0);
  sleep_ms(1000);

  char buffer[33];

  while (1) {
    bool current = gpio_get(BUTTON_PIN);

    if (current != last_state) {
      last_debounce_time = get_absolute_time();
    }

    if (!current && last_state) {
      printf("NEXT\n");  // Button pressed, send command once
    }
    last_state = current;
    sleep_ms(2);

    int i = 0;
    // Read one full line or until timeout
    while (i < sizeof(buffer) - 1) {
      int ch = getchar_timeout_us(1000000);
      if (ch == PICO_ERROR_TIMEOUT) break;
      if (ch == '\n' || ch == '\r') break;
      buffer[i++] = ch;
    }
    buffer[i] = '\0';

    // Ignore empty or whitespace-only messages
    if (i == 0 || buffer[0] == '\0') {
      continue;
    }

    // Debug print
    printf("Received: %s\n", buffer);

    lcd_clear(&lcd);
    lcd_set_cursor_pos(&lcd, 0, 0);
    lcd_string(&lcd, buffer);
    if (i > 16) {
      lcd_set_cursor_pos(&lcd, 1, 0);
      lcd_string(&lcd, buffer + 16);
    }
  }

  return 0;
}
