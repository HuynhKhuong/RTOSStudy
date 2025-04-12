#include "connect.hpp"

#include "net/NetMempool.hpp"
#include "led/LedReceiverPort.hpp"
#include "net/NetSenderPort.hpp"

namespace
{
  void mempoolConnect(void)
  {
    Port::g_netSenderPort_st.connectMempool(static_cast<mempool::TChangeableMemPoolBase*>(&mempool::g_netLedModeMempool_str));
  }
  

  void portConnect(void)
  {
    Port::g_netSenderPort_st.connect(Port::g_LedModeReceiverPort_st);
  }
}

void connect(void)
{
  mempoolConnect();
  portConnect();
}

