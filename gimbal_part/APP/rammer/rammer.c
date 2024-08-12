#include "rammer.h"  

OmniWheel_Infantry_Gimbal_Struct *Rammer_Struct;

//下供弹                       

void Rammer_Init(void)
{
  Rammer_Struct = get_infantry_struct();
  Encoder_Init(&Rammer_Struct->Rammer.Rammer_Motor.Encoder);
  Pid_Parameter_Init(&Rammer_Struct->Rammer.Rammer_Motor.Pid_position,DIAl_Kp,DIAl_Ki,DIAl_Kd,16000,0);
  Pid_Parameter_Init(&Rammer_Struct->Rammer.Rammer_Motor.Pid_speed,DIAl_Kp,DIAl_Ki,DIAl_Kd,16000,0);
}


/// @brief 拨弹状态选择
/// @param State 拨弹盘状态
uint8_t  Rammer_NOW;               
void RammerOnChoose(Rammer_State State)
{
  float set_encoder;
  if(Rammer_Struct->Friction.firestate == Friction_on)
  {
    if(State == Rammer_on)
    {
         Rammer_NOW = Rammer_on;
         set_encoder = ((Rammer_RotateAngle_limit)/360 * 8191 ) + Rammer_Struct->Rammer.Rammer_Motor.Encoder.Encoder_Record_val; 
         Rammer_Struct->Rammer.Rammer_Motor.Motor_Data.speed_pid_out = Position_2_Speed_Pid(&Rammer_Struct->Rammer.Rammer_Motor.Pid_position,
                                                                                            &Rammer_Struct->Rammer.Rammer_Motor.Pid_speed,
                                                                                            set_encoder,
                                                                                            Rammer_Struct->Rammer.Rammer_Motor.Encoder.Encoder_Record_val,
                                                                                            Rammer_Struct->Rammer.Rammer_Motor.Motor_Data.Motor_Get.speed_get
                                                                                            );
         Rammer_Struct->Rammer.Rammer_Motor.Motor_Data.give_current = (int16_t)Rammer_Struct->Rammer.Rammer_Motor.Motor_Data.speed_pid_out;
    }
  }
  else if(State == Rammer_off)
  {   
      if(Rammer_NOW != Rammer_off)
      {
        set_encoder =  Rammer_Struct->Rammer.Rammer_Motor.Encoder.Encoder_Record_val;
        Rammer_NOW = Rammer_off;
      }
      Rammer_Struct->Rammer.Rammer_Motor.Motor_Data.speed_pid_out = Position_2_Speed_Pid(&Rammer_Struct->Rammer.Rammer_Motor.Pid_position,
                                                                                            &Rammer_Struct->Rammer.Rammer_Motor.Pid_speed,
                                                                                            set_encoder,
                                                                                            Rammer_Struct->Rammer.Rammer_Motor.Encoder.Encoder_Record_val,
                                                                                            Rammer_Struct->Rammer.Rammer_Motor.Motor_Data.Motor_Get.speed_get
                                                                                            );
      Rammer_Struct->Rammer.Rammer_Motor.Motor_Data.give_current = (int16_t)Rammer_Struct->Rammer.Rammer_Motor.Motor_Data.speed_pid_out;                                                               
  }
  
}