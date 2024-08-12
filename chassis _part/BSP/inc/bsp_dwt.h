#ifndef __BSP_DWT_H
#define __BSP_DWT_H

#include "main.h"

typedef struct 
{
    uint32_t now_tick;
    uint32_t last_tick;
    uint16_t system_Hz;
    uint16_t sampleFreq;//单位为秒
}DWT_time_t;

void DWT_Init(DWT_time_t *time,uint16_t System_Hz);
void get_sampleFreq(DWT_time_t *time);
uint32_t DWTCountget(void);
#endif /*__BSP_DWT_H*/
