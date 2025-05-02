#include "LedEventHandler.hpp"
#include "menu/MenuSenderPort.hpp"

namespace Menu
{
  void LedEventHandler::handle(void)
  {
    Port::LEDModeReqInf& l_ledModeReqChunk_st{Port::g_menuLedSenderPort_st.reserve()};
    l_ledModeReqChunk_st.m_LedModSignal.setSignalVal(m_ledMode_u8);
  }
}//end of namespace menu
 
