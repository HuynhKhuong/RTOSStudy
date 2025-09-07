#ifndef PROTOCOLMCAL_HPP
#define PROTOCOLMCAL_HPP

#include <stdint.h>

extern "C"
{
#include "FreeRTOS.h"
#include "queue.h"
}

namespace NetCom 
{
  ///\brief HardwareObject Type Definition to be used on queue service offered by MCAL layer for upper layers
  struct ProtocolHardwareObjHandler
  {
    uint8_t* m_dataBuffer_u8;
    uint16_t m_BufferSize_u16;
  };

  extern QueueHandle_t g_MCALQueueHandler_st;

  ///\brief netComTransmitInfrasInit inits queuing list required for sending from application to hardware peripherals
  ///\param void
  ///\note  This function must be called at init time, before any calls to TxMainfunction 
  void netComTransmitInfrasInit(void);
    
  ///\brief netComRequestTransmit handles queuing request sending to physical communication line from application and 
  ///       trigger sending request to hardware peripherals
  ///\param dataBuffer[]: array container of data
  void netComRequestTransmit(uint8_t* dataBuffer, const uint16_t& size);

  ///\brief netComProcessTransmitRequest handles processing queuing request sending to physical communication line from application and 
  ///       trigger sending request to hardware peripherals
  ///\param void
  void netComProcessTransmitRequest(void);

  ///\brief netComReceive handles receiving message from master and dispatch
  ///       messages to signals
  ///\param dataBuffer[]: array container of data
  ///\note  netComReceive should be called from ISR context (event-based)
  void netComReceive(uint8_t *dataBuffer, uint16_t bufferSize_u16);
}

#endif

