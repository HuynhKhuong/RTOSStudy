#ifndef COMTRANSMIT_HPP
#define COMTRANSMIT_HPP

#include "ProtocolLayoutDef.hpp"

namespace NetCom {

  /// \brief netComSendSignal handles packing signal from user's provided source data into its internal container
  ///        and triggers sending message from ComMainTx scheduler 
  /// \param signalID: ID defined in "MessageConfigure.hpp"
  /// \param void* ptr: user pointer to be copied 
  void netComSendSignal(signalID ID, void *ptr);

  /// \brief netComSend handles packing internal signal container into messages buffer and send scheduled message 
  ///        from ComMainTx scheduler 
  /// 
  /// \param MessageLayoutInterface: Layout information and local buffer to extract signal from
  void netComSend(MessageHandlerInterface &messageLayout);

  /// \brief netComSendWrapper wraps lowerlayer APIs to trigger sending application messages buffer to hardware layers 
  ///        protocol 
  /// \param messageID: ID defined in "MessageConfigure.hpp"
  void netComSendWrapper(uint16_t messageID);
} //end of namespace NetCom

#endif

