#ifndef SWITCHTOIDLEEVENTHANDLER_HPP
#define SWITCHTOIDLEEVENTHANDLER_HPP

#include "../EventDefine.hpp"
#include "menu/MenuStateMachine.hpp"
#include "menu/StateDefine/IdleState.hpp"

namespace Menu
{
  class SwitchToIdle: public EventHandlerInf
  {
    public:
      SwitchToIdle():EventHandlerInf{static_cast<uint32_t>(EventType::SWITCH_TO_IDLE)}
      {
        m_toSwitchState_ptr = IdleState::getInstance();
        m_parentStateMachine_ptr = &g_machine_st;
      }

      ~SwitchToIdle() = default;     

      void handle(void) override;

    private: 
      StateInf* m_toSwitchState_ptr;
      StateMachine* m_parentStateMachine_ptr;
      
  };
}

#endif

