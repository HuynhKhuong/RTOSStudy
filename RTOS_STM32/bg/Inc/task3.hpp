#ifndef __TASK3_HPP__
#define __TASK3_HPP__

#include "task.hpp"

namespace Task
{
  class Task3Handler: public TaskHandler 
  {
    public: 
      Task3Handler():TaskHandler{400U}
      { }

      void run(void* param) override;
      static void task3Run(void* param);

    private:
      LEDHandler m_LEDHandler{GPIOD, GPIO_PIN_14};
  };

  extern Task3Handler task3; 

}//End of namespace Task

#endif
