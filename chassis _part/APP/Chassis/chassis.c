#include "chassis.h"
#include <math.h>

OmniWheel_Infantry_Chassis_Struct *OmniWheel_Chassis;

// 初始化
void Chassis_Init(void)
{
  OmniWheel_Chassis = get_infantry_struct();

  Motor_Attitude_Set(&OmniWheel_Chassis->Chassis.LB_Wheel.MotorAtt,M3508,LB_MOTOR_ID);
  Motor_Attitude_Set(&OmniWheel_Chassis->Chassis.LF_Wheel.MotorAtt,M3508,LF_MOTOR_ID);
  Motor_Attitude_Set(&OmniWheel_Chassis->Chassis.RB_Wheel.MotorAtt,M3508,RB_MOTOR_ID);
  Motor_Attitude_Set(&OmniWheel_Chassis->Chassis.RF_Wheel.MotorAtt,M3508,RF_MOTOR_ID);
  
  // 创建速度环
  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.LB_Wheel.Pid_speed, Chassis_Kp, Chassis_Ki, Chassis_Kd, 16000, 0);
  

  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.LF_Wheel.Pid_speed, Chassis_Kp, Chassis_Ki, Chassis_Kd, 16000, 0);
  
  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.RF_Wheel.Pid_speed, Chassis_Kp, Chassis_Ki, Chassis_Kd, 16000, 0);
  
  Pid_Parameter_Init(&OmniWheel_Chassis->Chassis.RB_Wheel.Pid_speed, Chassis_Kp, Chassis_Ki, Chassis_Kd, 16000, 0);

  // 创建一个一阶低通滤波器
  First_low_pass_fiterCreate(&OmniWheel_Chassis->Handle_RC.Filter_Chassis_X, Chassis_filter_alpha);
  First_low_pass_fiterCreate(&OmniWheel_Chassis->Handle_RC.Filter_Chassis_Y, Chassis_filter_alpha);
  First_low_pass_fiterCreate(&OmniWheel_Chassis->Handle_RC.Filter_Chassis_Yaw, Chassis_filter_alpha);
}

/// @brief 底盘数据处理
/// @param
void Chassis_RCDataHandle(Chassis_State State)
{
  // #if DR16_LOCATION_SET
  // static Chassis_State Now_state;
  float chassis_x, chassis_y;
  float sin_t, cos_t;

  OmniWheel_Chassis->Handle_RC.Chassis_X = -OmniWheel_Chassis->RC.rc.ch[3] * chassis_speed_gain;
  OmniWheel_Chassis->Handle_RC.Chassis_Y = OmniWheel_Chassis->RC.rc.ch[2] * chassis_speed_gain;
  OmniWheel_Chassis->Handle_RC.Chassis_Yaw = OmniWheel_Chassis->RC.rc.ch[0] * chassis_yaw_gain;

  // 对应云台坐标系的运动方向
  switch (State)
  {
  // 普通底盘模式
  case chassis_contrl:
  {
    // 默认云台不动
    cos_t = 1.0f;
    sin_t = 0.0f;

    chassis_x = OmniWheel_Chassis->Handle_RC.Chassis_X;
    chassis_y = OmniWheel_Chassis->Handle_RC.Chassis_Y;

    // 对速度进行分解
    OmniWheel_Chassis->Handle_RC.Chassis_X = chassis_x * cos_t - chassis_y * sin_t;
    OmniWheel_Chassis->Handle_RC.Chassis_Y = chassis_x * sin_t + chassis_y * cos_t;

    // 低通滤波
    OmniWheel_Chassis->Handle_RC.Chassis_X = First_orderfilter(&OmniWheel_Chassis->Handle_RC.Filter_Chassis_X, OmniWheel_Chassis->Handle_RC.Chassis_X);
    OmniWheel_Chassis->Handle_RC.Chassis_Y = First_orderfilter(&OmniWheel_Chassis->Handle_RC.Filter_Chassis_Y, OmniWheel_Chassis->Handle_RC.Chassis_Y);
    OmniWheel_Chassis->Handle_RC.Chassis_Yaw = First_orderfilter(&OmniWheel_Chassis->Handle_RC.Filter_Chassis_Yaw, OmniWheel_Chassis->Handle_RC.Chassis_Yaw);

    OmniWheelSpeedSolution(OmniWheel_Chassis->Handle_RC.Chassis_X, OmniWheel_Chassis->Handle_RC.Chassis_Y, OmniWheel_Chassis->Handle_RC.Chassis_Yaw);
    break;
  }

  
  // 小陀螺模式
  case chassis_dreidel_on:
  {
    // 需要获取当前云台位置(编码器)
    // 底盘坐标系与云台坐标系的相对角度
    OmniWheel_Chassis->Relative_angle = OmniWheel_Chassis->Gimbal.Yaw_angle - OmniWheel_Chassis->Gimbal.Gimbal_Yaw_Motor.Encoder.Encoder_Now_angle;
    //计算相对幅角
    if(OmniWheel_Chassis->Relative_angle > 180.0f)
    {
        OmniWheel_Chassis->Relative_angle -= 360.0f;                     
    }
    else if(OmniWheel_Chassis->Relative_angle < -180.0f) 
    {
        OmniWheel_Chassis->Relative_angle += 360.0f;
    }
    cos_t = cos(OmniWheel_Chassis->Relative_angle);
    sin_t = sin(OmniWheel_Chassis->Relative_angle);

    chassis_x = OmniWheel_Chassis->Handle_RC.Chassis_X;
    chassis_y = OmniWheel_Chassis->Handle_RC.Chassis_Y;

    OmniWheel_Chassis->Handle_RC.Chassis_X = chassis_x * cos_t - chassis_y * sin_t;
    OmniWheel_Chassis->Handle_RC.Chassis_Y = chassis_x * sin_t + chassis_y * cos_t;

    OmniWheel_Chassis->Handle_RC.Chassis_X = First_orderfilter(&OmniWheel_Chassis->Handle_RC.Filter_Chassis_X, OmniWheel_Chassis->Handle_RC.Chassis_X);
    OmniWheel_Chassis->Handle_RC.Chassis_Y = First_orderfilter(&OmniWheel_Chassis->Handle_RC.Filter_Chassis_Y, OmniWheel_Chassis->Handle_RC.Chassis_Y);
    OmniWheel_Chassis->Handle_RC.Chassis_Yaw = Chassis_dreidel_Speed;

    OmniWheelSpeedSolution(OmniWheel_Chassis->Handle_RC.Chassis_X, OmniWheel_Chassis->Handle_RC.Chassis_Y, OmniWheel_Chassis->Handle_RC.Chassis_Yaw);
    break;
  }
  }
}

