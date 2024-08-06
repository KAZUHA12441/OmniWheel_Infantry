#include "state_change.h"

//还不够完善，再想想

//发弹已完成
//还要写个退弹

//s1左拨，s2右拨

OmniWheel_Infantry_Chassis_Struct   _Omiwhel_Infantry_Chassis;

OmniWheel_Infantry_Chassis_Struct *get_infantry_struct(void)
{
    return  &_Omiwhel_Infantry_Chassis;
}

/// @brief 返回一个底盘状态
/// @param rc 遥控器数据
/// @return 底盘状态
Chassis_State chassis_stateChange(rc_data_t *rc_data)
{
  switch(rc_data->rc.s1)
  {
    case 1:
    {
       //底盘闲置
       return chassis_idle;
    }
    case 2:
    {
        //底盘锁定
       return chassis_lock;
    }
    case 3:
    {   
        if(rc_data->rc.s2 == 3)
        {
            //小陀螺开启
           return chassis_dreidel_on;
        }
        //操纵模式
        return chassis_contrl;
    }
    default:
    {
        return chassis_lock;
    }
  }
}

/// @brief 拨弹盘状态
/// @param rc_data 遥控器数据
/// @return 
Dial_State dial_stateChange(rc_data_t *rc_data)
{
   //保证摩擦轮开启，再进行拨弹
   if(rc_data->rc.s2 == 2)
   {
     if(rc_data->rc.ch[4] < -400)
     {
        return dial_on;
     }
     else if(rc_data->rc.ch[4] >= -400 && rc_data->rc.ch[4] <= 400)
     {
        return dial_off;
     }
   }
   return dial_off;
}