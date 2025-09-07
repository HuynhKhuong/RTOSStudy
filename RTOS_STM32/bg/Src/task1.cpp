#include "task1.hpp"
#include "ProtocolMCAL.hpp"
#include "net/NetRunnable.hpp"

extern "C"
{
#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "stm32f4xx_hal.h"
}

extern QueueHandle_t g_taskIdQueueCont_ptr; 
extern SemaphoreHandle_t g_taskIdSemprSignal_ptr;

namespace Task
{

    Task1Handler task1{3U};  //to define task1 here
    
    void Task1Handler::task1Run(void* param)
    {
        uint8_t s_staticTaskId_u8{0U};

        task1.m_currentWakeTimeTick = xTaskGetTickCount();
        NetCom::g_myNetRunnable_st->init();
        static_cast<void>(xSemaphoreGive(g_taskIdSemprSignal_ptr));
        while(1)
        {
            //NetCom::g_myNetRunnable_st->run(); 
            uint8_t l_randomTaskId_u8{s_staticTaskId_u8++};
            BaseType_t retVal{pdFAIL};

            retVal = xQueueSend(g_taskIdQueueCont_ptr, static_cast<const void*>(&l_randomTaskId_u8), portMAX_DELAY);
            if(retVal != pdTRUE)
            {
                //Failed to post the message
            }
            else
            {
                xSemaphoreGive(g_taskIdSemprSignal_ptr);
                taskYIELD(); //Exercise7: task manager is intended to yield control to task employee right after generating taskID
            }
            
            //Exercise7: task manager is intended to yield control to task employee right after generating taskID
            //vTaskDelayUntil(&task1.m_currentWakeTimeTick, task1.m_taskCycleTick);
        }
    }

    void Task1Handler::run(void* param) 
    {
        while(1)
        {
            //User code to do here
            //\todo Obsolete, will allocate it for later use
        }
    }

}//End of namespace Task
