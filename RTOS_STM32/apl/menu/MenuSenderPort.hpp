#ifndef MENUSENDERPORT_HPP
#define MENUSENDERPORT_HPP


#include "SenderPortDef.hpp"
#include "led/LedReceiverPort.hpp"
#include "net/NetReceiverPort.hpp"
#include "MenuPortIntf.hpp"

namespace Port
{
  using LedModuleSenderPort = SenderPort<2U, LedModuleReceiverPort, LEDModeReqInf>;
  using StateInfoSenderPort = SenderPort<2U, StateInfoReceiverPort, StateInfoInf>;

  extern LedModuleSenderPort g_menuLedSenderPort_st;
  extern StateInfoSenderPort g_menuStateInfoSenderPort_st;
}

#endif
