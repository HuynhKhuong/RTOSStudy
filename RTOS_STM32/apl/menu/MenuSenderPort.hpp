#ifndef MENUSENDERPORT_HPP
#define MENUSENDERPORT_HPP


#include "SenderPortDef.hpp"
#include "led/LedReceiverPort.hpp"
#include "net/NetReceiverPort.hpp"
#include "MenuPortIntf.hpp"
#include "rtc/RTCReceiverPort.hpp"

namespace Port
{
  using LedModuleSenderPort = SenderPort<2U, LedModuleReceiverPort, LEDModeReqInf>;
  using StateInfoSenderPort = SenderPort<2U, StateInfoReceiverPort, StateInfoInf>;
  using RTCConfigDataSenderPort = SenderPort<2U, RTCConfigDataReceiverPort, RTCConfigDataInf>;

  extern LedModuleSenderPort g_menuLedSenderPort_st;
  extern StateInfoSenderPort g_menuStateInfoSenderPort_st;
  extern RTCConfigDataSenderPort g_menuRTCConfigDataSenderPort_st;
}

#endif
