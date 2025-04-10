#ifndef NETSENDERPORT_HPP
#define NETSENDERPORT_HPP

#include "port/SenderPortDef.hpp"
#include "led/LedReceiverPort.hpp"
#include "NetPortIntf.hpp"

namespace Port
{
  class LedModuleSenderPort: public SenderPortUserType<2U, LedModuleReceiverPort, LEDModeReqInf>
  {
    public:
      LedModuleSenderPort() = default;
      ~LedModuleSenderPort() = default;

    private:
      LedModuleSenderPort(const LedModuleSenderPort&) = delete;
      LedModuleSenderPort(LedModuleSenderPort&&) = delete;
      LedModuleSenderPort& operator=(LedModuleSenderPort&) = delete;
      LedModuleSenderPort& operator=(LedModuleSenderPort&&) = delete;

  };

  extern Port::LedModuleSenderPort g_netSenderPort_st;
}

#endif
