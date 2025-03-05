#ifndef NETSENDERPORT_HPP
#define NETSENDERPORT_HPP

#include "NetPortIntf.hpp"
#include "port/QueuePortDef.hpp"

namespace Port
{

class LedModuleSenderPort: public QueueSenderPort<LEDModeReqInf, 1U>
{
  public:
    using BaseClass = QueueSenderPort<LEDModeReqInf, 1U>;
    ~LedModuleSenderPort() = default;

    static LedModuleSenderPort& getPortSingleton(void)
    {
      static LedModuleSenderPort l_privModulePort_st;
      return l_privModulePort_st;
    }

  protected:
    using BaseClass::m_receiveSubsriberList;
    void m_customerConnect(void) override;

  private:
    LedModuleSenderPort()
    {
      connect();
    }

};

}

#endif
