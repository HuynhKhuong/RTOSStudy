#ifndef SWITCHTOLEDEVENTHANDLER_HPP
#define SWITCHTOLEDEVENTHANDLER_HPP

#include "menu/EventDefine.hpp"
#include "menu/MenuStateMachine.hpp"
#include "menu/StateDefine/LedState.hpp"

namespace Menu
{
  class SwitchToLed: public EventHandlerInf
  {
    public:
      SwitchToLed():EventHandlerInf{static_cast<uint32_t>(EventType::LED_STATE)}
      {
        m_toSwitchState_ptr = LedState::getInstance();
        m_parentStateMachine_ptr = &g_machine_st;
      }

      ~SwitchToLed() = default;     

      void handle(void) override;

    private: 
      StateInf* m_toSwitchState_ptr;
      StateMachine* m_parentStateMachine_ptr;
      
  };
}

#endif

