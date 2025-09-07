#ifndef PROTOCOLINTERFACE_HPP
#define PROTOCOLINTERFACE_HPP

#include "ProtocolLayoutDef.hpp"

namespace NetCom {
  ///\brief function handles DLC check for required message
  ///\details function would iterate through the message buffer and count the
  ///         number of Iterating times from the beginning of the buffer to the
  ///         endOfFrameSymbol
  ///         If no endOfFrameSymbol catched in the buffer, set returnValue = false
  ///         If the number of Iterating time (DLCCount) equals to predefined DLC
  ///         then return true
  ///         Else return default value or set false returnValue = false
  /// \param  MessageLayoutInterface &messageHandler: contains predefined DLC
  /// \param  messageBuffer[] raw data buffer
  /// \param  size_u16 raw data buffer size
  bool netProtect_DLCCheck(NetCom::MessageHandlerInterface &messageHandler, const uint8_t *messageBuffer, const uint16_t size_u16);

  ///\brief   function handles filling header (DLC & ID) into lower layer data buffer for required message
  ///\details function would fill information of DLC & ID (already declared in NetCom::MessageHandlerInterface) 
  ///         into DLC field & ID field on local buffer of required message
  ///\param   MessageLayoutInterface &messageHandler: contains predefined DLC & ID and local buffer
  ///\note    Function shall only be triggered when requested from netComTxMainFunction()
  void netHeaderSetup(NetCom::MessageHandlerInterface &messageHandler);
}//end of namespace NetCom

#endif

