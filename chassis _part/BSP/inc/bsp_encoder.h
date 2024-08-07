#ifndef __BSP_ENCODER_H
#define __BSP_ENCODER_H

#include "main.h"

typedef  struct
{
    int32_t  Encoder_Record_val;   //累计码盘值
    int32_t  Encoder_Actual_val;   //真实码盘值
    
    uint16_t position;             
    uint16_t last_position;
    uint16_t first_encoder_val;

    float    Actual_angle;         //真实角度
    float    Record_angle;         //累计角度

    uint8_t  first_flag;
}Encoder_t;

#define  M3508_LapEncoder         8192
#define  M2006_LapEncoder         8192

void Encoder_Init(Encoder_t *encoder);
void Encoder_Calculate(Encoder_t *encoder,uint16_t position,uint16_t max_encoder);
#endif /*__BSP_ENCODER_H*/