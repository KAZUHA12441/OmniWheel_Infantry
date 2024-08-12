#ifndef __BSP_M6050_H
#define __BSP_M6050_H

#include "main.h"

//陀螺仪加速计原始数据



//who am i?

#define    AD_RESET   0x68   //01101000
#define    AD_Set     0x69   //01101001
#define    address    0xD0
//register


#define    SMPRT_DIV      0x19  //采样分频
#define    Config         0x1A  //低通滤波
#define    GYRO_Config    0x1B
#define    ACCEL_Config   0x1C
    //加速计
#define    ACCEL_XOUT_H   0x3B   //x轴高8位
#define    ACCEL_XOUT_L   0x3C  //x轴低8位
#define    ACCEL_YOUT_H   0x3D
#define    ACCEL_YOUT_L   0x3E
#define    ACCEL_ZOUT_H   0x3F
#define    ACCEL_ZOUT_L   0x40
    //温度计
#define    TEMP_OUT_H     0x41
#define    TEMP_OUT_L     0x42
    //陀螺仪
#define    GYRO_XOUT_H    0x43   //ROLL高8位
#define    GYRO_XOUT_L    0x44   //ROLL低8位
#define    GYRO_YOUT_H    0x45
#define    GYRO_YOUT_L    0x46
#define    GYRO_ZOUT_H    0x47
#define    GYRO_ZOUT_L    0x48

#define    PWR_MGMT_1     0x6B   //电源管理1
#define    PWR_MGMT_2     0x6C   //电源管理2

typedef struct GYRO
{
    float Gyro_X;
    float Gyro_Y;
    float Gyro_Z;
}GYRO_Data;

typedef struct ACCEL
{
   float x_g;
   float y_g;
   float z_g;  
}ACCEL_Data;

typedef struct 
{
   ACCEL_Data AD;
   GYRO_Data  GD;
   float template;
}M6050_t;



void M6050_SMPRT_DIV_SET(I2C_HandleTypeDef *hi2c,uint8_t div);
void M6050_PWR_MGMT1_SET(I2C_HandleTypeDef *hi2c,uint8_t data);
void M6050_PWR_MGMT2_SET(I2C_HandleTypeDef *hi2c,uint8_t data);
void M6050_GYRO_Config(I2C_HandleTypeDef *hi2c,uint8_t data);
void M6050_ACCEL_Config(I2C_HandleTypeDef *hi2c,uint8_t data);
void M6050_Init(I2C_HandleTypeDef *hi2c);
void GYRO_GetData(I2C_HandleTypeDef *hi2c,GYRO_Data *GD,uint8_t *pdata);
void ACCEL_GetData(I2C_HandleTypeDef *hi2c,ACCEL_Data *AD,uint8_t *pdata);
void GYRO_DataDecode(GYRO_Data *GD,uint8_t *pdata);
void ACCEL_DataDecode(ACCEL_Data *AD,uint8_t *pdata);
void M6050_Config(I2C_HandleTypeDef *hi2c,uint8_t data);
void Zerofloat_Offset(GYRO_Data *GD,ACCEL_Data *AD);

#endif /*__BSP_M6050_H*/