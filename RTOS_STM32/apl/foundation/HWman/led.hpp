#ifndef LED_HPP
#define LED_HPP

extern "C"
{
  #include "stm32f4xx_hal.h" ///Must include for stm32f4xx_hal_gpio.h 
  #include "stm32f4xx_hal_gpio.h" 
}

namespace ComplexDriver
{
  class LEDHandler
  {
    public:
      LEDHandler(GPIO_TypeDef* ledDrivingPort, uint16_t ledDrivingPin):
                  m_ledDrivingPort{ledDrivingPort}, m_ledDrivingPin{ledDrivingPin}
      { }

      void driveLED(const uint8_t ledStatus)
      {
        if((ledStatus != 1U) && (ledStatus != 0U)) return;
        if(m_ledDrivingPort == nullptr) return;

        HAL_GPIO_WritePin(m_ledDrivingPort, m_ledDrivingPin, static_cast<GPIO_PinState>(ledStatus));
        m_currentLedDrivingState = HAL_GPIO_ReadPin(m_ledDrivingPort, m_ledDrivingPin);
      }

      void blinkLED()
      {
        if(m_ledDrivingPort == nullptr) return;

        m_currentLedDrivingState = HAL_GPIO_ReadPin(m_ledDrivingPort, m_ledDrivingPin);
        if(m_currentLedDrivingState == GPIO_PinState::GPIO_PIN_RESET)
        {
          m_currentLedDrivingState = GPIO_PinState::GPIO_PIN_SET;
        }
        else //GPIO_PinState::GPIO_PIN_SET
        {
          m_currentLedDrivingState = GPIO_PinState::GPIO_PIN_RESET;
        }
        driveLED(static_cast<uint8_t>(m_currentLedDrivingState));
      }

    private:
      GPIO_TypeDef* m_ledDrivingPort;
      uint16_t m_ledDrivingPin;
      GPIO_PinState m_currentLedDrivingState{GPIO_PinState::GPIO_PIN_RESET};
  };
}
#endif

