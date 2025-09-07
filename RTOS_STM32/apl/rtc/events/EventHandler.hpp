#ifndef EVENTHANDLER_HPP_INCLUDED
#define EVENTHANDLER_HPP_INCLUDED

#include "../RTCReceiverPort.hpp"

namespace RTC_Handler
{
    class EventHandler
    {
    public:
        EventHandler() = default;
        virtual ~EventHandler() = default;
        EventHandler(const EventHandler&) = delete;
        EventHandler(EventHandler&&) = delete;
        EventHandler& operator=(const EventHandler&) = delete;
        EventHandler& operator=(EventHandler&&) = delete;

        virtual void handleEvent(const Port::RTCConfigDataInf& configData) = 0;
    };
}//end of namespace RTC

#endif
