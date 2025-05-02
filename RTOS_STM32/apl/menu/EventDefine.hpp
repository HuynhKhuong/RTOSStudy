#ifndef EVENTDEF_HPP
#define EVENTDEF_HPP

#include <stdint.h>

namespace Menu
{

enum class EventType: uint8_t
{
  LED_STATE = 0U,
  LED_CMD_1 = 1U,
  LED_CMD_2 = 2U,
  LED_CMD_3 = 3U,
  LED_CMD_4 = 4U,
  SWITCH_TO_IDLE = 5U,
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

