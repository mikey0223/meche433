/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include "hardware/i2c.h"
#include <math.h>



#define ADDR 0b0100000

int main() {
    stdio_init_all();

    // initialize spi
    i2c_init(i2c_default, 20*10000);

    //setup other spi pins
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    
    uint8_t dir_buffer[2], gpio_status_buffer[2];

    uint8_t reg = 0x00;
    uint8_t val = 0b1;
    dir_buffer[0] = reg;
    dir_buffer[1] = val;

    uint8_t reg2 = 0x9;
    uint8_t val2 = 0;
    gpio_status_buffer[0] = reg2;
    gpio_status_buffer[1] = val2;

    i2c_write_blocking(i2c_default, ADDR, dir_buffer, 2, false);
    i2c_write_blocking(i2c_default, ADDR, gpio_status_buffer, 2, false);

    uint8_t gpio_read_buffer[1];
    uint8_t curr_button_state = 1;
    while (true) {
      i2c_write_blocking(i2c_default, ADDR, &reg2, 1, true);
      i2c_read_blocking(i2c_default, ADDR, gpio_read_buffer, 1, false);


      uint8_t button_state = gpio_read_buffer[0] & 1;

      if (button_state != curr_button_state) {
        gpio_status_buffer[1] = (!button_state) << 7;

        i2c_write_blocking(i2c_default,ADDR, gpio_status_buffer, 2, false);
        curr_button_state = button_state;
      }
      

    }



    
}
