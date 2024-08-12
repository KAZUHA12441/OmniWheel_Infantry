#include "gimbal_task.h"

#include "gimbal.h"
#include "can1_send.h"
#include "can2_send.h"

#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

OmniWheel_Infantry_Gimbal_Struct *task_gimbal;

void gimbal_task(void const * argument)
{
   task_gimbal = get_infantry_struct();
   while(1)
   {
      GimbalControl(Gimbal_StateChange(task_gimbal->RC));
      taskENTER_CRITICAL(); 
      Gimbal_CAN_dataHandle_Part1(task_gimbal);
      CAN2_SENDDATA_Part3(task_gimbal);
      taskEXIT_CRITICAL();
      Gimbal_Data_Part1_Send();//pitch电机
      Gimbal_Data_Part3_Send();//yaw电机
      vTaskDelay(1);
   }
}