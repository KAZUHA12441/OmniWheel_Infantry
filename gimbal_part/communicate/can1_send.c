#include "can1_send.h"

#include "can.h"


//队列改
uint8_t CAN1_SendData_Part1[8];
uint8_t CAN1_SendData_Part2[8];


void Gimbal_CAN_dataHandle_Part1(OmniWheel_Infantry_Gimbal_Struct *gimbal_struct)
{
    //这里写的不太好
    //底盘部分
    CAN1_SendData_Part1[0] = gimbal_struct->Gimbal.Gimbal_Pitch_Motor.Motor_Data.give_current>>8;
    CAN1_SendData_Part1[1] = gimbal_struct->Gimbal.Gimbal_Pitch_Motor.Motor_Data.give_current;
    
}

void Gimbal_CAN_dataHandle_Part2(OmniWheel_Infantry_Gimbal_Struct *gimbal_struct)
{
    CAN1_SendData_Part2[2] = gimbal_struct->Friction.Friction_Master_Motor.Motor_Data.give_current>>8;
    CAN1_SendData_Part2[3] = gimbal_struct->Friction.Friction_Master_Motor.Motor_Data.give_current;
    CAN1_SendData_Part2[4] = gimbal_struct->Friction.Friction_Slave_Motor.Motor_Data.give_current>>8;
    CAN1_SendData_Part2[5] = gimbal_struct->Friction.Friction_Slave_Motor.Motor_Data.give_current;
    #if(Rammer_Location == head)
    CAN1_SendData_Part2[6] = gimbal_struct->Rammer.Rammer_Motor.Motor_Data.give_current>>8;
    CAN1_SendData_Part2[7] = gimbal_struct->Rammer.Rammer_Motor.Motor_Data.give_current;
    #endif
}


void Gimbal_Data_Part1_Send(void)
{
    CAN_TxHeaderTypeDef CAN_Tx1;

    CAN_MSG_TX_NOExtId(&hcan1,&CAN_Tx1,Gimbal_CAN1_SendData_ID1,CAN1_SendData_Part1);
}

void Gimbal_Data_Part2_Send(void)
{
    CAN_TxHeaderTypeDef CAN_Tx2;

    CAN_MSG_TX_NOExtId(&hcan1,&CAN_Tx2,Gimbal_CAN1_SendData_ID2,CAN1_SendData_Part2);
}