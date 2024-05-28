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

#include "bsp/board.h"
#include "tusb.h"

#include "usb_descriptors.h"


//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

/* Blink pattern
 * - 250 ms  : device not mounted
 * - 1000 ms : device mounted
 * - 2500 ms : device is suspended
 */
enum  {
  BLINK_NOT_MOUNTED = 250,
  BLINK_MOUNTED = 1000,
  BLINK_SUSPENDED = 2500,
};

static uint32_t blink_interval_ms = BLINK_NOT_MOUNTED;

void led_blinking_task(void);
void hid_task(void);

// config registers
#define CONFIG 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define PWR_MGMT_1 0x6B
#define PWR_MGMT_2 0x6C
// sensor data registers:
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H   0x41
#define TEMP_OUT_L   0x42
#define GYRO_XOUT_H  0x43
#define GYRO_XOUT_L  0x44
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48
#define WHO_AM_I     0x75

#define CHIP_ADDRESS 0x68 

void get_data(int16_t data_out[7]);

volatile int16_t z_data = 0;


// /*------------- MAIN -------------*/
// int main(void)
// {
//   board_init();
//   tusb_init();

//   while (1)
//   {
//     tud_task(); // tinyusb device task
//     led_blinking_task();

//     hid_task();
//   }
// }

//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
  blink_interval_ms = BLINK_NOT_MOUNTED;
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
  (void) remote_wakeup_en;
  blink_interval_ms = BLINK_SUSPENDED;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
  blink_interval_ms = BLINK_MOUNTED;
}

//--------------------------------------------------------------------+
// USB HID
//--------------------------------------------------------------------+

static void send_hid_report(uint8_t report_id, uint32_t btn)
{
  // skip if hid is not ready yet
  if ( !tud_hid_ready() ) return;

  switch(report_id)
  {
    case REPORT_ID_KEYBOARD:
    {
      // use to avoid send multiple consecutive zero report for keyboard
      static bool has_keyboard_key = false;

      if ( btn )
      {
        uint8_t keycode[6] = { 0 };
        keycode[0] = HID_KEY_A;

        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycode);
        has_keyboard_key = true;
      }else
      {
        // send empty key report if previously has key pressed
        if (has_keyboard_key) tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
        has_keyboard_key = false;
      }
    }
    break;

    case REPORT_ID_MOUSE:
    {

      int8_t delta = 50;
      if (z_data < 0){

        delta *=-1;
      }
      // no button, right + down, no scroll, no pan

      tud_hid_mouse_report(REPORT_ID_MOUSE, 0x00, delta, delta, 0, 0);
    }
    break;

    case REPORT_ID_CONSUMER_CONTROL:
    {
      // use to avoid send multiple consecutive zero report
      static bool has_consumer_key = false;

      if ( btn )
      {
        // volume down
        uint16_t volume_down = HID_USAGE_CONSUMER_VOLUME_DECREMENT;
        tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &volume_down, 2);
        has_consumer_key = true;
      }else
      {
        // send empty key report (release key) if previously has key pressed
        uint16_t empty_key = 0;
        if (has_consumer_key) tud_hid_report(REPORT_ID_CONSUMER_CONTROL, &empty_key, 2);
        has_consumer_key = false;
      }
    }
    break;

    case REPORT_ID_GAMEPAD:
    {
      // use to avoid send multiple consecutive zero report for keyboard
      static bool has_gamepad_key = false;

      hid_gamepad_report_t report =
      {
        .x   = 0, .y = 0, .z = 0, .rz = 0, .rx = 0, .ry = 0,
        .hat = 0, .buttons = 0
      };

      if ( btn )
      {
        report.hat = GAMEPAD_HAT_UP;
        report.buttons = GAMEPAD_BUTTON_A;
        tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));

        has_gamepad_key = true;
      }else
      {
        report.hat = GAMEPAD_HAT_CENTERED;
        report.buttons = 0;
        if (has_gamepad_key) tud_hid_report(REPORT_ID_GAMEPAD, &report, sizeof(report));
        has_gamepad_key = false;
      }
    }
    break;

    default: break;
  }
}

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(void)
{
  // Poll every 10ms
  const uint32_t interval_ms = 10;
  static uint32_t start_ms = 0;

  if ( board_millis() - start_ms < interval_ms) return; // not enough time
  start_ms += interval_ms;

  // uint32_t const btn = board_button_read();

  uint32_t const btn = 1;

  

  // Remote wakeup
  if ( tud_suspended() && btn )
  {
    // Wake up host if we are in suspend mode
    // and REMOTE_WAKEUP feature is enabled by host
    tud_remote_wakeup();
  }else
  {
    // Send the 1st of report chain, the rest will be sent by tud_hid_report_complete_cb()
    send_hid_report(REPORT_ID_MOUSE, btn);
  }
}

