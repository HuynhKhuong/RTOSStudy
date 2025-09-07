#ifndef RECEIVERPORTDEF_HPP
#define RECEIVERPORTDEF_HPP 

#include "container/Container.hpp"
#include "extension/receiverport/receiverConnect_ext.hpp"
#include "extension/receiverport/receiverMechanism_ext.hpp"
#include "extension/receiverport/receiverPortBase.hpp"
#include "extension/receiverport/receiverUser_ext.hpp"
#include "receiverMechanism_Lightweight_ext.hpp"
#include "receiverPortBase_lightweight.hpp"
#include <stdint.h>


namespace Port
{
  using namespace extension;

  template<typename PortDataType = Container::CInternal>
  using ReceiverPortUserType = ReceiverUser<ReceiverConnection<ReceiverMechanism<ReceiverPortBase>>,PortDataType>;
  
  template<typename PortDataType = Container::CInternal>
  using ReceiverPortUserTypeLightweight = ReceiverUser<ReceiverConnection<LightWeightReceiverMechanism<ReceiverPortBaseLightWeight>>,PortDataType>;
}

#endif

