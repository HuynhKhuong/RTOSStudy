#include "task4.hpp"
#include "task.hpp"
#include "task1.hpp"
#include "task2.hpp"
#include "utils.hpp"

namespace Task
{
  Task4Handler task4{2U};  //to define task4 here
  /*
   * Example for sending notification to task 1
   */

  void Task4Handler::task4Run(void* param)
  {
      task4.m_currentWakeTimeTick = xTaskGetTickCount();
      TaskHandler* taskHandleList[2U] = {&task1, &task2}; 
      UBaseType_t taskPriorityList[2U] = {task1.getTaskPriority(), task2.getTaskPriority()};
      uint8_t taskListIndexCount{0U};

      while(1)
      {
          //User code to do here
          task4.m_userInputHandler.queryInputFromHardware();
          if(task4.m_userInputHandler.isInputClicked())
          {
              switchVal<UBaseType_t>(taskPriorityList[0U], taskPriorityList[1U]);
              vTaskSuspendAll();
              while (taskListIndexCount < 2U) 
              {
                taskHandleList[taskListIndexCount]->setTaskPriority(taskPriorityList[taskListIndexCount]);
                taskListIndexCount++;
              }
              taskListIndexCount = 0;
              xTaskResumeAll();
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
