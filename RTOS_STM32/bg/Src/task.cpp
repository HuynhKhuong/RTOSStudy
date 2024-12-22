#include "task1.hpp"
#include "task2.hpp"
#include "task3.hpp"
#include "task4.hpp"

namespace //unknown namespace
{
  TaskHandle_t taskHandle1{nullptr};
  TaskHandle_t taskHandle2{nullptr};
  TaskHandle_t taskHandle3{nullptr};
  TaskHandle_t taskHandle4{nullptr};
}

namespace Task
{
  BaseType_t createTasks(void)
  {

    BaseType_t result{pdPASS};

    result = xTaskCreate(task1.task1Run, "task 1", 200U, NULL, 2U, &taskHandle1);

    configASSERT(result == pdPASS);

    result = xTaskCreate(task2.task2Run, "task 2", 200U, NULL, 2U, &taskHandle2);

    configASSERT(result == pdPASS);

    result = xTaskCreate(task3.task3Run, "task 3", 200U, NULL, 2U, &taskHandle3);

    configASSERT(result == pdPASS);

    result = xTaskCreate(task4.task4Run, "task 4", 200U, NULL, 2U, &taskHandle4);

    configASSERT(result == pdPASS);

    task1.setTaskHandle(taskHandle1);
    task2.setTaskHandle(taskHandle2);
    task3.setTaskHandle(taskHandle3);
    task4.setTaskHandle(taskHandle4);

    return result;
  }
}
