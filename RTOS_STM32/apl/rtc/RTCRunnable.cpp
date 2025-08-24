#include "RTCRunnable.hpp"
#include "MenuPortIntf.hpp"
#include "RTCReceiverPort.hpp"

namespace 
{
    RTC::RTCRunnable l_myRTCRunnable_st{};
}//anonymous namespace

namespace RTC
{
    RTCRunnable* g_myRTCRunnable_st{ nullptr };

    RTCRunnable::RTCRunnable(void)
    {
        g_myRTCRunnable_st = this;
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
                    // Process RTCConfigDataInf as needed
                }
            }
        }
    }

    void RTCRunnable::m_txCustomerHook(void)
    {
        /* do nothing*/
    }

    void RTCRunnable::m_customerRun(void)
    {
        // cyclic run
    }
} //end of namespace RTC


