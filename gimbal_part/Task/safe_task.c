#include "safe_task.h"
#include "can2_send.h"
#include "can1_send.h"
#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"


OmniWheel_Infantry_Gimbal_Struct *task_safe;

void safe_task(void const * argument)
{
   task_safe = get_infantry_struct();
   while(1)
   {
      #if(DR16_LOCATION_SET == head)
      //遥控器失联处理
      task_safe->RC->Lost_contact++;
      if(task_safe->RC->Lost_contact > lost_time_limit)
      {
        Lost_contact_CHSetZero(task_safe->RC);
      }
      taskENTER_CRITICAL();
      Board_CAN2_dataHandle_Part1(task_safe);
      taskEXIT_CRITICAL();
      Board_Data_Send();
      #endif
      Board_CAN2_dataHandle_Part2(task_safe);
      Gimbal_11Data_Part2_Send();
      vTaskDelay(1);
   }
} 