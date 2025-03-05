#ifndef QUEUEPORTDEF_HPP
#define QUEUEPORTDEF_HPP

#include "PortDef.hpp"

extern "C"
{
#include "FreeRTOS.h" ///required FreeRTOS.h before #include queue.h
#include <queue.h>
}

namespace Port
{
  template<typename PortInterface>
  class QueueReceiverPort: public ReceiverPort<PortInterface>
  {
    public:
      using BaseClass = ReceiverPort<PortInterface>;
      QueueReceiverPort() = default;
      ~QueueReceiverPort();
      
      ///\brief interface each synchronization method must implement
      bool isConnected(void) const override;
      bool hasNewData(void) override;
      bool hasData(void) override;
      bool update(void) override;

      ///\brief simple operator overloading for user to retrieve data
      const PortInterface& operator()(void) const;

      ///\brief  disconnect is the way QueueReceiverPort release the QueueHandler
      ///\note   QueueReceiverPort can release the resource explicitly (external call) or
      ///        implicitly if the SenderPort release the QueueHandler
      void disconnect(void) override;

      ///\brief   connection is made when QueueReceiverPort & QueueSenderPort holds the same QueueHandler
      ///\note    Must consider how QueueReceiverPort is holding/releaseing QueueHandler
      ///         Hence, connection to Receiver Port could only be established when requested from SenderPort
      void connect(QueueHandle_t const queuePtr) override;
      
    private:
      /*
       * typedef struct QueueDefinition* QueueHandle_t;
       */
      QueueHandle_t m_internalQueueContainer{nullptr};
      PortInterface m_internalDataContainer{};
      bool m_isNewDataReceived{false};
  };

  template<typename PortInterface, uint8_t MaxNumbOfSubscribers>
  class QueueSenderPort:public SenderPort<PortInterface, MaxNumbOfSubscribers>
  {
    public:
      using BaseClass = SenderPort<PortInterface, MaxNumbOfSubscribers>;
      QueueSenderPort();
      ~QueueSenderPort();

      ///\brief reserve method allows user to retrieve the actual container which shall be delivered
      ///       on Queue to Receiver
      ///\note  some usecases, in which the Queue is full, causes the latest container not able to be pushed into 
      ///       queue, sender port shall wait the queue to be free to push lastest container.
      ///       current container called by reserve shall be discarded by returning FALSE
      PortInterface& reserve() override;
      void deliver(void) override;
    protected:
      using BaseClass::m_receiveSubsriberList;

      ///\brief customer customized logic to connect to desired ReceiverPort
      virtual void m_customerConnect(void) = 0;

      void connect(void) override;
      void disconnect(void)
      {
        BaseClass::disconnect();

        vQueueDelete(m_internalQueueContainer);
        m_internalQueueContainer = nullptr;
      }
    private:
      /*
       * typedef struct QueueDefinition* QueueHandle_t;
       */
      QueueHandle_t m_internalQueueContainer{nullptr};
      PortInterface m_internalDataContainer{};
      bool m_isReservedAvailable_bo{false};
  };
}

#include "QueuePortDef.inl"

#endif

