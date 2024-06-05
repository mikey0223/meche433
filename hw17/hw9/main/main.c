/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include <math.h>
#include "hardware/uart.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 0
#define UART_RX_PIN 1

static int chars_rxed = 0;
volatile char uart_message[100];
static volatile unsigned int count=0;

volatile int pos_val = 0;


// RX interrupt handler
void on_uart_rx() {
 
    while (uart_is_readable(UART_ID)) {
        char ch = uart_getc(UART_ID);
        // printf("received\n");

        if (ch == '\n') {
          count = 0;
          printf("%s\n", uart_message);
          // pos_val = sscanf(uart_message, "%f\n", &pos_val);
          pos_val =  atoi(uart_message);
          memset(uart_message, '\0', sizeof(char)*100);
          
        }
        else{
          uart_message[count] = ch;
          count++;
        }
        
        chars_rxed++;
    }
}

void uart_setup(void) {
  // Set up our UART with a basic baud rate.
  uart_init(UART_ID, 2400);

  // Set the TX and RX pins by using the function select on the GPIO
  // Set datasheet for more information on function select
  // gpio_set_function(7, GPIO_FUNC_UART);
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  // Actually, we want a different speed
  // The call will return the actual baud rate selected, which will be as close as
  // possible to that requested
  int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);

  // Set UART flow control CTS/RTS, we don't want these, so turn them off
  uart_set_hw_flow(UART_ID, false, false);

  // Set our data format
  uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

  // Turn off FIFO's - we want to do this character by character
  uart_set_fifo_enabled(UART_ID, false);

  // Set up a RX interrupt
  // We need to set up the handler first
  // Select correct interrupt for the UART we are using
  int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

  // And set up and enable the interrupt handlers
  irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
  irq_set_enabled(UART_IRQ, true);

  // Now enable the UART to send interrupts - RX only
  uart_set_irq_enables(UART_ID, true, false);

  // OK, all set up.
  // Lets send a basic string out, and then run a loop and wait for RX interrupts
  // The handler will count them, but also reflect the incoming data back with a slight change!
  uart_puts(UART_ID, "\nHello, uart interrupts\n");

}



int main() {
    stdio_init_all();

    // initialize spi

    // //setup other i2c pins
    // gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    // gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);

    // Tell GPIO 0 and 1 they are allocated to the PWM
    gpio_set_function(10, GPIO_FUNC_PWM);
    gpio_set_function(11, GPIO_FUNC_PWM);
    gpio_set_function(12, GPIO_FUNC_PWM);
    gpio_set_function(13, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint slice_num = pwm_gpio_to_slice_num(10);
    uint slice_num2 = pwm_gpio_to_slice_num(12);

    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 65535);
    pwm_set_wrap(slice_num2, 65535);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 65535*2/3);
    pwm_set_chan_level(slice_num2, PWM_CHAN_A, 65535*2/3);
    // Set initial B output high for three cycles before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);
    pwm_set_chan_level(slice_num2, PWM_CHAN_B, 0);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);
    pwm_set_enabled(slice_num2, true);

    


    uart_setup();



    
    float pos = 0.0f;
    float gain_p = 40000.0f, gain_i = 0.0f, gain_d = 20000.0f;
    float integral_gain_max = 10;
    float total_error = 0;
    float prev_error = 0;
    while (true) {
      if (pos_val < 0) {continue;}
      pos = pos_val/1024.0f;
      // float fps1 = 1/((t2-t1)/1000000.0f);
      // t1 = to_us_since_boot(get_absolute_time());
      // ssd1306_drawPixel(0,0,1);
      // // int adc_val = adc_read();
      // // char message[50]; sprintf(message, "my var = %d", adc_val); draw_message(10,10,message);
      // char message2[50]; sprintf(message2, "fps = %.2f", fps1); draw_message(0,0,message2);
      
      // ssd1306_update();
      // t2 = to_us_since_boot(get_absolute_time());
      
      // scanf("%d", &a);
      // char s[10];  
      // printf("%d\n", a);
      // sprintf(s, "%d", a);
      // uart_puts(UART_ID, s);

      float error = pos-0.5f;
      if (fabs(error) < 0.10f) {continue;}
      total_error += error;

      if (total_error > integral_gain_max) {total_error = integral_gain_max;}
      else if (total_error < integral_gain_max * -1.0f) {total_error = integral_gain_max * -1.0f;}


      float u = error*gain_p + total_error * gain_i + (error-prev_error)*gain_d;

      prev_error = error;

      float left_motor = 65535*2.0f/3.0f - u;
      float right_motor = 65535*2.0f/3.0f + u;

      if (left_motor > 65535) {left_motor = 65535;}
      else if (left_motor < 0) {left_motor = 0;}
      if (right_motor > 65535) {right_motor = 655535;}
      else if (right_motor < 0) {right_motor = 0;}

      printf("Left motor: %d, Right motor: %d\n", (uint16_t) left_motor,(uint16_t) right_motor);
      
      

      pwm_set_chan_level(slice_num2, PWM_CHAN_A, (uint16_t) left_motor);
      pwm_set_chan_level(slice_num, PWM_CHAN_A, (uint16_t) right_motor);




      


    }

    
}

