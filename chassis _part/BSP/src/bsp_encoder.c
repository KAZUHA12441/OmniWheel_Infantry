#include "bsp_encoder.h"


/// @brief 编码器初始化
/// @param encoder 
void Encoder_Init(Encoder_t *encoder)
{
    encoder->Encoder_Actual_val = 0;
    encoder->Encoder_Record_val = 0;
    encoder->Record_angle = 0;
    encoder->Actual_angle = 0;
    encoder->first_flag = 0;
}

/// @brief 编码值计算
/// @param encoder  编码器
/// @param position 实际编码值 
/// @param max_encoder 最大编码值
void Encoder_Calculate(Encoder_t *encoder,uint16_t position,uint16_t max_encoder)
{
    encoder->position = position;
    if(encoder->first_flag == 1)
    {
        encoder->last_position = encoder->position;
        encoder->first_encoder_val =  encoder->last_position;
        encoder->Encoder_Actual_val += encoder->position;
        encoder->first_flag = 1;
    }
    int16_t err = encoder->position - encoder->last_position;
    encoder->last_position = encoder->position;
    if(err > (max_encoder/2))
    {
        err -= (max_encoder - 1);                     
    }
    if(err < -(max_encoder/2)) 
    {
        err += (max_encoder - 1);
    }
    encoder->Encoder_Record_val += err;
}


