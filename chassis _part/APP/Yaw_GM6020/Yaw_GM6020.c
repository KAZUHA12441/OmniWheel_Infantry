#include "Yaw_GM6020.h"

OmniWheel_Infantry_Chassis_Struct *Yaw_Motor;

void Yaw_Encoder_Init(void)
{
    Yaw_Motor = get_infantry_struct();
    Motor_Attitude_Set(&Yaw_Motor->Gimbal.Gimbal_Yaw_Motor.MotorAtt,GM6020,Yaw_Rece_ID);
    Encoder_Init(&Yaw_Motor->Gimbal.Gimbal_Yaw_Motor.Encoder);
}       
