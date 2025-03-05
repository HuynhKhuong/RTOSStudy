#include "ComBusInputNotify.hpp"
#include "SymbolicNames.hpp"
#include "ComReceive.hpp"
#include "net/NetPortIntf.hpp"
#include "net/NetSenderPort.hpp"

namespace NetCom 
{
  void s_LEDControlMsgNotif_Rx(void)
  { 
    uint8_t signalVal_u8{0U}; 
    netComReceiveSignal(g_LEDModeReqSignal, static_cast<void*>(&signalVal_u8));  
    Port::LEDModeReqInf& reservedChunk = Port::LedModuleSenderPort::getPortSingleton().reserve();
    reservedChunk.m_LedModSignal.setSignalVal(signalVal_u8);
  }

  void s_RTCControlMsgNotif_Rx(void){}
}


