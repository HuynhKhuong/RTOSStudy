#ifndef RTCMONITOR_HPP
#define RTCMONITOR_HPP

#include "RTCReceiverPort.hpp"
#include "foundation/HWman/rtc.hpp"

namespace RTC_Handler
{

class RTCMonitor
{
public:
    /**
     * \brief Construct RTCMonitor with optional RTC instance index.
     * \details Does not initialize RTC handler; call initRTCHandler() before use.
     * \input idx RTC instance index (default: ComplexDriver::RTCInstanceIdx::RTC_0)
     * \output None
     * \note Constructor is called when RTCMonitor is instantiated in the runnable context.
     *
    */
    RTCMonitor()=default;

    /*
     * \brief Initialize the RTC handler for the specified instance.
     * \details Retrieves and stores the RTC handler pointer for the given index.
     * \input idx RTC instance index (default: ComplexDriver::RTCInstanceIdx::RTC_0)
     * \output None
     * \note Should be called from RTCRunnable::init() to ensure proper initialization order.
     */
    void initRTCHandler(ComplexDriver::RTCInstanceIdx idx = ComplexDriver::RTCInstanceIdx::RTC_0);

    /**
     * \brief Perform periodic RTC monitoring tasks.
     * \details Intended for cyclic operations such as status checks or updates.
     * \input None
     * \output None
     * \note Called from RTCRunnable::m_customerRun() in the runnable's cyclic context.
     */
    void runPeriodic();

    /**
     * \brief Handle incoming RTC configuration events.
     * \details Delegates event handling to the appropriate strategy based on configOption.
     * \input configData RTC configuration data structure
     * \output None
     * \note Called from RTCRunnable::m_rxCustomerHook() when new RTC config data is received.
     */
    void onEvent(const Port::RTCConfigDataInf& configData);

    void enableReportRequest() { m_reportRequested = true; }
    void disableReportRequest() { m_reportRequested = false; }

private:
    ComplexDriver::RTCHandler* m_rtcHandler{nullptr};
    RTC_TimeTypeDef m_lastTime{};
    RTC_DateTypeDef m_lastDate{};
    bool m_reportRequested{false};
};

} ///end of namespace RTC_Handler

#endif
