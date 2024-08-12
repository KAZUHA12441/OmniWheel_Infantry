#include "imu_task.h"

#include "imu.h"

#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

OmniWheel_Infantry_Gimbal_Struct *task_imu;


void imu_task(void const * argument)
{   
    task_imu = get_infantry_struct();
    while(1)
    { 
       IMU_GETData(task_imu->Gimbal_Attitube.Attitube.imu_handledata);
       taskENTER_CRITICAL();
       EulerAngle_Decode();
       taskEXIT_CRITICAL();
       vTaskDelay(1);
    }
}

