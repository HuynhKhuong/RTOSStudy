#include "task.hpp"

namespace Task
{
  TaskHandle_t taskHandle1;
  TaskHandle_t taskHandle2;
  
  static void task1Run(void* param)
  {
    //uint32_t tickTime_u32{100}; //100 tick rate = 100ms
    while(1)
    {
      printf("Hello from task %d \n", 1U); 
      //vTaskDelay(tickTime_u32);
    }
  }

  static void task2Run(void* param)
  {
    //uint32_t tickTime_u32{100};
    while(1)
    {
      printf("Hello from task %d \n", 2U); 
      //vTaskDelay(tickTime_u32);
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
