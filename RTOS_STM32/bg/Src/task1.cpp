#include "task1.hpp"
#include "stm32f4xx_hal.h"

namespace Task
{
  Task1Handler task1{2U};  //to define task1 here

  void Task1Handler::task1Run(void* param)
  {
    task1.m_currentWakeTimeTick = xTaskGetTickCount();
    BaseType_t NotifyResult{pdFALSE};

    while(1)
    {
      //User code to do here
      NotifyResult = xTaskNotifyWait( 0U, 0U, nullptr, 0U);
      
      if(NotifyResult == pdFALSE)
      {
        task1.m_LEDHandler.blinkLED();
        HAL_Delay(task1.m_taskCycleTick); 
        //vTaskDelayUntil(&task1.m_currentWakeTimeTick, task1.m_taskCycleTick);
      }
      else
      {
        vTaskDelete(nullptr);
      }
    }
  }

  void Task1Handler::run(void* param) 
  {
    while(1)
    {
      //User code to do here
      //Obsolete, will allocate it for later use
    }
  }

}//End of namespace Task
