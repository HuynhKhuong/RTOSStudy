#include "connect.hpp"

#include "menu/MenuMempool.hpp"
#include "led/LedReceiverPort.hpp"
#include "net/NetSenderPort.hpp"
#include "net/NetReceiverPort.hpp"
#include "menu/MenuReceiverPort.hpp"
#include "menu/MenuSenderPort.hpp"

#include "task3.hpp"

namespace
{
  void mempoolConnect(void)
  {
    ///standard senderport port connection
    Port::g_menuLedSenderPort_st.connectMempool(static_cast<mempool::TChangeableMemPoolBase*>(&mempool::g_menuLedModeMempool_str));
    Port::g_menuStateInfoSenderPort_st.connectMempool(static_cast<mempool::TChangeableMemPoolBase*>(&mempool::g_menuStateInfoMempool_str));
  }
  

  void portConnect(void)
  {
    ///for lightweight receiver port, connect directly to task handler
    Port::g_menuReceiverPort_st.connect(Task::task3.getTaskHandle());
    Port::g_netMenuSenderPort_st.connect(Port::g_menuReceiverPort_st);
    
    ///standard senderport/receiver port connection
    Port::g_menuLedSenderPort_st.connect(Port::g_LedModeReceiverPort_st);
    Port::g_menuStateInfoSenderPort_st.connect(Port::g_netStateInfoReceiverPort_st);
  }
}

void connect(void)
{
  mempoolConnect();
  portConnect();
}

