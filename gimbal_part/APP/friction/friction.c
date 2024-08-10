#include "friction.h"


OmniWheel_Infantry_Gimbal_Struct *Friction_Struct;
/// @brief 摩擦轮初始化
/// @param  
void friction_Init(void)
{
    Friction_Struct = get_infantry_struct();

    //配合双环电流环限制弹速
    Pid_Parameter_Init(&Friction_Struct->Friction.Friction_Master_Motor.Pid_speed,friction_Kp,friction_Ki,friction_Kd,M3508_MAX_Current,0);
    Pid_Parameter_Init(&Friction_Struct->Friction.Friction_Master_Motor.Pid_current,friction_Kp,friction_Ki,friction_Kd,M3508_MAX_Current,0);

    Pid_Parameter_Init(&Friction_Struct->Friction.Friction_Slave_Motor.Pid_speed,friction_Kp,friction_Ki,friction_Kd,M3508_MAX_Current,0);
    Pid_Parameter_Init(&Friction_Struct->Friction.Friction_Slave_Motor.Pid_current,friction_Kp,friction_Ki,friction_Kd,M3508_MAX_Current,0);
}

/// @brief 摩擦轮电机驱动
/// @param  
void friction_motor_run(Fire_state State)
{
    if(State == Friction_on)
    {
        Friction_Struct->Friction.Friction_Master_Motor.Motor_Data.current_pid_out = Speed_2_Current_Pid(&Friction_Struct->Friction.Friction_Master_Motor.Pid_speed,
                                                                                                  &Friction_Struct->Friction.Friction_Master_Motor.Pid_current,
                                                                                                  friction_Max_firerate,
                                                                                                  Friction_Struct->Friction.Friction_Master_Motor.Motor_Data.Motor_Get.speed_get,
                                                                                                  Friction_Struct->Friction.Friction_Master_Motor.Motor_Data.Motor_Get.current_get);
        Friction_Struct->Friction.Friction_Slave_Motor.Motor_Data.current_pid_out = Speed_2_Current_Pid(&Friction_Struct->Friction.Friction_Slave_Motor.Pid_speed,
                                                                                                  &Friction_Struct->Friction.Friction_Slave_Motor.Pid_current,
                                                                                                  friction_Max_firerate,
                                                                                                  Friction_Struct->Friction.Friction_Slave_Motor.Motor_Data.Motor_Get.speed_get,
                                                                                                  Friction_Struct->Friction.Friction_Slave_Motor.Motor_Data.Motor_Get.current_get);

        Friction_Struct->Friction.Friction_Slave_Motor.Motor_Data.give_current = (int16_t)Friction_Struct->Friction.Friction_Slave_Motor.Motor_Data.current_pid_out;
        Friction_Struct->Friction.Friction_Master_Motor.Motor_Data.give_current = (int16_t)Friction_Struct->Friction.Friction_Master_Motor.Motor_Data.current_pid_out;

        Friction_Struct->Friction.firestate = Friction_on;
    }
    //摩擦轮无力
    else if(State == Friction_off)
    {
      //只做一次，节省时间
      if(Friction_Struct->Friction.firestate != Friction_off);
      {
        Friction_Struct->Friction.Friction_Slave_Motor.Motor_Data.give_current = 0;
        Friction_Struct->Friction.Friction_Master_Motor.Motor_Data.give_current = 0;
      }
      Friction_Struct->Friction.firestate = Friction_off;
    }
}