#include "task2.hpp"

namespace Task
{
  Task2Handler task2{3U};  //to define task2 here

  void Task2Handler::task2Run(void* param)
  {
    while(1)
    {
      //User code to do here
      task2.m_LEDHandler.blinkLED();
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
