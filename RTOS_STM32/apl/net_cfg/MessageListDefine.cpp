///\note This is user's configuration 
///      In practice, this configuration should be visualized with UI & code generating tool to prevent 
///      human mistake

#include "MessageListDefine.hpp"
#include "SymbolicNames.hpp"
#include "foundation_utils.hpp"
#include "RxProtect.hpp"
#include "notify/ComBusInputNotify.hpp"

namespace NetCom
{
MessageLayout<4U, 2U> g_LEDControlMsg{0x0U, rbNet_E2EProtect::LEDControlMsgDLCCheck, s_LEDControlMsgNotif_Rx, MessageHandlerInterface::MessageDir::RX, {g_IDLEDControlMsg_u8, g_LEDModeReqSignal_u8}}; //DataLength = ID + DLC + Data + *
MessageLayout<11U, 8U> g_RTCControlMsg{0x1U, rbNet_E2EProtect::RTCControlMsgDLCCheck, s_RTCControlMsgNotif_Rx, MessageHandlerInterface::MessageDir::RX,{g_IDRTCControlMsg_u8, g_RTCModeReqSignal_u8,
                                                                                                                                                        g_ReqHoursSignal_u8,
                                                                                                                                                        g_ReqMinutesSignal_u8,
                                                                                                                                                        g_ReqSecondsSignal_u8,
                                                                                                                                                        g_ReqDateSignal_u8,
                                                                                                                                                        g_ReqMonthSignal_u8,
                                                                                                                                                        g_ReqYearSignal_u16}}; //DataLength = ID + DLC + Data + *
MessageLayout<4U, 2U> g_StateRespondMsg{0x2U, nullptr, nullptr, MessageHandlerInterface::MessageDir::TX, {g_IDStateRespondMsg_u8, g_CurrentStateSignal_u8}};//DataLength = ID + DLC + Data + *
MessageLayout<6U, 4U> g_RTCRespondMsg{0x3U, nullptr, nullptr, MessageHandlerInterface::MessageDir::TX, {g_IDRTCRespondMsg_u8, g_HoursSignal_u8, g_MinutesSignal_u8, g_SecondsSignal_u8}};//DataLength = ID + DLC + Data + *

vfc::array<MessageHandlerInterface* const, g_numberOfMessages> g_messageConfigureTable{
  &g_LEDControlMsg,
  &g_RTCControlMsg,
	&g_StateRespondMsg,
	&g_RTCRespondMsg
};

}// End of namespace NetCom
