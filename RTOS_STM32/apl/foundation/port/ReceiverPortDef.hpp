#ifndef RECEIVERPORTDEF_HPP
#define RECEIVERPORTDEF_HPP 

#include "container/Container.hpp"
#include "extension/receiverport/receiverConnect_ext.hpp"
#include "extension/receiverport/receiverMechanism_ext.hpp"
#include "extension/receiverport/receiverPortBase.hpp"
#include "extension/receiverport/receiverUser_ext.hpp"
#include <stdint.h>


namespace Port
{
  using namespace extension;

  template<typename PortDataType = Container::CInternal>
  using ReceiverPortUserType = ReceiverUser<ReceiverConnection<ReceiverMechanism<ReceiverPortBase>>,PortDataType>;
  
}
#endif

