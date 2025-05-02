#ifndef LEDRECEIVERPORT_HPP
#define LEDRECEIVERPORT_HPP

#include "port/ReceiverPortDef.hpp"
#include "menu/MenuPortIntf.hpp"

namespace Port
{
  using LedModuleReceiverPort = ReceiverPortUserType<LEDModeReqInf>;
  extern LedModuleReceiverPort g_LedModeReceiverPort_st;
}

#endif
