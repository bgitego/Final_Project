/*
 * user_tim.h
 *
 *  Created on: Dec 28, 2021
 *      Author: bot-10
 */

#ifndef USER_INC_USER_DELAYS_H_
#define USER_INC_USER_DELAYS_H_

#include "main.h"

#define Delay_MS(milliseconds) HAL_Delay(milliseconds)

void Delay_US(uint16_t microseconds );

#endif /* USER_INC_USER_TIM_H_ */
