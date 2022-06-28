/*
 * user_main.c
 *
 *  Created on: Dec 16, 2021
 *      Author: bot-10
 */
#include "user_main.h"

extern UART_HandleTypeDef huart2;

#define ARM_COMMAND 32
#define DISARM_COMMAND 64
#define HEARTBEAT_FAILLED_TIMEOUT_MS 500


void user_main(void)
{

	uint8_t data = 0; //register to hold letter sent and received
	nrf24l01_initialize_debug(true, 1, true); //initialize the 24L01 to the debug configuration as RX, 1 data byte, and auto-ack enabled
	uint8_t armed_status = 0;
	uint8_t counter = 0;
	//uint8_t heartbeat_stopped,heartbeat_stop_count;
	uint8_t previous_data;
	t_time last_good_heartbeat_time,heartbeat_elapsed_time;

	extern IWDG_HandleTypeDef hiwdg;

	HAL_GPIO_WritePin(LD2_GPIO_Port,LD2_Pin,GPIO_PIN_RESET);

	while(1)
	{

		HAL_IWDG_Refresh(&hiwdg);
		//Do nothing if no data has been received.
		if(!(nrf24l01_irq_pin_active() && nrf24l01_irq_rx_dr_active()))
		{
			//printf("waiting for data\n");
		}
		else
		{

			HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
			nrf24l01_read_rx_payload(&data, 1); //read the packet into data
			nrf24l01_irq_clear_all(); //clear all interrupts in the 24L01
			printf("Rx: %d\n",data);

			if(data == 128)
			{
				data = user_nrf24l01_response_to_request_data(counter);
				if(data == 1)
				{
					printf("Response Succeeded\n");
				}

				counter++;
			}

			if(data == ARM_COMMAND)
			{
				HAL_GPIO_WritePin(LIGHT_CONTROL_GPIO_Port,LIGHT_CONTROL_Pin,GPIO_PIN_SET);
				armed_status = 1;
			}
			if(data == DISARM_COMMAND)
			{
				HAL_GPIO_WritePin(LIGHT_CONTROL_GPIO_Port,LIGHT_CONTROL_Pin,GPIO_PIN_RESET);
				armed_status =  0;
			}
		}

		if(armed_status == 1)
		{
			if(data == previous_data)
			{
				heartbeat_elapsed_time = time_passed(last_good_heartbeat_time);

				if(heartbeat_elapsed_time >= HEARTBEAT_FAILLED_TIMEOUT_MS )
				{
					armed_status = 0;
					HAL_GPIO_WritePin(LIGHT_CONTROL_GPIO_Port,LIGHT_CONTROL_Pin,GPIO_PIN_RESET);
					printf("elapsed time is: %d : ",(int)heartbeat_elapsed_time);
					printf("lost heartbeat while system is armed\n");
				}
			}
			else
			{
				previous_data = data;
				last_good_heartbeat_time = time_now();
			}
		}
	}
}

//External Interrupt call back function for nRF24L01_IRQ_EXTI_IRQn

void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin )
{
	if(GPIO_Pin == nRF24L01_IRQ_Pin)
	{
		HAL_GPIO_TogglePin(LD2_GPIO_Port,LD2_Pin);
	}
}
