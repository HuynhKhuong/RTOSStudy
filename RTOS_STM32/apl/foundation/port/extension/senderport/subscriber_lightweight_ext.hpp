#ifndef SUBSCRIBER_LIGHTWEIGHT_EXT_HPP
#define SUBSCRIBER_LIGHTWEIGHT_EXT_HPP

#include "utils/foundation_utils.hpp"

namespace extension
{
  template <typename MixinType, typename SubscriberType, uint8_t MaxNumbOfSubscribers = 255U>  
  class LightWeightSubscriber: public MixinType
  {
    public: 
      using Mixin_t = MixinType;
      using PortDataBase_t = typename MixinType::PortDataBase_t; 
      using Subscriber_t= SubscriberType;
      using SubscriberList_t = vfc::array<Subscriber_t*, MaxNumbOfSubscribers>;

      enum {MAX_SUBSCRIBERS = MaxNumbOfSubscribers};  

      LightWeightSubscriber(): Mixin_t{}
      {
        cleanSubscriber();
      }
      
      ~LightWeightSubscriber() = default;
           
    protected: 
      ///\brief add a subscriber to current subscriber list
      ///\note  if the list is full already, return false
      ///       Subscriber which are already in the list won't be added twice
      bool addSubscriber(Subscriber_t& subscriber)
      {
        bool retVal{false};

        if(!isListFull())
        {
          if(memberExist(&subscriber))
          {
            ///do nothing
          }
          else
          {
            m_receiveSubsriberList[m_subsriberListLatestIdx_u8++] = &subscriber; 
            
          }

          retVal = true;          
        }

        return retVal; 
      }

      inline void cleanSubscriber(void)
      {
        for(auto iterator = m_receiveSubsriberList.begin();
        		iterator != m_receiveSubsriberList.end();
        		iterator++)
        {
        	(*iterator) = nullptr;
        }
        m_subsriberListLatestIdx_u8 = 0;
      }    

      const SubscriberList_t& getReleaseList(void) const 
      {
        return m_receiveSubsriberList;
      }
      
      uint8_t getCurrentNumberOfSubscriber(void) const 
      {
        return m_subsriberListLatestIdx_u8;
      }

    private:
      LightWeightSubscriber(const LightWeightSubscriber&) = delete;
      LightWeightSubscriber(LightWeightSubscriber&&) = delete;
      LightWeightSubscriber& operator=(LightWeightSubscriber&) = delete;
      LightWeightSubscriber& operator=(LightWeightSubscriber&&) = delete;
      
      vfc::array<Subscriber_t*, MaxNumbOfSubscribers> m_receiveSubsriberList;
      uint8_t m_subsriberListLatestIdx_u8;
      
      inline bool memberExist(Subscriber_t* subscriberPtr)
      {
        bool retVal{false};
        for(auto element:m_receiveSubsriberList)
        {
          if(element == subscriberPtr)
          {
            retVal = true;
            break;
          }
        }

        return retVal;
      }

      inline bool isListFull(void)
      {
        return (m_subsriberListLatestIdx_u8 == MaxNumbOfSubscribers); 
      }
  };
}//end of namespace extension

#endif

