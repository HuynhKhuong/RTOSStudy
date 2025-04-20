#ifndef LATESTRESERVE_EXT_HPP
#define LATESTRESERVE_EXT_HPP

#include <stdint.h>

namespace extension
{
  ///\brief Extension to deliver current reserved mempool storage
  ///\details Reserve a valid mempool storage and deliver it. 
  ///         Ensure that only one chunk can be reserved at the same time. 
  ///         If a chunk has been reserved before and haven't been delivered, the current reserved chunk will be returend
  ///
  template <typename MixinType>  
  class LatestReserve: public MixinType
  {
    public:
      using Mixin_t = MixinType;
      using PortDataBase_t = typename MixinType::PortDataBase_t; 
      using ReferenceCounter_t = typename PortDataBase_t::ReferenceCounter_t;    
      using SubscriberList_t = typename MixinType::SubscriberList_t;
      using SubscriberType_t = typename MixinType::Subscriber_t;

      LatestReserve() = default;
      ~LatestReserve() = default;
      
      PortDataBase_t& reserveRaw(void)
      {
        return reserve(); 
      }
      
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
        collectDeposits();
        return Mixin_t::reserveIntern();
      }

      ///\brief Store the last deliered address. This information can be requested by user via getLastDelivery()
      void deliverIntern(PortDataBase_t& currentStorage)
      {
        Mixin_t::deliverIntern(currentStorage);
        
        // Before dispatching new data, make sure to collect all deposits
        collectDeposits();

        const SubscriberList_t& subscriberList = Mixin_t::getReleaseList();
        dispatch(subscriberList, currentStorage);
      }

      ///\brief Collect deposits from every subscriber 
      ///       All release request shall be collected.
      void collectDeposits(void)
      {
        const SubscriberList_t& subscriberList = Mixin_t::getReleaseList();
        typename SubscriberList_t::const_iterator itr = subscriberList.begin();
        typename SubscriberList_t::const_iterator itrEnd = subscriberList.end();  

        for(; itrEnd != itr; itr++)
        {
          //const SubscriberType_t* subscriber = (*itr);

          if((*itr) != nullptr)
          {
            PortDataBase_t* depositChunk{nullptr};
            static_cast<void>((*itr)->isReleased(&depositChunk));
            handleDeposit(depositChunk);
          }
        }
      }
      
      ///\brief Dispatch port data to every subscriber from subscriber list. 
      ///       Therefore, the assign API of the receiver is called.
      ///       The number of successful handleDispatches is count and returned
      void dispatch(const SubscriberList_t& subscriberList, const PortDataBase_t& portData)
      {
        uint16_t l_dispatchCount_u16{0U};
        typename SubscriberList_t::const_iterator itr = subscriberList.begin();
        typename SubscriberList_t::const_iterator itrEnd = subscriberList.end();  
        for(; itrEnd != itr; itr++)
        {
          //const SubscriberType_t* subscriber = (*itr);

          if((*itr) != nullptr)
          {
            PortDataBase_t* depositChunk{nullptr};
            const PortDataBase_t* portDataPtr{&portData};
            if((*itr)->assign(&portDataPtr, &depositChunk))
            {
              l_dispatchCount_u16++;
            }

            /// a new assignment could also trigger a release of pointer
            if(depositChunk != nullptr)
            {
              handleDeposit(depositChunk);
            }
          }
        }

        handleDispatches(l_dispatchCount_u16, &portData);
      }

    private: 
      void handleDeposit(const PortDataBase_t* portData_p)
      {
        if(portData_p != nullptr)
        {
          static_cast<void>(Mixin_t::releaseRef(*const_cast<PortDataBase_t*>(portData_p), 1U));
        }
      }

      void handleDispatches(uint16_t dispatchCount_u16, const PortDataBase_t* portData_p)
      {
        if(dispatchCount_u16 > 0)
        {
          Mixin_t::setRef(*const_cast<PortDataBase_t*>(portData_p), dispatchCount_u16);
        }
        else
        {
          Mixin_t::releaseChunk(*const_cast<PortDataBase_t*>(portData_p));
        }
      }

      LatestReserve(const LatestReserve&) = delete;
      LatestReserve(LatestReserve&&) = delete;
      LatestReserve& operator=(LatestReserve&) = delete;
      LatestReserve& operator=(LatestReserve&&) = delete;
      PortDataBase_t* m_currentStorage_p{nullptr};
  };
}

#endif

