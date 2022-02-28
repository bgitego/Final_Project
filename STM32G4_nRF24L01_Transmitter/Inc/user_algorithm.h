/*
 * user_algorithm.h
 *
 *  Created on: Feb 21, 2022
 *      Author: bot-10
 */

#ifndef INC_USER_ALGORITHM_H_
#define INC_USER_ALGORITHM_H_

#include "stdint.h"

void add_to_fifo_size_8(uint16_t * buffer, uint16_t new_sample);

uint16_t get_average_size_8(uint16_t * buffer);

#endif /* INC_USER_ALGORITHM_H_ */
