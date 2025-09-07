#ifndef MENUPORTINTF_HPP
#define MENUPORTINTF_HPP

#include "container/PortInterface.hpp"
#include "menu/EventHandlerDefine/RTCConfigEventHandler.hpp"
#include <stdint.h>

namespace Port
{
    
    struct LEDModeReqInf : public BasePortType
    {
        using LEDModSignalType = CSignalDescription<uint8_t, uint8_t>;
        LEDModSignalType m_LedModSignal{ LEDModSignalType::RawDataInfo<uint8_t>{ 255U, 0U, 1.0F, 0.0F } };
    };

    struct StateInfoInf : public BasePortType
    {
        using SignalType = CSignalDescription<uint8_t, uint8_t>;
        SignalType m_MainStateSignal{ SignalType::RawDataInfo<uint8_t>{ 255U, 0U, 1.0F, 0.0F } };
        SignalType m_SubStateSignal{ SignalType::RawDataInfo<uint8_t>{ 255U, 0U, 1.0F, 0.0F } };
    };

    struct RTCConfigDataInf : public BasePortType
    {
        Menu::DateInfo dateInfo;
        Menu::TimeInfo timeInfo;
        Menu::RTCConfigOption configOption;
    };
}

#endif

