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
        uint8_t modIndex{0U};
        static_cast<void>(Port::g_LedModeReceiverPort_st.update());
      
        const Port::LEDModeReqInf* l_Data = Port::g_LedModeReceiverPort_st.getData();
        l_Data->m_LedModSignal.getPhysVal(modIndex);
        m_ledModeManager.setLedMode(modIndex);
      }
    }
  }

  void LedRunnable::m_txCustomerHook(void) 
  {/* do nothing*/}

  void LedRunnable::m_customerRun(void) 
  {
    m_ledModeManager.blink();
  }
}//end of namespace LedCom


