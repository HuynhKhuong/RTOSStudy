#include "ComQuery.hpp"
#include "MessageListDefine.hpp"
#include "ComReceive.hpp"
#include "ComTransmit.hpp"

///for locking resources instructions
extern "C"{
	#include "FreeRTOS.h"
	#include "projdefs.h"
	#include "portmacro.h"
}

namespace NetCom {

void netComRxMainFunction(void)
{
  for(auto messageHandler_ptr: g_messageConfigureTable) 
  {
    bool l_notifyCall_bo{false};
    bool l_isNewMessage_bo{false};

    if(messageHandler_ptr->getMessageDir() == MessageHandlerInterface::MessageDir::TX)
    {continue;}

    portENTER_CRITICAL();
    l_isNewMessage_bo = messageHandler_ptr->getNewMessageEventFlag();
    portEXIT_CRITICAL();

    if(l_isNewMessage_bo == false)
    {continue;}

    //ELSE
    //dispatch message buffer into internal container
    portENTER_CRITICAL();
    if(messageHandler_ptr->m_cbkFnc == nullptr)
    {
      netComDispatchSignals(*messageHandler_ptr);
      l_notifyCall_bo = true;
    }
    else
    {
      if(messageHandler_ptr->m_cbkFnc(messageHandler_ptr->getLocalBuffer()) == true) 
      {
        netComDispatchSignals(*messageHandler_ptr);
        l_notifyCall_bo = true;
      }
    }

    messageHandler_ptr->setNewMessageEventFlag(false);
    portEXIT_CRITICAL();

    if(l_notifyCall_bo)
    {
      //call user callback notify function
      if(messageHandler_ptr->m_notifFunc != nullptr)
      {
        messageHandler_ptr->m_notifFunc();
      }
    }

  }
}

void netComTxMainFunction(void)
{
  for(auto messageHandler_ptr: g_messageConfigureTable) 
  {
    
    if(messageHandler_ptr->getMessageDir() == MessageHandlerInterface::MessageDir::RX)
    {continue;}
    if(messageHandler_ptr->getNewMessageEventFlag() == false)
    {continue;}

    //ELSE
    portENTER_CRITICAL();
    netComSend(*messageHandler_ptr);//patch internal container into message buffer 
    netComSendWrapper(*messageHandler_ptr);//trigger sending to lowerlayers
    portEXIT_CRITICAL();

  }
}

} // End of namespace NetCom
  
