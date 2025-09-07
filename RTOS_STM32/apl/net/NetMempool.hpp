#ifndef NET_MEMPOOL_HPP
#define NET_MEMPOOL_HPP

#include "mempool/mempool.hpp"
#include "net/NetPortIntf.hpp"

namespace mempool 
{
  using RTCReqInfMempool = TChangeableMemPool<Port::RTCReqInf, 2U>;

  extern RTCReqInfMempool g_rtcReqInfMempool_str;
}

#endif

