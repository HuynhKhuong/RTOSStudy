#include "task.hpp"

namespace Task
{
  TaskHandle_t taskHandle1;
  TaskHandle_t taskHandle2;
  constexpr uint8_t g_msgLength{100U};
  
  static void task1Run(void* param)
  {
    //uint32_t tickTime_u32{100}; //100 tick rate = 100ms
    char msg[g_msgLength]{0U};
    while(1)
    {
      snprintf(&msg[0U],g_msgLength,"Hello from task %d \n", 1U);
      SEGGER_SYSVIEW_PrintfTarget(msg);
      taskYIELD();
    }
  }

  static void task2Run(void* param)
  {
    //uint32_t tickTime_u32{100};
    char msg[g_msgLength]{0U};
    while(1)
    {
      snprintf(&msg[0U],g_msgLength,"Hello from task %d \n", 2U);
      SEGGER_SYSVIEW_PrintfTarget(msg);
      taskYIELD();
    }
  }

  BaseType_t createTasks(void)
  {
    BaseType_t result{pdPASS};

    result = xTaskCreate(task1Run, "task 1", 200U, NULL, 2U, &taskHandle1);

    configASSERT(result == pdPASS);

    result = xTaskCreate(task2Run, "task 2", 200U, NULL, 2U, &taskHandle2);

    return result;
  }
}
