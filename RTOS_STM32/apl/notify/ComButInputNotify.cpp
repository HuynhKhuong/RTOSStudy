#include "ComBusInputNotify.hpp"
#include "MenuStateMachine.hpp"
#include "SymbolicNames.hpp"
#include "ComReceive.hpp"
#include "net/NetPortIntf.hpp"
#include "net/NetSenderPort.hpp"

namespace
{
    constexpr uint32_t mainStateIdOffset_cu32{24U};
}

namespace NetCom 
{
    void s_LEDControlMsgNotif_Rx(void)
    { 
        uint8_t signalVal_u8{0U}; 
        netComReceiveSignal(g_LEDModeReqSignal_u8, static_cast<void*>(&signalVal_u8));  
        uint32_t& reservedChunk = Port::g_netMenuSenderPort_st.reserve();

        ///\brief  main state id and the signal value is stored into the same signal as for memory optimization
        reservedChunk = (static_cast<uint32_t>(Menu::MainStateIdList::LedMenu) << mainStateIdOffset_cu32) | static_cast<uint32_t>(signalVal_u8);
    }

    void s_RTCControlMsgNotif_Rx(void)
    {
        if((Port::g_netMenuRtcConfigSenderPort_st.isConnected() == false) || 
            (Port::g_netMenuSenderPort_st.isConnected() == false))
        {
            return;
        }

        Port::RTCReqInf& reservedChunk_st = Port::g_netMenuRtcConfigSenderPort_st.reserve();
        uint32_t& reservedChunk_u32 = Port::g_netMenuSenderPort_st.reserve();

        reservedChunk_u32 = static_cast<uint32_t>(Menu::MainStateIdList::RTCMenu) << mainStateIdOffset_cu32;
        {
            uint8_t signalVal_u8{0U}; 
            netComReceiveSignal(g_RTCModeReqSignal_u8, static_cast<void*>(&signalVal_u8));
            reservedChunk_st.m_RTCRequest.setSignalVal(signalVal_u8);
        }
        {
            uint8_t signalVal_u8{0U}; 
            netComReceiveSignal(g_ReqDateSignal_u8, static_cast<void*>(&signalVal_u8));
            reservedChunk_st.m_day.setRawSignalVal(signalVal_u8);
        }
        {
            uint8_t signalVal_u8{0U}; 
            netComReceiveSignal(g_ReqMonthSignal_u8, static_cast<void*>(&signalVal_u8));
            reservedChunk_st.m_month.setSignalVal(signalVal_u8);
        }
        {
            uint16_t signalVal_u16{0U}; 
            netComReceiveSignal(g_ReqYearSignal_u16, static_cast<void*>(&signalVal_u16));
            reservedChunk_st.m_year.setSignalVal(signalVal_u16);
        }
        {
            uint8_t signalVal_u8{0U}; 
            netComReceiveSignal(g_ReqSecondsSignal_u8, static_cast<void*>(&signalVal_u8));
            reservedChunk_st.m_second.setSignalVal(signalVal_u8);
        }
        {
            uint8_t signalVal_u8{0U}; 
            netComReceiveSignal(g_ReqMinutesSignal_u8, static_cast<void*>(&signalVal_u8));
            reservedChunk_st.m_minute.setSignalVal(signalVal_u8);
        }
        {
            uint8_t signalVal_u8{0U}; 
            netComReceiveSignal(g_HoursSignal_u8, static_cast<void*>(&signalVal_u8));
            reservedChunk_st.m_hour.setSignalVal(signalVal_u8);
        }
    }
}