/// @brief 全向轮解算
/// @param chassis_x 云台坐标系 to 底盘坐标系 的x速度
/// @param chassis_y 云台坐标系 to 底盘坐标系 的y速度
/// @param chassis_yaw 云台坐标系 to 底盘坐标系 的yaw速度
void OmniWheelSpeedSolution(float chassis_x, float chassis_y, float chassis_yaw)
{
  OmniWheel_Chassis->Chassis.LB_Wheel.Motor_Data.Motor_Set.speed_set = -chassis_x * ChassisIdle_InitAngle + chassis_y * ChassisIdle_InitAngle + chassis_yaw * ChassisDiagonalLength;

  OmniWheel_Chassis->Chassis.LF_Wheel.Motor_Data.Motor_Set.speed_set = -chassis_x * ChassisIdle_InitAngle - chassis_y * ChassisIdle_InitAngle + chassis_yaw * ChassisDiagonalLength;

  OmniWheel_Chassis->Chassis.RB_Wheel.Motor_Data.Motor_Set.speed_set = chassis_x * ChassisIdle_InitAngle - chassis_y * ChassisIdle_InitAngle + chassis_yaw * ChassisDiagonalLength;

  OmniWheel_Chassis->Chassis.RF_Wheel.Motor_Data.Motor_Set.speed_set = chassis_x * ChassisIdle_InitAngle + chassis_y * ChassisIdle_InitAngle + chassis_yaw * ChassisDiagonalLength;
}

// 底盘闲置
void Chassis_idle(void)
{
  // 电流值直接给0,无力
  OmniWheel_Chassis->Chassis.LB_Wheel.Motor_Data.give_current = 0;
  OmniWheel_Chassis->Chassis.LF_Wheel.Motor_Data.give_current = 0;
  OmniWheel_Chassis->Chassis.RB_Wheel.Motor_Data.give_current = 0;
  OmniWheel_Chassis->Chassis.RF_Wheel.Motor_Data.give_current = 0;
}

