#ifndef RTCRECEIVERPORT_HPP
#define RTCRECEIVERPORT_HPP

#include "port/ReceiverPortDef.hpp"
#include "menu/MenuPortIntf.hpp"

namespace Port
{
    using RTCConfigDataReceiverPort = ReceiverPortUserType<Port::RTCConfigDataInf>;
    extern RTCConfigDataReceiverPort g_rtcConfigDataReceiverPort_st;
}

#endif
