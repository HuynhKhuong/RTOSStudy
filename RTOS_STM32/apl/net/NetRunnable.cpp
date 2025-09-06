#include "NetRunnable.hpp"
#include "ComTransmit.hpp"
#include "MenuPortIntf.hpp"
#include "NetSenderPort.hpp"
#include "NetReceiverPort.hpp"
#include "SymbolicNames.hpp"
#include "net/ComQuery.hpp"
#include "rtc/TimeDataItf.hpp"

//extern void wrapperCallHUARTTransmit(const uint8_t*, uint8_t); // Call the wrapper function to transmit data

namespace 
{
    NetCom::NetRunnable l_myNetRunnable_st{};
} // anonymous namespace

namespace NetCom
{
    RunnableInf* g_myNetRunnable_st{nullptr};

    NetRunnable::NetRunnable(void)
    {
        g_myNetRunnable_st = static_cast<RunnableInf*>(this);
    }

    void NetRunnable::m_rxCustomerHook(void) 
    {
        if(Port::g_netStateInfoReceiverPort_st.isConnected())
        {
            if(Port::g_netStateInfoReceiverPort_st.hasNewData())
            {
                uint8_t l_subStateSignalRaw_u8{0U};
                uint8_t l_mainStateSignalRaw_u8{0U};
                uint8_t l_stateSignalRaw_u8{0U};
                static_cast<void>(Port::g_netStateInfoReceiverPort_st.update());
                const Port::StateInfoInf* l_Data_ptr = Port::g_netStateInfoReceiverPort_st.getData();

                l_Data_ptr->m_SubStateSignal.getRawVal(l_subStateSignalRaw_u8);
                l_Data_ptr->m_MainStateSignal.getRawVal(l_mainStateSignalRaw_u8);
                l_stateSignalRaw_u8 = static_cast<uint8_t>(l_mainStateSignalRaw_u8 << 2U) | l_subStateSignalRaw_u8;

                NetCom::netComSendSignal(g_CurrentStateSignal_u8, static_cast<void*>(&l_stateSignalRaw_u8)); 
            }
        }

        if(Port::g_netTimeDataReceiverPort_st.isConnected())
        {
            if(Port::g_netTimeDataReceiverPort_st.hasNewData())
            {
                static_cast<void>(Port::g_netTimeDataReceiverPort_st.update());
                const Port::TimeDataItf* l_Data_ptr = Port::g_netTimeDataReceiverPort_st.getData();
                {
                    uint8_t l_tempHourVal_u8{l_Data_ptr->hour};
                    NetCom::netComSendSignal(g_HoursSignal_u8, static_cast<void*>(&l_tempHourVal_u8)); 
                }
                {
                    uint8_t l_tempMinVal_u8{l_Data_ptr->minute};
                    NetCom::netComSendSignal(g_MinutesSignal_u8, static_cast<void*>(&l_tempMinVal_u8)); 
                }
                {
                    uint8_t l_tempSecVal_u8{l_Data_ptr->second};
                    NetCom::netComSendSignal(g_SecondsSignal_u8, static_cast<void*>(&l_tempSecVal_u8)); 
                }
            }
        }
    }

    void NetRunnable::m_txCustomerHook(void) 
    {
        Port::g_netMenuSenderPort_st.deliver();
        Port::g_netMenuRtcConfigSenderPort_st.deliver();
    }

    void NetRunnable::m_customerRun(void) 
    {
        netComTxMainFunction();
        netComRxMainFunction();
    }
} // end of namespace NetCom
