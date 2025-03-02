#ifndef COMRECEIVE_HPP_INCLUDED
#define COMRECEIVE_HPP_INCLUDED

#include "ProtocolLayoutDef.hpp"

namespace NetCom{

/// \brief netComDisptachSignals handles extracting signals from a message
///        buffer and save in internal data container
/// \param MessageLayoutInterface: Layout information and local buffer to extract signal from
/// \param Signals saved into internal signal container
/// \note  This function should be called cyclically to achieve polling behaviour
void netComDispatchSignals(MessageHandlerInterface &messageLayout);

/// \brief netComReceiveSignal handles getting signal from internal container
///        and return to user
/// \param signalID: ID defined in "MessageConfigure.hpp"
/// \param void* ptr: user pointer to be stored with latest signal value
void netComReceiveSignal(signalID ID, void *ptr);
} // End of namespace NetCom

#endif
