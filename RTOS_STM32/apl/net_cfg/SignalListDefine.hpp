///\note This is user's configuration 
///      In practice, this configuration should be visualized with UI & code generating tool to prevent 
///      human mistake

#ifndef SIGNALLISTDEFINE_INCLUDED_HPP
#define SIGNALLISTDEFINE_INCLUDED_HPP

#include "MessageListDefine.hpp"
#include "SymbolicNames.hpp"
#include "foundation_utils.hpp"

namespace NetCom {

constexpr vfc::array<SignalLayoutTypeDef, g_numberOfSignals> g_signalConfigureTable{
        SignalLayoutTypeDef(0U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_LEDControlMsgIndex), //IDLEDControlMsg
        SignalLayoutTypeDef(16U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_LEDControlMsgIndex), //LEDModeReqSignal
        SignalLayoutTypeDef(0U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_RTCControlMsgIndex), //IDRTCControlMsg
        SignalLayoutTypeDef(0U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_StateRespondMsgIndex), //IDStateRespondMsg
        SignalLayoutTypeDef(16U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_StateRespondMsgIndex), //CurrentStateSignal
        SignalLayoutTypeDef(0U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_RTCRespondMsgIndex), //IDRTCRespondMsg
        SignalLayoutTypeDef(16U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_RTCRespondMsgIndex), //HoursSignal
        SignalLayoutTypeDef(24U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_RTCRespondMsgIndex), //MinutesSignal
        SignalLayoutTypeDef(32U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_RTCRespondMsgIndex), //SecondsSignal

};
} //End of namespace NetCom
#endif
