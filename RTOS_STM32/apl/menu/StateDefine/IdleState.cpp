#include "IdleState.hpp"
#include "EventDefine.hpp"
#include "SwitchToRTCEventHandler.hpp"
#include "menu/EventHandlerDefine/SwitchToLedEventHandler.hpp"

namespace Menu
{
  void IdleState::eventListener(const uint32_t& eventType) 
  {
    EventHandlerInf* l_eventHandler_ptr{nullptr};
    auto extractEventCode = [eventType](void)->uint8_t
    {
      return eventType >> 24U;
    };

    ///factory method + strategy 
    switch (extractEventCode()) 
    {
      case static_cast<uint8_t>(EventType::LED_STATE):
      {
        l_eventHandler_ptr = new SwitchToLed();
        l_eventHandler_ptr->handle();
        break;
      }
      case static_cast<uint8_t>(EventType::RTC_STATE):
      {
        // Handle RTC state event
        l_eventHandler_ptr = new SwitchToRTC();
        l_eventHandler_ptr->handle();
        break;
      }
      default:
      {
        /* do nothing */
        break;
      }
    }

    delete(l_eventHandler_ptr);  
  }

  void IdleState::run(void)
  {
    /*
     * Perform Event Listen: API to listen to event 
     * try to put task into sleep if no event occurs
     */
  }

  void IdleState::updateState(void) 
  {
    /* Entrance Task*/
  }
}
