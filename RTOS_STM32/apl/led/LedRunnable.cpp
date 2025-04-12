#include "LedRunnable.hpp"
#include "LedReceiverPort.hpp"

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
    if(Port::g_LedModeReceiverPort_st.isConnected())
    {
      if(Port::g_LedModeReceiverPort_st.hasNewData())
      { 
        static_cast<void>(Port::g_LedModeReceiverPort_st.update());
      
        const Port::LEDModeReqInf* l_Data = Port::g_LedModeReceiverPort_st.getData();
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


