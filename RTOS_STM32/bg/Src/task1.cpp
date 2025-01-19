#include "task1.hpp"
#include "portmacro.h"
#include "task2.hpp"
#include "stm32f4xx_hal.h"

namespace Task
{
  extern bool isInputClicked;

  Task1Handler task1{2U};  //to define task1 here

  void Task1Handler::task1Run(void* param)
  {
    task1.m_currentWakeTimeTick = xTaskGetTickCount();

    while(1)
    {
        //global resource, need access block instruction
        portENTER_CRITICAL();
        const bool getInput{isInputClicked};
        portEXIT_CRITICAL();


        if(getInput) 
        {
            UBaseType_t exchangedPriority{task2.getTaskPriority()};
            UBaseType_t currentPriority{task1.getTaskPriority()};

            task1.setTaskPriority(exchangedPriority);
            task2.setTaskPriority(currentPriority);
        }

        task1.m_LEDHandler.blinkLED();
        HAL_Delay(task1.m_taskCycleTick); 
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
