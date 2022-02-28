/*
 * user_tim.c
 *
 *  Created on: Dec 28, 2021
 *      Author: bot-10
 */
#include "user_delays.h"
#include "main.h"
#include "tim.h"

void Delay_US(uint16_t microseconds )
{
	// Start timer
	HAL_TIM_Base_Start(&htim6);

	volatile uint16_t start_microseconds = __HAL_TIM_GET_COUNTER(&htim6);

	while ((__HAL_TIM_GET_COUNTER(&htim6) - start_microseconds) < microseconds )
	{
		;
	}

	// Stop timer
	HAL_TIM_Base_Stop(&htim6);
}

