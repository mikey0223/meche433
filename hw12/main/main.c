/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include <math.h>
#include "hardware/pwm.h"


#define PWM_PIN 0

void set_degrees(float f, uint16_t min, uint16_t max, uint slice_num);

int main() {
  stdio_init_all();

  gpio_set_function(PWM_PIN, GPIO_FUNC_PWM); // Set the LED Pin to be PWM
  uint slice_num = pwm_gpio_to_slice_num(PWM_PIN); // Get PWM slice number
  float div = 38; // must be between 1-255
  pwm_set_clkdiv(slice_num, div); // divider
  uint16_t wrap = 65535; // when to rollover, must be less than 65535
  pwm_set_wrap(slice_num, wrap);
  pwm_set_enabled(slice_num, true); // turn on the PWM

  uint16_t min = 0.0005f/(0.02f/wrap); // ~0.5ms
  uint16_t max = 0.0025f/(0.02f/wrap); // ~2.5ms

  pwm_set_gpio_level(PWM_PIN, max); 

  unsigned int start_time = to_ms_since_boot(get_absolute_time());

  while (true) {
    float degree_to_set = fabs((((to_ms_since_boot(get_absolute_time()) - start_time) % 4000) / 4000.0f * 360.0f) * -1.0f + 180.0f);
    printf("%f\n", degree_to_set);
    set_degrees(degree_to_set, min, max, slice_num);  

  }

 



    
}

void set_degrees(float f, uint16_t min, uint16_t max, uint slice_num) {
  pwm_set_gpio_level(slice_num, (uint16_t) ((max-min) * f/180.0f + min));

}


