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
void Encoder_Calculate(Encoder_t *encoder,uint16_t position,uint16_t max_encoder,uint16_t ratio)
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
    //因为电调采样时间为1000hz,不会影响采样值
    if(err > (max_encoder/2))
    {
        err -= (max_encoder - 1);                     
    }
    if(err < -(max_encoder/2)) 
    {
        err += (max_encoder - 1);
    }
    encoder->Encoder_Record_val += err;
    encoder->Encoder_Actual_val += err;
    encoder->Now_encoder += err;
    if(__fabs(encoder->Now_encoder) >max_encoder)
    {
        if(encoder->Now_encoder > 0)
        {
            encoder->Now_encoder -= max_encoder;
        }
        else if(encoder->Now_encoder < -max_encoder)
        {
            encoder->Now_encoder += max_encoder;
        }
    }
    encoder->Encoder_Now_angle = encoder->Encoder_Record_val*1.0f /max_encoder*ratio;
    if(encoder->Encoder_Now_angle > (180))
    {
        err -= 360 - 1;                     
    }
    else if(encoder->Encoder_Now_angle < 180) 
    {
        err += (360 - 1);
    }

}


