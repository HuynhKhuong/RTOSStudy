#ifndef LATESTRESERVE_LIGHTWEIGHT_EXT_HPP
#define LATESTRESERVE_LIGHTWEIGHT_EXT_HPP

#include <stdint.h>

namespace extension
{
  ///\brief Extension to deliver current reserved mempool storage
  ///\details Reserve a valid mempool storage and deliver it. 
  ///         Ensure that only one chunk can be reserved at the same time. 
  ///         If a chunk has been reserved before and haven't been delivered, the current reserved chunk will be returend
  ///
  template <typename MixinType>  
  class LightweightReserve: public MixinType
  {
    public:
      using Mixin_t = MixinType;
      using PortDataBase_t = typename MixinType::PortDataBase_t; 
      using SubscriberList_t = typename MixinType::SubscriberList_t;
      using SubscriberType_t = typename MixinType::Subscriber_t;

      LightweightReserve() = default;
      ~LightweightReserve() = default;
      
      
      bool isReserved(void)
      {
        return (m_currentStorage_p != nullptr);
      }

      ///\brief reserve a mempool chunk to work on
      ///\details provides memory chunk to write in. The chunk correspond with a port datatype.
      ///         Chunk shall be published to the subscriber via deliver
      ///\note    Ensure that only one chunk can be reserved at the same time.
      PortDataBase_t* reserve(void)
      {
        if(!(isReserved()))
        {
          m_currentStorage_p = reserveIntern();
        }
        
        if(m_currentStorage_p == nullptr)
        {
          while(1){} //custom assertion
        }

        return m_currentStorage_p;
      }

      void deliver(void)
      {
        //do deliver only if there was reserve before
        if(isReserved())
        {
          deliverIntern(*m_currentStorage_p);
          m_currentStorage_p = nullptr;
        }
      }

    protected:

      ///\brief Extension handle: collect deposit from subscriber and  
      ///       do publish new reserved chunk
      PortDataBase_t* reserveIntern(void)
      {
        return Mixin_t::reserveIntern();
      }

      ///\brief Store the last deliered address. This information can be requested by user via getLastDelivery()
      void deliverIntern(PortDataBase_t& currentStorage)
      {
        Mixin_t::deliverIntern(currentStorage);
        const SubscriberList_t& subscriberList = Mixin_t::getReleaseList();
        dispatch(subscriberList, currentStorage);
      }
      
      ///\brief Dispatch port data to every subscriber from subscriber list. 
      ///       Therefore, the assign API of the receiver is called.
      ///       The number of successful handleDispatches is count and returned
      void dispatch(const SubscriberList_t& subscriberList, const PortDataBase_t& portData)
      {
        typename SubscriberList_t::const_iterator itr = subscriberList.begin();
        typename SubscriberList_t::const_iterator itrEnd = subscriberList.end();  
        for(; itrEnd != itr; itr++)
        {
          //const SubscriberType_t* subscriber = (*itr);
          if((*itr) != nullptr)
          {
            PortDataBase_t* depositChunk{nullptr};
            const PortDataBase_t* portDataPtr{&portData};
            static_cast<void>((*itr)->assign(&portDataPtr, depositChunk));
          }
        }
      }

    private: 
      LightweightReserve(const LightweightReserve&) = delete;
      LightweightReserve(LightweightReserve&&) = delete;
      LightweightReserve& operator=(LightweightReserve&) = delete;
      LightweightReserve& operator=(LightweightReserve&&) = delete;
      PortDataBase_t* m_currentStorage_p{nullptr};
  };
}

#endif

