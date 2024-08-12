#include "can1_send.h"
#include "can.h"


//队列改
uint8_t CAN1_SendData_Part1[8];
uint8_t CAN1_SendData_Part2[8];

//在任务函数
void chassis_CAN_dataHandle_Part1(OmniWheel_Infantry_Chassis_Struct *chassis_struct)
{
    //这里写的不太好
    //底盘部分
    CAN1_SendData_Part1[0] = chassis_struct->Chassis.LB_Wheel.Motor_Data.give_current>>8;
    CAN1_SendData_Part1[1] = chassis_struct->Chassis.LB_Wheel.Motor_Data.give_current;
    CAN1_SendData_Part1[2] = chassis_struct->Chassis.LF_Wheel.Motor_Data.give_current >>8;
    CAN1_SendData_Part1[3] = chassis_struct->Chassis.LF_Wheel.Motor_Data.give_current ;
    CAN1_SendData_Part1[4] = chassis_struct->Chassis.RB_Wheel.Motor_Data.give_current >>8;
    CAN1_SendData_Part1[5] = chassis_struct->Chassis.RB_Wheel.Motor_Data.give_current;
    CAN1_SendData_Part1[6] = chassis_struct->Chassis.RF_Wheel.Motor_Data.give_current >>8;
    CAN1_SendData_Part1[7] = chassis_struct->Chassis.RF_Wheel.Motor_Data.give_current;
    
}

void chassis_CAN_dataHandle_Part2(OmniWheel_Infantry_Chassis_Struct *chassis_struct)
{
    CAN1_SendData_Part2[0] = chassis_struct->Rammer.Rammer_Motor.Motor_Data.give_current>>8;
    CAN1_SendData_Part2[0] = chassis_struct->Rammer.Rammer_Motor.Motor_Data.give_current;
}

void Chassis_Data_Part1_Send(void)
{
    CAN_TxHeaderTypeDef CAN_Tx1;
    
    CAN_MSG_TX_NOExtId(&hcan1,&CAN_Tx1,Chassis_Send_ID,CAN1_SendData_Part1);
    
}

void Chassis_Data_Part2_Send(void)
{
    CAN_TxHeaderTypeDef CAN_Tx2;
    CAN_MSG_TX_NOExtId(&hcan1,&CAN_Tx2,Rammer_Send_ID,CAN1_SendData_Part2);
}