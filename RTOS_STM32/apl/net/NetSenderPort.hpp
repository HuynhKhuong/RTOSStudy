#ifndef NETSENDERPORT_HPP
#define NETSENDERPORT_HPP

#include "port/SenderPortDef.hpp"
#include "led/LedReceiverPort.hpp"
#include "NetPortIntf.hpp"

namespace Port
{
  using LedModuleSenderPort = SenderPort<2U, LedModuleReceiverPort, LEDModeReqInf>;

  extern Port::LedModuleSenderPort g_netSenderPort_st;
}

#endif
