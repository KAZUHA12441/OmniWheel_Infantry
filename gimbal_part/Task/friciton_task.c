#include "friction_task.h"

#include "rammer.h"
#include "friction.h"
#include "can1_send.h"

#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

OmniWheel_Infantry_Gimbal_Struct *task_fire;


void friction_task(void const * argument)
{
    task_fire = get_infantry_struct();
    while(1)
    {
        friction_motor_run(friction_State(task_fire->RC));
        #if(Rammer_Location == head)
        RammerOnChoose(Rammer_stateChange(task_fire->RC->rc.s2));
        #endif
        taskENTER_CRITICAL();
        Gimbal_CAN_dataHandle_Part2(task_fire);
        taskEXIT_CRITICAL();
        Gimbal_Data_Part2_Send();
        vTaskDelay(1);
    }
}