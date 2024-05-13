/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include "hardware/spi.h"
#include <math.h>



static void write_data(uint16_t data) {
  uint16_t message;
  //message += 0b0011<<12;
  //message += data << 2;
  uint8_t messages[2];
  messages[0] = (0b0011 << 4) + (data >> 6) ;
  messages[1] = data << 2;
  asm volatile("nop \n nop \n nop");
  gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 0);
  asm volatile("nop \n nop \n nop");
  spi_write_blocking(spi_default, messages, 2);
  asm volatile("nop \n nop \n nop");
  gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
  asm volatile("nop \n nop \n nop");
}


int main() {
    stdio_init_all();

    // initialize spi
    spi_init(spi_default, 20*10000);

    // setup CSN pin
    gpio_init(PICO_DEFAULT_SPI_CSN_PIN);
    gpio_set_dir(PICO_DEFAULT_SPI_CSN_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_SPI_CSN_PIN, 1);
    //setup other spi pins
    gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);

    uint16_t c = 0;
    uint16_t data;
    while (1) {
      c++;
      
      if (c > 1000) {c = 0;}
      if (c <= 500) {
      data = ((c / 500.0f)*1024.0);
      }
      else {data = ((2-(c/500.0f)) * 1024.0);}
      write_data(data);
      sleep_ms(1);
      
    }
    
}
