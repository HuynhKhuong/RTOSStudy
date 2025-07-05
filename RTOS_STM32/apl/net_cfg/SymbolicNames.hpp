#ifndef SIGNALLISTID_HPP
#define SIGNALLISTID_HPP

#include <stdint.h>
#include <ContainerListCfg.hpp>

/// @brief signal list declaration
constexpr uint8_t g_numberOfSignals{NetCom::g_totalNumberOfSignals};

/// @brief signal index to define orders in SignalListDefine.hpp
constexpr uint16_t g_IDLEDControlMsg_u8{0U};
constexpr uint16_t g_LEDModeReqSignal_u8{1U};
constexpr uint16_t g_IDRTCControlMsg_u8{2U};
constexpr uint16_t g_RTCModeReqSignal_u8{3U};
constexpr uint16_t g_ReqHoursSignal_u8{4U};
constexpr uint16_t g_ReqMinutesSignal_u8{5U};
constexpr uint16_t g_ReqSecondsSignal_u8{6U};
constexpr uint16_t g_ReqDateSignal_u8{7U};
constexpr uint16_t g_ReqMonthSignal_u8{8U};
constexpr uint16_t g_IDStateRespondMsg_u8{9U};
constexpr uint16_t g_CurrentStateSignal_u8{10U};
constexpr uint16_t g_IDRTCRespondMsg_u8{11U};
constexpr uint16_t g_HoursSignal_u8{12U};
constexpr uint16_t g_MinutesSignal_u8{13U};
constexpr uint16_t g_SecondsSignal_u8{14U};

constexpr uint16_t g_ReqYearSignal_u16{15U};

/// @brief message list declaration
constexpr uint8_t g_numberOfMessages{4U};

/// @brief message index to define orders in MessageListDefine.hpp
constexpr uint16_t g_LEDControlMsgIndex{0U};
constexpr uint16_t g_RTCControlMsgIndex{1U};
constexpr uint16_t g_StateRespondMsgIndex{2U};
constexpr uint16_t g_RTCRespondMsgIndex{3U};

#endif

