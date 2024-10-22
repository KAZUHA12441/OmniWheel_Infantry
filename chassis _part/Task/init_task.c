#include "init_task.h"

#include "chassis.h"
#include "rammer.h"
#include "Yaw_GM6020.h"

#include "chassis_task.h"
#include "rammer_task.h"
#include "safe_task.h"

#include "freertos.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "cmsis_os.h"

extern osThreadId TaskInit;
extern osThreadId Initialize;
osThreadId TaskChassis;
osThreadId TaskRammer;
osThreadId TaskSafe;


void Init_Task(void const * argument)
{
 
  taskENTER_CRITICAL(); 

  //创建安全任务
  osThreadDef(SAFE_TASK,safe_task,osPriorityRealtime, 0, 1024);
  TaskSafe = osThreadCreate(osThread(SAFE_TASK), NULL);

  //创建底盘任务  
  osThreadDef(CHASSIS_TASK, chassis_task, osPriorityRealtime, 0, 1024);
  TaskChassis = osThreadCreate(osThread(CHASSIS_TASK), NULL);
  
  #if(Rammer_Location == chassis)
  //创建拨弹盘任务
  osThreadDef(RAMMER_TASK,rammer_task,osPriorityRealtime, 0, 1024);
  TaskRammer = osThreadCreate(osThread(RAMMER_TASK), NULL);
  #endif 
  
  vTaskDelete(TaskInit);
  taskEXIT_CRITICAL();
}

void Init_Part(void const * argument)
{
  //Init
  Chassis_Init();
  #if(DR16_LOCATION_SET == chassis)
  USART_PtrInit();
  #endif
  CAN1_Rece_Init();
  CAN2_Rece_Init();
  #if(Rammer_Location == chassis)
  Rammer_Init();
  #endif
  Yaw_Encoder_Init();
  vTaskSuspend(Initialize);
}

