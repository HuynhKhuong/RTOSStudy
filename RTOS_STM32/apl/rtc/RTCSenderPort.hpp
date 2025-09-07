#ifndef RTCSENDERPORT_HPP
#define RTCSENDERPORT_HPP

#include "net/NetReceiverPort.hpp"
#include "port/SenderPortDef.hpp"
#include "TimeDataItf.hpp"

namespace Port
{

using TimeDataSenderPort = SenderPort<3U, TimeDataReceiverPort, TimeDataItf>;

extern TimeDataSenderPort g_rtcTimeDataSenderPort_st;

} // namespace Port

#endif
