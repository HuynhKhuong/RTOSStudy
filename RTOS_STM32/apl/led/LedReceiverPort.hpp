#ifndef LEDRECEIVERPORT_HPP
#define LEDRECEIVERPORT_HPP

#include "port/QueuePortDef.hpp"
#include "net/NetPortIntf.hpp"

namespace Port
{

class LedModuleReceiverPort: public QueueReceiverPort<LEDModeReqInf>
{
  public:
    LedModuleReceiverPort() = default;
    ~LedModuleReceiverPort() = default;
};

}

#endif
