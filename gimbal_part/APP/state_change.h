#ifndef __STATE_CHANGE_H
#define __STATE_CHANGE_H

#include "System_Variables.h"


Fire_state friction_State(rc_data_t *rc_data);
Rammer_State Rammer_stateChange(rc_data_t *rc_data);
Gimbal_State Gimbal_StateChange(rc_data_t *rc_data);
#endif /*__STATE_CHANGE_H*/