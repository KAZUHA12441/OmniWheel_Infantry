#include "chassis_task.h"

#include "chassis.h"
#include "rammer.h"
#include "Yaw_GM6020.h" 

#include "can1_send.h"



#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

OmniWheel_Infantry_Chassis_Struct *task_chassis;

void chassis_task(void const * argument)
{
  Init_Part();
  task_chassis = get_infantry_struct();
  while(1)
  {
   ChassisControlChoose(chassis_stateChange(task_chassis->RC));
   taskENTER_CRITICAL();//进入临界区，防止数据串改
   chassis_CAN_dataHandle_Part1(task_chassis);
   taskENTER_CRITICAL();
   Chassis_Data_Part1_Send();
   vTaskDelay(1);
  }
}

void Init_Part(void)
{
  //Init
  Chassis_Init();
  #if(DR16_LOCATION_SET == chassis)
  USART_PtrInit();
  #endif
  CAN1_Rece_Init();
  CAN2_Rece_Init();
  Rammer_Init();
  Yaw_Encoder_Init();
}