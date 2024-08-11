#ifndef __SYSTEM_CONFIG_H
#define __SYSTEM_CONFIG_H



#define head                  1
#define chassis               2 

//DR16_位置状态选择   
#define DR16_LOCATION_SET    chassis

//拨弹盘位置选择
#define Rammer_Location      chassis

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

//电机id
#define LF_MOTOR_ID          1
#define RF_MOTOR_ID          2
#define LB_MOTOR_ID          3
#define RB_MOTOR_ID          4
#define Rammer_MOTOR_ID        5

//CAN_id
#define Chassis_Send_ID           (uint32_t)0x200
#define Rammer_Send_ID            (uint32_t)0x1FF
#define Yaw_Rece_ID               (uint32_t)0x20A
//板间通信
#define chassis_board_rece_data_ID1     (uint32_t)0x4FF
#define chassis_board_rece_data_ID2     (uint32_t)0x5FF        
#define head_board_rece_data_ID1        (uint32_t)0x6FF
#define head_board_rece_data_ID2        (uint32_t)0x7FF

//发送
#define chassis_board_send_data_ID1     (uint32_t)0x8FF
#define chassis_board_send_data_ID2     (uint32_t)0x9FF

//pid系数
#define Chassis_Kp           10.0f
#define Chassis_Ki           0.0f
#define Chassis_Kd           0.75f

#define DIAl_Kp              10.0f
#define DIAl_Ki              0.0f
#define DIAl_Kd              0.75f

#define  Rammer_RotateAngle_limit  30
//一阶低通滤波系数
#define Chassis_filter_alpha 0.03f



#define PI                         3.141592654f 
















#endif // !__SYSTEM_CONFIG_H
