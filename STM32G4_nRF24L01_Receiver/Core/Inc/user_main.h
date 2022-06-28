/*
 * user_main.h
 *
 *  Created on: Dec 16, 2021
 *      Author: bot-10
 */

#ifndef USER_MAIN_H_
#define USER_MAIN_H_

#include "main.h"
#include "user_spi.h"
#include "user_delays.h"
#include "user_retarget.h"
#include "user_nrf24l01.h"

#include "tim.h"

extern uint8_t bg_buffer[256];
extern uint16_t bg_length;

void user_main(void);



#endif /* USER_MAIN_H_ */
