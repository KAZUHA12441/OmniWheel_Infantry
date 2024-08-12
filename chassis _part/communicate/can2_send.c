#include "can2_send.h"
#include "can.h"

uint8_t CAN2_SendData_Part1[8];
uint8_t CAN2_SendData_Part2[8];


void Board_CAN1_dataHandle(OmniWheel_Infantry_Chassis_Struct *chassis_struct)
{
    
    CAN2_SendData_Part1[0] = chassis_struct->RC->rc.ch[0] >> 8;
    CAN2_SendData_Part1[1] = chassis_struct->RC->rc.ch[0];
    CAN2_SendData_Part1[2] = chassis_struct->RC->rc.ch[1] >> 8;
    CAN2_SendData_Part1[3] = chassis_struct->RC->rc.ch[1];
    CAN2_SendData_Part1[4] = chassis_struct->RC->rc.ch[2] >> 8;
    CAN2_SendData_Part1[5] = chassis_struct->RC->rc.ch[2];
    CAN2_SendData_Part1[6] = chassis_struct->RC->rc.ch[3] >> 8;
    CAN2_SendData_Part1[7] = chassis_struct->RC->rc.ch[3];
    
    CAN2_SendData_Part2[0] = chassis_struct->RC->rc.ch[4] >> 8;
    CAN2_SendData_Part2[1] = chassis_struct->RC->rc.ch[4];
    CAN2_SendData_Part2[2] = chassis_struct->RC->rc.s1;
    CAN2_SendData_Part2[3] = chassis_struct->RC->rc.s2;
}

void Board_Data_Send(void)
{
    CAN_TxHeaderTypeDef CAN_Tx1;
    CAN_TxHeaderTypeDef CAN_Tx2;
    CAN_MSG_TX_NOExtId(&hcan2,&CAN_Tx1,chassis_board_send_data_ID1,CAN2_SendData_Part1);
    CAN_MSG_TX_NOExtId(&hcan2,&CAN_Tx2,chassis_board_send_data_ID2,CAN2_SendData_Part2);
}


