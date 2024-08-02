#include "bsp_m6050.h"
#include "i2c.h"
//AD脚默认置0

//还能优化

static float gyro_offset[3] = {0.0f,0.0f,0.0f}; //对应 x,y,z三轴角加速度数据
static float accel_offset[2] = {0.0f,0.0f}; //对应x,y加速度数据，z轴默认为1不校准
static float template_offset  = 0.0f;       //温度


/// @brief 采样分频初始化 
/// @param div 8位分频系数
void M6050_SMPRT_DIV_SET(I2C_HandleTypeDef *hi2c,uint8_t div)
{
    HAL_I2C_Mem_Write(hi2c,address,0x19,I2C_MEMADD_SIZE_8BIT,&div,1,1000);
}

/// @brief 电源管理1
/// @param data 
void M6050_PWR_MGMT1_SET(I2C_HandleTypeDef *hi2c,uint8_t data)
{
    HAL_I2C_Mem_Write(hi2c,address,0x6B,I2C_MEMADD_SIZE_8BIT,&data,1,1000);
}

/// @brief 电源管理2
/// @param data 
void M6050_PWR_MGMT2_SET(I2C_HandleTypeDef *hi2c,uint8_t data)
{
    HAL_I2C_Mem_Write(hi2c,address,0x6C,I2C_MEMADD_SIZE_8BIT,&data,1,1000);
}

/// @brief 陀螺仪配置自检
/// @param data 
void M6050_GYRO_Config(I2C_HandleTypeDef *hi2c,uint8_t data)
{
    HAL_I2C_Mem_Write(hi2c,address,0x1B,I2C_MEMADD_SIZE_8BIT,&data,1,1000);
}

/// @brief 加速计配置自检
/// @param data 
void M6050_ACCEL_Config(I2C_HandleTypeDef *hi2c,uint8_t data)
{
   HAL_I2C_Mem_Write(hi2c,address,0x1C,I2C_MEMADD_SIZE_8BIT,&data,1,1000); 
}
/// @brief 滤波
/// @param data 
void M6050_Config(I2C_HandleTypeDef *hi2c,uint8_t data)
{
  HAL_I2C_Mem_Write(hi2c,address,0x1A,I2C_MEMADD_SIZE_8BIT,&data,1,1000);
}
/// @brief 推荐配置初始化
/// @param 
void M6050_Init(I2C_HandleTypeDef *hi2c)
{
  M6050_SMPRT_DIV_SET(hi2c,0x07);
  M6050_GYRO_Config(hi2c,0x00); //对应131.0f/°/s 
  M6050_ACCEL_Config(hi2c,0x00); //对应16384.0f/°/s
  M6050_PWR_MGMT1_SET(hi2c,0x00);
  M6050_Config(hi2c,0x06);//
}

