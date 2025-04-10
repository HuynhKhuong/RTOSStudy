#ifndef CONNECTION_EXT_HPP
#define CONNECTION_EXT_HPP

extern "C"
{
#include "FreeRTOS.h" ///required FreeRTOS.h before #include queue.h
#include <queue.h>
}

namespace extension
{
  template<typename MixinType>
  class Connection: public MixinType
  {
    public:
      using Mixin_t = MixinType;
      using Subscriber_t = typename MixinType::Subscriber_t;

      Connection() = default;

      ~Connection()
      {
        disconnect();
        vQueueDelete(m_internalQueueContainer);
      }
      
      void init(void)
      {
        const UBaseType_t uxItemSize{Mixin_t::getChunkSize()};
        m_internalQueueContainer = xQueueCreate(Mixin_t::MAX_SUBSCRIBERS, uxItemSize);
      }

      ///\brief connect a subscriber to sender port
      ///       trigger connect from the subscriber as well
      void connect(Subscriber_t& subscriber)
      {
        if(Mixin_t::addSubscriber(subscriber))
        {
          subscriber.connect(m_internalQueueContainer);
        }
      }

      ///\brief Return the information whether at leset on subscriber is connected
      bool isConnected(void)
      {
        return (Mixin_t::getCurrentNumberOfSubscriber() != 0U);
      }

      ///\brief disconnect sender port from all receiver ports
      void disconnect(void)
      {
        const SubscriberList_t& subscriberList = Mixin_t::getReleaseList();
        typename SubscriberList_t::const_iterator itr = subscriberList.begin();
        typename SubscriberList_t::const_iterator itrEnd = subscriberList.end();  

        for(; itrEnd != itr; itr++)
        {
          if((*itr) != nullptr)
          {
            (*itr)->disconnect();  
        }
        }

        Mixin_t::cleanSubscriber();
      }

    private:
      Connection(const Connection&) = delete;
      Connection(Connection&&) = delete;
      Connection& operator=(Connection&) = delete;
      Connection& operator=(Connection&&) = delete;

      QueueHandle_t m_internalQueueContainer{nullptr};
  };
}// end of namespace extension
 
#endif

