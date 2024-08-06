#ifndef __SYSTEM_CHOOSE_H
#define __SYSTEM_CHOOSE_H\




typedef enum
{
  chassis_lock,
  chassis_contrl,
  chassis_idle,
  chassis_dreidel_on,
}Chassis_State;             //底盘状态

typedef enum
{
  dial_on,                  //开火状态
  dial_off,
}Dial_State;


#endif /*__SYSTEM_CHOOSE_H*/