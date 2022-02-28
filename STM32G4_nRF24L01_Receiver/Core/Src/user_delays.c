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

// Based on example form Making Embedded Systems book Chapter 5 pg.140.
t_time time_passed(t_time since )
{
	t_time now = HAL_GetTick();

	if (now >= since)
	{
		return (now - since);
	}
	else
	{
		return (now + (1 + TIME_MAX - since));
	}
}
t_time time_now()
{
	return (t_time)HAL_GetTick();
}
