#include "dial.h"  

OmniWheel_Infantry_Chassis_Struct *Dial_Struct;

//下供弹

void Dial_Init(void)
{
  Dial_Struct = get_infantry_struct();
  Pid_Parameter_Init(&Dial_Struct->Dial.Dial_Motor.Pid_position,DIAl_Kp,DIAl_Ki,DIAl_Kd,16000,0);
  Pid_Parameter_Init(&Dial_Struct->Dial.Dial_Motor.Pid_speed,DIAl_Kp,DIAl_Ki,DIAl_Kd,16000,0);
}


/// @brief 拨弹盘打开
/// @param State 拨弹盘状态
void DialOnAchieve(Dial_State State)
{
  if(Dial_Struct->Gimbal.firestate == Friction_on)
  {
    if(State == dial_on)
    {
       
    }
  }
}