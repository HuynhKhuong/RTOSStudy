#include "ComQuery.hpp"
#include "MessageListDefine.hpp"
#include "ComReceive.hpp"

namespace NetCom {

void netComRxMainFunction(void)
{
  //do nothing
  for(auto messageHandler_ptr: g_messageConfigureTable) 
  {
    if(messageHandler_ptr->getNewMessageEventFlag() == true)
    {
      //dispatch message buffer into internal container
      netComDispatchSignals(*messageHandler_ptr);

      //call user callback notify function
      if(messageHandler_ptr->m_notifFunc != nullptr)
      {
        messageHandler_ptr->m_notifFunc();
      }
    }
  }
}

} // End of namespace NetCom
  
