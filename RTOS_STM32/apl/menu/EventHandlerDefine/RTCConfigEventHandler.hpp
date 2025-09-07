#ifndef RTCCONFIGEVENTHANDLER_HPP
#define RTCCONFIGEVENTHANDLER_HPP

#include "EventDefine.hpp"


namespace Menu
{

    enum class RTCConfigOption : uint8_t
    {
        TIMECONFIG = 0U,
        DATECONFIG,
        REPORTREQUEST,
        MAXCONFIG
    };

    struct TimeInfo
    {
        uint8_t m_hour_u8;
        uint8_t m_minute_u8;
        uint8_t m_second_u8;
    };

    struct DateInfo
    {
        uint16_t m_year_u16;
        uint8_t m_month_u8;
        uint8_t m_day_u8;
    };

    class RTCConfigEventHandler : public EventHandlerInf
    {
    public:
        RTCConfigEventHandler(uint32_t eventId) : EventHandlerInf{ eventId }
        {
            /*do nothing*/
        }

        ~RTCConfigEventHandler() = default;

        void setRTCConfigMode(const RTCConfigOption option_u8)
        {
            m_configOption_en = option_u8;
        }

        void setRTCDateInfo(const DateInfo dateInfo_cst)
        {
            m_dateInfo_st = dateInfo_cst; ///Shallow copy
        }

        void setRTCTimeInfo(const TimeInfo timeInfo_cst)
        {
            m_timeInfo_st = timeInfo_cst; ///Shallow copy
        }

        void handle(void) override;

    private:

        /// @brief util function to help Flush the RTC configuration inside eventhandler
        void flushRTCConfig(void);

        DateInfo m_dateInfo_st{ 0U, 0U, 0U };
        TimeInfo m_timeInfo_st{ 0U, 0U, 0U };
        RTCConfigOption m_configOption_en{ RTCConfigOption::MAXCONFIG };
    };
}
#endif


