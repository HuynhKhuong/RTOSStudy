#ifndef TIMEDATAITF_HPP
#define TIMEDATAITF_HPP

#include "container/PortInterface.hpp"
#include <stdint.h>

namespace Port
{

class TimeDataItf : public BasePortType
{
public:
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

} // namespace RTC_Handler

#endif
