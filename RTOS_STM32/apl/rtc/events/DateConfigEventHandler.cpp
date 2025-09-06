#include "DateConfigEventHandler.hpp"

namespace RTC_Handler
{

void DateConfigEventHandler::handleEvent(const Port::RTCConfigDataInf& configData)
{
    if ((m_rtcHandler != nullptr) && (configData.configOption == Menu::RTCConfigOption::DATECONFIG))
    {
        RTC_DateTypeDef date;
        date.Year = configData.dateInfo.m_year_u16 % 100; // STM32 expects 2-digit year
        date.Month = configData.dateInfo.m_month_u8;
        date.Date = configData.dateInfo.m_day_u8;
        m_rtcHandler->setDate(date);
    }
}

} // namespace RTC_Handler
  
