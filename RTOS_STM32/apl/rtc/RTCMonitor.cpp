#include "RTCMonitor.hpp"
#include "events/TimeConfigEventHandler.hpp"
#include "events/DateConfigEventHandler.hpp"

namespace RTC_Handler
{

RTCMonitor::RTCMonitor(ComplexDriver::RTCInstanceIdx idx)
    : m_rtcHandler{ComplexDriver::getRTCHandlerInstance(idx)}
{
}

void RTCMonitor::initRTCHandler(ComplexDriver::RTCInstanceIdx idx)
{
    m_rtcHandler = ComplexDriver::getRTCHandlerInstance(idx);
}


void RTCMonitor::onEvent(const Port::RTCConfigDataInf& configData)
{
    EventHandler* handler = nullptr;
    switch (configData.configOption)
    {
        case Menu::RTCConfigOption::TIMECONFIG:
            handler = new RTC_Handler::TimeConfigEventHandler(m_rtcHandler);
            break;
        case Menu::RTCConfigOption::DATECONFIG:
            handler = new RTC_Handler::DateConfigEventHandler(m_rtcHandler);
            break;
        default:
            break;
    }

    if (handler != nullptr)
    {
        handler->handleEvent(configData);
        delete handler;
    }
}
} // namespace RTC
  
