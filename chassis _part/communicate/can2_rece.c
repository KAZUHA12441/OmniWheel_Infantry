#include "can2_rece.h"
#include "can.h"



OmniWheel_Infantry_Chassis_Struct *CAN2_Struct;

void CAN2_Rece_Init(void)
{
    CAN2_Struct = get_infantry_struct();
    CAN2_Filter_Init();
}


//CAN1接收过滤器初始化
void CAN2_Filter_Init(void)
{
    CAN_FilterTypeDef CAN2_Filter;
    CAN_Filter_Init(&hcan2,&CAN2_Filter,
                    0X0000,
                    0X0000,
                    CAN_FILTERMODE_IDMASK,
                    0,
                    CAN_RX_FIFO0,
                    CAN_FILTERSCALE_32BIT);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void CAN2_Rece_DATAHandle(void)
{
    
    CAN_RxHeaderTypeDef CAN_RX;
    uint8_t Rx_Data[8];
    if (HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &CAN_RX, Rx_Data) == HAL_OK)
	{
		switch (CAN_RX.StdId)
		{
            case Yaw_Rece_ID:
            {
                CAN2_Struct->Gimbal.Gimbal_Yaw_Motor.Motor_Data.Motor_Get.position_get = (uint16_t)(Rx_Data[0] << 8) | Rx_Data[1];
                //获取底盘机械角度
                Encoder_Calculate(&CAN2_Struct->Gimbal.Gimbal_Yaw_Motor.Encoder,
                                 CAN2_Struct->Gimbal.Gimbal_Yaw_Motor.Motor_Data.Motor_Get.position_get,
                                 CAN2_Struct->Gimbal.Gimbal_Yaw_Motor.MotorAtt.Max_Encoder_val,
                                 CAN2_Struct->Gimbal.Gimbal_Yaw_Motor.MotorAtt.Reduction_ratio);
                break;
            }
            case chassis_board_rece_data_ID1:
            {
                 #if(DR16_LOCATION_SET == head)
                         CAN2_Struct->RC->rc.ch[2] = (int16_t)(Rx_Data[0]<<8)|Rx_Data[1];
                         CAN2_Struct->RC->rc.ch[3] = (int16_t)(Rx_Data[2]<<8)|Rx_Data[3];
                         CAN2_Struct->RC->rc.ch[4] = (int16_t)(Rx_Data[4]<<8)|Rx_Data[5];
                         CAN2_Struct->RC->rc.s1 = Rx_Data[6];
                         CAN2_Struct->RC->rc.s2 = Rx_Data[7];
                 #endif
                break;
            }
            case chassis_board_rece_data_ID2:
            {
                 CAN2_Struct->Gimbal.firestate = (Fire_state)Rx_Data[0];
                 CAN2_Struct->Gimbal.Yaw_angle = _8bits_to_float(Rx_Data[1],Rx_Data[2],Rx_Data[3],Rx_Data[4]);
                break;
            }
            default:
            {
                break;
            }
		}
	}
	HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);
}

float _8bits_to_float(uint8_t part1,uint8_t part2,uint8_t part3,uint8_t part4)
{
    uint16_t hight_part = (part1<<8)|part2;
    uint16_t low_part = (part3<<8)|part4;

    return (hight_part<<16)|(low_part);
}