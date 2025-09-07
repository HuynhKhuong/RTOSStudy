#ifndef __TASK1_HPP__
#define __TASK1_HPP__

#include "task.hpp"

namespace Task
{
  void taskRun(void* param);

  class Task1Handler: public TaskHandler 
  {
    public: 
      Task1Handler(): TaskHandler{convertTickFromMs(10U)}
      { }

      explicit Task1Handler(UBaseType_t taskPriority): TaskHandler{convertTickFromMs(10U), taskPriority, "Task-1"}
      { }

      void run(void* param) override;
      static void task1Run(void* param);
  };

  extern Task1Handler task1; 

}//End of namespace Task

#endif
