#include "ComQuery.hpp"
#include "MessageListDefine.hpp"
#include "ComReceive.hpp"

namespace NetCom {

void netComRxMainFunction(void)
{
  //do nothing
  for(auto messageHandler_ptr: g_messageConfigureTable) 
  {
    if(messageHandler_ptr->getNewMessageReceivedFlag() == true)
    {
      //dispatch message buffer into internal container
      netComDispatchSignals(*messageHandler_ptr);

      //call user callback notify function
      /* to do */
    }
  }
}

} // End of namespace NetCom
  
