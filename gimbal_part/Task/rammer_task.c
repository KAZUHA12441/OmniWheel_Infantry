#include "rammer_task.h"

#include "rammer.h"

#include "can1_send.h"

#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

OmniWheel_Infantry_Gimbal_Struct *task_rammer;

void rammer_task(void const * argument)
{
  task_rammer = get_infantry_struct();
  while(1)
  {
    RammerOnChoose(Rammer_stateChange(task_rammer->RC));
    //没测过，不知到会不会出bug
    taskENTER_CRITICAL();//进入临界区
    Gimbal_CAN_dataHandle_Part2(task_rammer);
    taskENTER_CRITICAL();
    Gimbal_Data_Part2_Send();
    vTaskDelay(1);
  }
}