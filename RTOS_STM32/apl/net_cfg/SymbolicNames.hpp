#ifndef SIGNALLISTID_HPP
#define SIGNALLISTID_HPP

#include <stdint.h>
#include <ContainerListCfg.hpp>

/// @brief signal list declaration
constexpr uint8_t g_numberOfSignals{NetCom::g_totalNumberOfSignals};

constexpr uint16_t g_IDLEDControlMsg{0U};
constexpr uint16_t g_LEDModeReqSignal{1U};
constexpr uint16_t g_IDRTCControlMsg{2U};
constexpr uint16_t g_IDStateRespondMsg{3U};
constexpr uint16_t g_CurrentStateSignal{4U};
constexpr uint16_t g_IDRTCRespondMsg{5U};
constexpr uint16_t g_HoursSignal{6U};
constexpr uint16_t g_MinutesSignal{7U};
constexpr uint16_t g_SecondsSignal{8U};

/// @brief message list declaration
constexpr uint8_t g_numberOfMessages{4U};

constexpr uint16_t g_LEDControlMsgIndex{0U};
constexpr uint16_t g_RTCControlMsgIndex{1U};
constexpr uint16_t g_StateRespondMsgIndex{2U};
constexpr uint16_t g_RTCRespondMsgIndex{3U};

#endif
