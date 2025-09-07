#ifndef BASE_HPP
#define BASE_HPP

#include "mempool/mempool_interface.hpp"

namespace extension
{
  class Default: public mempool::CMemPoolInterface
  {
    public:
      using MemoryInterface_t = mempool::CMemPoolInterface;
  };


  class SenderPortBase: public Default
  {
    public:
      using MemoryInterface_t = Default::MemoryInterface_t;
      using Memory = MemoryInterface_t::Memory;
      using PortDataBase_t = MemoryInterface_t::PortDataBase_t; 
      SenderPortBase() = default;
      ~SenderPortBase() = default;

      PortDataBase_t* reserveIntern(void) 
      {
        return MemoryInterface_t::getChunk();
      }

      void deliverIntern(PortDataBase_t& currentStorage) 
      {
        m_lastDelivery_p = &currentStorage;
      }

      const PortDataBase_t* getLastDelivery(void) const 
      {
        return m_lastDelivery_p;
      }

      bool isMempoolConnected(void) const
      {
        return MemoryInterface_t::isMempoolConnected();   
      }
      
      void connectMempool(Memory* pool_ptr)
      {
        MemoryInterface_t::connectMempool(pool_ptr);
      }
      
    private:
      SenderPortBase(const SenderPortBase& that) = delete;
      SenderPortBase(SenderPortBase&& that) = delete;
      SenderPortBase& operator=(SenderPortBase& that) = delete;
      SenderPortBase& operator=(SenderPortBase&& that) = delete;

      const PortDataBase_t* m_lastDelivery_p{nullptr};
  };
}//end of namespace extension
#endif

