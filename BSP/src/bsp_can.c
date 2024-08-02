#include "bsp_can.h"


CAN_FilterTypeDef CAN_Filter;

//该重构了


uint32_t mailbox;
/// @brief CAN过滤器初始化
/// @param filter 
/// @param rece_id 
/// @param mask_id 
/// @param filter_mode 
/// @param fiter_bank 
/// @param fifo_num 
/// @param activation_state 
void CAN_Filter_Init(CAN_FilterTypeDef *filter,
                     uint32_t rece_id,
                     uint32_t mask_id,
                     uint32_t filter_mode,
                     uint32_t filter_bank,
                     uint32_t fifo_num,
                     uint32_t fifo_scale
                     )
{
 //过滤器设置   
 filter->FilterActivation = CAN_FILTER_ENABLE;
 filter->FilterActivation = fifo_num;
 filter->FilterBank =  filter_bank; 
 filter->FilterMode = filter_mode;
 filter->FilterScale = fifo_scale;
 //过滤器掩码mask设置
 filter->FilterIdHigh = (rece_id>>16)&0xFFF;
 filter->FilterIdLow  = (rece_id<<16);
 filter->FilterMaskIdHigh = (mask_id>>16)&0xFF;
 filter->FilterMaskIdLow  = (mask_id<<16); 
}

/// @brief can信息发送
/// @param hcan can
/// @param CAN_Tx 
/// @param data 
void CAN_MSG_TX(CAN_HandleTypeDef *hcan,CAN_TxHeaderTypeDef *CAN_Tx,uint16_t *data)
{
	  
	        uint8_t send_data[8];
             
		    int i;
			for(i = 0;i<8;i++)
			{
				send_data[i] = data[i];
			}
            CAN_Tx->StdId = 0x200;
            CAN_Tx->DLC = 8;
	        CAN_Tx->ExtId = 0;
	        CAN_Tx->IDE = CAN_ID_STD;
	        CAN_Tx->RTR = CAN_RTR_DATA;
	        CAN_Tx->TransmitGlobalTime = DISABLE;
	        HAL_CAN_AddTxMessage(hcan, CAN_Tx, send_data, &mailbox);  
}
