#ifndef CONTAINERLIST_HPP_INCLUDED
#define CONTAINERLIST_HPP_INCLUDED

#include <stdint.h>

namespace NetCom{

struct InternalDataContainer 
{
  InternalDataContainer(uint8_t *signalTypeUint8_t,
                        uint16_t *signalTypeUint16_t,
                        uint32_t *signalTypeUint32_t, 
                        float *signalTypeFloat, 
                        uint8_t *signalTypeOthers):
                        m_signalTypeUint8_t{signalTypeUint8_t},
                        m_signalTypeUint16_t{signalTypeUint16_t},
                        m_signalTypeUint32_t{signalTypeUint32_t},
                        m_signalTypeFloat{signalTypeFloat}, 
                        m_signalTypeOthers{signalTypeOthers}{}

  uint8_t *const m_signalTypeUint8_t;
  uint16_t *const m_signalTypeUint16_t;
  uint32_t *const m_signalTypeUint32_t;
  float *const m_signalTypeFloat;
  uint8_t *const m_signalTypeOthers;
};

extern InternalDataContainer prvSignalContainer;

/// \brief signalLayoutToSignalContainerMap maps signal data index within internal container
///        corresponding to user signal ID
/// \param signalID: ID defined in "MessageConfigure.hpp"
uint16_t signalLayoutToSignalContainerMap(uint16_t signalIndex);

} // End of namespace NetCom

#endif
