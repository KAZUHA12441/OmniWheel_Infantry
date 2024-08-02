#include "kalman.h"

/// @brief 创建一阶卡尔曼滤波器
/// @param kalmanfiter 
/// @param vk 协方差Q 
/// @param wk 协方差R
void First_kalman_Create(First_kalman_t *kalmanfiter,float vk,float wk)  
{
 kalmanfiter->Q = vk;
 kalmanfiter->R = wk;
 kalmanfiter->pk_out = 0;
 kalmanfiter->xk_out = 0;
 kalmanfiter->A = 1;
 kalmanfiter->B = 0;
 kalmanfiter->pk = 0;
 kalmanfiter->H  = 1;
 kalmanfiter->I = 1;
 kalmanfiter->pk_last = 0;
 kalmanfiter->xk_last = 0;
 kalmanfiter->xk = 0;
 kalmanfiter->uk  = 0;
}

/// @brief 一阶卡尔曼滤波
/// @param kalmanfiter 一阶卡尔曼滤波结构体
/// @param input 输入值
/// @return 
float First_kalmanfiter_run(First_kalman_t *kalmanfiter,float input)
{
  kalmanfiter->xk = kalmanfiter->A * kalmanfiter->xk_last + kalmanfiter->B * kalmanfiter->uk; //x_k  = A * (X_k_1) + B*u_k
  kalmanfiter->pk = kalmanfiter->A * kalmanfiter->pk_last + kalmanfiter->Q;                   //p_k  = A * (P_k_1) + Q
  kalmanfiter->Kk = kalmanfiter->pk/(kalmanfiter->pk + kalmanfiter->R);                       //k_k  = p_k / (p_k + R);
  kalmanfiter->xk_out = kalmanfiter->xk+kalmanfiter->Kk*(input - kalmanfiter->xk);            //xk_out  = x_k + k_k (z_k - H * x_k)
  kalmanfiter->pk_out = (kalmanfiter->I - kalmanfiter->Kk*kalmanfiter->H)*kalmanfiter->pk;    //pk_out  = (I - k_k*H)*p_k
  
  kalmanfiter->xk_last = kalmanfiter->xk_out;
  kalmanfiter->pk_last = kalmanfiter->pk_out;
  
  return kalmanfiter->xk_out;
}

