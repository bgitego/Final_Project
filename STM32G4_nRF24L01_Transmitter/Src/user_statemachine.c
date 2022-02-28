/*
 * user_statemachine.c
 *
 *  Created on: Feb 22, 2022
 *      Author: bot-10
 *      based on tutorial by https://blog.mbedded.ninja/programming/general/control-methodology/a-function-pointer-based-state-machine/
 */


#include "user_statemachine.h"

static state_function_row_t state_functionA[] = {
//Name	//FUNC
{"ST_INIT",	&st_init},
{"ST_IDLE",	&st_ilde},
{"ST_ARM",	&st_arm},
{"ST_POLL",	&st_poll},
{"ST_UPDATE_HEARTBEAT",	&st_update_heartbeat},
{"ST_CHECK_RX",	&st_check_rx},
{"ST_DISARM",	&st_disarm},
};


//Transition Matrix table

static state_transition_matrix_row_t state_transition_matrix[] = {
{ST_INIT, EV_IDLE, ST_IDLE},
{ST_IDLE, EV_ARM, ST_ARM},
{ST_IDLE, EV_CHECK_RX, ST_CHECK_RX},
{ST_ARM, EV_POLL, ST_POLL},
{ST_POLL, EV_DISARM, ST_DISARM},
{ST_POLL, EV_UPDATE_HEARTBEAT, ST_UPDATE_HEARTBEAT},
{ST_UPDATE_HEARTBEAT, EV_CHECK_RX, ST_CHECK_RX},
{ST_CHECK_RX, EV_DISARM, ST_DISARM},
{ST_CHECK_RX, EV_POLL, ST_POLL},
{ST_CHECK_RX, EV_IDLE, ST_IDLE},
{ST_CHECK_RX, EV_ARM, ST_ARM},
{ST_DISARM, EV_IDLE, ST_IDLE},
};


VL53L0X_Dev_t VL53L0XDev;
VL53L0X_Error status;
VL53L0X_RangingMeasurementData_t RangingMeasurementData;

uint8_t data = 0; //register to hold letter sent and received
uint8_t  armed_status = 0;
uint8_t disarmed_status = 0;
uint16_t fifo_buffer[8] = {0,0,0,0,0,0,0,0};
uint8_t fifo_buffer_len = 0;
uint16_t average, percent_diff;

//State function definitions
void st_init(void)
{
	if(g_enable_debugging_STMC){printf("Inside Init Function\n");}
	/*______________________________________________VLX53L0x________________________________________*/

	VL53L0XDev.Id = 0;
	VL53L0XDev.DevLetter ='l';
	VL53L0XDev.I2cHandle = &hi2c1;
	VL53L0XDev.I2cDevAddr = 0x52;
	user_vl53l0x_init(&VL53L0XDev);

	/*______________________________________________________________________________________________*/

	/*______________________________________________nrf24l01________________________________________*/

    nrf24l01_initialize_debug(false, 1, false); //initialize the 24L01 to the debug configuration as TX, 1 data byte, and auto-ack disabled
	/*______________________________________________________________________________________________*/

	ConsoleInit(); //Command console


	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);
	user_nrf24l01_send_data(DISARM_COMMAND);
}
void st_ilde(void)
{
	;
}
void st_arm(void)
{
	if(g_enable_debugging_STMC){printf("Inside Arming Command\n");}
	user_nrf24l01_send_data(ARM_COMMAND);
	armed_status = 1;
	g_arm_system_flag = 0;
	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);
	Delay_MS(5000);
	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);
}

void st_poll(void)
{
	if(g_enable_debugging_STMC){printf("Inside polling function\n");}
	status = VL53L0X_PerformSingleRangingMeasurement(&VL53L0XDev,&RangingMeasurementData);
	add_to_fifo_size_8(fifo_buffer,RangingMeasurementData.RangeMilliMeter);
	if(fifo_buffer_len <= 8){fifo_buffer_len +=1;}
	average = get_average_size_8(fifo_buffer);
	percent_diff = (((average - fifo_buffer[0])/(float)average) * 100);

	if(g_enable_debugging_vl53l0x){printf("Sts(0=Ok): %d Dst mm: %d, avg: %d,deviation (%%): %d\n",(int) RangingMeasurementData.RangeStatus,(int) RangingMeasurementData.RangeMilliMeter,average,(int)percent_diff);}

	if((percent_diff > 10 ) && (armed_status == 1))
	{
		disarmed_status = 1;
	}
}
void st_update_heartbeat(void)
{
	if(g_enable_debugging_STMC){printf("Inside heartbeat function\n");}
	data +=1;
	if(data >=8){data=0;}
	user_nrf24l01_send_data(data);
	HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
}

void st_check_rx(void)
{
	if(g_enable_debugging_STMC){printf("Inside  check rx function \n");}
	if(usb_cdc_received_buffer_len > 0)
	{
		ConsoleProcess();
	}

}
void st_disarm(void)
{
	if(g_enable_debugging_STMC){printf("Inside Disarm function\n");}
	user_nrf24l01_send_data(DISARM_COMMAND);
	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);
	disarmed_status = 0;
	armed_status = 0;
}

//state machine specific functions
void state_machine_init(state_machine_t *state_machine)
{
	//state_machine->current_state = ST_IDLE;
	state_machine->current_state = ST_INIT;
}
void state_machine_run_iteration(state_machine_t *state_machine, event_t event)
{
    // Iterate through the state transition matrix, checking if there is both a match with the current state
    // and the event
    for(int i = 0; i < sizeof(state_transition_matrix)/sizeof(state_transition_matrix[0]); i++)
    {
        if(state_transition_matrix[i].current_state == state_machine->current_state)
        {
            if((state_transition_matrix[i].event == event) /*|| (state_transition_matrix[i].event == EV_ANY)*/)
            {

            	// Call the function associated with transition
                (state_functionA[state_machine->current_state].func)();

            	// Transition to the next state
                state_machine->current_state =  state_transition_matrix[i].next_state;
                break;
            }
        }
    }
}
const char * state_machine_get_state_name(state_t state)
{
    return state_functionA[state].name;
}
