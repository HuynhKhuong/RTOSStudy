#include "task1.hpp"

namespace Task
{
  Task1Handler task1{};  //to define task1 here

  void Task1Handler::task1Run(void* param)
  {
    task1.m_currentWakeTimeTick = xTaskGetTickCount();
    uint32_t ulNotificationValue{0U};

    while(1)
    {
      //User code to do here
      //

      xTaskNotifyWait( 0U, 0x1U, &ulNotificationValue, 0U);
      if(ulNotificationValue == 1)
      {
        vTaskDelete(task1.getTaskHandle());
      }
      else
      {
        task1.m_LEDHandler.blinkLED();
        vTaskDelayUntil(&task1.m_currentWakeTimeTick, task1.m_taskCycleTick);
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
