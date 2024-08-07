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
  dial_on,                  
  dial_off,
}Dial_State;

typedef enum
{
  Friction_on,
  Friction_off,
}Fire_state;

#endif /*__SYSTEM_CHOOSE_H*/