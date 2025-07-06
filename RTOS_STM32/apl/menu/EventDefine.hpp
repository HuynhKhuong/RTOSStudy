#ifndef EVENTDEF_HPP
#define EVENTDEF_HPP

#include <stdint.h>

namespace Menu
{

///\note This enum must adhere to the value of MainStateIdList
enum class EventType: uint32_t
{
  LED_STATE = 0U,
  RTC_STATE = 1U,
  SWITCH_TO_IDLE = 254U,
  DEFAULT = 255U
};

class EventHandlerInf
{
  public:
    explicit EventHandlerInf(uint32_t eventId):m_eventId{eventId}
    {/*do nothing*/}

    virtual ~EventHandlerInf(void) = default;
    
    virtual void handle(void)
    {/*do nothing*/}

    const uint32_t m_eventId;
};

}

#endif

