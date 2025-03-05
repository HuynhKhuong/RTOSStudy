#ifndef NETPORTINTF_HPP
#define NETPORTINTF_HPP

#include "container/PortInterface.hpp"
#include <stdint.h>

namespace Port
{

struct LEDModeReqInf: public ContainerInterface
{
    using LEDModSignalType = CSignalDescription<uint8_t, uint8_t>;
    LEDModSignalType m_LedModSignal{LEDModSignalType::RawDataInfo<uint8_t>{255U, 0U, 1.0F, 0.0F}};
};

}

#endif

