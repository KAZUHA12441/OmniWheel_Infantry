#ifndef __CAN2_SEND_H
#define __CAN2_SEND_H

#include "System_Variables.h"


void Board_CAN2_dataHandle_Part1(OmniWheel_Infantry_Gimbal_Struct *Gimbal_struct);
void Board_CAN2_dataHandle_Part2(OmniWheel_Infantry_Gimbal_Struct *Gimbal_struct);
void float_to_8bits(uint32_t data,uint8_t *part1,uint8_t *part2,uint8_t *part3,uint8_t *part4);
void Board_Data_Send(void);
void Gimbal_Data_Part3_Send(void);
void Gimbal_11Data_Part2_Send(void);
void CAN2_SENDDATA_Part3(OmniWheel_Infantry_Gimbal_Struct *Gimbal_struct);
#endif /*__CAN2_SEND_H*/