#ifndef NETRECEIVERPORT_HPP
#define NETRECEIVERPORT_HPP

#include "ReceiverPortDef.hpp"
#include "MenuPortIntf.hpp"
#include "rtc/TimeDataItf.hpp"

namespace Port
{
    using StateInfoReceiverPort = ReceiverPortUserType<StateInfoInf>;
    using TimeDataReceiverPort = ReceiverPortUserType<TimeDataItf>;

    extern StateInfoReceiverPort g_netStateInfoReceiverPort_st;
    extern TimeDataReceiverPort g_netTimeDataReceiverPort_st;
}

#endif
