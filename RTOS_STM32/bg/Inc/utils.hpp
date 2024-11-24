#ifndef __UTILS_HPP__
#define __UTILS_HPP__

extern "C"
{
  #include <stdio.h>
  #include "FreeRTOS.h"
  #include "task.h"
  #include "stm32f4xx_hal.h"
}


constexpr TickType_t convertTickFromMs(uint32_t miliSec)
{
  return miliSec/portTICK_PERIOD_MS;
}

#endif
