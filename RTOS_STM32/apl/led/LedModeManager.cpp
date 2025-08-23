#include "LedModeManager.hpp"
#include <cstdint>

namespace Led
{
  void LedManager::blink(void)
  {
    if(m_currentLedMode != nullptr)
    {
      m_currentLedMode->blink();
    }
  }

  void LedManager::setLedMode(uint8_t index) 
  {
    /* Strategy pattern + factory method for choosing the correct mode */
    switch(index)
    {
        case 0U:
          m_currentLedMode = static_cast<LedModeInf*>(&LedModeAllBlink::getSingleton());
          break;
        case 1U:
          m_currentLedMode = static_cast<LedModeInf*>(&LedModePairBlink1::getSingleton());
          break;
        case 2U:
          m_currentLedMode = static_cast<LedModeInf*>(&LedModePairBlink2::getSingleton());
          break;
        case 3U:
          m_currentLedMode = static_cast<LedModeInf*>(&LedModeBlinkCircle::getSingleton());
          break;
        default:
          m_currentLedMode = static_cast<LedModeInf*>(&LedModeStop::getSingleton());
          break;
    }
  }
}

