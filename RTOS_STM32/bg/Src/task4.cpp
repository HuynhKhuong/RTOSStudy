#include "task4.hpp"
#include "task1.hpp"
#include "task2.hpp"
#include "task3.hpp"
#include "utils.hpp"

namespace Task
{
  Task4Handler task4{};  //to define task4 here
  /*
   * Example for sending notification to task 1
   */

  void Task4Handler::task4Run(void* param)
  {
      task4.m_currentWakeTimeTick = xTaskGetTickCount();
      TaskHandle_t taskHandleList[3U] = {task1.getTaskHandle(), task2.getTaskHandle(), task3.getTaskHandle()};
      uint8_t taskListIndexCount{0U};
      while(1)
      {
          //User code to do here
          task4.m_userInputHandler.queryInputFromHardware();
          if(task4.m_userInputHandler.isInputClicked() && 
              taskListIndexCount < 3U)
          {
              TaskHandle_t curTaskHandle{taskHandleList[taskListIndexCount]};
              if(curTaskHandle != nullptr)
              {
                (void)xTaskNotify(curTaskHandle, 0U, eNotifyAction::eNoAction);
              }
              taskListIndexCount++;
          }

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
