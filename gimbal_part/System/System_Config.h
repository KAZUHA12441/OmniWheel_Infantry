#ifndef __SYSTEM_CONFIG_H
#define __SYSTEM_CONFIG_H

#define head                  1
#define chassis               2 

//DR16_位置状态选择   
#define DR16_LOCATION_SET    chassis

//拨弹盘位置选择
#define Rammer_Location      chassis

//407的最大频率
#define  SYSTEM_Hz                 168

#define lost_time_limit         2000

#define PI                         3.141592654f  
#define radtoangle                 57.295779513f
//底盘参数
#define chassis_speed_gain         7.0f
#define chassis_yaw_gain           3.0f
#define ChassisIdle_InitAngle (1.414213562373f)/2.0f
#define ChassisDiagonalLength      900
#define Chassis_dreidel_Speed      5000
#define Dial_Rotate_Encoder_limit  300                    //位置环锁死规定每次转动位置,防止卡弹

//云台参数
//调节灵敏度
#define gimbal_pitch_gain          0.03f
#define gimbal_yaw_gain            0.03f
#define gimbal_pitch_compensate    (int16_t)1000

//云台pid系数
#define Gimbal_Pitch_Kp            10.0f
#define Gimbal_Yaw_Kp              10.0f 
#define Gimbal_Pitch_Ki            0.0f
#define Gimbal_Yaw_Ki              0.0f
#define Gimbal_Pitch_Kd            0.75f
#define Gimbal_Yaw_Kd              0.75f  

//pitch限位值
#define Gimbal_Pitch_Max_SetVal         75.0f
#define Gimbal_Pitch_Min_SetVal         -75.0f

//摩擦轮系数
#define friction_Kp                10.0f
#define friction_Ki                0.0f
#define friction_Kd                0.75
//弹速

#define DIAl_Kp              10.0f
#define DIAl_Ki              0.0f
#define DIAl_Kd              0.75f

#define friction_Max_firerate      6000

//输出最大值
#define M3508_MAX_Current    16000
#define GM6020_MAX_Current   10000
#define M2006_MAX_Current    16000  

#define GM6020_MAX_SPEED    10000
#define M3508_Max_SPEED     8000
                    
//CAN网络通讯id
#define Gimbal_CAN1_SendData_ID1  0X1FE
#define Gimbal_CAN1_SendData_ID2  0x200  
#define Gimbal_CAN2_SendData_ID1  0X1FE
#define Gimbal_CAN2_SendData_ID2  0X205

#define chassis_board_send_data_ID1     (uint32_t)0x4FF
#define chassis_board_send_data_ID2     (uint32_t)0x5FF
#define chassis_board_rece_data_ID1     (uint32_t)0x8FF
#define chassis_board_rece_data_ID2     (uint32_t)0x9FF

//电机id
#define Gimbal_Pitch_MotorID  5
#define Gimbal_Yaw_MotorID    5
#define Friction_Master_Motor_ID     2
#define Friction_Slave_Motor_ID      3
#define Rammer_MOTOR_ID        4
//一阶低通滤波系数
#define Gimbal_filter_alpha 0.03f

//卡尔曼滤波系数
#define Kalman_Q             0.7f
#define Kalman_R             0.3f

#define rotate_angle_increase_limit   1.5f
#define pitch_max_limit      75.0f

#define  Rammer_RotateAngle_limit  30

















#endif // !__SYSTEM_CONFIG_H
