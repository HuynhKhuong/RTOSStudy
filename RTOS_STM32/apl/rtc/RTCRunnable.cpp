#include "RTCRunnable.hpp"
#include "MenuPortIntf.hpp"
#include "RTCReceiverPort.hpp"
#include "RTCSenderPort.hpp"
#include "RTCMonitor.hpp"

namespace 
{
    RTC_Handler::RTCRunnable l_myRTCRunnable_st{};
    RTC_Handler::RTCMonitor g_rtcMonitor{};
}//anonymous namespace
 
namespace RTC_Handler
{
    RTCRunnable* g_myRTCRunnable_st{ nullptr };

    RTCRunnable::RTCRunnable(void)
    {
        g_myRTCRunnable_st = this;
    }

    void RTCRunnable::init(void)
    {
        g_rtcMonitor.initRTCHandler();
    }

    void RTCRunnable::m_rxCustomerHook(void)
    {
        if (Port::g_rtcConfigDataReceiverPort_st.isConnected())
        {
            if (Port::g_rtcConfigDataReceiverPort_st.hasNewData())
            {
                static_cast<void>(Port::g_rtcConfigDataReceiverPort_st.update());
                const Port::RTCConfigDataInf* l_data_pst = Port::g_rtcConfigDataReceiverPort_st.getData();
                if (l_data_pst != nullptr)
                {
                    g_rtcMonitor.onEvent(*l_data_pst);
                }
            }
        }
    }

    void RTCRunnable::m_txCustomerHook(void)
    {
        Port::g_rtcTimeDataSenderPort_st.deliver();
    }
    

    void RTCRunnable::m_customerRun(void)
    {
        // cyclic run
        g_rtcMonitor.runPeriodic();
    }
} //end of namespace RTC_Handler

