#include "task2.hpp"

namespace Task
{
  Task2Handler task2{};  //to define task2 here

  void Task2Handler::task2Run(void* param)
  {
    while(1)
    {
      task2.m_LEDHandler.blinkLED();
      vTaskDelay(task2.m_taskCycle_ms);
    }
  }

  void Task2Handler::run(void* param) 
  {
    while(1)
    {
      //User code to do here
    }
  }
}//End of namespace Task
