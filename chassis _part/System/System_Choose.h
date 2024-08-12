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
  Rammer_on = 1,                  
  Rammer_off,
}Rammer_State;

typedef enum
{
  Friction_on = 1 ,
  Friction_off,
}Fire_state;

#endif /*__SYSTEM_CHOOSE_H*/