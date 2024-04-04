/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define LED_PIN 15
#define BUTTON_PIN 20


int main() {
    stdio_init_all();
    while (!stdio_usb_connected()) {
        sleep_ms(100);
    }
    gpio_init(LED_PIN);
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

    int adc_vals[100];
    while (1) {
        printf("Start\r\n");
        gpio_put(LED_PIN, 1); // turn led on
        while (!gpio_get(BUTTON_PIN)) { } // do nothing while button is not pressed
        gpio_put(LED_PIN, 0); // turn led off

        printf("How many samples would you like (between 1 and 100)?\r\n");
        int num;
        scanf("%d", &num);
        printf("Number of sample requested: %d\r\n",num);
        for (int i = 0; i < num; i++) {
          adc_vals[i] = adc_read();
          sleep_ms(10);
        }
        float volt;
        for (int i=0; i < num; i++) {
          volt = adc_vals[i]*3.3/4096.0;
          printf("voltage is %.2f \r\n", volt);
        }
    }
}
