#ifndef PORTDEFLIGHTWEIGHT_INCLUDED
#define PORTDEFLIGHTWEIGHT_INCLUDED

///\brief Definition of a sender/receiver port which is a wrapper implementing 
///       different synchronization mechanism
///
#include <stdint.h>

namespace extension
{
  class ReceiverPortBaseLightWeight 
  {
    public:
      using PortDataBase_t = uint32_t;

      ReceiverPortBaseLightWeight() = default;

  };
}

#endif

