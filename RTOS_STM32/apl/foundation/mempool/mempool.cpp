#include "mempool.hpp"

namespace mempool
{
  bool CChangeableMemPoolStorage::validate(const void* const chunk_p) const
  {
    bool retVal_bo{true};
    const char* const l_chunkFree_p{static_cast<const char*>(chunk_p)};
    if(l_chunkFree_p == nullptr)
    {
      retVal_bo = false;
    }
    else 
    {
      if((l_chunkFree_p < m_memPoolbase_p)||(l_chunkFree_p > m_memPoolEnd_p))
      {
        retVal_bo = false; 
      }
      else
      {
        ///is chunk_p is properly aligned within the mempool?
        const vfc::ptrdiff_t chunkOffset
            {static_cast<vfc::ptrdiff_t>(static_cast<const char*>(chunk_p) - static_cast<const char*>(m_memPoolbase_p))};

        if(chunkOffset%static_cast<vfc::ptrdiff_t>(getChunkSize()) != 0)
        {
          retVal_bo = false; 
        }
      }
    }
    return retVal_bo;
  }

  void CChangeableMemPoolStorage::releaseChunk(void* chunk_p)
  {
    if(validate(chunk_p)) 
    {
      Container::Chunk& chunk = *(static_cast<Container::Chunk*>(chunk_p));
      if(m_freeListHeadID == static_cast<uint16_t>(Container::Chunk::LimitValue::Head_Prev))
      {
        Container::Chunk::pushBack(chunk, chunk,  m_freeListHeadID);
      }
      else
      {
        if(m_minFreeCurrent < getChunkCount())
        {
          const uint16_t chunkSize_cu16 = static_cast<uint16_t>(getChunkSize());
          const uint16_t freeChunkOffset = chunkSize_cu16*(static_cast<uint16_t>(m_freeListHeadID) - 1U);
          void* tempPtr = static_cast<void*>(m_memPoolbase_p + freeChunkOffset);
          Container::Chunk* const freeChunkHead_p = static_cast<Container::Chunk*>(tempPtr);

          Container::Chunk::pushBack(chunk, (*freeChunkHead_p),  m_freeListHeadID);

          m_minFreeCurrent++;
        }
      }
    }
  }

  void* CChangeableMemPoolStorage::getChunk(void)
  {
    void* returnVal;

    if(isEmpty())
    {
      returnVal = nullptr;
    }
    else
    {
      const uint16_t chunkSize_cu16 = static_cast<uint16_t>(getChunkSize());
      const uint16_t freeChunkOffset = chunkSize_cu16*(static_cast<uint16_t>(m_freeListHeadID) - 1U);
      void* tempPtr = static_cast<void*>(m_memPoolbase_p + freeChunkOffset);

      Container::Chunk* const freeChunkHead_p = static_cast<Container::Chunk*>(tempPtr); 
      returnVal = static_cast<void*>(freeChunkHead_p);

      if(freeChunkHead_p->getPrev() == static_cast<uint16_t>(Container::Chunk::LimitValue::Head_Prev))
      {
        Container::Chunk::popBack((*freeChunkHead_p), (*freeChunkHead_p),  m_freeListHeadID);
      }
      else
      {
        const uint16_t nextfreeChunkOffset_cu16 = chunkSize_cu16*(static_cast<uint16_t>(freeChunkHead_p->getPrev()) - 1U);
        void* tempPtr1 = static_cast<void*>(m_memPoolbase_p + nextfreeChunkOffset_cu16);
        Container::Chunk* const freeChunkHead1 = static_cast<Container::Chunk*>(tempPtr1); 
        Container::Chunk::popBack((*freeChunkHead_p), (*(freeChunkHead1)),  m_freeListHeadID);
      }

      ///Underflow has not to be considered There can't be more chunks provided as 
      ///available
      m_minFreeCurrent--;

      if(m_minFreeEver > m_minFreeCurrent)
      {
        m_minFreeEver = m_minFreeCurrent;
      }
    }
    return returnVal;
  }

