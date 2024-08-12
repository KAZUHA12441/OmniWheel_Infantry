#ifndef __CAN1_SEND_H
#define __CAN1_SEND_H

#include "System_Variables.h"

void chassis_CAN_dataHandle_Part1(OmniWheel_Infantry_Chassis_Struct *chassis_struct);
void chassis_CAN_dataHandle_Part2(OmniWheel_Infantry_Chassis_Struct *chassis_struct);

void Chassis_Data_Part1_Send(void);
void Chassis_Data_Part2_Send(void);
#endif /*__CAN1_SEND_H*/