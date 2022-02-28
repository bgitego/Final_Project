/*
 * user_nrf24l01.c
 *
 *  Created on: Feb 14, 2022
 *      Author: bot-10
 */

#include "user_nrf24l01.h"
#include <stddef.h>
#include "user_main.h"

uint8_t user_nrf24l01_send_data(uint8_t data)
{
	nrf24l01_write_tx_payload(&data, 1, true); //transmit received char over RF
    //printf("sending data to receiver\n");

	//wait until the packet has been sent or the maximum number of retries has been reached
	while(!(nrf24l01_irq_pin_active() && nrf24l01_irq_tx_ds_active()))
	{
		//wait for the other 24L01 to come from standby to RX
	  //printf("wait for transmission to complete\n");
	}
	nrf24l01_irq_clear_all(); //clear all interrupts in the 24L01
	//printf("transmission completed\n");
	return 1;
}

uint8_t user_nrf24l01_request_data(uint8_t data)
{
	//printf("Requesting data\n");

	uint8_t returned_data = 255; //if request fail return 255 as result.
	uint16_t count;
	if(user_nrf24l01_send_data(data) == 1)
	{
		nrf24l01_set_as_rx(true); //configure rx
		HAL_Delay(1);
		//wait for up to 10 seconds for data then timeout.
		for(count = 0; count < 100000; count++)
		{
			//printf("inside for loop waiting for data to come\n");
			HAL_Delay(1);
			//check to see if the data has been received.  if so, get the data and exit the loop.
			//  if the loop is at its last count, assume the packet has been lost and set the data
			if((nrf24l01_irq_pin_active() && nrf24l01_irq_rx_dr_active()))
			{
				nrf24l01_read_rx_payload(&returned_data, 1); //get the payload into data
		 		break;
			}
		}

		printf("Delay time: %d",count);
		nrf24l01_irq_clear_all(); //clear interrupts again1
		nrf24l01_set_as_tx(); //configure as TX
	}

	return returned_data;
}

uint8_t user_nrf24l01_response_to_request_data(uint8_t data)
{
	nrf24l01_set_as_tx(); //configure as TX
	HAL_Delay(1);
	user_nrf24l01_send_data(data);
	nrf24l01_set_as_rx(true); //configure rx
	HAL_Delay(1);
	return 1;
}
