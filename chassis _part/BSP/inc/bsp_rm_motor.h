#ifndef __BSP_RM_MOTOR_H
#define __BSP_RM_MOTOR_H

#include "main.h"

typedef enum
{
  M3508  = 1,
  M2006,
  GM6020,
}Motor_Type;                //电机类型

typedef struct
{
    Motor_Type Type;
    uint16_t Reduction_ratio; 
    uint16_t Max_Encoder_val;
    uint16_t Max_Current_val;
    uint32_t Motor_id;  
}MotorAttribute_t;


 void Motor_Attitude_Set(MotorAttribute_t *Motor_Att,uint32_t motorType,int32_t motor_id);

#endif /*__BSP_RM_MOTOR_H*/