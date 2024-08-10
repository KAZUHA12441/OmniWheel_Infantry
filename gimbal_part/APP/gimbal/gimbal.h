#ifndef __GIMBAL_H
#define __GIMBAL_H

#include "System_Variables.h"


void CheckOutput_Change(void);
void  Gimbal_Init(void);
float AngletoAmplitude(float angle);
void RCHandleData(void);
void GimbalControl(void);
void CheckOutput_Change(void);
#endif /*__GIMBAL_H*/