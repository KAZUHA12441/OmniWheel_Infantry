#ifndef __FIRST_ORDER_FILTER_H
#define __FIRST_ORDER_FILTER_H

typedef struct 
{
    float  alpha;
    float  val;
    float  last_val;
}first_order_filter_t;

void First_low_pass_fiterCreate(first_order_filter_t *filter,float alpha);
float First_orderfilter(first_order_filter_t *filter,float input);
#endif  /*__FIRST_ORDER_FILTER_H*/