//配合位置环，底盘锁死
void Chassis_lock(void)
{

  
  OmniWheel_Chassis->Chassis.LB_Wheel.Motor_Data.speed_pid_out = Speed_lap_pid(&OmniWheel_Chassis->Chassis.LB_Wheel.Pid_speed,
                                                                               0,
                                                                               OmniWheel_Chassis->Chassis.LB_Wheel.Motor_Data.Motor_Get.speed_get);

  OmniWheel_Chassis->Chassis.LF_Wheel.Motor_Data.speed_pid_out = Speed_lap_pid(&OmniWheel_Chassis->Chassis.LF_Wheel.Pid_speed,
                                                                               0,
                                                                               OmniWheel_Chassis->Chassis.LF_Wheel.Motor_Data.Motor_Get.speed_get);

  OmniWheel_Chassis->Chassis.RB_Wheel.Motor_Data.speed_pid_out = Speed_lap_pid(&OmniWheel_Chassis->Chassis.RB_Wheel.Pid_speed,
                                                                               0,
                                                                               OmniWheel_Chassis->Chassis.RB_Wheel.Motor_Data.Motor_Get.speed_get);

  OmniWheel_Chassis->Chassis.RF_Wheel.Motor_Data.speed_pid_out = Speed_lap_pid(&OmniWheel_Chassis->Chassis.RF_Wheel.Pid_speed,
                                                                               0,
                                                                               OmniWheel_Chassis->Chassis.RF_Wheel.Motor_Data.Motor_Get.speed_get);
}

void ChassisControlStateSPid(void)
{
  OmniWheel_Chassis->Chassis.LB_Wheel.Motor_Data.speed_pid_out = Speed_lap_pid(&OmniWheel_Chassis->Chassis.LB_Wheel.Pid_speed,
                                                                               OmniWheel_Chassis->Chassis.LB_Wheel.Motor_Data.Motor_Set.speed_set,
                                                                               OmniWheel_Chassis->Chassis.LB_Wheel.Motor_Data.Motor_Get.speed_get);

  OmniWheel_Chassis->Chassis.LF_Wheel.Motor_Data.speed_pid_out = Speed_lap_pid(&OmniWheel_Chassis->Chassis.LF_Wheel.Pid_speed,
                                                                               OmniWheel_Chassis->Chassis.LF_Wheel.Motor_Data.Motor_Set.speed_set,
                                                                               OmniWheel_Chassis->Chassis.LF_Wheel.Motor_Data.Motor_Get.speed_get);

  OmniWheel_Chassis->Chassis.RB_Wheel.Motor_Data.speed_pid_out = Speed_lap_pid(&OmniWheel_Chassis->Chassis.RB_Wheel.Pid_speed,
                                                                               OmniWheel_Chassis->Chassis.RB_Wheel.Motor_Data.Motor_Set.speed_set,
                                                                               OmniWheel_Chassis->Chassis.RB_Wheel.Motor_Data.Motor_Get.speed_get);

  OmniWheel_Chassis->Chassis.RF_Wheel.Motor_Data.speed_pid_out = Speed_lap_pid(&OmniWheel_Chassis->Chassis.RF_Wheel.Pid_speed,
                                                                               OmniWheel_Chassis->Chassis.RF_Wheel.Motor_Data.Motor_Set.speed_set,
                                                                               OmniWheel_Chassis->Chassis.RF_Wheel.Motor_Data.Motor_Get.speed_get);
}

//对数据进行强转16位
void ChassisControlStateOutput(void)
{
  
  OmniWheel_Chassis->Chassis.LB_Wheel.Motor_Data.give_current = (int16_t)OmniWheel_Chassis->Chassis.LB_Wheel.Motor_Data.speed_pid_out;
  OmniWheel_Chassis->Chassis.LF_Wheel.Motor_Data.give_current = (int16_t)OmniWheel_Chassis->Chassis.LF_Wheel.Motor_Data.speed_pid_out;
  OmniWheel_Chassis->Chassis.RB_Wheel.Motor_Data.give_current = (int16_t)OmniWheel_Chassis->Chassis.RB_Wheel.Motor_Data.speed_pid_out;
  OmniWheel_Chassis->Chassis.RF_Wheel.Motor_Data.give_current = (int16_t)OmniWheel_Chassis->Chassis.RF_Wheel.Motor_Data.speed_pid_out;
}

void ChassisControlAchieve(Chassis_State State)
{
    OmniWheel_Chassis->Chassis.ChassisState = State;
    switch(State)
    {
      case chassis_idle: 
      {
        Chassis_idle();
        break;
      }
      case chassis_lock:
      {
        Chassis_lock();
        break;
      }
      case chassis_contrl||chassis_dreidel_on:
      {
        Chassis_RCDataHandle(State);
        ChassisControlStateSPid();
        ChassisControlStateOutput();
        break;
      }
    }
}
