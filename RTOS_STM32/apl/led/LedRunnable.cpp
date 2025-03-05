#include "LedRunnable.hpp"
#include "net/NetPortIntf.hpp"

namespace 
{
  LedCom::LedRunnable l_myLedRunnable_st{};
}//anonymous namespace

namespace LedCom
{
  LedRunnable* g_myLedRunnable_st{nullptr};
  LedRunnable::LedRunnable(void)
  {
    g_myLedRunnable_st = this;
  }

  void LedRunnable::m_rxCustomerHook(void) 
  {
    if(m_LedModeSourcePort.isConnected())
    {
      static_cast<void>(m_LedModeSourcePort.update());
      if(m_LedModeSourcePort.hasNewData())
      {
        Port::LEDModeReqInf l_Data = m_LedModeSourcePort();
        static_cast<void>(l_Data);
        ///do something
      }
    }
  }

  void LedRunnable::m_txCustomerHook(void) 
  {
    ///doing flag check and trigger sending to synchronization port
  }

  void LedRunnable::m_customerRun(void) 
  {
  }
}//end of namespace LedCom


