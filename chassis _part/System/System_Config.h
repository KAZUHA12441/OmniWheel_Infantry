#ifndef __SYSTEM_CONFIG_H
#define __SYSTEM_CONFIG_H

#define chassis_speed_gain 7.0f
#define chassis_yaw_gain   3.0f


//输出最大值
#define M3508_MAX_Current 16000
#define GM6020_MAX_Current 16000
#define M2006_MAX_Current  16000

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
#define Chassis_filter_alpha  0.03f




















#endif // !__SYSTEM_CONFIG_H
