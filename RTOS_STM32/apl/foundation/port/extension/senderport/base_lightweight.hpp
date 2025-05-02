#ifndef BASE_LIGHTWEIGHT_HPP
#define BASE_LIGHTWEIGHT_HPP

#include <stdint.h>

namespace extension
{
  class SenderPortBaseLightWeight
  {
    public:
      using PortDataBase_t = uint32_t;
      SenderPortBaseLightWeight() = default;
      ~SenderPortBaseLightWeight() = default;

      PortDataBase_t* reserveIntern(void) 
      {
        return &m_internalContainer_u32;
      }

      void deliverIntern(PortDataBase_t& currentStorage) 
      {
        /*do nothing*/
      }

    private:
      SenderPortBaseLightWeight(const SenderPortBaseLightWeight& that) = delete;
      SenderPortBaseLightWeight(SenderPortBaseLightWeight&& that) = delete;
      SenderPortBaseLightWeight& operator=(SenderPortBaseLightWeight& that) = delete;
      SenderPortBaseLightWeight& operator=(SenderPortBaseLightWeight&& that) = delete;

      PortDataBase_t m_internalContainer_u32;
  };
}//end of namespace extension
#endif

