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

        BaseType_t result{pdFAIL};

        result = xTaskCreate(task1.task1Run, task1.getTaskName(), 200U, NULL, task1.getTaskPriority(), &taskHandle1);

        configASSERT(result == pdPASS);

        result = xTaskCreate(task2.task2Run, task2.getTaskName(), 200U, NULL, task2.getTaskPriority(), &taskHandle2);

        configASSERT(result == pdPASS);

        result = xTaskCreate(task3.task3Run, task3.getTaskName(), 200U, NULL, task3.getTaskPriority(), &taskHandle3);

        configASSERT(result == pdPASS);

        result = xTaskCreate(task4.task4Run, task4.getTaskName(), 200U, NULL, task4.getTaskPriority(), &taskHandle4);

        configASSERT(result == pdPASS);

        task1.setTaskHandle();
        task2.setTaskHandle();
        task3.setTaskHandle();
        task4.setTaskHandle();

        return result;
    }
}
