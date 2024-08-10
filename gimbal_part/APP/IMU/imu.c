#include "imu.h" 
#include "i2c.h"

OmniWheel_Infantry_Gimbal_Struct *IMU_Struct;

/// @todo 准备改成队列
uint8_t GYRO_pdata[6];//陀螺仪数据缓存区
uint8_t ACCEL_pdata[6];//加速度计速度缓冲区

/// @brief IMU部分初始化
/// @todo 
void IMU_Init(void)
{
   IMU_Struct = get_infantry_struct();
   //imu模式设定
   M6050_Init(&hi2c2);
   //开启dwt计时器
   DWT_Init(&IMU_Struct->System_time,SYSTEM_Hz);
   
   //创建卡尔曼滤波器
   First_kalman_Create(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_ACCEL_X,Kalman_Q,Kalman_R);
   First_kalman_Create(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_ACCEL_Y,Kalman_Q,Kalman_R);
   First_kalman_Create(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_ACCEL_Z,Kalman_Q,Kalman_R);
   First_kalman_Create(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_GYRO_X,Kalman_Q,Kalman_R);
   First_kalman_Create(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_GYRO_Y,Kalman_Q,Kalman_R);
   First_kalman_Create(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_GYRO_Z,Kalman_Q,Kalman_R);
   //imu初始化标志位重置
   IMU_Struct->Gimbal_Attitube.IMU_Init_complate = 0;
}

/// @brief 获取IMU数据
/// @param pdata 处理后各轴的数据
void IMU_GETData(float *pdata)
{
   GYRO_DataDecode(&IMU_Struct->Gimbal_Attitube.M6050_IMU.GD,GYRO_pdata);
   ACCEL_DataDecode(&IMU_Struct->Gimbal_Attitube.M6050_IMU.AD,ACCEL_pdata);
   Zerofloat_Offset(&IMU_Struct->Gimbal_Attitube.M6050_IMU.GD,&IMU_Struct->Gimbal_Attitube.M6050_IMU.AD);

   if(!(IMU_Struct->Gimbal_Attitube.IMU_Init_complate))
      IMU_Struct->Gimbal_Attitube.IMU_Init_complate = 1;
   else
   {
     //这里写的不太好，后面找时间重构
     pdata[0] = First_kalmanfiter_run(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_ACCEL_X,IMU_Struct->Gimbal_Attitube.M6050_IMU.AD.x_g);
     pdata[1] = First_kalmanfiter_run(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_ACCEL_Y,IMU_Struct->Gimbal_Attitube.M6050_IMU.AD.y_g);
     pdata[2] = First_kalmanfiter_run(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_ACCEL_Z,IMU_Struct->Gimbal_Attitube.M6050_IMU.AD.z_g);
     pdata[3] = First_kalmanfiter_run(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_GYRO_X,IMU_Struct->Gimbal_Attitube.M6050_IMU.GD.Gyro_X);
     pdata[4] = First_kalmanfiter_run(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_GYRO_X,IMU_Struct->Gimbal_Attitube.M6050_IMU.GD.Gyro_Y);
     pdata[5] = First_kalmanfiter_run(&IMU_Struct->Gimbal_Attitube.IMU_Handle.Kalmanfilter_GYRO_X,IMU_Struct->Gimbal_Attitube.M6050_IMU.GD.Gyro_Z);
   }
}

/// @brief  云台姿态角解算
void EulerAngle_Decode(void)
{ 
   get_sampleFreq(&IMU_Struct->System_time);
   //四元数
   MahonyAHRSupdateIMU(IMU_Struct->Gimbal_Attitube.Attitube.quaternion,
                        IMU_Struct->Gimbal_Attitube.Attitube.imu_handledata[5],
                        IMU_Struct->Gimbal_Attitube.Attitube.imu_handledata[4],
                        IMU_Struct->Gimbal_Attitube.Attitube.imu_handledata[3],
                        IMU_Struct->Gimbal_Attitube.Attitube.imu_handledata[0],
                        IMU_Struct->Gimbal_Attitube.Attitube.imu_handledata[1],
                        IMU_Struct->Gimbal_Attitube.Attitube.imu_handledata[2],
                        IMU_Struct->System_time.sampleFreq);

   //姿态解算
   
   Attitube_Algoirthm(&IMU_Struct->Gimbal_Attitube.Attitube.Euler_angle,IMU_Struct->Gimbal_Attitube.Attitube.quaternion);

   //当前姿态
   IMU_Struct->Gimbal.Pitch.Get_angle= IMU_Struct->Gimbal_Attitube.Attitube.Euler_angle.Pitch * radtoangle;
   IMU_Struct->Gimbal.Yaw.Get_angle = IMU_Struct->Gimbal_Attitube.Attitube.Euler_angle.Yaw * radtoangle;
}

