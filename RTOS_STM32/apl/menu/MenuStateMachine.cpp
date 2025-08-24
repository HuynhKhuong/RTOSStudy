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
            m_currentState->eventListener(m_rawEventId_u32);
            m_isNewEvent_bo = false;
        }

        ///cyclic task invoked here
        m_currentState->run();
    }

}//end of namespace Menu

