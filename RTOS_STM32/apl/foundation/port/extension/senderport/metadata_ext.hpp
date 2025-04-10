#ifndef METADATA_EXT_HPP
#define METADATA_EXT_HPP

#include <stdint.h>

namespace extension{

template<typename MixinType, typename PortMetaDataType>
class MetaData: public MixinType
{
  public:
    using Mixin_t = MixinType;
    using PortMetaData_t = PortMetaDataType;
    using PortDataBase_t = typename MixinType::PortDataBase_t; 

    MetaData() = default;
    ~MetaData() = default;
    
    void deliverIntern(PortDataBase_t& portDataBase)
    {
      Mixin_t::deliverIntern(portDataBase);
      prepare(portDataBase);
    }

  private:
    MetaData(const MetaData&) = delete;
    MetaData(MetaData&&) = delete;
    MetaData& operator=(MetaData&) = delete;
    MetaData& operator=(MetaData&&) = delete;

    void prepare(PortDataBase_t& portDataBase)
    {
      m_sequenceNumber++;
      static_cast<PortMetaData_t&>(portDataBase).prepareForDeliver(m_sequenceNumber);
    }

    uint16_t m_sequenceNumber{0U}; 
};

}//end of namespace extension

#endif

