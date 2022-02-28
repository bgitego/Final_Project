/*
 * user_statemachine.h
 *
 *  Created on: Feb 22, 2022
 *      Author: bot-10
 *      https://blog.mbedded.ninja/programming/general/control-methodology/a-function-pointer-based-state-machine/
 */

#ifndef INC_USER_STATEMACHINE_H_
#define INC_USER_STATEMACHINE_H_

#include "user_main.h"

//Possible states of states machine
typedef  enum {
	ST_INIT,
	ST_IDLE,
	ST_ARM,
	ST_POLL,
	ST_UPDATE_HEARTBEAT,
	ST_CHECK_RX,
	ST_DISARM,
} state_t;

//Possible events of states machine
typedef enum{
	EV_IDLE,
	EV_ARM,
	EV_CHECK_RX,
	EV_POLL,
	EV_DISARM,
	EV_UPDATE_HEARTBEAT
} event_t;

//Define a row in a transition matrix table.
typedef struct {
	state_t current_state;
	event_t event;
	state_t next_state;
} state_transition_matrix_row_t;


//holds a function pointer to function called in each states;
typedef struct {
	const char * name;
	void (*func)(void);
} state_function_row_t;


//Struct to hold current state state, to be passed as a pointer.
typedef struct {
	state_t current_state;
} state_machine_t;


//State function definitions
void st_init(void);
void st_ilde(void);
void st_arm(void);
void st_poll(void);
void st_update_heartbeat(void);
void st_check_rx(void);
void st_disarm(void);

//state machine specific functions
void state_machine_init(state_machine_t *state_machine);
void state_machine_run_iteration(state_machine_t *state_machine, event_t event);
const char * state_machine_get_state_name(state_t state);


#endif /* INC_USER_STATEMACHINE_H_ */
