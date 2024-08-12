#ifndef __STATE_CHANGE_H
#define __STATE_CHANGE_H

#include "System_Variables.h"

Chassis_State chassis_stateChange(rc_data_t *rc_data);
Rammer_State Rammer_stateChange(rc_data_t *rc_data);
#endif  /*__STATE_CHANGE_H*/