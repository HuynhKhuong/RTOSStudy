#include "MenuStateMachine.hpp"

namespace Menu
{
  StateMachine g_machine_st{}; 

  ///\todo  needs improvement later
  void StateMachine::run(void)
  {
    ///polling for event
    if(m_isNewEvent_bo)
    {
      EventType eventType{EventType::DEFAULT};
      switch(m_rawEventId_u32)
      {
        case static_cast<uint32_t>(EventType::LED_STATE):
        case static_cast<uint32_t>(EventType::LED_CMD_1):
        case static_cast<uint32_t>(EventType::LED_CMD_2):
        case static_cast<uint32_t>(EventType::LED_CMD_3):
        case static_cast<uint32_t>(EventType::LED_CMD_4):
        case static_cast<uint32_t>(EventType::SWITCH_TO_IDLE):
        case static_cast<uint32_t>(EventType::DEFAULT):
          eventType = static_cast<EventType>(m_rawEventId_u32);
		break;
        default:
          /*do nothing*/
        break;
      }

      m_currentState->eventListener(eventType);

      m_isNewEvent_bo = false;
    }

    ///cyclic task invoked here
    m_currentState->run();
  }

}//end of namespace Menu

