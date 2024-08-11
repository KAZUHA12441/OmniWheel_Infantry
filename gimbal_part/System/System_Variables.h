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
#include "MahonyAHRS.h"
#include "kalman.h"
#include "bsp_dwt.h"

#define max_value_limit(x, max, min) x > max ? max : (x < min ? min : x)
// #define AngletoAmplitude(angle) ((angle>180.0f) ? (angle-=360.0f) : (angle<-180.0f) ? (angle += 360.0f):angle = angle)
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

typedef struct 
{
 
  float Gimbal_Yaw;
  float Gimbal_Pitch;

  first_order_filter_t  Filter_Gimbal_Pitch;
  first_order_filter_t  Filter_Gimbal_Yaw;
}RCData_Handle_t;

typedef struct
{
    float quaternion[4]; //四元数
    float imu_handledata[6];
    attritude_angle Euler_angle;
}Attitude_data_t;

typedef struct 
{
    First_kalman_t Kalmanfilter_GYRO_X;
    First_kalman_t Kalmanfilter_GYRO_Y;
    First_kalman_t Kalmanfilter_GYRO_Z;
    First_kalman_t Kalmanfilter_ACCEL_X;
    First_kalman_t Kalmanfilter_ACCEL_Y;
    First_kalman_t Kalmanfilter_ACCEL_Z;
}IMU_KFFilterover;
 
typedef struct 
{
    float Set_angle;
    float Get_angle;
    float Now_angle;
}Gimbal_angle_t;


typedef struct
{
 
 struct 
 {
    Motor_t  Gimbal_Yaw_Motor;
    Motor_t  Gimbal_Pitch_Motor;
    Gimbal_angle_t Yaw;
    Gimbal_angle_t Pitch;
    Gimbal_State  GimbalState;
 }Gimbal;

 struct
 {
    Motor_t Friction_Master_Motor;
    Motor_t Friction_Slave_Motor;
    Fire_state firestate;
 }Friction;
 //遥控数据
 rc_data_t RC;
 RCData_Handle_t  Handle_RC; 
 DWT_time_t System_time;
 //陀螺仪&云台姿态数据
 struct 
 {
    M6050_t  M6050_IMU;
    Attitude_data_t Attitube;
    IMU_KFFilterover IMU_Handle;
    uint8_t  IMU_Init_complate;
 }Gimbal_Attitube;
 

}OmniWheel_Infantry_Gimbal_Struct;

OmniWheel_Infantry_Gimbal_Struct *get_infantry_struct(void);

#endif /*__SYSTEM_INC_H*/
