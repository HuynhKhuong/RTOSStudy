#include "MessageListDefine.hpp"

namespace rbNet_E2EProtect {

///\brief function handles DLC check for required message
///\details function would iterate through the message buffer and count the
///         number of Iterating times from the beginning of the buffer to the
///         endOfFrameSymbl
///         If no endOfFrameSymbol catched in the buffer, set returnValue = false
///         If the number of Iterating time (DLCCount) equals to predefined DLC
///         then return true
///         Else return default value or set false returnValue = false
/// \param MessageLayoutInterface &messageHandler: contains predefined DLC
/// \param messageBuffer[] raw data buffer
static bool rbNetProtect_DLCCheck(NetCom::MessageHandlerInterface &messageHandler,
                                  const uint8_t *messageBuffer) 
{
  bool returnValue{false};
  uint16_t DLCCount{0U};
  const char endOfFrameSymbl{'*'};
  const uint16_t maxDataLength{UINT16_MAX};
  uint8_t* localBuffer{messageHandler.getLocalBuffer()};

  while ((*messageBuffer) != endOfFrameSymbl) 
  {

      //To prevent buffer overflow
      if(DLCCount < messageHandler.m_DLC)
      {
          *localBuffer = *messageBuffer;
      }
      DLCCount++;
      localBuffer++;
      messageBuffer++;

      if (DLCCount == maxDataLength) //Data Length reaches maximum allowed
      {
          returnValue = false;
          break;
      }
  }

  if (DLCCount == (messageHandler.m_DLC - 1U)) //Data length counted locally eliminates EoF symbol
  {
      returnValue = true;
  }

  return returnValue;
}


bool LEDControlMsgDLCCheck(uint8_t *messageBuffer)
{
  return rbNetProtect_DLCCheck(NetCom::g_LEDControlMsg,messageBuffer);
}

bool RTCControlMsgDLCCheck(uint8_t *messageBuffer)
{
  return rbNetProtect_DLCCheck(NetCom::g_RTCControlMsg,messageBuffer);
}

} // End of namespace rbNet_E2EProtect
