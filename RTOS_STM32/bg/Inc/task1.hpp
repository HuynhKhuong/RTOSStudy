#ifndef __TASK1_HPP__
#define __TASK1_HPP__

#include "task.hpp"

namespace Task
{
  void taskRun(void* param);

  class Task1Handler: public TaskHandler 
  {
    public: 
      Task1Handler(): TaskHandler{1000U}
      { }

      void run(void* param) override;
      static void task1Run(void* param);

    private:
      LEDHandler m_LEDHandler{GPIOD, GPIO_PIN_12};
  };

  extern Task1Handler task1; 

}//End of namespace Task

#endif
