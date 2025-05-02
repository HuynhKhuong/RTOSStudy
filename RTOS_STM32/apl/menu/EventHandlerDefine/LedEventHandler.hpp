#ifndef LEDEVENTHANDLER_HPP
#define LEDEVENTHANDLER_HPP

#include "../EventDefine.hpp"

namespace Menu
{
  class LedEventHandler: public EventHandlerInf
  {
    public:
      LedEventHandler(uint32_t eventId):EventHandlerInf{eventId} 
      {/*do nothing*/}

      ~LedEventHandler() = default;

      void setLedMode(const uint8_t ledMode_u8)
      {
        m_ledMode_u8 = ledMode_u8;
      }

      void handle(void) override;

    private: 
      uint8_t m_ledMode_u8{0U};
      //m_triggerPort_st;
  };
}

#endif

