#ifndef __CAN2_RECE_H
#define __CAN2_RECE_H

#include "System_Variables.h"

void CAN2_Rece_Init(void);
void CAN2_Filter_Init(void);
void CAN2_Rece_DATAHandle(void);
float _8bits_to_float(uint8_t part1,uint8_t part2,uint8_t part3,uint8_t part4);
#endif /*__CAN2_RECE_H*/