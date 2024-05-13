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
#include "ssd1306.h"
#include "font.h"
#include "hardware/adc.h"

void draw_char(unsigned char x, unsigned char y, unsigned char c);

void draw_message(unsigned char x, unsigned char y, char *message);

#define ADDR 0b0100000

int main() {
    stdio_init_all();

    // initialize spi
    i2c_init(i2c_default, 4*100000);

    //setup other i2c pins
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    
    // configure ssd1306
    ssd1306_setup();
    ssd1306_clear();

    // configure adc
    adc_init();
    adc_gpio_init(26);
    adc_select_input(0);

    unsigned int t1=0, t2=100000000;

    while (true) {
      float fps1 = 1/((t2-t1)/1000000.0f);
      t1 = to_us_since_boot(get_absolute_time());
      ssd1306_drawPixel(0,0,1);
      int adc_val = adc_read();
      char message[50]; sprintf(message, "my var = %d", adc_val); draw_message(10,10,message);
      char message2[50]; sprintf(message2, "fps = %.2f", fps1); draw_message(0,0,message2);
      
      ssd1306_update();
      t2 = to_us_since_boot(get_absolute_time());
      

    }

    
}

void draw_char(unsigned char x, unsigned char y, unsigned char c) {
  for (uint8_t i =0; i < 5; i++){
    for (uint8_t j =0; j < 8; j++) {
      if (ASCII[c][i] >> j &0x1 == 1){
        ssd1306_drawPixel(x+i,31-y+j-8,1);
      }
      else {
        ssd1306_drawPixel(x+i, 31-y+j-8,0);
      }
    }
  }
}

void draw_message(unsigned char x, unsigned char y, char* message) {
  size_t l = strlen(message);
  for (size_t i =0; i < l; i++){
    if (x >= 128) {
      y -= 8; x =0;
    }
    draw_char(x,y, message[i]-0x20);

    x += 5;
  }

}
