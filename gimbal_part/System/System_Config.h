#ifndef __SYSTEM_CONFIG_H
#define __SYSTEM_CONFIG_H

//407的最大频率
#define  SYSTEM_Hz                 168


#define PI                         3.141592654f  

//底盘参数
#define chassis_speed_gain         7.0f
#define chassis_yaw_gain           3.0f
#define ChassisIdle_InitAngle (1.414213562373f)/2.0f
#define ChassisDiagonalLength      900
#define Chassis_dreidel_Speed      5000
#define Dial_Rotate_Encoder_limit  300                    //规定每次转动位置,防止卡弹

//输出最大值
#define M3508_MAX_Current    16000
#define GM6020_MAX_Current   16000
#define M2006_MAX_Current    16000

//DR16_位置状态选择                         
#define DR16_LOCATION_SET    1

//电机id
#define LF_MOTOR_ID          1
#define RF_MOtOR_ID          2
#define LB_MOTOR_ID          3
#define RB_MOTOR_ID          4
#define DIEL_MOTOR_ID        5

//pid系数
#define Chassis_Kp           10.0f
#define Chassis_Ki           0.0f
#define Chassis_Kd           0.75f

#define DIAl_Kp              10.0f
#define DIAl_Ki              0.0f
#define DIAl_Kd              0.75f

//一阶低通滤波系数
#define Chassis_filter_alpha 0.03f

//卡尔曼滤波系数
#define Kalman_Q             0.7f
#define Kalman_R             0.3f




















#endif // !__SYSTEM_CONFIG_H
