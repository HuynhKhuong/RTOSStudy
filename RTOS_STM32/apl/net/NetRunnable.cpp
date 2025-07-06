#include "NetRunnable.hpp"
#include "ComTransmit.hpp"
#include "MenuPortIntf.hpp"
#include "NetSenderPort.hpp"
#include "NetReceiverPort.hpp"

#include "SymbolicNames.hpp"
#include "net/ComQuery.hpp"

//extern void wrapperCallHUARTTransmit(const uint8_t*, uint8_t); // Call the wrapper function to transmit data

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
    if(Port::g_netStateInfoReceiverPort_st.isConnected())
    {
      if(Port::g_netStateInfoReceiverPort_st.hasNewData())
      {
        uint8_t l_subStateSignalRaw_u8{0U};
        uint8_t l_mainStateSignalRaw_u8{0U};
        uint8_t l_stateSignalRaw_u8{0U};
        static_cast<void>(Port::g_netStateInfoReceiverPort_st.update());
        const Port::StateInfoInf* l_Data_ptr = Port::g_netStateInfoReceiverPort_st.getData();

        l_Data_ptr->m_SubStateSignal.getRawVal(l_subStateSignalRaw_u8);
        l_Data_ptr->m_MainStateSignal.getRawVal(l_mainStateSignalRaw_u8);
        l_stateSignalRaw_u8 = static_cast<uint8_t>(l_mainStateSignalRaw_u8 << 2U) | l_subStateSignalRaw_u8;

        NetCom::netComSendSignal(g_CurrentStateSignal_u8, static_cast<void*>(&l_stateSignalRaw_u8)); 
      }
    }
  }

  void NetRunnable::m_txCustomerHook(void) 
  {
	  Port::g_netMenuSenderPort_st.deliver();
    Port::g_netMenuRtcConfigSenderPort_st.deliver();
  }

  void NetRunnable::m_customerRun(void) 
  {
    netComTxMainFunction();
    netComRxMainFunction();
  }
}//end of namespace NetCom


