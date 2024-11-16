#include "task1.hpp"
#include "task2.hpp"
#include "task3.hpp"

namespace Task
{
  
  BaseType_t createTasks(void)
  {
    TaskHandle_t taskHandle1{nullptr};
    TaskHandle_t taskHandle2{nullptr};
    TaskHandle_t taskHandle3{nullptr};

    BaseType_t result{pdPASS};

    result = xTaskCreate(task1.task1Run, "task 1", 200U, NULL, 2U, &taskHandle1);

    configASSERT(result == pdPASS);

    result = xTaskCreate(task2.task2Run, "task 2", 200U, NULL, 2U, &taskHandle2);

    configASSERT(result == pdPASS);

    result = xTaskCreate(task3.task3Run, "task 3", 200U, NULL, 2U, &taskHandle3);

    task1.setTaskHandle(taskHandle1);
    task2.setTaskHandle(taskHandle2);
    task3.setTaskHandle(taskHandle3);

    return result;
  }
}
