#ifndef CONTAINERLISTCFG_HPP
#define CONTAINERLISTCFG_HPP

#include <stdint.h>

namespace NetCom{

constexpr uint8_t g_totalNumberOfSignalTypeUint8{15U};
extern uint8_t prvSignalTypeUint8_t[g_totalNumberOfSignalTypeUint8];

constexpr uint8_t g_totalNumberOfSignalTypeUint16{1U};
extern uint16_t prvSignalTypeUint16_t[g_totalNumberOfSignalTypeUint16];


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
    0U, //g_IDLEDControlMsg_u8
    1U, //g_LEDModeReqSignal_u8
    2U, //g_IDRTCControlMsg_u8
    3U, //g_RTCModeReqSignal_u8
    4U, //g_ReqHoursSignal_u8
    5U, //g_ReqMinutesSignal_u8
    6U, //g_ReqSecondsSignal_u8
    7U, //g_ReqDateSignal_u8
    8U, //g_ReqMonthSignal_u8
    9U, //g_IDStateRespondMsg_u8
    10U, //g_CurrentStateSignal_u8
    11U, //g_IDRTCRespondMsg_u8
    12U, //g_HoursSignal_u8
    13U, //g_MinutesSignal_u8
    14U, //g_SecondsSignal_u8
         
    /* prvSignalTypeUint16_t*/
    0U //g_ReqYearSignal_u16
};

}

#endif
