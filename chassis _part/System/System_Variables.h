#ifndef __SYSTEM_INC_H
#define __SYSTEM_INC_H

#include "main.h"
#include "pid.h"
#include "System_Config.h"
#include "System_Choose.h"
#include "bsp_encoder.h"
#include "bsp_dbus.h"
#include "bsp_m6050.h"
#include "first_order_filter.h"
#include "attitude.h"
#include "bsp_can.h"
#include "bsp_rm_motor.h"
#include "state_change.h"
#include "can2_rece.h"
#include "can1_rece.h"





#define max_value_limit(x, max, min) x > max ? max : (x < min ? min : x)

//

//获取的电机数据
typedef struct                      
{
    uint16_t  position_get;
    int16_t   speed_get;
    int16_t   current_get;
}MotorGet_t;

typedef struct
{
    int16_t current_set;
    int16_t speed_set;
    int16_t position_set;
}MototSet_t;

//电机数据综合
typedef struct
{

    MotorGet_t Motor_Get;
    MototSet_t Motor_Set;
    float current_pid_out;
    float position_pid_out;
    float speed_pid_out;
    int16_t give_current;

}MotorData_t;

//对单个电机数据的定义 
typedef struct 
{
    MotorData_t  Motor_Data;         //电机数据
    pid_parameter_t  Pid_position;   //电机位置环
    pid_parameter_t  Pid_speed;      //电机速度环
    pid_parameter_t  Pid_current;    //电机电流环
    MotorAttribute_t MotorAtt;       //电机属性
    Encoder_t Encoder;               //电机编码器
}Motor_t;

// typedef struct 
// {
//     float  roll;
//     float  pitch; 
//     float  yaw;
// }Euler_angle_t;

typedef struct 
{
  float Chassis_X;
  float Chassis_Y;
  float Chassis_Yaw;
  
  first_order_filter_t  Filter_Chassis_X;
  first_order_filter_t  Filter_Chassis_Y;
  first_order_filter_t  Filter_Chassis_Yaw;
}RCData_Handle_t;

typedef struct
{
    float quaternion[4]; //四元数
    attritude_angle Euler_angle;
}Attitude_data_t;

 
typedef struct
{
 //底盘
 struct
 {
    Motor_t  LF_Wheel;
    Motor_t  RF_Wheel;
    Motor_t  LB_Wheel;
    Motor_t  RB_Wheel;
    Chassis_State ChassisState;  
 }Chassis; 
 
 struct 
 {
    Motor_t Gimbal_Yaw_Motor;
    float Yaw_angle;
    Fire_state firestate;
 }Gimbal;
 //拨弹盘
 struct
 { 
    Motor_t  Rammer_Motor;
 }Rammer;
 //遥控数据
 rc_data_t *RC;
 RCData_Handle_t  Handle_RC; 
 float Relative_angle;
 //陀螺仪&云台姿态数据
 struct 
 {
    M6050_t  M6050_IMU;
    Attitude_data_t Attitube;
 }Gimbal_Attitube;
 
}OmniWheel_Infantry_Chassis_Struct;

OmniWheel_Infantry_Chassis_Struct *get_infantry_struct(void);

#endif /*__SYSTEM_INC_H*/
