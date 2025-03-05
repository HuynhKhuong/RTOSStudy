#include "QueuePortDef.hpp"
#include "port/PortDef.hpp"

namespace Port
{
  template<typename PortInterface>
  QueueReceiverPort<PortInterface>::~QueueReceiverPort()
  {
    disconnect();
  }

  template<typename PortInterface>
  void QueueReceiverPort<PortInterface>::connect(QueueHandle_t const queuePtr) 
  {
    m_internalQueueContainer = queuePtr;
  }

  template<typename PortInterface>
  void QueueReceiverPort<PortInterface>::disconnect(void)
  {
    m_internalQueueContainer = nullptr;
  }

  template<typename PortInterface>
  bool QueueReceiverPort<PortInterface>::isConnected(void) const
  {
    return (m_internalQueueContainer != nullptr);
  }

  template<typename PortInterface>
  bool QueueReceiverPort<PortInterface>::update(void)
  {
    bool retStatus{false};
    if(isConnected())
    {
      retStatus = xQueueReceive(m_internalQueueContainer, static_cast<void*>(&m_internalDataContainer), 0U);
    }

    m_isNewDataReceived = retStatus;
    return retStatus;
  }

  template<typename PortInterface>
  bool QueueReceiverPort<PortInterface>::hasData(void)
  {
    return (m_internalDataContainer.getSequenceCounter() != 0U);
  }

  template<typename PortInterface>
  bool QueueReceiverPort<PortInterface>::hasNewData(void)
  {
    bool retVal = m_isNewDataReceived;
    m_isNewDataReceived = false;

    return retVal; 
  }

  template<typename PortInterface>
  const PortInterface& QueueReceiverPort<PortInterface>::operator()(void) const
  {
    return m_internalDataContainer;
  }

  template<typename PortInterface, uint8_t MaxNumbOfSubscribers>
  QueueSenderPort<PortInterface, MaxNumbOfSubscribers>::QueueSenderPort()
  {
    constexpr UBaseType_t uxItemSize{sizeof(PortInterface)};
    m_internalQueueContainer = xQueueCreate(MaxNumbOfSubscribers, uxItemSize);
  }

  template<typename PortInterface, uint8_t MaxNumbOfSubscribers>
  QueueSenderPort<PortInterface, MaxNumbOfSubscribers>::~QueueSenderPort()
  {
    disconnect(); //SenderPort is no longer used
  }

  template<typename PortInterface, uint8_t MaxNumbOfSubscribers>
  void QueueSenderPort<PortInterface, MaxNumbOfSubscribers>::connect(void) 
  {
    m_customerConnect();
    for (auto element: BaseClass::m_receiveSubsriberList) 
    {
      if(element != nullptr)
      {
        element->connect(m_internalQueueContainer);
      }
    }
  }

  template<typename PortInterface, uint8_t MaxNumbOfSubscribers>
  PortInterface& QueueSenderPort<PortInterface, MaxNumbOfSubscribers>::reserve(void)
  {
    return m_internalDataContainer;
  }

  template<typename PortInterface, uint8_t MaxNumbOfSubscribers>
  void QueueSenderPort<PortInterface, MaxNumbOfSubscribers>::deliver(void)
  {
    if((m_internalQueueContainer != nullptr)&&(uxQueueSpacesAvailable(m_internalQueueContainer) != 0U))
    {
        m_internalDataContainer.increaseSequenceCounter();
        static_cast<void>(xQueueSend(m_internalQueueContainer, &m_internalDataContainer, 0U));
    }
  }
}///end of namespace Port

