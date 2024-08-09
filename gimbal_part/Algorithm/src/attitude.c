#include "attitude.h"
#include "math.h"

/// @brief 姿态解算
/// @param angle 欧拉角结构体
/// @param q     四元数



void Attitube_Algoirthm(attritude_angle *angle,float *q)
{
  angle->Yaw = atan2((q[0] * q[3] + q[1] * q[2]),(q[0] * q[0] + q[1] * q[1] - 0.5f));
  angle->Pitch = atan2(((2 * q[0] * q[2]) - (2 * q[1] * q[3])),1.0f);
  angle->Roll  = atan2((q[0] * q[1] + q[2] * q[3]),(q[0] * q[0] + q[3] * q[3]-0.5f));
}