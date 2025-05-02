#ifndef MENURECEIVERPORT_HPP
#define MENURECEIVERPORT_HPP

#include "ReceiverPortDef.hpp"

namespace Port
{
  using MenuReceiverPort = ReceiverPortUserTypeLightweight<uint32_t>;

  extern MenuReceiverPort g_menuReceiverPort_st;
}

#endif
