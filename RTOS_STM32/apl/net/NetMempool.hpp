#ifndef NETMEMPOOL_HPP
#define NETMEMPOOL_HPP

#include "mempool/mempool.hpp"
#include "NetPortIntf.hpp"

namespace mempool 
{
  using NetLedModeMempool = TChangeableMemPool<Port::LEDModeReqInf, 2U>;
  extern NetLedModeMempool g_netLedModeMempool_str; 
}


#endif

