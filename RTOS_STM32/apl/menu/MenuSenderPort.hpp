#ifndef MENUSENDERPORT_HPP
#define MENUSENDERPORT_HPP


#include "SenderPortDef.hpp"
#include "led/LedReceiverPort.hpp"
#include "MenuPortIntf.hpp"

namespace Port
{
  using LedModuleSenderPort = SenderPort<2U, LedModuleReceiverPort, LEDModeReqInf>;

  extern LedModuleSenderPort g_menuLedSenderPort_st;
}

#endif
