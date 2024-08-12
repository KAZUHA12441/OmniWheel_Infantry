#include "safe_task.h"

#include "can2_send.h"

#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"


OmniWheel_Infantry_Chassis_Struct *task_safe;

void safe_task(void const * argument)
{
   task_safe = get_infantry_struct();
   while(1)
   {
      task_safe->RC->Lost_contact++;
      if(task_safe->RC->Lost_contact > lost_time_limit)
      {
        Lost_contact_CHSetZero(task_safe->RC);
      }
      #if(DR16_LOCATION_SET == chassis)
      taskENTER_CRITICAL();
      Board_CAN1_dataHandle(task_safe);
      taskENTER_CRITICAL();
      Board_Data_Send();
      #endif
      vTaskDelay(1);
   }
} 