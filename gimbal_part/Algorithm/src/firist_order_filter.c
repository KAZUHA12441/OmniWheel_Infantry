#include "first_order_filter.h"

// 滤波系数越小，滤波结果越平稳，但是灵敏度越低；滤波系数越大，灵敏度越高，但是滤波结果越不稳定。



/// @brief 创建一阶低通滤波器
/// @param filter 一阶低通滤波器结构体
/// @param alpha  滤波系数
void First_low_pass_fiterCreate(first_order_filter_t *filter,float alpha)
{
  filter->alpha =  alpha;
  filter->val   = 0;
  filter->last_val  = 0;
}



/// @brief 一阶低通滤波器
/// @param filter 
/// @param input 
/// @return 
float First_orderfilter(first_order_filter_t *filter,float input)
{
  filter->val = (1.0f - filter->alpha) * filter->last_val + filter->alpha * input;
  filter->last_val =  filter->val;
  return filter->val;
}