/*
 * user_spi.c
 *
 *  Created on: Dec 28, 2021
 *      Author: bot-10
 */
#include "user_spi.h"


uint8_t spi1_send_read_byte(uint8_t byte)
{
	uint16_t SPI1_DATA_LEN = 1;
	uint32_t SPI1_TIMEOUT_MS = 1000;
	uint8_t received = 0;
	HAL_SPI_TransmitReceive(&hspi1,&byte,&received,SPI1_DATA_LEN,SPI1_TIMEOUT_MS);

	return received;
}
