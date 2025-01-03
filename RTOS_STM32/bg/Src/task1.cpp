#include "task1.hpp"
#include "stm32f4xx_hal.h"

namespace Task
{
  Task1Handler task1{2U};  //to define task1 here

  void Task1Handler::task1Run(void* param)
  {
    task1.m_currentWakeTimeTick = xTaskGetTickCount();

    while(1)
    {
      //User code to do here
      task1.m_LEDHandler.blinkLED();
      vTaskDelayUntil(&task1.m_currentWakeTimeTick, task1.m_taskCycleTick);
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