/// @brief 读陀螺仪数据
/// @param pdata 数据数组指针
void GYRO_GetData(I2C_HandleTypeDef *hi2c,GYRO_Data *GD,uint8_t *pdata)
{
  HAL_I2C_Mem_Read(hi2c,address,GYRO_XOUT_H,I2C_MEMADD_SIZE_8BIT,pdata,1,1000); 
  HAL_I2C_Mem_Read(hi2c,address,GYRO_XOUT_L,I2C_MEMADD_SIZE_8BIT,pdata+1,1,1000); 
  HAL_I2C_Mem_Read(hi2c,address,GYRO_YOUT_H,I2C_MEMADD_SIZE_8BIT,pdata+2,1,1000);
  HAL_I2C_Mem_Read(hi2c,address,GYRO_YOUT_L,I2C_MEMADD_SIZE_8BIT,pdata+3,1,1000);
  HAL_I2C_Mem_Read(hi2c,address,GYRO_ZOUT_H,I2C_MEMADD_SIZE_8BIT,pdata+4,1,1000);
  HAL_I2C_Mem_Read(hi2c,address,GYRO_ZOUT_L,I2C_MEMADD_SIZE_8BIT,pdata+5,1,1000);
  GYRO_DataDecode(GD,pdata);    
}
/// @brief 
/// @param hi2c 
/// @param AD 
/// @param pdata 
void ACCEL_GetData(I2C_HandleTypeDef *hi2c,ACCEL_Data *AD,uint8_t *pdata)
{
  HAL_I2C_Mem_Read(hi2c,address,ACCEL_XOUT_H,I2C_MEMADD_SIZE_8BIT,pdata,1,1000); 
  HAL_I2C_Mem_Read(hi2c,address,ACCEL_XOUT_L,I2C_MEMADD_SIZE_8BIT,pdata+1,1,1000); 
  HAL_I2C_Mem_Read(hi2c,address,ACCEL_YOUT_H,I2C_MEMADD_SIZE_8BIT,pdata+2,1,1000);
  HAL_I2C_Mem_Read(hi2c,address,ACCEL_YOUT_L,I2C_MEMADD_SIZE_8BIT,pdata+3,1,1000);
  HAL_I2C_Mem_Read(hi2c,address,ACCEL_ZOUT_H,I2C_MEMADD_SIZE_8BIT,pdata+4,1,1000);
  HAL_I2C_Mem_Read(hi2c,address,ACCEL_ZOUT_L,I2C_MEMADD_SIZE_8BIT,pdata+5,1,1000);
  //量程要根据设置自检值来选择，具体看手册
  ACCEL_DataDecode(AD,pdata);    
}

/// @brief 陀螺仪数据解码
/// @param GD 欧拉角数据结构体指针
/// @param pdata 陀螺仪数据高低存储数组指针
void GYRO_DataDecode(GYRO_Data *GD,uint8_t *pdata)
{
 GD->Gyro_X  = (int16_t)(pdata[0]<<8|pdata[1]);
 GD->Gyro_Y = (int16_t)(pdata[2]<<8|pdata[3]);
 GD->Gyro_Z   = (int16_t)(pdata[4]<<8|pdata[5]);

 GD->Gyro_X  = (GD->Gyro_X/131.0f) - gyro_offset[0]; 
 GD->Gyro_Y = (GD->Gyro_Y/131.0f) - gyro_offset[1];
 GD->Gyro_Z   = (GD->Gyro_Z/131.0f)- gyro_offset[2];
}

/// @brief 加速度计数据解码
/// @param AD 加速度计结构体指针
/// @param pdata 加速度数据数组
void ACCEL_DataDecode(ACCEL_Data *AD,uint8_t *pdata)
{
 AD->x_g = (int16_t)(pdata[0]<<8|pdata[1]);
 AD->y_g = (int16_t)(pdata[2]<<8|pdata[3]);
 AD->z_g = (int16_t)(pdata[4]<<8|pdata[5]);

 AD->x_g = AD->x_g/16384.0f - accel_offset[0];
 AD->y_g = AD->y_g/16384.0f- accel_offset[1];
 AD->z_g = AD->z_g/16384.0f;
}

/// @brief 陀螺仪零飘处理(取稳态误差) 应该在系统启动前启动陀螺仪校准
/// @param GD 
/// @param gyro_offset 
void Zerofloat_Offset(GYRO_Data *GD,ACCEL_Data *AD)
{
  static uint8_t complate = 0;
  static uint8_t Num_samples = 0;
  if(complate == 0)
  {
  Num_samples++; 
  gyro_offset[0] +=  GD->Gyro_X;
  gyro_offset[1] +=  GD->Gyro_Y;
  gyro_offset[2] +=  GD->Gyro_Z;
  accel_offset[0] += AD->x_g;
  accel_offset[1] += AD->y_g;
   if(Num_samples == 200)
   {
    for(int i = 0;i < 3;i++)
    {
      gyro_offset[i] = gyro_offset[i] / (Num_samples*0.1f);//对平均值进行强转
      if(i<=1)
      {
         accel_offset[i] = accel_offset[i] / (Num_samples*0.1f);
      }
    }
    Num_samples = 0;
    complate = 1;
   }
  }
}