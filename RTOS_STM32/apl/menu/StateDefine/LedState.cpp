#include "LedState.hpp"
#include "MenuSenderPort.hpp"

#include "menu/EventHandlerDefine/SwitchToIdleEventHandler.hpp"
#include "menu/EventHandlerDefine/LedEventHandler.hpp"
namespace Menu
{
  void LedState::eventListener(const EventType& eventType) 
  {
    EventHandlerInf* l_eventHandler_ptr{nullptr};
    ///factory method + strategy 
    switch (eventType) 
    {
      case EventType::LED_STATE:
        l_eventHandler_ptr = new EventHandlerInf(static_cast<uint8_t>(EventType::DEFAULT)); ///dummy value, to be re-defined 
        break;
      case EventType::LED_CMD_1:
      case EventType::LED_CMD_2:
      case EventType::LED_CMD_3:
      case EventType::LED_CMD_4:
        l_eventHandler_ptr = new LedEventHandler(static_cast<uint8_t>(eventType), static_cast<uint8_t>(eventType));
        break;
      default: 
        l_eventHandler_ptr = new SwitchToIdle();
        break;
    }

    l_eventHandler_ptr->handle();
    delete(l_eventHandler_ptr);  
  }

  void LedState::run(void) 
  {/*cyclic run*/}

  void LedState::updateState(void) 
  {
    Port::StateInfoInf& l_stateInfoReqChunk_st{Port::g_menuStateInfoSenderPort_st.reserve()};
  }

}//end of namespace Menu
