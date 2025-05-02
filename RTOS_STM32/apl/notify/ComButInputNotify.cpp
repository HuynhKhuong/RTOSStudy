#include "ComBusInputNotify.hpp"
#include "SymbolicNames.hpp"
#include "ComReceive.hpp"
#include "net/NetSenderPort.hpp"

namespace NetCom 
{
  void s_LEDControlMsgNotif_Rx(void)
  { 
    uint8_t signalVal_u8{0U}; 
    netComReceiveSignal(g_LEDModeReqSignal, static_cast<void*>(&signalVal_u8));  
    uint32_t& reservedChunk = Port::g_netMenuSenderPort_st.reserve();
    reservedChunk = signalVal_u8;
  }

  void s_RTCControlMsgNotif_Rx(void)
  {/*do nothing*/}
}


