#include "LedState.hpp"
#include "MenuSenderPort.hpp"

#include "menu/EventHandlerDefine/SwitchToIdleEventHandler.hpp"
#include "menu/EventHandlerDefine/LedEventHandler.hpp"
namespace Menu
{
  void LedState::eventListener(const uint8_t& eventType) 
  {
    EventHandlerInf* l_eventHandler_ptr{nullptr};
    ///factory method + strategy 
    switch (eventType) 
    {
      case static_cast<uint8_t>(LedStateSubEvent::LED_CMD_1):
      case static_cast<uint8_t>(LedStateSubEvent::LED_CMD_2):
      case static_cast<uint8_t>(LedStateSubEvent::LED_CMD_3):
      case static_cast<uint8_t>(LedStateSubEvent::LED_CMD_4):
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
    l_stateInfoReqChunk_st.m_MainStateSignal.setSignalVal(static_cast<uint8_t>(EventType::LED_STATE));
    l_stateInfoReqChunk_st.m_SubStateSignal.setSignalVal(static_cast<uint8_t>(LedStateSubEvent::MAXIMUM_LED_CMD)); ///for example
  }

}//end of namespace Menu
