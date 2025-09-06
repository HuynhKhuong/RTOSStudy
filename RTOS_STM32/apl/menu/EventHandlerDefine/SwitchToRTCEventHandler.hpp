#ifndef SWITCHTORTCEVENTHANDLER_HPP
#define SWITCHTORTCEVENTHANDLER_HPP

#include "menu/EventDefine.hpp"
#include "menu/MenuStateMachine.hpp"
#include "menu/StateDefine/RTCState.hpp"

namespace Menu
{
    class SwitchToRTC : public EventHandlerInf
    {
        public:
            SwitchToRTC() : EventHandlerInf{static_cast<uint32_t>(EventType::LED_STATE)}
            {
                m_toSwitchState_ptr = RTCState::getInstance();
                m_parentStateMachine_ptr = &g_machine_st;
            }

            ~SwitchToRTC() = default;

            void handle(void) override;

        private:
            StateInf* m_toSwitchState_ptr;
            StateMachine* m_parentStateMachine_ptr;
    };
}

#endif
