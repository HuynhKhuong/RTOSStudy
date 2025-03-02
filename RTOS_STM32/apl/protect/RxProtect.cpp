#include "MessageListDefine.hpp"

namespace rbNet_E2EProtect {



bool LEDControlMsgDLCCheck(uint8_t *messageBuffer)
{
  //return rbNetProtect_DLCCheck(NetCom::g_LEDControlMsg,messageBuffer);
  return true;
}

bool RTCControlMsgDLCCheck(uint8_t *messageBuffer)
{
  //return rbNetProtect_DLCCheck(NetCom::g_RTCControlMsg,messageBuffer);
  return true;
}

} // End of namespace rbNet_E2EProtect
