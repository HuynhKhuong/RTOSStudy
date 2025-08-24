#include "RTCConfigEventHandler.hpp"
#include "menu/MenuSenderPort.hpp"

namespace Menu 
{
void RTCConfigEventHandler::handle(void) 
{
  
}

void RTCConfigEventHandler::flushRTCConfig(void)
{
    setRTCConfigMode(RTCConfigOption::MAXCONFIG);
    setRTCDateInfo(DateInfo{0U, 0U, 0U});
    setRTCTimeInfo(TimeInfo{0U, 0U, 0U});
}

}//end of namespace menu
 
