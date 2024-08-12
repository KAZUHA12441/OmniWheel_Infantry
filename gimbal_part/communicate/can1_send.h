#ifndef __CAN1_SEND_H
#define __CAN1_SEND_H

#include "System_Variables.h"

void Gimbal_CAN_dataHandle_Part1(OmniWheel_Infantry_Gimbal_Struct *gimbal_struct);
void Gimbal_Data_Part1_Send(void);
void Gimbal_Data_Part2_Send(void);
void Gimbal_CAN_dataHandle_Part2(OmniWheel_Infantry_Gimbal_Struct *gimbal_struct);
#endif /*__CAN1_SEND_H*/