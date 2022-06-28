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

#include "tim.h"
#include "console.h"


#define USB_RX_BUFFER_LEN 128
#define USB_TX_BUFFER_LEN 128
#define BUTTON_PRESSED 1
#define PERCENT_DIFF_DEV 5
#define ARM_COMMAND 32
#define DISARM_COMMAND 64

#define DISARMED 0
#define ARMED 1

void user_main(void);

#endif /* USER_MAIN_H_ */
