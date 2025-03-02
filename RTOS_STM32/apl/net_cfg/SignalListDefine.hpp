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
        SignalLayoutTypeDef(8U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_LEDControlMsgIndex), //LEDModeReqSignal
        SignalLayoutTypeDef(0U, 8U,
                            SignalLayoutTypeDef::ByteOrderTypeDef::INTEL,
                            SignalLayoutTypeDef::SignalDataType::UINT8Type,
                            g_RTCControlMsgIndex), //IDRTCControlMsg

};
} //End of namespace NetCom
#endif