// Invoked when sent REPORT successfully to host
// Application can use this to send the next report
// Note: For composite reports, report[0] is report ID
void complete_cb(uint8_t instance, uint8_t const* report, uint16_t len)
{
  (void) instance;
  (void) len;

  uint8_t next_report_id = report[0] + 1;

  if (next_report_id < REPORT_ID_COUNT)
  {
    send_hid_report(next_report_id, board_button_read());
  }
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
  (void) instance;

  if (report_type == HID_REPORT_TYPE_OUTPUT)
  {
    // Set keyboard LED e.g Capslock, Numlock etc...
    if (report_id == REPORT_ID_KEYBOARD)
    {
      // bufsize should be (at least) 1
      if ( bufsize < 1 ) return;

      uint8_t const kbd_leds = buffer[0];

      if (kbd_leds & KEYBOARD_LED_CAPSLOCK)
      {
        // Capslock On: disable blink, turn led on
        blink_interval_ms = 0;
        board_led_write(true);
      }else
      {
        // Caplocks Off: back to normal blink
        board_led_write(false);
        blink_interval_ms = BLINK_MOUNTED;
      }
    }
  }
}

//--------------------------------------------------------------------+
// BLINKING TASK
//--------------------------------------------------------------------+
void led_blinking_task(void)
{
  static uint32_t start_ms = 0;
  static bool led_state = false;

  // blink is disabled
  if (!blink_interval_ms) return;

  // Blink every interval ms
  if ( board_millis() - start_ms < blink_interval_ms) return; // not enough time
  start_ms += blink_interval_ms;

  board_led_write(led_state);
  led_state = 1 - led_state; // toggle
}




int main() {
    stdio_init_all();

    // initialize spi
    i2c_init(i2c_default, 348000);

    //setup other spi pins
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    
    uint8_t readbuf[1], writebuf[1];

    writebuf[0] = 0x75;


    i2c_write_blocking(i2c_default, CHIP_ADDRESS, writebuf, 1, true);
    i2c_read_blocking(i2c_default, CHIP_ADDRESS, readbuf, 1, false);


    // Set config
    uint8_t writebuf2[2];

    writebuf2[0] = PWR_MGMT_1;
    writebuf2[1] = 0;
    i2c_write_blocking(i2c_default, CHIP_ADDRESS, writebuf2, 2, false);

    writebuf2[0] = ACCEL_CONFIG;
    writebuf2[1] = 0;
    i2c_write_blocking(i2c_default, CHIP_ADDRESS, writebuf2, 2, false);

    writebuf2[0] = GYRO_CONFIG;
    writebuf2[1] = 0x3 << 3;
    i2c_write_blocking(i2c_default, CHIP_ADDRESS, writebuf2, 2, false);


    unsigned int last_time = to_ms_since_boot(get_absolute_time());
    int16_t recevied_data[7];

    board_init();
    tusb_init();


    while (true){
      // while (to_ms_since_boot(get_absolute_time()) - last_time - 10000 < 0) {}
      // sleep_ms(500);
      // last_time = to_ms_since_boot(get_absolute_time());

      get_data(recevied_data);

      z_data = recevied_data[2];

      // printf("gryo: x: %d y: %d, z: %d\n", recevied_data[4], recevied_data[5], recevied_data[6]);
      // printf("acceleration: x: %d, y: %d, z: %d\n", recevied_data[0], recevied_data[1], recevied_data[2]);

      // i2c_write_blocking(i2c_default, CHIP_ADDRESS, writebuf, 1, true);
      // i2c_read_blocking(i2c_default, CHIP_ADDRESS, readbuf, 1, false);

      // printf("whoami: %d\n", readbuf[0]);

      tud_task(); // tinyusb device task
      led_blinking_task();

      hid_task();



      
    }
}


void get_data(int16_t data_out[7]){
    uint8_t writebuf1[1], data_in_buff[14];
    writebuf1[0] = ACCEL_XOUT_H;
    i2c_write_blocking(i2c_default, CHIP_ADDRESS, writebuf1, 1, true);
    i2c_read_blocking(i2c_default, CHIP_ADDRESS, data_in_buff, 14, false);
  
    int16_t accelx, accely, accelz, tmp, gyrox, gyroy, gyroz;

    accelx = (int16_t) ((data_in_buff[0] << 8) | data_in_buff[1]);
    // accelx *= 0.000061;

    accely = (int16_t)  ((data_in_buff[2] << 8) | data_in_buff[3]);
    // accely *= 0.000061;

    accelz = (int16_t)  ((data_in_buff[4] << 8) | data_in_buff[5]);
    // accelz *= 0.000061;

    tmp = (int16_t)  ((data_in_buff[6] << 8) | data_in_buff[7]);
    // tmp = tmp/340.0f + 36.53;

    gyrox = (int16_t)  ((data_in_buff[8] << 8) | data_in_buff[9]);
    // gyrox *= 0.007630;

    gyroy = (int16_t)  ((data_in_buff[10] << 8) | data_in_buff[11]);
    // gyroy *= 0.007630;

    gyroz = (int16_t)  ((data_in_buff[12] << 8) | data_in_buff[13]);
    // gyroz *= 0.007630;

    data_out[0] = accelx;
    data_out[1] = accely;
    data_out[2] = accelz;
    data_out[3] = tmp;
    data_out[4] = gyrox;
    data_out[5] = gyroy;
    data_out[6] = gyroz;
}
    

