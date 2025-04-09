#ifndef MEMPOOLINTERFACE_HPP
#define MEMPOOLINTERFACE_HPP

#include "mempool.hpp"

namespace mempool
{
///\brief Mempool Interface. Enable the access from other SW entities to a specific mempool 
///       The connection has to be set at system init and is only valid if one mempool is 
///       connected 
///       Mempool Interface shall abstract chunk type by using pointers of void
class CMemPoolInterfaceBase
{
  public:
    CMemPoolInterfaceBase() = default;
    ~CMemPoolInterfaceBase() = default;

    bool isMempoolConnected(void)  const
    {
      return (m_pool_ptr != nullptr);
    }
    
    void connectMempool(void* pool_ptr)
    {
      if(!isMempoolConnected())
      {
        m_pool_ptr = pool_ptr;
      }
    }
    
    ///\note if one mempool is connected, API call shall return a valid  
    ///      pointer, otherwise, returns nullptr
    void* getMemPool()
    {
      return m_pool_ptr;
    }


  private:
    void* m_pool_ptr{nullptr};
    CMemPoolInterfaceBase(const CMemPoolInterfaceBase& that) = delete;
    CMemPoolInterfaceBase(CMemPoolInterfaceBase&& that) = delete;
    CMemPoolInterfaceBase& operator=(CMemPoolInterfaceBase& that) = delete;
    CMemPoolInterfaceBase& operator=(CMemPoolInterfaceBase&& that) = delete;
};

///\brief wrapper for easier access to mempool in comparison with base class 
class CMemPoolInterface: public CMemPoolInterfaceBase
{
  public:
    using Base_t = CMemPoolInterfaceBase;
    using Memory = TChangeableMemPoolBase;
    using PortDataBase_t = Memory::PortDataBase_t;  

    CMemPoolInterface() = default;
    ~CMemPoolInterface() = default;

    Memory& getMemPool(void)
    {
      return *(static_cast<Memory*>(Base_t::getMemPool())); 
    }

    void releaseRef(PortDataBase_t& chunk, uint16_t subscriberCount)
    {
      static_cast<void>(getMemPool().releaseRef(chunk, subscriberCount));
    }

    void setRef(PortDataBase_t& chunk, uint16_t subscriberCount)
    {
      getMemPool().setRef(chunk, subscriberCount);
    }
    
    void releaseChunk(PortDataBase_t& chunk)
    {
      getMemPool().releaseChunk(chunk);
    }
  
    void connectMempool(Memory* pool_ptr) 
    {
      Base_t::connectMempool(static_cast<void*>(pool_ptr));
    }
    
    PortDataBase_t* getChunk(void)
    {
      return getMemPool().getChunk();
    }

    uint16_t getChunkCount(void)
    {
      return getMemPool().getChunkCount();
    }

    uint16_t getChunkSize(void)
    {
      return getMemPool().getChunkSize();
    }

  private:
    CMemPoolInterface(const CMemPoolInterface& that) = delete;
    CMemPoolInterface(CMemPoolInterface&& that) = delete;
    CMemPoolInterface& operator=(CMemPoolInterface& that) = delete;
    CMemPoolInterface& operator=(CMemPoolInterface&& that) = delete;
};

}//end of namespace mempool
 

#endif

