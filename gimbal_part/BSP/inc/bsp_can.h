#ifndef  __BSP_CAN_H
#define  __BSP_CAN_H

#include "main.h"

void CAN_Filter_Init(CAN_FilterTypeDef *filter,
                     uint32_t rece_id,
                     uint32_t mask_id,
                     uint32_t filter_mode,
                     uint32_t filter_bank,
                     uint32_t fifo_num,
                     uint32_t fifo_scale
                     );

void CAN_MSG_TX(CAN_HandleTypeDef *hcan,CAN_TxHeaderTypeDef *CAN_Tx,uint16_t stdid,uint16_t *data);








#endif   /*__BSP_CAN_H*/