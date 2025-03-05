#ifndef PORTDEF_INCLUDED
#define PORTDEF_INCLUDED

///\brief Definition of a sender/receiver port which is a wrapper implementing 
///       different synchronization mechanism
#include <stdint.h>
#include "utils/foundation_utils.hpp"

extern "C"
{
#include "FreeRTOS.h" ///required FreeRTOS.h before #include queue.h
#include <queue.h>
}

namespace Port
{
  template<typename PortInterface>
  class ReceiverPort
  {
    public:
      ReceiverPort() = default;
      ///\brief interface each synchronization method must implement
      virtual bool hasNewData(void) = 0;
      virtual bool hasData(void) = 0;
      virtual bool isConnected(void) const = 0;
      virtual bool update(void) = 0;
      virtual void disconnect(void) = 0;
      virtual void connect(QueueHandle_t const queuePtr) = 0;
  };

  template<typename PortInterface, uint8_t MaxNumbOfSubscribers>
  class SenderPort
  {
    public:
      SenderPort()
      {

        for(auto iterator = m_receiveSubsriberList.begin();
        		iterator != m_receiveSubsriberList.end();
        		iterator++)
        {
        	(*iterator) = nullptr;
        }
      }

      ///\brief interface each synchronization method must implement
      virtual PortInterface& reserve(void) = 0;
      virtual void deliver(void) = 0;
      virtual void connect(void) = 0;

    protected:
      void disconnect(void)
      {
        for (auto element: m_receiveSubsriberList) 
        {
          if(element != nullptr)
          {
            element->disconnect();
            element = nullptr;
          }
        }
      }
      vfc::array<ReceiverPort<PortInterface>*, MaxNumbOfSubscribers> m_receiveSubsriberList;
  };
}

#endif

