#include "MenuRunnable.hpp"
#include "menu/MenuReceiverPort.hpp"
#include "menu/MenuSenderPort.hpp"
#include "menu/MenuStateMachine.hpp"

namespace 
{
  Menu::MenuRunnable l_myMenuRunnable_st{};
}//anonymous namespace

namespace Menu
{
  MenuRunnable* g_myMenuRunnable_st{nullptr};
  MenuRunnable::MenuRunnable(void)
  {
    g_myMenuRunnable_st = this;
  }

  void MenuRunnable::m_rxCustomerHook(void) 
  {
    if(Port::g_menuReceiverPort_st.isConnected())
    {
      if(Port::g_menuReceiverPort_st.hasNewData())
      {
        static_cast<void>(Port::g_menuReceiverPort_st.update()); ///Task notify would block task3 right here

        const uint32_t* l_Data_pu32 = Port::g_menuReceiverPort_st.getData();
        const uint32_t l_processVal_u32 = *(l_Data_pu32);

        g_machine_st.setRawEventId(l_processVal_u32);
      }
    }
  }

  void MenuRunnable::m_txCustomerHook(void) 
  {
    Port::g_menuLedSenderPort_st.deliver();
    Port::g_menuStateInfoSenderPort_st.deliver();
  }

  void MenuRunnable::m_customerRun(void) 
  {
	  g_machine_st.run();
  }
}//end of namespace Menu


