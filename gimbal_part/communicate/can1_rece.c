#include "can1_rece.h"
#include "can.h"
#include "can2_rece.h"

OmniWheel_Infantry_Gimbal_Struct *CAN1_Struct;

void CAN1_Rece_Init(void)
{
    CAN1_Struct = get_infantry_struct();
    CAN1_Filter_Init();
}

//CAN1接收过滤器初始化
void CAN1_Filter_Init(void)
{
    CAN_FilterTypeDef CAN1_Filter;
    CAN_Filter_Init(&hcan1,&CAN1_Filter,
                    0X0000,
                    0X0000,
                    CAN_FILTERMODE_IDMASK,
                    0,
                    CAN_RX_FIFO0,
                    CAN_FILTERSCALE_32BIT);
    HAL_CAN_Start(&hcan1);
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}



void CAN1_Rece_DATAHandle(void)
{
    CAN_RxHeaderTypeDef CAN_RX;
    uint8_t Rx_Data[8];
    if (HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &CAN_RX, Rx_Data) == HAL_OK)
	{
		switch (CAN_RX.StdId)
		{
            case 0x200 + Gimbal_Pitch_MotorID:
            {
                CAN1_Struct->Gimbal.Gimbal_Pitch_Motor.Motor_Data.Motor_Get.speed_get = (uint16_t)(Rx_Data[2] << 8) | Rx_Data[3];   
                break;
            }
            case 0x200 +Friction_Master_Motor_ID:
            {
                CAN1_Struct->Friction.Friction_Master_Motor.Motor_Data.Motor_Get.speed_get = (uint16_t)(Rx_Data[2] << 8) | Rx_Data[3];
            }
            case 0x200 + Friction_Slave_Motor_ID:
            {
                CAN1_Struct->Friction.Friction_Slave_Motor.Motor_Data.Motor_Get.speed_get = (uint16_t)(Rx_Data[2] << 8) | Rx_Data[3];
            }
            case 0x200 + Rammer_MOTOR_ID: 
            {
                #if(Rammer_Location == head)
				CAN1_Struct->Rammer.Rammer_Motor.Motor_Data.Motor_Get.position_get = (uint16_t)(Rx_Data[0] << 8) | Rx_Data[1];
				CAN1_Struct->Rammer.Rammer_Motor.Motor_Data.Motor_Get.speed_get = (uint16_t)(Rx_Data[2] << 8) | Rx_Data[3];
				Encoder_Calculate(&CAN1_Struct->Rammer.Rammer_Motor.Encoder,CAN1_Struct->Rammer.Rammer_Motor.Motor_Data.Motor_Get.position_get,CAN1_Struct->Rammer.Rammer_Motor.MotorAtt.Max_Encoder_val,CAN1_Struct->Rammer.Rammer_Motor.MotorAtt.Reduction_ratio);
                #endif

                break;
            }              
            default:
            {
                break;
            }
		}
	}
	HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}

// void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
// {
// 	if (hcan == &hcan1)
// 	{
// 		CAN1_Rece_DATAHandle();
// 	}
// 	if (hcan == &hcan2)
// 	{
// 		CAN2_Rece_DATAHandle();
// 	}
// }