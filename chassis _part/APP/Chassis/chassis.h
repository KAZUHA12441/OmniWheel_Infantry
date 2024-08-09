#ifndef __CHASSIS_H
#define __CHASSIS_H

#include "System_Variables.h"


void OmniWheelSpeedSolution(float chassis_x,float chassis_y, float chassis_yaw);
void Chassis_Init(void);
void Chassis_RCDataHandle(Chassis_State State);
void OmniWheelSpeedSolution(float chassis_x, float chassis_y, float chassis_yaw);
void Chassis_idle(void);
void Chassis_lock(void);
void ChassisControlStateSPid(void);
void ChassisControlStateOutput(void);
void ChassisControlAchieve(Chassis_State State);
#endif /*__CHASSIS_H*/