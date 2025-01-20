#ifndef RX_PROTECT_HPP_INCLUDED
#define RX_PROTECT_HPP_INCLUDED

#include <cstdint>

namespace rbNet_E2EProtect {
///\brief Callback Functions to be called for each message
///\details Callback Functions is called everytime a new message is received
/// and the corresponding ID is checked
/// \todo
/// \input: dataBuffer[] raw data container
bool LEDControlMsgDLCCheck(uint8_t *messageBuffer);
bool RTCControlMsgDLCCheck(uint8_t *messageBuffer);

} // End of namespace rbNet_E2EProtect

#endif
