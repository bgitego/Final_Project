/*
 * user_tim.h
 *
 *  Created on: Dec 28, 2021
 *      Author: bot-10
 */

#ifndef USER_INC_USER_DELAYS_H_
#define USER_INC_USER_DELAYS_H_

#include "main.h"

#define TIME_MAX 4294967296

typedef __uint32_t t_time ;

#define Delay_MS(milliseconds) HAL_Delay(milliseconds)

void Delay_US(uint32_t microseconds );

t_time time_passed(t_time );
t_time time_now();

#endif /* USER_INC_USER_TIM_H_ */
