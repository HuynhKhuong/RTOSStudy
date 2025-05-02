#include "IdleState.hpp"
#include "menu/EventHandlerDefine/SwitchToLedEventHandler.hpp"
namespace Menu
{
  void IdleState::eventListener(const EventType& eventType) 
  {
    EventHandlerInf* l_eventHandler_ptr{nullptr};
    ///factory method + strategy 
    static_cast<void>(eventType);
    l_eventHandler_ptr = new SwitchToLed();
    l_eventHandler_ptr->handle();
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
