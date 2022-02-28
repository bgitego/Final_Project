/*
 * user_main.h
 *
 *  Created on: Dec 16, 2021
 *      Author: bot-10
 */

#ifndef USER_MAIN_H_
#define USER_MAIN_H_

#include "main.h"
#include "i2c.h"
#include "user_spi.h"
#include "user_delays.h"
#include "user_nrf24l01.h"
#include "user_retarget.h"
#include "user_vl53l0x.h"
#include "vl53l0x_platform.h"
#include "user_algorithm.h"

#include "console.h"

#define USB_TX_BUFFER_LEN 128
#define USB_RX_BUFFER_LEN 128
#define BUTTON_PRESSED 1
#define PERCENT_DIFF_DEV 10
#define ARM_COMMAND 32
#define DISARM_COMMAND 64

#define DISARMED 0
#define ARMED 1

uint8_t g_buffer[128];
uint16_t g_length;

extern VL53L0X_Dev_t VL53L0XDev;
extern VL53L0X_Error status;
extern VL53L0X_RangingMeasurementData_t RangingMeasurementData;

extern uint8_t data; //register to hold letter sent and received
extern uint8_t  armed_status;
extern uint8_t disarmed_status;
extern uint16_t fifo_buffer[8];
extern uint8_t fifo_buffer_len;
extern uint16_t average, percent_diff;



/*______________________________________________________________________________________________*/

volatile uint8_t g_enable_debugging;    //Used to enable writing to USB serial port
volatile uint8_t g_enable_debugging_vl53l0x;    //Used to enable logging for the vl53l0x
volatile uint8_t g_enable_debugging_STMC;    //Used to enable logging for the state machine
volatile uint8_t g_raw_button_pressed;  //Used to detect button pressed.
volatile uint8_t usb_cdc_transmit_buffer[USB_TX_BUFFER_LEN];    //Used to enable writing to USB serial port
volatile uint8_t usb_cdc_transmit_buffer_len;
volatile uint8_t usb_cdc_received_buffer[USB_RX_BUFFER_LEN];    //Used to enable writing to USB serial port
volatile uint8_t usb_cdc_received_buffer_len;
volatile uint8_t g_raw_button_pressed;  //Used to detect button pressed.
volatile uint8_t g_arm_system_flag;
void user_main(void);

#endif /* USER_MAIN_H_ */
