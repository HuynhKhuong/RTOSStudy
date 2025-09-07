#include "task2.hpp"
#include "led/LedRunnable.hpp" //to restore when menu task is done
                               
extern "C"
{
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "stm32f4xx_hal.h"
}

extern UART_HandleTypeDef huart2;
extern QueueHandle_t g_taskIdQueueCont_ptr; 
extern SemaphoreHandle_t g_taskIdSemprSignal_ptr;

namespace Task
{
    Task2Handler task2{1U};  //to define task2 here

    void Task2Handler::task2Run(void* param)
    {
        task2.m_currentWakeTimeTick = xTaskGetTickCount();
        LedCom::g_myLedRunnable_st->init();

        while(1)
        {
            BaseType_t getSemphrRetVal_u8{xSemaphoreTake(g_taskIdSemprSignal_ptr, 0U)};
            if(getSemphrRetVal_u8 == pdTRUE)
            {
                uint8_t l_receivedTaskId_u8{0U};
                BaseType_t getQueueRetVal_u8{xQueueReceive(g_taskIdQueueCont_ptr, static_cast<void* const>(&l_receivedTaskId_u8), 0U)};
                if(getQueueRetVal_u8 == pdTRUE)
                {
                    ///do something with received TaskID
                    HAL_UART_Transmit_IT(&huart2, &l_receivedTaskId_u8, 1U);
                }
                else
                {
                    /// report failure here
                }
            }
            else
            {
                /// report failure here
            }
            //LedCom::g_myLedRunnable_st->run();
            vTaskDelayUntil(&task2.m_currentWakeTimeTick, task2.m_taskCycleTick);
        }
    }

    void Task2Handler::run(void* param) 
    {
        while(1)
        {
            //User code to do here
            //Obsolete, will allocate it for later use
        }
    }
}//End of namespace Task
