#ifndef NETPORTINTF_HPP
#define NETPORTINTF_HPP

#include "container/PortInterface.hpp"
#include <stdint.h>

namespace Port
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

    struct RTCReqInf : public BasePortType
    {
        using BaseU8Type = CSignalDescription<uint8_t, uint8_t>;
        using BaseU16Type = CSignalDescription<uint16_t, uint16_t>;
        BaseU8Type m_RTCRequest{BaseU8Type::RawDataInfo<uint8_t>{3U, 0U, 1.0F, 0.0F}};

        BaseU8Type m_hour{BaseU8Type::RawDataInfo<uint8_t>{23U, 0U, 1.0F, 0.0F}};
        BaseU8Type m_minute{BaseU8Type::RawDataInfo<uint8_t>{59U, 0U, 1.0F, 0.0F}};
        BaseU8Type m_second{BaseU8Type::RawDataInfo<uint8_t>{59U, 0U, 1.0F, 0.0F}};

        BaseU16Type m_year{BaseU16Type::RawDataInfo<uint16_t>{0xFFFFU, 0U, 1.0F, 0.0F}};
        BaseU8Type m_month{BaseU8Type::RawDataInfo<uint8_t>{12U, 0U, 1.0F, 0.0F}};
        BaseU8Type m_day{BaseU8Type::RawDataInfo<uint8_t>{31U, 1U, 1.0F, 0.0F}};
    };
}
#endif
