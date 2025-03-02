#ifndef MESSAGELISTDEFINE_HPP
#define MESSAGELISTDEFINE_HPP

#include "ProtocolLayoutDef.hpp"
#include "SymbolicNames.hpp"

/// \note declared as constexpr in .hpp file would be treated as const and
/// inline variables ODR would never be broken

namespace NetCom {

//register messages handler into configuration table
extern MessageLayout<4U, 2U> g_LEDControlMsg; 
extern MessageLayout<4U, 1U> g_RTCControlMsg; 

extern vfc::array<MessageHandlerInterface* const, g_numberOfMessages> g_messageConfigureTable;
}// End of namespace NetCom
#endif
