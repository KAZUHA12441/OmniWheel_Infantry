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
#endif /*__PID_H*/