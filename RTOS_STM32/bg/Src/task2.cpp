#include "task2.hpp"

namespace Task
{
  Task2Handler task2{3U};  //to define task2 here

  void Task2Handler::task2Run(void* param)
  {

    BaseType_t NotifyResult{pdFALSE};

    while(1)
    {
      //User code to do here
      NotifyResult = xTaskNotifyWait( 0U, 0U, nullptr, 0U);
      
      if(NotifyResult == pdFALSE)
      {
        //User code to do here
        task2.m_LEDHandler.blinkLED();
        HAL_Delay(task2.m_taskCycleTick); 
        //vTaskDelayUntil(&task2.m_currentWakeTimeTick, task2.m_taskCycleTick);
      }
      else
      {
        vTaskDelete(nullptr);
      }
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
