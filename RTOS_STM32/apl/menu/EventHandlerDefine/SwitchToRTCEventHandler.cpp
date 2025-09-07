#include "menu/EventHandlerDefine/SwitchToRTCEventHandler.hpp"
#include "menu/MenuStateMachine.hpp"

namespace Menu
{
  void SwitchToRTC::handle(void)
  {
    ///perform switchState
    SwitchStateEngine::switchState(m_toSwitchState_ptr, m_parentStateMachine_ptr);
  }
}

