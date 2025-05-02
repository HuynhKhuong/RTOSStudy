#include "task3.hpp"
#include "menu/MenuRunnable.hpp"

namespace Task
{
  Task3Handler task3{2U};  //to define task3 here

  void Task3Handler::task3Run(void* param)
  {
    task3.m_currentWakeTimeTick = xTaskGetTickCount();
    Menu::g_myMenuRunnable_st->init();

    while(1)
    {
      //User code to do here
      Menu::g_myMenuRunnable_st->run();
      vTaskDelayUntil(&task3.m_currentWakeTimeTick, task3.m_taskCycleTick);
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
