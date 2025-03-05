#include "NetSenderPort.hpp"
#include "led/LedRunnable.hpp"

namespace Port
{

void LedModuleSenderPort::m_customerConnect(void) 
{
  BaseClass::m_receiveSubsriberList[0U] = &(LedCom::g_myLedRunnable_st->m_LedModeSourcePort);
}

}

