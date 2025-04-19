#include "task3.hpp"

namespace Task
{
  Task3Handler task3{2U};  //to define task3 here

  void Task3Handler::task3Run(void* param)
  {

    BaseType_t NotifyResult{pdFALSE};

    while(1)
    {
      //User code to do here
      NotifyResult = xTaskNotifyWait( 0U, 0U, nullptr, 0U);
      
      if(NotifyResult == pdFALSE)
      {
        //User code to do here
        vTaskDelayUntil(&task3.m_currentWakeTimeTick, task3.m_taskCycleTick);
      }
      else
      {
        vTaskDelete(nullptr);
      }
    }
  }

  void Task3Handler::run(void* param) 
  {
    while(1)
    {
      //User code to do here
      //Obsolete, will allocate it for later use
    }
  }
}//End of namespace Task
