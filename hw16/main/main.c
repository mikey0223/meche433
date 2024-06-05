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


void draw_char(unsigned char x, unsigned char y, unsigned char c);

void draw_message(unsigned char x, unsigned char y, char *message);

// RX interrupt handler
void on_uart_rx() {
 
    while (uart_is_readable(UART_ID)) {
        char ch = uart_getc(UART_ID);
        // printf("received\n");

        if (ch == '\n') {
          count = 0;
          printf("%s\n", uart_message);
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

    uart_setup();

    unsigned int t1=0, t2=100000000;

    

    // Tell GPIO 0 and 1 they are allocated to the PWM
    gpio_set_function(0, GPIO_FUNC_PWM);
    gpio_set_function(1, GPIO_FUNC_PWM);

    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint slice_num = pwm_gpio_to_slice_num(0);

    // Set period of 4 cycles (0 to 3 inclusive)
    pwm_set_wrap(slice_num, 65535);
    // Set channel A output high for one cycle before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 65535/2);
    // Set initial B output high for three cycles before dropping
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);
    // Set the PWM running
    pwm_set_enabled(slice_num, true);

    int a;

    while (true) {
    //   // float fps1 = 1/((t2-t1)/1000000.0f);
    //   // t1 = to_us_since_boot(get_absolute_time());
    //   // ssd1306_drawPixel(0,0,1);
    //   // // int adc_val = adc_read();
    //   // // char message[50]; sprintf(message, "my var = %d", adc_val); draw_message(10,10,message);
    //   // char message2[50]; sprintf(message2, "fps = %.2f", fps1); draw_message(0,0,message2);
      
    //   // ssd1306_update();
    //   // t2 = to_us_since_boot(get_absolute_time());
      
    //   scanf("%d", &a);
    //   char s[10];  
    //   printf("%d\n", a);
    //   sprintf(s, "%d", a);
    //   uart_puts(UART_ID, s);

      scanf("%d", &a);
      printf("inputted %d\n", a);

      if (a > 0){
        a = a/100.0f *65535;
        pwm_set_chan_level(slice_num, PWM_CHAN_A ,(uint16_t) a);
        pwm_set_chan_level(slice_num, PWM_CHAN_B, 0);
      }
      else {
        a = a/100.0f *-65535;
        pwm_set_chan_level(slice_num, PWM_CHAN_B ,(uint16_t) a);
        pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);

      }


    }

    
}


