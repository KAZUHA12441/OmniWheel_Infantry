#include "state_change.h"




OmniWheel_Infantry_Gimbal_Struct   _Omiwhel_Infantry_Gimbal;

OmniWheel_Infantry_Gimbal_Struct *get_infantry_struct(void)
{
    return  &_Omiwhel_Infantry_Gimbal;
}

/// @brief 摩擦轮状态选择
/// @param s1 左拨
/// @param s2 右拨
/// @return 返回状态
Fire_state friction_State(rc_data_t *rc_data)
{      
   switch (rc_data->rc.s2)
   {
      case 2:
      {
        return Friction_on;
    
      }
       default:
       {
        return Friction_off;
       }
       
   }
}

Rammer_State Rammer_stateChange(rc_data_t *rc_data)
{
   //保证摩擦轮开启，再进行拨弹
   if(rc_data->rc.s2 == 2)
   {
     if(rc_data->rc.ch[4] < -400)
     {
        return Rammer_on;
     }
     else if(rc_data->rc.ch[4] >= -400 && rc_data->rc.ch[4] <= 400)
     {
        return Rammer_off;
     }
   }
   return Rammer_off;
}

Gimbal_State Gimbal_StateChange(rc_data_t *rc_data)
{
  if(rc_data->rc.s1 == 3||rc_data->rc.s1 == 2)
  {
    return Gimbal_Control;
  }
  else
  {
       return Gimbal_idle;
  }
}
