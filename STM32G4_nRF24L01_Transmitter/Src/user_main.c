/*
 * user_main.c
 *
 *  Created on: Dec 16, 2021
 *      Author: bot-10
 */
#include "user_main.h"
#include "user_statemachine.h"



void user_main()
{

	//creating state machine object
	state_machine_t state_machine;

	//Initialize state machine. and put system in idle.
	state_machine_init(&state_machine);
	state_machine_run_iteration(&state_machine,EV_IDLE);

	while(1)
	{
		Delay_MS(25);
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

