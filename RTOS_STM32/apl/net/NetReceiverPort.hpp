#ifndef NETRECEIVERPORT_HPP
#define NETRECEIVERPORT_HPP

#include "ReceiverPortDef.hpp"
#include "MenuPortIntf.hpp"

namespace Port
{
  using StateInfoReceiverPort = ReceiverPortUserType<StateInfoInf>;
  extern StateInfoReceiverPort g_netStateInfoReceiverPort_st;
}

#endif
