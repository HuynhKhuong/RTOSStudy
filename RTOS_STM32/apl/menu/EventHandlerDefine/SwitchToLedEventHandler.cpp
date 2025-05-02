#include "menu/EventHandlerDefine/SwitchToLedEventHandler.hpp"
#include "menu/MenuStateMachine.hpp"

namespace Menu
{
  void SwitchToLed::handle(void)
  {
    ///perform switchState
    SwitchStateEngine::switchState(m_toSwitchState_ptr, m_parentStateMachine_ptr);
  }
}

