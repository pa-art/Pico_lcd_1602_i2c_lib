/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>
#include "lcd_1602_i2c_lib.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "hardware/adc.h"

#define CONV_FACTOR (3.25f / (1 << 12))

int main() {

    int x, y, c;
    char chr[1], mes_lcd[MAX_CHARS+1];
    uint16_t temp_dat;
    float temp, voltage;

    // This example will use I2C0 on GPIO4 (SDA) and GPIO5 (SCL)
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(4, GPIO_FUNC_I2C);
    gpio_set_function(5, GPIO_FUNC_I2C);
    gpio_pull_up(4);
    gpio_pull_up(5);
    // Make the I2C pins available to picotool
    bi_decl( bi_2pins_with_func(4, 5, GPIO_FUNC_I2C));

    lcd_init();

    stdio_init_all();
    x = y = 0;

    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);    // ADC selected

    const uint LED_PIN = 25;
    bool state = true;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    static uint8_t *message[] =
            {
                    "RP2040 by", "Raspberry Pi",
                    "A brand new", "microcontroller",
                    "Twin core M0", "Full C SDK",
                    "More power in", "your product",
                    "More beans", "than Heinz!"
            };

    while (1) {
/*
        for (int m = 0; m < sizeof(message) / sizeof(message[0]); m += MAX_LINES) {
            for (int line = 0; line < MAX_LINES; line++) {
                lcd_set_cursor(line, (MAX_CHARS / 2) - strlen(message[m + line]) / 2);
                lcd_string(message[m + line]);
            }
            sleep_ms(2000);
            lcd_clear();
        }
*/
/*
        lcd_set_cursor(0,0);
        lcd_string("Hello, world!");
        sleep_ms(2000);
        lcd_clear();
        sleep_ms(1000);
        puts("Hello, world!");
*/
        temp_dat = adc_read();
        voltage = temp_dat * CONV_FACTOR;
        temp = 27 - (voltage - 0.706) / 0.001721;
        //printf("voltage:%2.2f, tempraure:%2.2f\n", voltage, temp);
        sprintf(mes_lcd, "v=%2.3f, T=%2.1f", voltage, temp);
        lcd_set_cursor(0, 0);
        lcd_string(mes_lcd);
        gpio_put(LED_PIN, state);
        sleep_ms(500);
        state = !state;
/*
        if ((c = getchar()) != 0) {
            *chr = (char)c;
            lcd_set_cursor(1, x);
            if (x == 0) {
                lcd_string("                ");
                lcd_set_cursor(1, x);
            }
            lcd_char(*chr);
            putchar(*chr);
            x++;
            if (x >= MAX_CHARS) {
                x = 0;
            }
        }
*/
    }

    return 0;
}
