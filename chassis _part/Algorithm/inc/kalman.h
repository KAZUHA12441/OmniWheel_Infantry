#ifndef __KALMAN_H
#define __KALMAN_H

typedef struct kalman
{
  float xk;
  float xk_last;
  float xk_out;
  float pk_out;
  float pk;
  float pk_last;
  float Kk;
  float Q;        //协方差wk
  float R;        //协方差vk
  float uk;       
  float H;
  float A;
  float B; 
  float I;
}First_kalman_t;

void First_kalman_Create(First_kalman_t *kalmanfiter,float vk,float wk);
float First_kalmanfiter_run(First_kalman_t *kalmanfiter,float input);  


#endif /*__KALMAN_H*/