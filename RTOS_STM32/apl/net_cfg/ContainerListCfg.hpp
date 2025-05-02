#ifndef CONTAINERLISTCFG_HPP
#define CONTAINERLISTCFG_HPP

#include "ContainerList.hpp"

namespace NetCom{

constexpr uint8_t g_totalNumberOfSignalTypeUint8{9U};
extern uint8_t prvSignalTypeUint8_t[g_totalNumberOfSignalTypeUint8];

constexpr uint8_t g_totalNumberOfSignalTypeUint16{0U};
/* no signal type uint16 declared*/

constexpr uint8_t g_totalNumberOfSignalTypeUint32{0U};
/* no signal type uint32 declared*/

constexpr uint8_t g_totalNumberOfSignalTypeFloat{0U};
/* no signal type float declared*/

constexpr uint8_t g_totalNumberOfSignals{
                  g_totalNumberOfSignalTypeUint8 + 
                  g_totalNumberOfSignalTypeUint16 +
                  g_totalNumberOfSignalTypeUint32 +
                  g_totalNumberOfSignalTypeFloat};

constexpr uint8_t prvsignalContainerMappingTable[g_totalNumberOfSignals]{
    /* prvSignalTypeUint8_t*/
    0U,
    1U,
    2U,
    3U,
    4U,
    5U,
    6U,
    7U,
    8U,
};

}

#endif
