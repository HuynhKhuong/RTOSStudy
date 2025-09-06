#include "rtc.hpp"
#include "utils/foundation_utils.hpp"
#include <cstdint>

extern RTC_HandleTypeDef hrtc;

namespace 
{
    ///\brief defintion of all RTCHandler instances 
    ComplexDriver::RTCHandler rtcHandler_1{&hrtc};

    ///\brief central storage for all RTCHandler instances
    constexpr uint16_t maxOfPeripherals{static_cast<uint16_t>(ComplexDriver::RTCInstanceIdx::MAX_RTC)};

    vfc::array<ComplexDriver::RTCHandler*, maxOfPeripherals> s_centralHandlerStorage
    {
        {&rtcHandler_1}
    };

    auto findHandler = [](uint8_t l_instanceidx_u8) ->ComplexDriver::RTCHandler*
    {
        if(l_instanceidx_u8 >= maxOfPeripherals) return nullptr;
        return s_centralHandlerStorage[l_instanceidx_u8];
    };

} //anonymous namespace
namespace  ComplexDriver{

    RTCHandler* getRTCHandlerInstance(uint8_t l_instanceidx_u8)
    {
        return findHandler(l_instanceidx_u8);
    }
}

