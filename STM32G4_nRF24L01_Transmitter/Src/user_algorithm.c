/*
 * user_algorithm.c
 *
 *  Created on: Feb 21, 2022
 *      Author: bot-10
 */
#include "user_algorithm.h"

void add_to_fifo_size_8(uint16_t * buffer, uint16_t new_sample)
{
	buffer[7] = buffer[6];
	buffer[6] = buffer[5];
	buffer[5] = buffer[4];
	buffer[4] = buffer[3];
	buffer[3] = buffer[2];
	buffer[2] = buffer[1];
	buffer[1] = buffer[0];
	buffer[0] = new_sample;
}

uint16_t get_average_size_8(uint16_t * buffer)
{
	return  ((buffer[0] + buffer[1] + buffer[2] + buffer[3] + buffer[4] + buffer[5] + buffer[6] + buffer[7])/(uint32_t)(8));
}

