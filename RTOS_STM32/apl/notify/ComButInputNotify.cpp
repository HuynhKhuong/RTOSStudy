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
    netComReceiveSignal(g_LEDModeReqSignal_u8, static_cast<void*>(&signalVal_u8));  
    uint32_t& reservedChunk = Port::g_netMenuSenderPort_st.reserve();
    reservedChunk = signalVal_u8;
  }

  void s_RTCControlMsgNotif_Rx(void)
  {
    if(Port::g_netMenuRtcConfigSenderPort_st.isConnected())
    {
      Port::RTCReqInf& reservedChunk = Port::g_netMenuRtcConfigSenderPort_st.reserve();
			{
				uint8_t signalVal_u8{0U}; 
				netComReceiveSignal(g_RTCModeReqSignal_u8, static_cast<void*>(&signalVal_u8));
	      reservedChunk.m_RTCRequest.setSignalVal(signalVal_u8);
			}
			{
				uint8_t signalVal_u8{0U}; 
				netComReceiveSignal(g_ReqDateSignal_u8, static_cast<void*>(&signalVal_u8));
	      reservedChunk.m_day.setRawSignalVal(signalVal_u8);
			}
			{
				uint8_t signalVal_u8{0U}; 
				netComReceiveSignal(g_ReqMonthSignal_u8, static_cast<void*>(&signalVal_u8));
	      reservedChunk.m_month.setRawSignalVal(signalVal_u8);
			}
			{
				uint16_t signalVal_u16{0U}; 
				netComReceiveSignal(g_ReqYearSignal_u16, static_cast<void*>(&signalVal_u16));
	      reservedChunk.m_year.setRawSignalVal(signalVal_u16);
			}
			{
				uint8_t signalVal_u8{0U}; 
				netComReceiveSignal(g_ReqSecondsSignal_u8, static_cast<void*>(&signalVal_u8));
	      reservedChunk.m_second.setRawSignalVal(signalVal_u8);
			}
			{
				uint8_t signalVal_u8{0U}; 
				netComReceiveSignal(g_ReqMinutesSignal_u8, static_cast<void*>(&signalVal_u8));
	      reservedChunk.m_minute.setRawSignalVal(signalVal_u8);
			}
			{
				uint8_t signalVal_u8{0U}; 
				netComReceiveSignal(g_HoursSignal_u8, static_cast<void*>(&signalVal_u8));
	      reservedChunk.m_hour.setRawSignalVal(signalVal_u8);
			}
    }
  }
}


