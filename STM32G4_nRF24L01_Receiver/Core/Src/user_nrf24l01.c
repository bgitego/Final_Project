/*
 * user_nrf24l01.c
 *
 *  Created on: Feb 14, 2022
 *      Author: bot-10
 */

#include "user_nrf24l01.h"
#include <stddef.h>
#include "user_main.h"

#define MAX_COUNT_WAIT_10MS 10000  //how long to wait for status of transmission before declaring as failed.
uint8_t user_nrf24l01_send_data(uint8_t data)
{
	uint16_t time_out_count;

	nrf24l01_write_tx_payload(&data, 1, true); //transmit received char over RF

	for(time_out_count = 0; time_out_count <= MAX_COUNT_WAIT_10MS; time_out_count++)	//wait until the packet has been sent or the maximum number of retries has been reached
	{
		Delay_US(1);

		if(nrf24l01_irq_pin_active() && ( nrf24l01_irq_tx_ds_active() || nrf24l01_irq_max_rt_active()))
		{
			if(nrf24l01_irq_max_rt_active())
			{
				nrf24l01_flush_tx(); //get the unsent character out of the TX FIFO
				printf("***\n");
			}
			break;
		}

	}

	nrf24l01_irq_clear_all(); //clear all interrupts in the 24L01


	if( time_out_count == MAX_COUNT_WAIT_10MS) 	//if we've waited more then 10ms let's assume transmission failed and inform users with timeout.
	{
	    printf("tx time_out\n");
	    return 0;
	}
	else
	{
		return 1;
	}
}

uint8_t user_nrf24l01_request_data(uint8_t data)
{
	uint8_t returned_data = 255; //if request fail return 255 as result.
	uint16_t time_out_count;

	if((user_nrf24l01_send_data(data) == 1))
	{
		nrf24l01_set_as_rx(true); //configure rx
		//wait for up to 10 seconds for data then timeout.
		for(time_out_count = 0; time_out_count <= MAX_COUNT_WAIT_10MS; time_out_count++)
		{

			Delay_US(1);
			//check to see if the data has been received.  if so, get the data and exit the loop.
			//  if the loop is at its last count, assume the packet has been lost and set the data
			if((nrf24l01_irq_pin_active() && nrf24l01_irq_rx_dr_active()))
			{
				nrf24l01_read_rx_payload(&returned_data, 1); //get the payload into data
		 		break;
			}
		}
		if( time_out_count == MAX_COUNT_WAIT_10MS) 	//if we've waited more then 10ms let's assume receive failed.
		{
		    printf("Rcv time_out\n");
		}

	}
	else
	{
		printf("request failed to transmit\n");
	}

	//printf("time: %d\n",count);
	nrf24l01_irq_clear_all(); //clear interrupts again1
	Delay_US(130);
	nrf24l01_set_as_tx(); //configure as TX

	return returned_data;
}

uint8_t user_nrf24l01_response_to_request_data(uint8_t data)
{
	Delay_US(130); //wait for transmitter to switch from standby to RX
	nrf24l01_set_as_tx(); //configure as TX
	user_nrf24l01_send_data(data);
	nrf24l01_set_as_rx(true); //configure rx
	return 1;
}
