#ifndef SENDERPORTDEF_HPP
#define SENDERPORTDEF_HPP 

#include "extension/senderport/base.hpp"
#include "extension/senderport/connection_ext.hpp"
#include "extension/senderport/latestreserve_ext.hpp"
#include "extension/senderport/metadata_ext.hpp"
#include "extension/senderport/subscriber_ext.hpp"
#include "extension/senderport/user_ext.hpp"



#include "extension/senderport/base_lightweight.hpp"
#include "extension/senderport/connection_lightweight_ext.hpp"
#include "extension/senderport/latestreserve_lightweight_ext.hpp"
#include "extension/senderport/subscriber_lightweight_ext.hpp"

namespace Port
{
  using namespace extension;
  
  template<uint8_t NumbOfSub, typename ReceiverPortType, typename PortMetaDataType = Container::CInternal>
  using SenderPortUserType = User<LatestReserve<MetaData<Connection<DynamicSubscriber<SenderPortBase,ReceiverPortType, NumbOfSub>>,PortMetaDataType>>, PortMetaDataType>;

  template<uint8_t NumbOfSub, typename ReceiverPortType, typename PortMetaDataType = Container::CInternal>
  using SenderPortLightWeight = User<LightweightReserve<ConnectionLightWeight<LightWeightSubscriber<SenderPortBaseLightWeight,ReceiverPortType, NumbOfSub>>>,PortMetaDataType>;

  template<uint8_t NumbOfSub, typename ReceiverPortType, typename PortMetaDataType = Container::CInternal>
  class SenderPort: public SenderPortUserType<NumbOfSub, ReceiverPortType, PortMetaDataType>
  {

  };

}

#endif 

