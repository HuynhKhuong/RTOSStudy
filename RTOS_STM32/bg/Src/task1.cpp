#include "task1.hpp"
#include "stm32f4xx_hal.h"
#include "net/NetRunnable.hpp"

namespace Task
{

    Task1Handler task1{2U};  //to define task1 here

    void Task1Handler::task1Run(void* param)
    {
        task1.m_currentWakeTimeTick = xTaskGetTickCount();
        NetCom::g_myNetRunnable_st->init();
        
        while(1)
        {
            NetCom::g_myNetRunnable_st->run();
            vTaskDelayUntil(&task1.m_currentWakeTimeTick, task1.m_taskCycleTick);
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
