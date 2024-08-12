#include "init_task.h"

#include "gimbal.h"

#include "IMU.h"
#include "rammer.h"
#include "can1_rece.h"
#include "can2_rece.h"
#include "friction.h"

#include "friction_task.h"
#include "rammer_task.h"
#include "safe_task.h"
#include "gimbal_task.h"
#include "imu_task.h"
#include "safe_task.h"

#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "cmsis_os.h"

extern osThreadId TaskInit;
extern osThreadId Initialize;   

osThreadId TaskGimbal;
osThreadId TaskFire;
osThreadId TaskSafe;
osThreadId TaskIMU;

void Init_Task(void const * argument)
{
  
  taskENTER_CRITICAL();

  //imu任务
  osThreadDef(IMU_TASK,imu_task,osPriorityRealtime,0,1024);
  TaskIMU = osThreadCreate(osThread(IMU_TASK), NULL);
  //云台任务
  osThreadDef(GIMBAL_TASK,gimbal_task,osPriorityRealtime,0,1024);
  TaskGimbal = osThreadCreate(osThread(GIMBAL_TASK), NULL);
  //开火任务
  osThreadDef(FIRE_TASK,friction_task,osPriorityRealtime,0,1024);
  TaskFire = osThreadCreate(osThread(FIRE_TASK), NULL);
  //安全任务
  osThreadDef(SAFE_TASK,safe_task,osPriorityRealtime,0,1024);
  TaskSafe = osThreadCreate(osThread(SAFE_TASK), NULL);

  
  vTaskDelete(TaskInit);
  taskEXIT_CRITICAL();
}

void Init_Part(void const * argument)
{
    while(1)
    {
        
        friction_Init();
        Gimbal_Init();
        IMU_Init();
        #if(DR16_LOCATION_SET == head)
        USART_PtrInit();
        #endif
        #if(Rammer_Location == head)
        Rammer_Init();
        #endif
        CAN1_Rece_Init();
        CAN2_Rece_Init();
        vTaskSuspend(Initialize);
    }
}

