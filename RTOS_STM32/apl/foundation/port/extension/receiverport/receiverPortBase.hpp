#ifndef PORTDEF_INCLUDED
#define PORTDEF_INCLUDED

///\brief Definition of a sender/receiver port which is a wrapper implementing 
///       different synchronization mechanism
///
#include <stdint.h>
#include "Container.hpp"

namespace extension
{
  class ReceiverPortBase 
  {
    public:
      using PortDataBase_t = Container::CInternal;

      ReceiverPortBase() = default;

  };
}

#endif

