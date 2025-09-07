#ifndef MENURECEIVERPORT_HPP
#define MENURECEIVERPORT_HPP

#include "ReceiverPortDef.hpp"
#include "net/NetPortIntf.hpp"

namespace Port
{
  using MenuReceiverPort = ReceiverPortUserTypeLightweight<uint32_t>;
  using MenuRTCConfigReceiverPort = ReceiverPortUserType<Port::RTCReqInf>;

  extern MenuReceiverPort g_menuReceiverPort_st;
  extern MenuRTCConfigReceiverPort g_menuRTCConfigReceiverPort_st;
}

#endif
