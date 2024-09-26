#include "task.hpp"

namespace Task
{
  TaskHandle_t taskHandle1 = static_cast<TaskHandle_t>(pvPortMalloc(sizeof(TaskHandle_t)));
  TaskHandle_t taskHandle2 = static_cast<TaskHandle_t>(pvPortMalloc(sizeof(TaskHandle_t)));
  
  static void task1Run(void* param)
  {
    while(1)
    {
      printf("Hello from task %d \n", 1U); 

    }
  }

  static void task2Run(void* param)
  {
    while(1)
    {
      printf("Hello from task %d \n", 2U); 
    }
  }

  BaseType_t createTasks(void)
  {
    BaseType_t result{pdPASS};

    result = xTaskCreate(task1Run, "task 1", 200U, NULL, 0U, &taskHandle1);

    configASSERT(result == pdPASS);

    result = xTaskCreate(task2Run, "task 2", 200U, NULL, 0U, &taskHandle2);

    return result;
  }
}
