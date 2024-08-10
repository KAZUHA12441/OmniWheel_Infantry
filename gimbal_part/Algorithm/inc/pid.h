#ifndef __PID_H
#define __PID_H



//pid系数
typedef struct 
{
 float pid_Kp;
 float pid_Ki;
 float pid_Kd;
}pid_coefficient_t;

//pid总结构体
typedef struct 
{
    pid_coefficient_t  pid_coe;
    float  err;
    float  last_err;
    float  pout;
    float  iout;
    float  dout;
    float  out;
    
    float  iout_limit;   //积分限幅
    float  out_limit;    //输出限幅
}pid_parameter_t;


void Pid_Parameter_Init(pid_parameter_t *pid,float Kp,float Ki,float Kd,float outmax,float ioutmax);
void Pid_Reset(pid_parameter_t *pid);
float Pid_Parameter(pid_parameter_t *pid,float setval,float getval);
float Current_lap_pid(pid_parameter_t *pid,float setcurrent,float getcurrent);
float Position_lap_pid(pid_parameter_t *pid,float setposition,float getposition);
float Speed_lap_pid(pid_parameter_t *pid,float setspeed,float getspeed);
float Position_2_Speed_Pid(pid_parameter_t *pid_position,pid_parameter_t *pid_speed,float setposition,float getposition,float getspeed);
float Position_2_Speed_2_Current_Pid(pid_parameter_t *pid_position,
                                     pid_parameter_t *pid_speed,
                                     pid_parameter_t *pid_current,
                                     float setposition,float getposition,float getspeed,float getcurrent);
float Speed_2_Current_Pid(pid_parameter_t *pid_speed,pid_parameter_t *pid_current,float setspeed,float getspeed,float getcurrent);
#endif /*__PID_H*/