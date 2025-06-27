#ifndef NETMEMPOOL_HPP
#define NETMEMPOOL_HPP

#include "mempool/mempool.hpp"
#include "MenuPortIntf.hpp"

namespace mempool 
{
  using MenuLedModeMempool = TChangeableMemPool<Port::LEDModeReqInf, 2U>;
  using MenuStateInfoMempool = TChangeableMemPool<Port::StateInfoInf, 2U>;

  extern MenuStateInfoMempool g_menuStateInfoMempool_str;
  extern MenuLedModeMempool g_menuLedModeMempool_str; 
}


#endif

