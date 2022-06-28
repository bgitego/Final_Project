/*
 * user_main.c
 *
 *  Created on: Dec 16, 2021
 *      Author: bot-10
 */
#include "user_main.h"
#include "user_statemachine.h"

#define POLL_RECV_mSEC 25
#define RX_CHECK_INTERVAL_mSEC 60000


uint8_t g_buffer[128];
uint16_t g_length;

VL53L0X_Dev_t VL53L0XDev;
VL53L0X_Error status;
VL53L0X_RangingMeasurementData_t RangingMeasurementData;

uint8_t  data = 0; //register to hold letter sent and received
uint8_t  armed_status = 0;
uint8_t  disarmed_status = 0;
uint16_t fifo_buffer[8] = {0,0,0,0,0,0,0,0};
uint8_t  fifo_buffer_len = 0;


/*______________________________________________________________________________________________*/

uint8_t g_enable_debugging;								//Used to enable writing to USB serial port
uint8_t g_enable_debugging_vl53l0x;						//Used to enable logging for the vl53l0x
uint8_t g_enable_debugging_STMC;    					//Used to enable logging for the state machine
uint8_t g_raw_button_pressed;  							//Used to detect button pressed.
uint8_t usb_cdc_transmit_buffer[USB_TX_BUFFER_LEN];     //Used to enable writing to USB serial port
uint8_t usb_cdc_transmit_buffer_len;
uint8_t usb_cdc_received_buffer[USB_RX_BUFFER_LEN];    //Used to enable writing to USB serial port
uint8_t usb_cdc_received_buffer_len;

uint8_t g_arm_system_flag;

void user_main()
{

	//uint8_t dummy = 0;
	t_time poll_rcv_now,rx_stuck_check_now;
	uint8_t rx_stuck_count;
	//creating state machine object
	state_machine_t state_machine;

	//Initialize state machine. and put system in idle.
	state_machine_init(&state_machine);
	state_machine_run_iteration(&state_machine,EV_IDLE);

	st_init();


	poll_rcv_now = time_now();
	rx_stuck_check_now = time_now();

	while(1)
	{
		Delay_MS(1);

		if( time_passed(poll_rcv_now) >= POLL_RECV_mSEC )
		{
			//printf("sending data\t");
			//user_nrf24l01_send_data(data);
			//dummy = user_nrf24l01_request_data(128);
			//printf("Rvd :%d\t",dummy);
			HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
			poll_rcv_now = time_now();
			data++;
		}

		if( time_passed(rx_stuck_check_now) >= RX_CHECK_INTERVAL_mSEC )
		{
			printf("checking on rx state\n");
			nrf24l01_irq_clear_all(); //clear interrupts again1
			Delay_US(130);
			nrf24l01_set_as_tx(); //configure as TX

			if(nrf24l01_ce_pin_active())
			{
				rx_stuck_count++;
				if(rx_stuck_count >= 10)
				{
					printf("looks like were stuck in received mode\n");
				}
			}
			else
			{
				rx_stuck_count = 0;
			}
			rx_stuck_check_now = time_now();
		}
		//Initializing the state machine.

		if( state_machine.current_state == ST_IDLE )
		{
			//If arm condition initiated from interrupt
			if(g_arm_system_flag == 1)
			{
				if(g_enable_debugging_STMC){printf("Arming System, current state is: %s.\n", state_machine_get_state_name(state_machine.current_state));}
				state_machine_run_iteration(&state_machine,EV_ARM);
			}
			else if(armed_status == false)
			{
				if(g_enable_debugging_STMC){printf("Checking console, current state is: %s.\n", state_machine_get_state_name(state_machine.current_state));}
				state_machine_run_iteration(&state_machine,EV_CHECK_RX);
			}
		}
		else if( state_machine.current_state == ST_ARM )
		{
			if(armed_status == true || (g_arm_system_flag == true))
			{
				//If current state is ARMED, enable polling for door intrustion.
				if(g_enable_debugging_STMC){printf("Polling for door status, current state is: %s.\n", state_machine_get_state_name(state_machine.current_state));}
				state_machine_run_iteration(&state_machine,EV_POLL);
			}
		}
		else if( state_machine.current_state == ST_POLL )
		{
			//if condition to disarm is met while polling set disarm events.
			if( disarmed_status == true )
			{
				if(g_enable_debugging_STMC){printf("Setting disarm events, current state is: %s.\n", state_machine_get_state_name(state_machine.current_state));}
				state_machine_run_iteration(&state_machine,EV_DISARM);
			}
			//if the system is armed while polling  we need to set update heartbeat events.
			else if(armed_status == true)
			{
				if(g_enable_debugging_STMC){printf("Setting heartbeat events, current state is: %s.\n", state_machine_get_state_name(state_machine.current_state));}
				state_machine_run_iteration(&state_machine,EV_UPDATE_HEARTBEAT);
			}
		}
		else if( state_machine.current_state == ST_UPDATE_HEARTBEAT )
		{
			//if current state is update heartbeat, set next events to Check RX
			if(g_enable_debugging_STMC){printf("Checking console, current state is: %s.\n", state_machine_get_state_name(state_machine.current_state));}
			state_machine_run_iteration(&state_machine,EV_CHECK_RX);
		}
		else if( state_machine.current_state == ST_CHECK_RX )
		{
			//if condition to disarm is met while polling set disarm events.
			if( disarmed_status == true )
			{
				if(g_enable_debugging_STMC){printf("Setting disarm events, current state is: %s.\n", state_machine_get_state_name(state_machine.current_state));}
				state_machine_run_iteration(&state_machine,EV_DISARM);
			}

			//if the system is armed while checking console  we need to set update polling events.
			else if(armed_status == true)
			{
				//If current state is ARMED, enable polling for door intrustion.
				if(g_enable_debugging_STMC){printf("Polling for door status, current state is: %s.\n", state_machine_get_state_name(state_machine.current_state));}
				state_machine_run_iteration(&state_machine,EV_POLL);
			}
			else if(armed_status == false)
			{
				//If current state is ST_CHECK_RX, and system is not armedtransition to IDLE states
				state_machine_run_iteration(&state_machine,EV_IDLE);
			}
			else if(g_arm_system_flag == 1)
			{
				if(g_enable_debugging_STMC){printf("Arming System, current state is: %s.\n", state_machine_get_state_name(state_machine.current_state));}
				state_machine_run_iteration(&state_machine,EV_ARM);
			}
		}
		else if( state_machine.current_state == ST_DISARM )
		{
			//If current state is DISARM, transition to IDLE states
			state_machine_run_iteration(&state_machine,EV_IDLE);
		}
	}
}


//External Interrupt call back function for nRF24L01_IRQ_EXTI_IRQn

void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin )
{
	if(GPIO_Pin == nRF24L01_IRQ_Pin)
	{
		//HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
	}

	if(GPIO_Pin == BUTTON_Pin)
	{
		g_arm_system_flag = 1;
	}
}

