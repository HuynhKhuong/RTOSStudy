#include "ComTransmit.hpp"
#include "ProtocolInterface.hpp"
#include "ProtocolMCAL.hpp"
#include "SymbolicNames.hpp"
#include "SignalListDefine.hpp"

namespace NetCom {

  ///\brief utils to do variable primitive type casting for (void) type variables
  inline void castingSignalType(const SignalLayoutTypeDef::SignalDataType type,
                                        const void* source, 
                                        void* destination)
  {

    if(type == SignalLayoutTypeDef::SignalDataType::UINT8Type)
    {
        uint8_t tempContainer{*(static_cast<const uint8_t*>(source))};
        *(static_cast<uint8_t*>(destination)) = tempContainer;
    }
    else if(type == SignalLayoutTypeDef::SignalDataType::UINT16Type)
    {  
      uint16_t tempContainer{*(static_cast<const uint16_t *>(source))};
        *(static_cast<uint16_t *>(destination)) = tempContainer;
    }
    else if(type == SignalLayoutTypeDef::SignalDataType::UINT32Type)
    {
        uint32_t tempContainer{*(static_cast<const uint32_t  *>(source))};
        *(static_cast<uint32_t*>(destination)) = tempContainer;
    }
    else if(type == SignalLayoutTypeDef::SignalDataType::FLOATType)
    {
        float tempContainer{*(static_cast<const float*>(source))};
        *(static_cast<float*>(destination)) = tempContainer;
    }
    else 
    {
        //Do nothing
    }
  }


