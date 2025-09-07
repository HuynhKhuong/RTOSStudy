#ifndef MEMPOOL_HPP
#define MEMPOOL_HPP

#include "utils/foundation_utils.hpp"
#include "container/container.hpp"
#include "extension.hpp"

/*
 * zero copy mechanism and mempool is used to hold the port data just once at one place. 
 * storage type which could contain 1:N chunks.  
 * In a chunk the one port data to send can be stored.
 * The management of the free chunk could be discussed later 
 * */

namespace mempool
{

///\brief Mempool storage process based on atomic unit
class CChangeableMemPoolStorage
{
public:
  CChangeableMemPoolStorage():m_memPoolbase_p{nullptr},
                              m_memPoolEnd_p{nullptr}, 
                              m_freeListHeadID{0U},
                              m_chunkCount{0U}, 
                              m_minFreeEver{0U},
                              m_minFreeCurrent{0U}
  {}

  ///\brief provide a chunk to write on 
  ///\note  if no chunk is available, returns nullpointer
  void* getChunk(void);

  ///\brief request to release the chunk into freelist
  void releaseChunk(void* chunk_p);

  ///\brief get the number of Chunks
  uint16_t getChunkCount(void) const;

  ///\brief get the size (in bytes) of a single chunk
  ///\note return=(end-begin)/(number of Chunks)
  uint16_t getChunkSize(void) const;

  ///\brief set the operation scope of the mempool. 
  ///       The operation scope is defined as range between start to end address of the mempool
  ///       The size of this range has to be = (x * single chunk size)
  void init(void* memPoolBase_p, const void* const memPoolEnd_p, const uint16_t chunkSize);

protected:
  uint16_t getMinFreeCurrent(void) const
  {
    return m_minFreeCurrent;
  }

  uint16_t getMinFreeEver(void) const
  {
    return m_minFreeEver;
  }

private:
  ///\brief initialize the mempool and list of free chunks
  void initializer(void);

  ///\brief check whether passed chunk address is in the range of mempool
  bool validate(const void* const chunk_p) const;

  bool isEmpty(void) const;

  uint16_t getChunkID(const void* const chunk_p) const;

  CChangeableMemPoolStorage& operator=(const CChangeableMemPoolStorage&) = delete;
  CChangeableMemPoolStorage& operator=(CChangeableMemPoolStorage&&) = delete;
  CChangeableMemPoolStorage(const CChangeableMemPoolStorage&) = delete;
  CChangeableMemPoolStorage(CChangeableMemPoolStorage&&) = delete; 
  
  char* m_memPoolbase_p; ///pointer the start address of the mempool
  const char* m_memPoolEnd_p; ///pointer the end addrss of the mempool (first address outside mempool)
  uint16_t m_freeListHeadID; ///index of free list head (0 = mempool is empty)
  uint16_t m_chunkCount; ///amount of maintained one chunks
  ///\brief maximum amount of chunk which has not been used at all during the whole lifetim of this mempool
  uint16_t m_minFreeEver; 
  ///\brief current amount of unused chunks
  ///\todo  query strategy is ongoing
  uint16_t m_minFreeCurrent;
};

using TChangeableMemPoolBase = extension::ReferenceCounter<CChangeableMemPoolStorage>;

///\brief Mempool is used to hold the port data just once at one place.
///       Mempool contains storage type which could contain 1:N chunks. In a chunk, the one port data to send can be 
///       stored. The number of chunks depends on the system context of the sender port
///       The management of the free chunk is done in CChangeableMemPoolStorage
///\param PortDataType: Type of interface which maintained by the mempool
///\param NumberOfChunksValue: number of chunk which will be contained by the mempool
///\param ParamAlign[deprecated]: has to be derived from daddy::mempool::ParamByteAlign. Contains the alignment in byte
template<typename PortDataType, uint16_t NumberOfChunksValue>
class TChangeableMemPool: public TChangeableMemPoolBase 
{
public:
  using Base_t = TChangeableMemPoolBase;
  using PortData_t = PortDataType;
  static constexpr uint16_t NumberOfChunks{NumberOfChunksValue};
  static constexpr uint16_t ChunkSize{sizeof(PortData_t)};
  
  TChangeableMemPool():Base_t{}
  {
    Base_t::init(m_pool.begin(), m_pool.end(), static_cast<uint16_t>(sizeof(PortData_t)));
  }

  ///\brief Public destructor
  ///       clear memory pool to prevent memory leaks
  ~TChangeableMemPool() = default;
  
private:
  vfc::array<PortData_t, NumberOfChunks> m_pool;

  ///prevent copy
  TChangeableMemPool& operator=(const TChangeableMemPool&) = delete;
  TChangeableMemPool& operator=(TChangeableMemPool&&) = delete;
  TChangeableMemPool(const TChangeableMemPool&) = delete;
  TChangeableMemPool(TChangeableMemPool&&) = delete; 
};

}//end of namespace mempool

#endif

