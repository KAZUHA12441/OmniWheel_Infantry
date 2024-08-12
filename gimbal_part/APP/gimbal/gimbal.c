#include "gimbal.h"

// 默认取劣弧处理

OmniWheel_Infantry_Gimbal_Struct *Gimbal_Struct;

/// @brief 云台初始化
/// @param
void Gimbal_Init(void)
{
    Gimbal_Struct = get_infantry_struct();
    Encoder_Init(&Gimbal_Struct->Gimbal.Gimbal_Yaw_Motor.Encoder);
    // 电机属性赋值
    Motor_Attitude_Set(&Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.MotorAtt, GM6020, Gimbal_Pitch_MotorID);
    Motor_Attitude_Set(&Gimbal_Struct->Gimbal.Gimbal_Yaw_Motor.MotorAtt, GM6020, Gimbal_Yaw_MotorID);

    Pid_Parameter_Init(&Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Pid_position, Gimbal_Pitch_Kp, Gimbal_Pitch_Ki, Gimbal_Pitch_Kd, GM6020_MAX_SPEED, 0);
    Pid_Parameter_Init(&Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Pid_speed, Gimbal_Pitch_Kp, Gimbal_Pitch_Ki, Gimbal_Pitch_Kd, GM6020_MAX_Current, 0);

    Pid_Parameter_Init(&Gimbal_Struct->Gimbal.Gimbal_Yaw_Motor.Pid_position, Gimbal_Pitch_Kp, Gimbal_Pitch_Ki, Gimbal_Pitch_Kd, GM6020_MAX_SPEED, 0);
    //因为编码器要给底盘用所以不用串级
    // Pid_Parameter_Init(&Gimbal_Struct->Gimbal.Gimbal_Yaw_Motor.Pid_speed, Gimbal_Pitch_Kp, Gimbal_Pitch_Ki, Gimbal_Pitch_Kd, GM6020_MAX_Current, 0);

    First_low_pass_fiterCreate(&Gimbal_Struct->Handle_RC.Filter_Gimbal_Yaw, Gimbal_filter_alpha);
    First_low_pass_fiterCreate(&Gimbal_Struct->Handle_RC.Filter_Gimbal_Pitch, Gimbal_filter_alpha);
}

// 转劣弧
float AngletoAmplitude(float angle)
{
    if (angle > 180) {
        angle -= 360;
    }
    if (angle < -180) {
        angle += 360;
    }
    return angle;
}

/// @brief 数据处理
/// @param
void RCHandleData(void)
{
    // 取遥控器增量
    Gimbal_Struct->Handle_RC.Gimbal_Yaw += Gimbal_Struct->RC->rc.ch[0] * gimbal_yaw_gain;
    Gimbal_Struct->Handle_RC.Gimbal_Pitch += -Gimbal_Struct->RC->rc.ch[1] * gimbal_pitch_gain;
    // 劣弧增量相加
    Gimbal_Struct->Gimbal.Yaw.Set_angle += AngletoAmplitude(Gimbal_Struct->Handle_RC.Gimbal_Yaw);
    Gimbal_Struct->Gimbal.Pitch.Set_angle += AngletoAmplitude(Gimbal_Struct->Handle_RC.Gimbal_Pitch);
    // 再次取劣弧
    Gimbal_Struct->Gimbal.Yaw.Set_angle   = AngletoAmplitude(Gimbal_Struct->Gimbal.Yaw.Set_angle);
    Gimbal_Struct->Gimbal.Pitch.Set_angle = AngletoAmplitude(Gimbal_Struct->Gimbal.Pitch.Set_angle);

    First_orderfilter(&Gimbal_Struct->Handle_RC.Filter_Gimbal_Pitch, Gimbal_filter_alpha);
    First_orderfilter(&Gimbal_Struct->Handle_RC.Filter_Gimbal_Yaw, Gimbal_filter_alpha);
}

