#include "ProtocolInterface.hpp"

namespace NetCom {
  bool netProtect_DLCCheck(NetCom::MessageHandlerInterface &messageHandler, 
                            const uint8_t *messageBuffer, 
                            const uint16_t size_u16)
  {
    bool returnValue{false};
    uint16_t DLCCount{0U};
    const char endOfFrameSymbl{'*'};
    const uint16_t maxDataLength{UINT16_MAX};
    uint8_t* localBuffer{messageHandler.getLocalBuffer()};

    if(messageHandler.m_DLC > size_u16) return false;
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


  void netHeaderSetup(NetCom::MessageHandlerInterface &messageHandler)
  {
    ///\todo  currently there's no DLC field defined 
    const uint8_t l_messageIDval_cu8{messageHandler.m_messageID};
    const uint8_t l_messageIDBytePos_cu8{0U};
    
    uint8_t* l_msgLocalBuffer_au8{messageHandler.getLocalBuffer()};

    if(messageHandler.getMessageDir() == NetCom::MessageHandlerInterface::MessageDir::TX)
    {
      l_msgLocalBuffer_au8[l_messageIDBytePos_cu8] = l_messageIDval_cu8; 
    }
  }

}//end of namespace NetCom