  uint16_t CChangeableMemPoolStorage::getChunkCount(void) const
  {
    return m_chunkCount;
  }
  
  uint16_t CChangeableMemPoolStorage::getChunkSize(void) const
  {
    ///\todo should we have a validate statement to ensure [m_memPoolEnd_p > m_memPoolbase_p]?
    const vfc::ptrdiff_t memPoolSize = m_memPoolEnd_p - m_memPoolbase_p;
    const vfc::ptrdiff_t chunkSize = memPoolSize/static_cast<vfc::ptrdiff_t>(getChunkCount());  

    return static_cast<uint16_t>(chunkSize);
  }

  uint16_t CChangeableMemPoolStorage::getChunkID(const void* const chunk_p) const
  {
    const char* const l_chunk_p = static_cast<const char*>(chunk_p);

    const vfc::ptrdiff_t chunkOffset = l_chunk_p - m_memPoolbase_p; 
    const vfc::ptrdiff_t chunkSize = static_cast<vfc::ptrdiff_t>(getChunkSize());

    const vfc::ptrdiff_t indexOffset{1U};
    const vfc::ptrdiff_t id = (chunkOffset/chunkSize)  + indexOffset;
    return id;
  }

  bool CChangeableMemPoolStorage::isEmpty(void) const
  {
    return (m_freeListHeadID == static_cast<uint16_t>(Container::Chunk::LimitValue::Head_Prev));
  }

  ///\todo validate statement to ensure [m_memPoolEnd_p > m_memPoolbase_p]?
  void CChangeableMemPoolStorage::init(void* memPoolBase_p, const void* const memPoolEnd_p, const uint16_t chunkSize)
  {
    m_memPoolbase_p = reinterpret_cast<char*>(memPoolBase_p);
    m_memPoolEnd_p = reinterpret_cast<const char*>(memPoolEnd_p);
    
    const vfc::ptrdiff_t memPoolSize = m_memPoolEnd_p - m_memPoolbase_p;
    const vfc::ptrdiff_t chunkCount = memPoolSize/static_cast<vfc::ptrdiff_t>(chunkSize); 
    m_chunkCount = chunkCount;
    m_minFreeEver = m_chunkCount;
    m_minFreeCurrent = m_chunkCount;
    initializer();
  }

  void CChangeableMemPoolStorage::initializer(void)
  {
    const vfc::ptrdiff_t chunkSize{static_cast<vfc::ptrdiff_t>(getChunkSize())};

    uint16_t curIdx_u16{1U};
    uint16_t preIdx_u16{static_cast<uint16_t>(Container::Chunk::LimitValue::Head_Prev)};
    uint16_t nextIdx_u16{2U};
    uint16_t curTail_u16{curIdx_u16};
    const char* const lastElement_pcc{m_memPoolEnd_p - chunkSize};
    for(char* chunk_p{m_memPoolbase_p}; chunk_p < m_memPoolEnd_p; chunk_p+=chunkSize)
    {
    
      Container::Chunk& chunk = *(static_cast<Container::Chunk*>(static_cast<void*>(chunk_p)));
      if(chunk_p == lastElement_pcc)  ///for the final element: tails' next shall be marked with limit value
      {
        nextIdx_u16 = static_cast<uint16_t>(Container::Chunk::LimitValue::Tail_Next); 
        chunk.initVal(nextIdx_u16, preIdx_u16, curIdx_u16, getChunkCount());
      }
      else
      {
        chunk.initVal(nextIdx_u16, preIdx_u16, curIdx_u16, getChunkCount());
        preIdx_u16 = curIdx_u16;
        curIdx_u16 = nextIdx_u16;
        nextIdx_u16 = curIdx_u16+1U; 
        curTail_u16 = curIdx_u16;
      }
    }
    m_freeListHeadID = curTail_u16; 
  }
}//end of namespace mempool
 

