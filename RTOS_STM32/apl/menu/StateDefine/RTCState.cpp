#include "RTCState.hpp"
#include "EventDefine.hpp"
#include "RTCConfigEventHandler.hpp"
#include "MenuPortIntf.hpp"
#include "MenuSenderPort.hpp"
#include "MenuReceiverPort.hpp"
#include "MenuStateMachine.hpp"
#include "SwitchToIdleEventHandler.hpp"

namespace
{
    auto convertLambda = [](uint8_t retrieveVal_u8) -> Menu::RTCConfigOption
    {
        switch (retrieveVal_u8)
        {
            case static_cast<uint8_t>(Menu::RTCConfigOption::TIMECONFIG):
                return Menu::RTCConfigOption::TIMECONFIG;
            case static_cast<uint8_t>(Menu::RTCConfigOption::DATECONFIG):
                return Menu::RTCConfigOption::DATECONFIG;
            default:
                return Menu::RTCConfigOption::MAXCONFIG;
        }
    };
} //anonymous namespace

namespace Menu
{
    void RTCState::eventListener(const uint32_t& eventType)
    {
        EventHandlerInf* l_eventHandler_ptr{ nullptr };
        /* Factory method + strategy opting */
        static_cast<void>(eventType);

        if (Port::g_menuRTCConfigReceiverPort_st.isConnected())
        {
            if (Port::g_menuRTCConfigReceiverPort_st.hasNewData())
            {
                static_cast<void>(Port::g_menuRTCConfigReceiverPort_st.update());
                const Port::RTCReqInf* l_RTCReqInf_pst = Port::g_menuRTCConfigReceiverPort_st.getData();

                if (l_RTCReqInf_pst != nullptr)
                {
                    uint8_t retrieveVal_u8{ 0U };
                    l_RTCReqInf_pst->m_RTCRequest.getPhysVal(retrieveVal_u8);
                    RTCConfigOption configOption = convertLambda(retrieveVal_u8);

                    if (configOption == RTCConfigOption::MAXCONFIG)
                    {
                        l_eventHandler_ptr = new SwitchToIdle();
                    }
                    else
                    {
                        RTCConfigEventHandler* l_localEventHandler_ptr = new RTCConfigEventHandler(eventType);
                        {
                            l_localEventHandler_ptr->setRTCConfigMode(configOption);
                        }
                        {
                            uint8_t retrieveDateVal_u8{ 0U };
                            uint8_t retrieveMonthVal_u8{ 0U };
                            uint16_t retrieveYearVal_u16{ 0U };
                            l_RTCReqInf_pst->m_year.getPhysVal(retrieveYearVal_u16);
                            l_RTCReqInf_pst->m_month.getPhysVal(retrieveMonthVal_u8);
                            l_RTCReqInf_pst->m_day.getPhysVal(retrieveDateVal_u8);

                            l_localEventHandler_ptr->setRTCDateInfo(DateInfo{ retrieveYearVal_u16, retrieveMonthVal_u8, retrieveDateVal_u8 });
                        }
                        {
                            uint8_t retrieveSecondsVal_u8{ 0U };
                            uint8_t retrieveMinuteVal_u8{ 0U };
                            uint8_t retrieveHourVal_u8{ 0U };
                            l_RTCReqInf_pst->m_hour.getPhysVal(retrieveHourVal_u8);
                            l_RTCReqInf_pst->m_minute.getPhysVal(retrieveMinuteVal_u8);
                            l_RTCReqInf_pst->m_second.getPhysVal(retrieveSecondsVal_u8);

                            l_localEventHandler_ptr->setRTCTimeInfo(TimeInfo{ retrieveHourVal_u8, retrieveMinuteVal_u8, retrieveSecondsVal_u8 });
                        }
                        l_eventHandler_ptr = static_cast<EventHandlerInf*>(l_localEventHandler_ptr);
                    }

                    l_eventHandler_ptr->handle();
                }
            }
        }

        delete(l_eventHandler_ptr);
    }

    void RTCState::run(void)
    {
        /* cyclcic run */
    }

    void RTCState::updateState(void)
    {
        Port::StateInfoInf& l_stateInfoReqChunk_st{ Port::g_menuStateInfoSenderPort_st.reserve() };
        l_stateInfoReqChunk_st.m_MainStateSignal.setSignalVal(static_cast<uint8_t>(MainStateIdList::RTCMenu));
    }

}//end of namespace Menu

