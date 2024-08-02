#include "pid.h"
#include "main.h"

/// @brief pid控制器参数初始化
/// @param pid  pid结构体
/// @param Kp   系数p
/// @param Ki   系数i
/// @param Kd   系数d
/// @param outmax 输出限幅
/// @param ioutmax 积分限幅度
void Pid_Parameter_Init(pid_parameter_t *pid,float Kp,float Ki,float Kd,float outmax,float ioutmax)
{   
    pid->pid_coe.pid_Kp = Kp;
    pid->pid_coe.pid_Ki = Ki;
    pid->pid_coe.pid_Kd = Kd;
    pid->out_limit  = outmax;
    pid->iout_limit = ioutmax;
    Pid_Reset(pid);
}

/// @brief 重置pid
/// @param pid 
void Pid_Reset(pid_parameter_t *pid)
{
    pid->err = 0;
    pid->last_err = 0;
    pid->pout = 0;
    pid->iout = 0;
    pid->dout = 0;
}

/// @brief pid控制器
/// @param pid pid结构体
/// @param setval 设定值
/// @param getval 获取值
/// @return  计算后的输出值
float  Pid_Parameter(pid_parameter_t *pid,float setval,float getval)
{
    pid->last_err = pid->err;
    pid->err = setval - getval;
    pid->pout = pid->err * pid->pid_coe.pid_Kp;
    pid->iout += pid->err * pid->pid_coe.pid_Ki;
    pid->dout = (pid->err - pid->last_err) * pid->pid_coe.pid_Kd;
    if(__fabs(pid->iout)>pid->iout_limit)
    {
        pid->iout = 0;
    }
    pid->out = pid->pout + pid->iout + pid->dout;
    return  pid->out;
} 

/// @brief 电流环
/// @param pid 
/// @param setcurrent 设定电流值
/// @param getcurrent 获取电流值
float Current_lap_pid(pid_parameter_t *pid,float setcurrent,float getcurrent)
{     
    return Pid_Parameter(pid,setcurrent,getcurrent);
}

/// @brief 位置环
/// @param pid 
/// @param setposition 设定位置值 
/// @param getposition 获取位置值
float Position_lap_pid(pid_parameter_t *pid,float setposition,float getposition)
{
    return Pid_Parameter(pid,setposition,getposition);
}

/// @brief 速度环
/// @param pid 
/// @param setspeed  设定速度
/// @param getspeed  获取速度
float Speed_lap_pid(pid_parameter_t *pid,float setspeed,float getspeed)
{
    return Pid_Parameter(pid,setspeed,getspeed);
}

/// @brief 位置速度串级控制
/// @param pid pid结构体
/// @param setposition 设定位置
/// @param getposition 获取位置
/// @param getspeed    获取速度
float Position_2_Speed_Pid(pid_parameter_t *pid_position,pid_parameter_t *pid_speed,float setposition,float getposition,float getspeed)
{
    float speed_val = Position_lap_pid(pid_position,setposition,getposition);
    return Speed_lap_pid(pid_speed,speed_val,getspeed);
}

/// @brief 位置速度电流三环串级控制
/// @param pid_position 
/// @param pid_speed 
/// @param pid_position 
/// @param setposition 
/// @param getposition 
/// @param getspeed 
/// @param getcurrent      
/// @return 电流值
float Position_2_Speed_2_Current_Pid(pid_parameter_t *pid_position,
                                     pid_parameter_t *pid_speed,
                                     pid_parameter_t *pid_current,
                                     float setposition,float getposition,float getspeed,float getcurrent)
{
  float speed_val = Position_lap_pid(pid_position,setposition,getposition);
  float current_val = Speed_lap_pid(pid_speed,speed_val,getspeed);
  return Current_lap_pid(pid_current, current_val,getcurrent);
}