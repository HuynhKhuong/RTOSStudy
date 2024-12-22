#include "task4.hpp"

namespace Task
{
  Task4Handler task4{};  //to define task4 here

  void Task4Handler::task4Run(void* param)
  {
    task4.m_currentWakeTimeTick = xTaskGetTickCount();

    while(1)
    {
      //User code to do here
      vTaskDelayUntil(&task4.m_currentWakeTimeTick, task4.m_taskCycleTick);
    }
  }

  void Task4Handler::run(void* param) 
  {
    while(1)
    {
      //User code to do here
      //Obsolete, will allocate it for later use
    }
  }

}//End of namespace Task
