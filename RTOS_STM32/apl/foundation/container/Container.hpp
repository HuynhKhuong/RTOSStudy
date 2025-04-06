#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <stdint.h>

///debug purpose
namespace mempool
{
  class CChangeableMemPoolStorage;
}


namespace Container
{
  ///\brief  Free chunk list is organized as a linked list: 
  ///        - getChunk shall pop the tail of the linked list
  ///        - release Chunk shall insert to the tail of the linked list
  ///        With that being said, A base class organizing linked list behavior shall be created for all
  ///        Chunk member
  class Chunk
  {
    public:
      enum class LimitValue: uint16_t
      {
        Tail_Next = 65535U,
        Head_Prev = 65534U
      };

      void initVal(uint16_t next_u16, uint16_t prev_u16, uint16_t curr_u16, uint16_t listSize_u16)
      {
        m_next_u16 = next_u16;
        m_prev_u16 = prev_u16;
        m_curr_u16 = curr_u16;
        g_listSize_u16 = listSize_u16;
      }

      uint16_t getPrev(void) const
      {
        return m_prev_u16;
      }

      uint16_t getNext(void) const
      {
        return m_next_u16;
      }

      uint16_t getCurr(void) const
      {
        return m_curr_u16;
      }
      
      static void popBack(Chunk& currentTail, Chunk& prevOfTail, uint16_t& traceTailIndex_u16)
      {
        ///\rationale: in case there's only head in the list, Head Element = Tail Element  
        ///            if so, prevOfTail is not a valid element
        if(currentTail.getPrev() != static_cast<uint16_t>(LimitValue::Head_Prev))
        {
          prevOfTail.setNext(static_cast<uint16_t>(LimitValue::Tail_Next));
          traceTailIndex_u16 = prevOfTail.m_curr_u16;
        }
        else
        {
          traceTailIndex_u16 = static_cast<uint16_t>(LimitValue::Head_Prev);
        }
      }

      static void pushBack(Chunk& toPushElement, Chunk& currentTail, uint16_t& traceTailIndex_u16)
      {
        ///\rationale (A) - special handling if the list is empty: user is allowed to write into list
        ///                 currenTail is not valid
        ///           (B) - if the list is not full: user is allowed to write into list, currentTail is a valid tail
        ///           (C) - [to be handled by user]special handling if the list is full: user is not allowed to write into list
        ///
        if(traceTailIndex_u16 == static_cast<uint16_t>(LimitValue::Head_Prev)) ///(A)
        {
          toPushElement.setNext(static_cast<uint16_t>(LimitValue::Tail_Next));
          toPushElement.setPrev(static_cast<uint16_t>(LimitValue::Head_Prev));

          traceTailIndex_u16 = toPushElement.getCurr();
        }
        else ///(B)
        {
          currentTail.setNext(toPushElement.getCurr());
          toPushElement.setNext(static_cast<uint16_t>(LimitValue::Tail_Next));
          toPushElement.setPrev(currentTail.getCurr());

          traceTailIndex_u16 = toPushElement.getCurr();
        }
      }

    private:
      ///\brief Dynamic position setup for dynamic pop/push tail in the flat array of linkedlist
      void setPrev(uint16_t const prev)
      {
        m_prev_u16 = prev;
      }

      void setNext(uint16_t const next)
      {
        m_next_u16 = next;
      }

      ///\note  special limit values:
      ///       next in tail: 65535      
      ///       prev in head: 65534
      uint16_t m_next_u16;
      uint16_t m_prev_u16;
      uint16_t m_curr_u16;///current index of element in the list    
      uint16_t g_listSize_u16;///size 
  };

  ///\brief CInternal class is the parent class which provides standard info like sequence number and 
  ///       reference counter
  ///\note  As PortData shall be queried from a chunk list managed by a storage handler
  ///       It must inherit from a LinkedList member handler
  class CInternal: public Chunk
  {
      public:
        using ReferenceCounter_t = uint16_t;

        CInternal() = default;
        ~CInternal() = default;
        
        ///Special handling on copying mechanism as chunk might be copied
        ///in various system context
        bool operator==(const CInternal& that) const 
        {
          return ((that.m_sequenceCounter == m_sequenceCounter) && 
                  (that.m_referenceCounter == m_referenceCounter));
        }

        bool operator!=(const CInternal& that) const 
        {
          return !operator==(that);
        }

        ///prevent copying overidding internal data
        CInternal& operator=(const CInternal& that)
        {
          return *this;
        }

        void prepareForDeliver(uint16_t sequenceCounter)
        {
          m_sequenceCounter = sequenceCounter;
        }

        uint16_t m_referenceCounter{0U};///size 
        uint16_t m_sequenceCounter{0U};///size 
  };
}//end of namespace Container
#endif

