#ifndef NETRUNNABLE_HPP
#define NETRUNNABLE_HPP

#include "runnable/RunnableDefine.hpp"
#include "ProtocolMCAL.hpp"
#include "NetSenderPort.hpp"

namespace NetCom {

class NetRunnable:public RunnableInf
{
public:
  NetRunnable(void);

  void init(void) override
  {
    netComTransmitInfrasInit();
  }

protected:
  void m_rxCustomerHook(void) override;
  void m_txCustomerHook(void) override;
  void m_customerRun(void) override;
};

extern RunnableInf* g_myNetRunnable_st;

}//end of namespace NetCom

#endif