  ///\brief   patch a single signal into dedicated buffer
  ///\param   SignalLayoutTypeDef layoutInfo of a signal
  ///\param   localBuffer: destination buffer
  ///\return  localBuffer is written with new data from internal container
  ///\note    This function only processes data with primary datatype
  ///         e.g: int, float, double....
  static void prv_ComSignalPatch(const SignalLayoutTypeDef &layoutInfo,
                                   uint8_t *localBuffer,
                                   void* const sourceBuffer) {
    // Max data supported is 32bit long
    uint32_t dataContainer{0U};
    const uint8_t byteLength{8U};
    const uint32_t bitMask_u32{0xffffffU};
    const uint8_t bitMask_u8{0xffU};
    const uint8_t bitOffsetInByte{static_cast<uint8_t>(layoutInfo.m_startBit % 8U)};
    uint8_t byteNumber{static_cast<uint8_t>(layoutInfo.m_startBit >> 3U)};

    // For copying progess
    uint32_t numberOfBitsLeft{0U};
    uint32_t totalOfBitsCopied{0U};

    ///\brief signal layout (bytewise) diagram
    ///\note  x means occupied by signal
    ///       o means not occupied by signal
    ///(Little Endian)
    ///|b7|b6|b5|b4|b3|b2|b1|b0| - byte 0
    ///|x |x |x |x |0 |0 |0 |0 | - byte 0 (LSbyte)
    ///|x |x |x |x |x |x |x |x | - byte 1
    ///|0 |0 |0 |x |x |x |x |x | - byte 2
    ///|0 |0 |0 |0 |0 |0 |0 |0 | - byte 3
    ///
    ///(Big Endian)
    ///|b7|b6|b5|b4|b3|b2|b1|b0| - byte 0
    ///|0 |0 |0 |0 |x |x |x |x | - byte 0
    ///|x |x |x |x |x |x |x |x | - byte 1 
    ///|x |x |x |0 |0 |0 |0 |0 | - byte 2 (LSbyte)
    ///|0 |0 |0 |0 |0 |0 |0 |0 | - byte 3

    if (layoutInfo.m_dataType == SignalLayoutTypeDef::SignalDataType::OTHERS) 
    {
      // Other ways to handle this signal
      uint16_t signalByteLength{static_cast<uint16_t>(layoutInfo.m_bitLength >> 3U)};
      uint8_t* curBuffer = static_cast<uint8_t* const>(sourceBuffer);

      uint16_t iterator{0U};

      while(iterator < signalByteLength)
      {
        localBuffer[iterator + byteNumber] = *curBuffer;
        curBuffer++;
        iterator++;
      }
    } 
    else 
    {
      /* Technical Rationale: casting data from smaller primitive datatype to larger primitive shall not cause SW crash*/
      castingSignalType(SignalLayoutTypeDef::SignalDataType::UINT32Type , sourceBuffer, static_cast<void*>(&dataContainer));

      if (layoutInfo.m_bitLength >= static_cast<uint16_t>(8U - bitOffsetInByte)) 
      {
        // bit length is larger than 1 byte
        const uint8_t l_tempMask_u8{static_cast<uint8_t>(0xFFU << bitOffsetInByte)}; //0xxxxxx000b where x is the dedicated signal 
                                                                                   
        /* Technical Rationale: processed data type in this case is < 1 byte so 
         * casting data from UINT32Type to smaller primitive datatype is ensured within safety in this case
         */
        uint8_t l_tempDataContainer_u8 = static_cast<uint8_t>(dataContainer & 0xFFU);  
        l_tempDataContainer_u8 = static_cast<uint8_t>(l_tempDataContainer_u8 << bitOffsetInByte) ;

        *(localBuffer + byteNumber) &= l_tempMask_u8; 
        *(localBuffer + byteNumber) |= l_tempDataContainer_u8;

        totalOfBitsCopied = byteLength - bitOffsetInByte;
      } 
      else 
      {
        // bit length is smaller than 1 byte & placed within a byte
        // create mask on signal areas within a byte 
        const uint8_t l_rightTempMask_u8{static_cast<uint8_t>(bitMask_u8 << bitOffsetInByte)}; //0x111xx000b where x is the dedicated signal 
        const uint8_t l_leftTempMask_u8{static_cast<uint8_t>(bitMask_u8 >> (8U - (bitOffsetInByte + layoutInfo.m_bitLength)))};// 0x000xx111b where x is the dedicated signal 
                                                                                                                              
        const uint8_t l_tempMask_u8 = (l_leftTempMask_u8 & l_rightTempMask_u8);

        /* Technical Rationale: processed data type in this case is < 1 byte so 
         * casting data from UINT32Type to smaller primitive datatype is ensured within safety in this case
         */
        const uint8_t l_tempDataContainer_u8 = static_cast<uint8_t>(static_cast<uint8_t>(dataContainer) << bitOffsetInByte) 
                                               & l_leftTempMask_u8;

        *(localBuffer + byteNumber) &= static_cast<uint8_t>(~l_tempMask_u8);
        *(localBuffer + byteNumber) |= static_cast<uint8_t>(l_tempDataContainer_u8); 

        totalOfBitsCopied = layoutInfo.m_bitLength;
      }

      //Process if bit length is larger than 1 byte
      while(totalOfBitsCopied < layoutInfo.m_bitLength)
      {
        if(layoutInfo.m_byteOrder == SignalLayoutTypeDef::ByteOrderTypeDef::INTEL)
        {
          byteNumber++;
        }
        else
        {
          //SignalLayoutTypeDef::ByteOrderTypeDef::MOTOROLA)
          byteNumber--;
        }

        numberOfBitsLeft =  layoutInfo.m_bitLength - totalOfBitsCopied; 
        uint8_t tempContainer{static_cast<uint8_t>((dataContainer >> totalOfBitsCopied) & bitMask_u8)}; //Copy to next byte
                                                               
        if(numberOfBitsLeft >= byteLength) //copy the whole byte
        {
          *(localBuffer + byteNumber) = tempContainer;
          totalOfBitsCopied += byteLength;
        }
        else /// last byte to be copied
        {
          totalOfBitsCopied += numberOfBitsLeft;

          uint8_t tempBitMask{static_cast<uint8_t>(bitMask_u8 >> (byteLength - numberOfBitsLeft))};
          *(localBuffer + byteNumber) &= static_cast<uint8_t>(~tempBitMask);
          *(localBuffer + byteNumber) |= static_cast<uint32_t>(tempContainer);
        }

      }
    }
  }

