#include "task2.hpp"
#include "task1.hpp"

namespace Task
{
  extern bool isInputClicked;
  Task2Handler task2{3U};  //to define task2 here

  void Task2Handler::task2Run(void* param)
  {

    while(1)
    {
        //global resource, need access block instruction
        portENTER_CRITICAL();
        const bool getInput{isInputClicked};
        portEXIT_CRITICAL();


        if(getInput) 
        {
            UBaseType_t exchangedPriority{task1.getTaskPriority()};
            UBaseType_t currentPriority{task2.getTaskPriority()};

            task2.setTaskPriority(exchangedPriority);
            task1.setTaskPriority(currentPriority);
        }

        task2.m_LEDHandler.blinkLED();
        HAL_Delay(task2.m_taskCycleTick); 
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
