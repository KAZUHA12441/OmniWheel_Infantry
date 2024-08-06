#include "chassis.h"
 
OmniWheel_Infantry_Chassis_Struct *OmniWheel_Chassis;

//初始化
void Chassis_Init(void)
{ 
  OmniWheel_Chassis = get_infantry_struct();
  
  //创建速度环 ，位置环pid
  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.LB_Wheel.Pid_speed,Chassis_Kp,Chassis_Ki,Chassis_Kd,16000,0);
  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.LB_Wheel.Pid_position,Chassis_Kp,Chassis_Ki,Chassis_Kd,16000,0);

  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.LF_Wheel.Pid_speed,Chassis_Kp,Chassis_Ki,Chassis_Kd,16000,0);
  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.LF_Wheel.Pid_position,Chassis_Kp,Chassis_Ki,Chassis_Kd,16000,0);

  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.RF_Wheel.Pid_speed,Chassis_Kp,Chassis_Ki,Chassis_Kd,16000,0);
  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.RF_Wheel.Pid_position,Chassis_Kp,Chassis_Ki,Chassis_Kd,16000,0);

  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.RB_Wheel.Pid_speed,Chassis_Kp,Chassis_Ki,Chassis_Kd,16000,0);
  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.RB_Wheel.Pid_position,Chassis_Kp,Chassis_Ki,Chassis_Kd,16000,0);

  //创建一个一阶低通滤波器
  First_low_pass_fiterCreate(&OmniWheel_Chassis->Handle_RC.Filter_Chassis_X,Chassis_filter_alpha);
  First_low_pass_fiterCreate(&OmniWheel_Chassis->Handle_RC.Filter_Chassis_Y,Chassis_filter_alpha);
  First_low_pass_fiterCreate(&OmniWheel_Chassis->Handle_RC.Filter_Chassis_Yaw,Chassis_filter_alpha);
}






