#ifndef __BSP_ENCODER_H
#define __BSP_ENCODER_H

#include "main.h"

typedef  struct
{
    int32_t  Encoder_Record_val;   //累计码盘值
    int32_t  Encoder_Actual_val;   //真实码盘值
    float    Actual_angle;         //真实角度
    float    Record_angle;         //累计角度
}Encoder_t;

#endif /*__BSP_ENCODER_H*/