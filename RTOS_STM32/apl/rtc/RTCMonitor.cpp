#include "RTCMonitor.hpp"
#include "RTCSenderPort.hpp"
#include "RTCConfigEventHandler.hpp"
#include "events/TimeConfigEventHandler.hpp"
#include "events/DateConfigEventHandler.hpp"

namespace RTC_Handler
{

void RTCMonitor::initRTCHandler(ComplexDriver::RTCInstanceIdx idx)
{
    m_rtcHandler = ComplexDriver::getRTCHandlerInstance(idx);
}


void RTCMonitor::onEvent(const Port::RTCConfigDataInf& configData)
{
    RTC_Handler::EventHandler* handler = nullptr;
    switch (configData.configOption)
    {
        case Menu::RTCConfigOption::TIMECONFIG:
            handler = new RTC_Handler::TimeConfigEventHandler(m_rtcHandler);
            break;
        case Menu::RTCConfigOption::DATECONFIG:
            handler = new RTC_Handler::DateConfigEventHandler(m_rtcHandler);
            break;
        case Menu::RTCConfigOption::REPORTREQUEST:
            enableReportRequest();
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

void RTCMonitor::runPeriodic()
{
    if (m_reportRequested)
    {
        if (m_rtcHandler != nullptr)
        {
            RTC_TimeTypeDef time;
            RTC_DateTypeDef date;
            m_rtcHandler->getTime(time);
            m_rtcHandler->getDate(date);
            m_lastTime = time;
            m_lastDate = date;

            // Map to TimeDataItf for SenderPort
            Port::TimeDataItf& timeDataChunk = Port::g_rtcTimeDataSenderPort_st.reserve();
            timeDataChunk.hour   = time.Hours;
            timeDataChunk.minute = time.Minutes;
            timeDataChunk.second = time.Seconds;
        }
    }
}

}//enfd of namespace RTC_Handler
