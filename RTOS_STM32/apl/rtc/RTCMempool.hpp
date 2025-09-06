#ifndef RTCMEMPOOL_HPP
#define RTCMEMPOOL_HPP

#include "TimeDataItf.hpp"
#include "mempool/mempool.hpp"

namespace mempool
{

using TimeDataMempool = TChangeableMemPool<Port::TimeDataItf, 3U>;

extern TimeDataMempool g_timeDataMempool_st;

}
#endif
