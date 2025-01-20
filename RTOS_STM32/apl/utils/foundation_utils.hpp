#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <stdint.h>
namespace vfc
{

  template<typename ElementDataType, uint16_t ContainerSize>
  struct array
  {
      static_assert(ContainerSize != 0, "Size can't be 0");

      inline ElementDataType*  begin()
      {
        return &m_Container[0U];
      }

      inline ElementDataType*  end()
      {
        return &m_Container[ContainerSize - 1U];
      }

      const ElementDataType& operator[](const uint16_t pos) const
      {
          if(pos >= ContainerSize)
          {
              return m_Container[0U];
          }
          else 
          {
              return m_Container[pos];
          }
      }

      ElementDataType m_Container[ContainerSize];
  };
} //end of namespace vfc

#endif
