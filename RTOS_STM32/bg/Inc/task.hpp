#ifndef __TASK_HPP__
#define __TASK_HPP__

#include "utils.hpp"

namespace Task
{
  BaseType_t createTasks(void); 
  extern TaskHandle_t taskHandle1;
  extern TaskHandle_t taskHandle2;
}//End of namespace Task
#endif