/// @brief 云台操纵
/// @param
void GimbalControl(Gimbal_State State)
{
    switch (State) {
        // 云台无力
        case Gimbal_idle: {
            Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Motor_Data.give_current = 0;
            Gimbal_Struct->Gimbal.Gimbal_Yaw_Motor.Motor_Data.give_current   = 0;
            break;
        }
        case Gimbal_Control: {
            RCHandleData();
            //---------------------------------------------------PITCH-------------------------------------------------------------
            // stepin
            if ((Gimbal_Struct->Gimbal.Pitch.Set_angle - Gimbal_Struct->Gimbal.Pitch.Now_angle) > rotate_angle_increase_limit) {
                Gimbal_Struct->Gimbal.Pitch.Now_angle += rotate_angle_increase_limit;
                Gimbal_Struct->Gimbal.Pitch.Now_angle = AngletoAmplitude(Gimbal_Struct->Gimbal.Pitch.Now_angle);
            } else if ((Gimbal_Struct->Gimbal.Pitch.Set_angle - Gimbal_Struct->Gimbal.Pitch.Now_angle) < -rotate_angle_increase_limit) {
                Gimbal_Struct->Gimbal.Pitch.Now_angle -= rotate_angle_increase_limit;
                Gimbal_Struct->Gimbal.Pitch.Now_angle = AngletoAmplitude(Gimbal_Struct->Gimbal.Pitch.Now_angle);
            } else {
                Gimbal_Struct->Gimbal.Pitch.Now_angle = Gimbal_Struct->Gimbal.Pitch.Set_angle;
            }

            Gimbal_Struct->Gimbal.Pitch.Now_angle = max_value_limit(Gimbal_Struct->Gimbal.Pitch.Now_angle, Gimbal_Pitch_Max_SetVal, Gimbal_Pitch_Min_SetVal);
            // pid计算
            //串级锁死，防止乱动
            Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Motor_Data.speed_pid_out = Position_2_Speed_Pid(&Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Pid_position,
                                                                                                     &Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Pid_speed,
                                                                                                     Gimbal_Struct->Gimbal.Pitch.Now_angle,
                                                                                                     Gimbal_Struct->Gimbal.Pitch.Get_angle,
                                                                                                     Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Motor_Data.Motor_Get.speed_get);

            //----------------------------------------------------YAW-------------------------------------------------------------------
            if ((Gimbal_Struct->Gimbal.Yaw.Set_angle - Gimbal_Struct->Gimbal.Yaw.Now_angle) > rotate_angle_increase_limit) {
                Gimbal_Struct->Gimbal.Yaw.Now_angle += rotate_angle_increase_limit;
                Gimbal_Struct->Gimbal.Yaw.Now_angle = AngletoAmplitude(Gimbal_Struct->Gimbal.Yaw.Now_angle);
            } else if ((Gimbal_Struct->Gimbal.Yaw.Set_angle - Gimbal_Struct->Gimbal.Yaw.Now_angle) < -rotate_angle_increase_limit) {
                Gimbal_Struct->Gimbal.Yaw.Now_angle -= rotate_angle_increase_limit;
                Gimbal_Struct->Gimbal.Yaw.Now_angle = AngletoAmplitude(Gimbal_Struct->Gimbal.Yaw.Now_angle);
            } else {
                Gimbal_Struct->Gimbal.Yaw.Now_angle = Gimbal_Struct->Gimbal.Yaw.Set_angle;
            }

            //直接位置环锁死
            Gimbal_Struct->Gimbal.Gimbal_Yaw_Motor.Motor_Data.speed_pid_out = Position_lap_pid(&Gimbal_Struct->Gimbal.Gimbal_Yaw_Motor.Pid_position,
                                                                                                   Gimbal_Struct->Gimbal.Yaw.Now_angle,
                                                                                                   Gimbal_Struct->Gimbal.Yaw.Get_angle);
            CheckOutput_Change();
            break;
        }
    }
}

/// @brief  float转16位,提供pitch重力补偿量
/// @param
void CheckOutput_Change(void)
{
    Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Motor_Data.give_current = (int16_t)Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Motor_Data.speed_pid_out;
    Gimbal_Struct->Gimbal.Gimbal_Yaw_Motor.Motor_Data.give_current   = (int16_t)Gimbal_Struct->Gimbal.Gimbal_Yaw_Motor.Motor_Data.speed_pid_out;

    // PITCH重力软件补偿
    if (Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Motor_Data.give_current < 1000 && Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Motor_Data.give_current > 0)
        ;
    {
        Gimbal_Struct->Gimbal.Gimbal_Pitch_Motor.Motor_Data.give_current = gimbal_pitch_compensate;
    }
}