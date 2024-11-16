#include "task1.hpp"

namespace Task
{
  Task1Handler task1{};  //to define task1 here

  void Task1Handler::task1Run(void* param)
  {
    while(1)
    {
      //User code to do here
      task1.m_LEDHandler.blinkLED();
      vTaskDelay(task1.m_taskCycle_ms); 
    }
  }

  void Task1Handler::run(void* param) 
  {
    while(1)
    {
      //User code to do here
    }
  }

}//End of namespace Task
