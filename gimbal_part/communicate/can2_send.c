#include "can2_send.h"

#include "can.h"

uint8_t CAN2_SendData_Part1[8];
uint8_t CAN2_SendData_Part2[8];
uint8_t CAN2_SendData_Part3[8];

//哥们摆烂了
//我是取名大师

void CAN2_SENDDATA_Part3(OmniWheel_Infantry_Gimbal_Struct *Gimbal_struct)
{
    CAN2_SendData_Part3[0] = Gimbal_struct->Gimbal.Gimbal_Yaw_Motor.Motor_Data.give_current>>8;
    CAN2_SendData_Part3[1] = Gimbal_struct->Gimbal.Gimbal_Yaw_Motor.Motor_Data.give_current;
}

void Board_CAN2_dataHandle_Part1(OmniWheel_Infantry_Gimbal_Struct *Gimbal_struct)
{
    #if(DR16_LOCATION_SET == head)
    CAN2_SendData_Part1[0] = Gimbal_struct->RC->rc.ch[2] >> 8;
    CAN2_SendData_Part1[1] = Gimbal_struct->RC->rc.ch[2];
    CAN2_SendData_Part1[2] = Gimbal_struct->RC->rc.ch[3] >> 8;
    CAN2_SendData_Part1[3] = Gimbal_struct->RC->rc.ch[3];
    CAN2_SendData_Part1[4] = Gimbal_struct->RC->rc.ch[4] >> 8;
    CAN2_SendData_Part1[5] = Gimbal_struct->RC->rc.ch[4];
    CAN2_SendData_Part1[6] = Gimbal_struct->RC->rc.s1;
    CAN2_SendData_Part1[7] = Gimbal_struct->RC->rc.s2;
    #endif
}

void Board_CAN2_dataHandle_Part2(OmniWheel_Infantry_Gimbal_Struct *Gimbal_struct)
{
    //常驻数据
    CAN2_SendData_Part2[0] = (uint8_t)Gimbal_struct->Friction.firestate;
    float_to_8bits(Gimbal_struct->Gimbal.Yaw.Get_angle,
                   &CAN2_SendData_Part2[1],
                   &CAN2_SendData_Part2[2],
                   &CAN2_SendData_Part2[3],
                   &CAN2_SendData_Part2[4]);
}

void Gimbal_Data_Part3_Send(void)
{
    CAN_TxHeaderTypeDef CAN_Tx3;
    CAN_MSG_TX_NOExtId(&hcan2,&CAN_Tx3,Gimbal_CAN2_SendData_ID2,CAN2_SendData_Part3);
}


void Gimbal_11Data_Part2_Send(void)
{   CAN_TxHeaderTypeDef CAN_Tx2;
    CAN_MSG_TX_NOExtId(&hcan2,&CAN_Tx2,chassis_board_send_data_ID2,CAN2_SendData_Part2);
}


void Board_Data_Send(void)
{
    CAN_TxHeaderTypeDef CAN_Tx1;
   
    #if(DR16_LOCATION_SET == head)
    CAN_MSG_TX_NOExtId(&hcan2,&CAN_Tx1,chassis_board_send_data_ID1,CAN2_SendData_Part1);
    #endif
    
}

//从大端开始
void float_to_8bits(uint32_t data,uint8_t *part1,uint8_t *part2,uint8_t *part3,uint8_t *part4)
{
    uint16_t higth_part = data >>16;
    uint16_t low_part = data;
    *part1 = higth_part>>8;
    *part2 = higth_part;
    *part3 = low_part>>8;
    *part4 = low_part;
}