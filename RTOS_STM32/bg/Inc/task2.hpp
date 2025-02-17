#ifndef __TASK2_HPP__
#define __TASK2_HPP__

#include "task.hpp"

namespace Task
{
  class Task2Handler: public TaskHandler 
  {
    public: 
      Task2Handler():TaskHandler{convertTickFromMs(800U)}
      { }
      
      explicit Task2Handler(UBaseType_t taskPriority): TaskHandler{convertTickFromMs(800U), taskPriority, "Task-2"}
      { }
      static void task2Run(void* param);
      void run(void* param) override;

    private:
      LEDHandler m_LEDHandler{GPIOD, GPIO_PIN_13};
  };

  extern Task2Handler task2; 

}//End of namespace Task

#endif
