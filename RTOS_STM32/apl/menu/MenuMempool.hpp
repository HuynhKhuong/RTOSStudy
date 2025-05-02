#ifndef NETMEMPOOL_HPP
#define NETMEMPOOL_HPP

#include "mempool/mempool.hpp"
#include "MenuPortIntf.hpp"

namespace mempool 
{
  using MenuLedModeMempool = TChangeableMemPool<Port::LEDModeReqInf, 2U>;
  extern MenuLedModeMempool g_menuLedModeMempool_str; 
}


#endif

