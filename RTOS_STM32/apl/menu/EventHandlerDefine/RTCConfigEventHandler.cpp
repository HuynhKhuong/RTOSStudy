#include "RTCConfigEventHandler.hpp"
#include "menu/MenuSenderPort.hpp"

namespace Menu 
{
void RTCConfigEventHandler::handle(void) 
{
    if((Port::g_menuRTCConfigDataSenderPort_st.isConnected() == false)) return;  

    Port::RTCConfigDataInf& reservedChunk_st = Port::g_menuRTCConfigDataSenderPort_st.reserve();

    reservedChunk_st.configOption = m_configOption_en; ///shallow copy 
    reservedChunk_st.dateInfo = m_dateInfo_st; ///shallow copy 
    reservedChunk_st.timeInfo = m_timeInfo_st;  ///shallow copy 
}

void RTCConfigEventHandler::flushRTCConfig(void)
{
    setRTCConfigMode(RTCConfigOption::MAXCONFIG);
    setRTCDateInfo(DateInfo{0U, 0U, 0U});
    setRTCTimeInfo(TimeInfo{0U, 0U, 0U});
}

}//end of namespace menu
 
