#include "task2.hpp"
#include "led/LedRunnable.hpp" //to restore when menu task is done

namespace Task
{
    Task2Handler task2{2U};  //to define task2 here

    void Task2Handler::task2Run(void* param)
    {
        task2.m_currentWakeTimeTick = xTaskGetTickCount();
        LedCom::g_myLedRunnable_st->init();
        while(1)
        {
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
