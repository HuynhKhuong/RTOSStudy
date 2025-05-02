#ifndef NETSENDERPORT_HPP
#define NETSENDERPORT_HPP

#include "port/SenderPortDef.hpp"
#include "menu/MenuReceiverPort.hpp"

namespace Port
{
  
  using MenuModuleSenderPort = SenderPortLightWeight<1U, MenuReceiverPort, uint32_t>;

  extern MenuModuleSenderPort g_netMenuSenderPort_st;

}

#endif
