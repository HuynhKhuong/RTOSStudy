#include "TimeConfigEventHandler.hpp"

namespace RTC_Handler
{
void TimeConfigEventHandler::handleEvent(const Port::RTCConfigDataInf& configData)
{
    if ((m_rtcHandler != nullptr) && (configData.configOption == Menu::RTCConfigOption::TIMECONFIG))
    {
        RTC_TimeTypeDef time;
        time.Hours = configData.timeInfo.m_hour_u8;
        time.Minutes = configData.timeInfo.m_minute_u8;
        time.Seconds = configData.timeInfo.m_second_u8;
        m_rtcHandler->setTime(time);
    }
}

} // namespace RTC_Handler
  
