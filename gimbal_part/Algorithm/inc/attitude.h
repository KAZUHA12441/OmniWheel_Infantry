#ifndef __ATTITUDE_H
#define __ATTITUDE_H



typedef struct
{
    float Roll;
    float Pitch;
    float Yaw;

}attritude_angle;

void Attitube_Algoirthm(attritude_angle *angle,float *q);

#endif /*__ATTITUDE_H*/