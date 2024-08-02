#ifndef __SYSTEM_CHOOSE_H
#define __SYSTEM_CHOOSE_H\



typedef enum
{
  M3508  = 1,
  M2006,
  GM6020,
}Motor_Type;                //电机类型

typedef enum
{
  chassis_lock,
  chassis_contrl,
  chassis_idle,
}chassis_State;             //底盘状态

typedef enum
{
  chassis_dreidel_on,
  chassis_dreidel_off,
}dreidel_State;             //陀螺状态

typedef enum
{
  fire_on,                  //开火状态
  fire_off,
}fire_State;


#endif /*__SYSTEM_CHOOSE_H*/