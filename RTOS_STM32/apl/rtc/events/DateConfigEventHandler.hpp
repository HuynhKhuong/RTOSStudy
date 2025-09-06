#ifndef DATECONFIGEVENTHANDLER_HPP
#define DATECONFIGEVENTHANDLER_HPP

#include "EventHandler.hpp"
#include "foundation/HWman/rtc.hpp"

namespace RTC_Handler
{

class DateConfigEventHandler : public EventHandler
{
public:
    /**
     * \brief Construct DateConfigEventHandler with RTC handler pointer.
     * \details Stores the pointer for use in event handling.
     * \input handler Pointer to RTCHandler instance.
     * \output None
     * \note Used by RTCMonitor to delegate DATECONFIG events.
     */
    explicit DateConfigEventHandler(ComplexDriver::RTCHandler* handler):m_rtcHandler{handler}
    {}

    /**
     * \brief Handle DATECONFIG RTC configuration event.
     * \details Sets the RTC date using the provided configuration data.
     * \input configData RTC configuration data structure.
     * \output None
     * \note Called by RTCMonitor when DATECONFIG event is received.
     */
    void handleEvent(const Port::RTCConfigDataInf& configData) override;

private:
    ComplexDriver::RTCHandler* m_rtcHandler;
};

} // namespace RTC_Handler

#endif

