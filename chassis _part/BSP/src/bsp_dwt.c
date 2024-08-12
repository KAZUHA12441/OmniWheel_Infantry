#include "bsp_dwt.h"



/// @brief dwt初始化
/// @param System_Hz
void DWT_Init(DWT_time_t *time,uint16_t System_Hz)
{
    //使能dwt
    CoreDebug->DEMCR |= 1<<24;
    //dwt计数清0 
    DWT->CYCCNT = 0;
    //使能的dwt计数 
    DWT->CTRL |= 1<<0;
    time->system_Hz = System_Hz;
    time->now_tick = 0;
    time->last_tick = 0;
    time->sampleFreq = 0;  
}

/// @brief DWTCNT获取
/// @param  无
/// @return 返回DWT CYCCNTDE的计数值
uint32_t DWTCountget(void)
{
    //dwt的最大计数值为 4294967296
    //按秒计算当震动到4294967296时候即为计算了59秒最大为59秒
    return DWT->CYCCNT;
}

/// @brief 获取采样时间
/// @param time dwt时间结构体
/// 时间间隔会存入DWT_TIME_T的sampleFreq
void get_sampleFreq(DWT_time_t *time)
{ 
  time->now_tick = DWTCountget();
  time->sampleFreq = (time->now_tick - time->last_tick)/time->system_Hz;
  time->last_tick = time->now_tick;
}
