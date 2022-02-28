/*
 * user_nRF24L01.h
 *
 *  Created on: Feb 14, 2022
 *      Author: bot-10
 */

#ifndef INC_USER_NRF24L01_H_
#define INC_USER_NRF24L01_H_

#include "nrf24l01.h"

uint8_t user_nrf24l01_send_data(uint8_t data);
uint8_t user_nrf24l01_request_data(uint8_t data);
uint8_t user_nrf24l01_response_to_request_data(uint8_t data);

#endif /* INC_USER_NRF24L01_H_ */
