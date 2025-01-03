#ifndef __UTILS_HPP__
#define __UTILS_HPP__

extern "C"
{
  #include <stdio.h>
  #include "FreeRTOS.h"
  #include "task.h"
  #include "stm32f4xx_hal.h"
}

#include<type_traits>

constexpr TickType_t convertTickFromMs(uint32_t miliSec)
{
  return miliSec/portTICK_PERIOD_MS;
}

template<typename ParamType>
inline void switchVal(ParamType& param1, ParamType& param2)
{
  static_assert(std::is_arithmetic<ParamType>::value == true, "parameter type error");

  ParamType tempVal = param1;
  param1 = param2;
  param2 = tempVal;
}

#endif
