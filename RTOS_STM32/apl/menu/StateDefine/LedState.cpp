#include "LedState.hpp"
#include "MenuSenderPort.hpp"

#include "MenuStateMachine.hpp"
#include "menu/EventHandlerDefine/SwitchToIdleEventHandler.hpp"
#include "menu/EventHandlerDefine/LedEventHandler.hpp"
namespace Menu
{
    void LedState::eventListener(const uint32_t& eventType) 
    {
        EventHandlerInf* l_eventHandler_ptr{nullptr};
        auto extractSubEventCode = [eventType](void)->uint8_t
        {
            return static_cast<uint8_t>(eventType & 0xFFU); // Extract the smallest 8 bits as the event code
        };
        ///factory method + strategy 
        switch (extractSubEventCode()) 
        {
            case static_cast<uint8_t>(LedStateSubEvent::LED_CMD_1):
            case static_cast<uint8_t>(LedStateSubEvent::LED_CMD_2):
            case static_cast<uint8_t>(LedStateSubEvent::LED_CMD_3):
            case static_cast<uint8_t>(LedStateSubEvent::LED_CMD_4):
                l_eventHandler_ptr = new LedEventHandler(eventType, extractSubEventCode());
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
        l_stateInfoReqChunk_st.m_MainStateSignal.setSignalVal(static_cast<uint8_t>(MainStateIdList::LedMenu));
        l_stateInfoReqChunk_st.m_SubStateSignal.setSignalVal(static_cast<uint8_t>(LedStateSubEvent::MAXIMUM_LED_CMD)); ///for example
    }

}//end of namespace Menu