  void netComSendSignal(signalID ID, void *ptr)
  {
    if(ptr == nullptr) return;

    // hook to get signal handler
    signalID tempID{ID};

    if(tempID >= g_numberOfSignals)
    {
      tempID = g_numberOfSignals - 1U;
    } 
    const SignalLayoutTypeDef& signalInstance{g_signalConfigureTable[static_cast<const uint16_t>(tempID)]};
    const uint16_t index{signalLayoutToSignalContainerMap(tempID)};
    
    // hook to get matched message handler
    MessageHandlerInterface* msgHandlerPtr{g_messageConfigureTable[signalInstance.m_correspondingPDUIndex]};
    bool l_messageDirTx{false};
    l_messageDirTx = (msgHandlerPtr->getMessageDir() == MessageHandlerInterface::MessageDir::TX); 
    if(!l_messageDirTx) return;

    switch(signalInstance.m_dataType) 
    {
      case SignalLayoutTypeDef::SignalDataType::UINT8Type:
        castingSignalType(signalInstance.m_dataType, 
                          ptr,
                          static_cast<void*>(&(prvSignalContainer.m_signalTypeUint8_t[index])));
        break;
      case SignalLayoutTypeDef::SignalDataType::UINT16Type:
        castingSignalType(signalInstance.m_dataType, 
                          ptr,
                          static_cast<void*>(&(prvSignalContainer.m_signalTypeUint16_t[index])));
        break;
      case SignalLayoutTypeDef::SignalDataType::UINT32Type:
        castingSignalType(signalInstance.m_dataType, 
                          ptr,
                          static_cast<void*>(&(prvSignalContainer.m_signalTypeUint32_t[index])));
        break;
      case SignalLayoutTypeDef::SignalDataType::FLOATType:
        castingSignalType(signalInstance.m_dataType, 
                          ptr,
                          static_cast<void*>(&(prvSignalContainer.m_signalTypeFloat[index])));
        break;
      case SignalLayoutTypeDef::SignalDataType::OTHERS:
        {
          uint16_t signalByteLength{static_cast<uint16_t>(signalInstance.m_bitLength >> 3U)};
          uint16_t curIndex{index};
          uint16_t iterator{0U};

          while(iterator < signalByteLength)
          {
            static_cast<uint8_t*>(ptr)[iterator] = prvSignalContainer.m_signalTypeOthers[curIndex];  
            curIndex++;
            iterator++;
          }
        }
      default:
        break;
    }

    msgHandlerPtr->setNewMessageEventFlag(true);
  }

  void netComSend(MessageHandlerInterface &messageLayout)
  {
    const uint16_t numbOfSignals{messageLayout.getNumberOfSignals()};
    const uint16_t *signalList{messageLayout.getSignalIDList()};
    uint8_t *localBuffer{messageLayout.getLocalBuffer()};

    for (uint8_t i{0U}; i < numbOfSignals; i++) 
    {
      const SignalLayoutTypeDef& signalInstance{g_signalConfigureTable[signalList[i]]};
      const uint16_t index{signalLayoutToSignalContainerMap(signalList[i])};
         
      switch(signalInstance.m_dataType) 
      {
        case SignalLayoutTypeDef::SignalDataType::UINT8Type:
          prv_ComSignalPatch(signalInstance, localBuffer, static_cast<void*>(&(prvSignalContainer.m_signalTypeUint8_t[index])));
          break;
        case SignalLayoutTypeDef::SignalDataType::UINT16Type:
          prv_ComSignalPatch(signalInstance, localBuffer, static_cast<void*>(&(prvSignalContainer.m_signalTypeUint16_t[index])));
          break;
        case SignalLayoutTypeDef::SignalDataType::UINT32Type:
          prv_ComSignalPatch(signalInstance, localBuffer, static_cast<void*>(&(prvSignalContainer.m_signalTypeUint32_t[index])));
          break;
        case SignalLayoutTypeDef::SignalDataType::FLOATType:
          prv_ComSignalPatch(signalInstance, localBuffer, static_cast<void*>(&(prvSignalContainer.m_signalTypeFloat[index])));
          break;
        case SignalLayoutTypeDef::SignalDataType::OTHERS:
          prv_ComSignalPatch(signalInstance, localBuffer, static_cast<void*>(&(prvSignalContainer.m_signalTypeOthers[index])));
          break;
        default:
          break;
      }
    }
  }

  void netComSendWrapper(MessageHandlerInterface &messageLayout)
  {
    bool messageE2EProtectPassed{true};

    if(messageLayout.m_cbkFnc != nullptr)
    {
      messageE2EProtectPassed = messageLayout.m_cbkFnc(messageLayout.getLocalBuffer());
    }

    if(messageE2EProtectPassed)
    {
      netHeaderSetup(messageLayout);
      netComRequestTransmit(messageLayout.getLocalBuffer(), messageLayout.m_DLC);

      netComProcessTransmitRequest(); ///\todo  to define better context to call this process function
    }
  }

} //end of namespace NetCom

