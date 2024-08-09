#ifndef __IMU_H
#define __IMU_H

#include "System_Variables.h"

void IMU_Init(void);
void IMU_GETData(float *pdata);
void EulerAngle_Decode(void);
#endif /*__IMU_H*/