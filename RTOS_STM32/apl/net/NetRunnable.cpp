#include "NetRunnable.hpp"
#include "net/ComQuery.hpp"

namespace 
{
  NetCom::NetRunnable l_myNetRunnable_st{};
}//anonymous namespace

namespace NetCom
{
  RunnableInf* g_myNetRunnable_st{nullptr};
  NetRunnable::NetRunnable(void)
  {
    g_myNetRunnable_st = static_cast<RunnableInf*>(this);
  }

  void NetRunnable::m_rxCustomerHook(void) 
  {
    ///doing flag check and trigger sending to synchronization port
  }

  void NetRunnable::m_txCustomerHook(void) 
  {
    ///doing flag check and trigger sending to synchronization port
  }

  void NetRunnable::m_customerRun(void) 
  {
    netComTxMainFunction();
    netComRxMainFunction();
  }
}//end of namespace NetCom


