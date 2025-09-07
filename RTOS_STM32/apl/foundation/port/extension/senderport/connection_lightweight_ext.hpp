#ifndef CONNECTION_LIGHTWEIGHT_EXT_HPP
#define CONNECTION_LIGHTWEIGHT_EXT_HPP

extern "C"
{
#include "FreeRTOS.h" ///required FreeRTOS.h before #include queue.h
#include <task.h>
}

namespace extension
{
  template<typename MixinType>
  class ConnectionLightWeight: public MixinType
  {
    public:
      using Mixin_t = MixinType;
      using SubscriberList_t = typename MixinType::SubscriberList_t;
      using Subscriber_t = typename MixinType::Subscriber_t;

      ConnectionLightWeight() = default;

      ~ConnectionLightWeight()
      {
        disconnect();
      }
      
      void init(void)
      {/*do nothing*/}

      ///\brief connect a subscriber to sender port
      void connect(Subscriber_t& subscriber)
      {
        static_cast<void>(Mixin_t::addSubscriber(subscriber));
      }

      ///\brief Return the information whether at leset on subscriber is connected
      bool isConnected(void)
      {
        return (Mixin_t::getCurrentNumberOfSubscriber() != 0U);
      }

      ///\brief disconnect sender port from all receiver ports
      void disconnect(void)
      {
        Mixin_t::cleanSubscriber();
      }

    private:
      ConnectionLightWeight(const ConnectionLightWeight&) = delete;
      ConnectionLightWeight(ConnectionLightWeight&&) = delete;
      ConnectionLightWeight& operator=(ConnectionLightWeight&) = delete;
      ConnectionLightWeight& operator=(ConnectionLightWeight&&) = delete;
  };
}// end of namespace extension
 
#endif

