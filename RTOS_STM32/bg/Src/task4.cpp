#include "task4.hpp"
#include "rtc/RTCRunnable.hpp"

namespace Task
{
    Task4Handler task4{2U};  //to define task4 here

    void Task4Handler::task4Run(void* param)
    {
        task4.m_currentWakeTimeTick = xTaskGetTickCount();
        RTC_Handler::g_myRTCRunnable_st->init();
        while(1)
        {
            RTC_Handler::g_myRTCRunnable_st->run();
            vTaskDelayUntil(&task4.m_currentWakeTimeTick, task4.m_taskCycleTick);
        }
    }

    void Task4Handler::run(void* param) 
    {
        while(1)
        {
            // Main function left blank for new change
        }
    }

} //End of namespace Task
  //
