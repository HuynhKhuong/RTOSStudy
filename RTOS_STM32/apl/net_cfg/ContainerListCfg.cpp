#include "ContainerListCfg.hpp"

namespace NetCom
{

uint8_t prvSignalTypeUint8_t[g_totalNumberOfSignalTypeUint8]{0U};
InternalDataContainer prvSignalContainer(&prvSignalTypeUint8_t[0U],
                                         nullptr, // no uint16_t signals
                                         nullptr, // no uint32_t signals
                                         nullptr, // no float signal,
                                         nullptr);

uint16_t signalLayoutToSignalContainerMap(uint16_t signalIndex)
{
  uint16_t mappedIndex{signalIndex};
  if (signalIndex >= g_totalNumberOfSignals) {
    mappedIndex = 0U;
  }

  return prvsignalContainerMappingTable[mappedIndex];
}

} // end of namespace NetCom 
