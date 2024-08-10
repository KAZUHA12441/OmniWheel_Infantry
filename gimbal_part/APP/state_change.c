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
Fire_state friction_State(uint8_t s1,uint8_t s2)
{      
   switch (s2)
   {
      case 1:
      {
        return Friction_on;
    
      }
       default:
       {
        return Friction_off;
       }
       
   }
   
}