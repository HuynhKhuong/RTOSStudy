#ifndef RECEIVER_CONNECTION_EXT_HPP
#define RECEIVER_CONNECTION_EXT_HPP

extern "C"
{
#include "FreeRTOS.h" ///required FreeRTOS.h before #include queue.h
#include <queue.h>
}

namespace extension
{
  template<typename MixinType>
  class ReceiverConnection: public MixinType
  {
    public:
      using Mixin_t = MixinType;
      using MediumType_t = typename Mixin_t::MediumType_t;
      ReceiverConnection() = default;
      ~ReceiverConnection() = default;

      void disconnect(void) 
      {
        MediumType_t* l_transporter_pst{Mixin_t::getTransporter()};
        *(l_transporter_pst) = nullptr;
      }

      void connect(MediumType_t const queuePtr) 
      {
        MediumType_t* l_transporter_pst{Mixin_t::getTransporter()};
        *(l_transporter_pst) = queuePtr;
      }

      bool isConnected(void) 
      {
        const MediumType_t* l_transporter_pst{Mixin_t::getTransporter()};
		return (*(l_transporter_pst)!= nullptr);
      }

    private:
      ReceiverConnection(const ReceiverConnection&) = delete;
      ReceiverConnection(ReceiverConnection&&) = delete;
      ReceiverConnection& operator=(ReceiverConnection&) = delete;
      ReceiverConnection& operator=(ReceiverConnection&&) = delete;
  };
}//end of namespace extension

#endif

