#ifndef __TASK4_HPP__
#define __TASK4_HPP__

#include "task.hpp"

namespace Task
{
  void taskRun(void* param);

  class Task4Handler: public TaskHandler 
  {
    public: 
      Task4Handler(): TaskHandler{convertTickFromMs(10U)} //task cycle 10ms
      { }

      explicit Task4Handler(UBaseType_t taskPriority): TaskHandler{convertTickFromMs(10U), taskPriority, "Task-4"}
      { }

      void run(void* param) override;
      static void task4Run(void* param);

    private:
      UserInputHandler m_userInputHandler{GPIOA, GPIO_PIN_0};
  };

  extern Task4Handler task4; 

}//End of namespace Task

#endif
