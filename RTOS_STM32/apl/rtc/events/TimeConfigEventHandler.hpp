#ifndef TIMECONFIGEVENTHANDLER_HPP
#define TIMECONFIGEVENTHANDLER_HPP

#include "EventHandler.hpp"
#include "foundation/HWman/rtc.hpp"

namespace RTC_Handler
{

class TimeConfigEventHandler : public EventHandler
{
public:
    /**
     * \brief Construct TimeConfigEventHandler with RTC handler pointer.
     * \details Stores the pointer for use in event handling.
     * \input handler Pointer to RTCHandler instance.
     * \output None
     * \note Used by RTCMonitor to delegate TIMECONFIG events.
     */
    explicit TimeConfigEventHandler(ComplexDriver::RTCHandler* handler):m_rtcHandler{handler}
    {}

    /**
     * \brief Handle TIMECONFIG RTC configuration event.
     * \details Sets the RTC time using the provided configuration data.
     * \input configData RTC configuration data structure.
     * \output None
     * \note Called by RTCMonitor when TIMECONFIG event is received.
     */
    void handleEvent(const Port::RTCConfigDataInf& configData) override;

private:
    ComplexDriver::RTCHandler* m_rtcHandler;
};

} // namespace RTC_Handler

#endif

