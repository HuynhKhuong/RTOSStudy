#ifndef EXTENSION_HPP_INCLUDED
#define EXTENSION_HPP_INCLUDED

#include "container/container.hpp"

namespace extension
{

///\brief ReferenceCounter 
///       does the deposit handling of (port data to deliver) and (delivered chunk)
///       deposit handling is done via a reference counter of the chunk
///       Port data to deliver will be dispatched to assign subscriber list during the deliver. 
///       Before a new chunk is reserved, the retrieval of port data of the release subscriber list is done
///       Both lists have to be provided by the lower extension layer.
///
template<typename MixinType>
class ReferenceCounter: public MixinType
{
  public: 
    using Minxin_t = MixinType;
    using PortDataBase_t = Container::CInternal;

    ReferenceCounter() = default;

    void setRef(PortDataBase_t& chunk, uint16_t subscriberCount)
    {
        chunk.m_referenceCounter = subscriberCount;
    }

    ///\brief releaseChunk forward call to lower layer
    void releaseChunk(PortDataBase_t& chunk)
    {
      Minxin_t::releaseChunk(static_cast<void*>(&chunk));
    }

    ///\brief getChunk forward call to lower layer
    PortDataBase_t* getChunk(void)
    {
      return static_cast<PortDataBase_t*>(Minxin_t::getChunk());
    }
    
    ///\brief method is called if a deposit is release from a subscriber.
    ///       On release will decrement the reference counter of the returned port data
    ///       If no one is subscribed to the port data anymore, the port data will be freed
    bool releaseRef(PortDataBase_t& chunk, uint16_t subscriberCount)
    {
      bool retVal{false};
      if(chunk.m_referenceCounter < subscriberCount)
      { 
        //do nothing
      } 
      else 
      {
          chunk.m_referenceCounter-=subscriberCount;
          if(chunk.m_referenceCounter == 0)
          {
            releaseChunk(chunk); 
            retVal = true;
          }
      }

      return retVal;
    }

  private:
    ReferenceCounter(const ReferenceCounter&) = delete;
    ReferenceCounter(ReferenceCounter&&) = delete;
    ReferenceCounter& operator=(ReferenceCounter&) = delete;
    ReferenceCounter& operator=(ReferenceCounter&&) = delete;
};

}//end of namespace extension

#endif

