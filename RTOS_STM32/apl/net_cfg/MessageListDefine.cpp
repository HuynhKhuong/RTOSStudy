///\note This is user's configuration 
///      In practice, this configuration should be visualized with UI & code generating tool to prevent 
///      human mistake

#include "MessageListDefine.hpp"
#include "foundation_utils.hpp"
#include "RxProtect.hpp"
#include "notify/ComBusInputNotify.hpp"
namespace NetCom
{
MessageLayout<4U, 2U> g_LEDControlMsg{0x0U, rbNet_E2EProtect::LEDControlMsgDLCCheck, s_LEDControlMsgNotif_Rx, MessageHandlerInterface::MessageDir::RX, {g_IDLEDControlMsg, g_LEDModeReqSignal}}; //DataLength = ID + DLC + Data + *
MessageLayout<4U, 1U> g_RTCControlMsg{0x1U, rbNet_E2EProtect::RTCControlMsgDLCCheck, s_RTCControlMsgNotif_Rx, MessageHandlerInterface::MessageDir::RX, {g_IDRTCControlMsg}}; //DataLength = ID + DLC + Data + *

vfc::array<MessageHandlerInterface* const, g_numberOfMessages> g_messageConfigureTable{
  &g_LEDControlMsg,
  &g_RTCControlMsg
};

}// End of namespace NetCom
