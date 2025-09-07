#include "SwitchToIdleEventHandler.hpp"

namespace Menu
{
  void SwitchToIdle::handle(void)
  {
    ///perform switchState
    SwitchStateEngine::switchState(m_toSwitchState_ptr, m_parentStateMachine_ptr);
  }
}

