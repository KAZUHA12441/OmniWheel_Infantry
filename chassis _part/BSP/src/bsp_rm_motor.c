#include "bsp_rm_motor.h"
#include <stdio.h> 

/// @brief 属性赋值
/// @param Motor_Att 电机结构体 
/// @param motorType 电机类型
/// @param motor_id  电机can id
void Motor_Attitude_Set(MotorAttribute_t *Motor_Att,uint32_t motorType,int32_t motor_id)
{
    
    switch(motorType)
    {
        case M3508:
        {
            //搭配C620电调
            Motor_Att->Type = M3508;
            Motor_Att->Reduction_ratio = 19;
            Motor_Att->Max_Encoder_val = 8191;    //对应转子角度360
            Motor_Att->Max_Current_val = 16384;   //对应电流20A
            Motor_Att->Motor_id = motor_id;  
        }
        case M2006:
        {
            //搭配C610电调
            Motor_Att->Type =  M2006;
            Motor_Att->Reduction_ratio = 36;
            Motor_Att->Max_Encoder_val = 8191;
            Motor_Att->Max_Current_val = 10000;  //
            Motor_Att->Motor_id = motor_id;
        }
        case GM6020:
        {
            //GM6020自带
            Motor_Att->Type = GM6020;
            Motor_Att->Reduction_ratio = 1;
            Motor_Att->Max_Encoder_val = 8191;
            Motor_Att->Max_Current_val = 16384;
            Motor_Att->Motor_id = motor_id;
        }

    }
}