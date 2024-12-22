#ifndef __TASK_HPP__
#define __TASK_HPP__

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "utils.hpp"
#include <stdint.h>

namespace Task
{
  BaseType_t createTasks(void); 

  class TaskHandler
  {
  public:
    explicit TaskHandler(TaskHandle_t const taskHandle,uint16_t const taskCycle): m_taskHandle{taskHandle},m_taskCycleTick{taskCycle}
    { }

    explicit TaskHandler(uint16_t const taskCycle): m_taskCycleTick{taskCycle}
    { }

    TaskHandler() = default;

    virtual void run(void* param) = 0;

    const TaskHandle_t getTaskHandle(void) const
    {
      return m_taskHandle;
    }

    void setTaskHandle(TaskHandle_t taskHandle) 
    {
      if(taskHandle == nullptr) return;
      m_taskHandle = taskHandle;
    }

  protected:
    TaskHandle_t m_taskHandle{nullptr}; ///member to keep the control block of Task
    TickType_t m_currentWakeTimeTick{0U}; ///default WakeTime, shall be updated in task handler
    uint16_t m_taskCycleTick; 
  };


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

  class UserInputHandler
  {
    public:
      UserInputHandler(GPIO_TypeDef* inputSensingPort, uint16_t inputSensingPin):
                  m_inputSensingPort{inputSensingPort}, m_inputSensingPin{inputSensingPin}
      { }

      const GPIO_PinState senseInput(void) 
      {
          return m_currentInputState;
      }
        
      /*
       * isInputClicked checks if there is a single rise from LOW to HIGH state
       * of the input
       */
      bool isInputClicked(void)
      {
        bool returnVal; 
        static GPIO_PinState l_preInputState{senseInput()};
        GPIO_PinState l_curInputState{senseInput()};

        if((l_preInputState == GPIO_PinState::GPIO_PIN_RESET) && 
            (l_curInputState == GPIO_PinState::GPIO_PIN_SET))
        {
          returnVal = true;
        }
        else 
        {
          returnVal = false;
        }

        l_preInputState = l_curInputState; 
        return returnVal;
      }

      /*
       * To query pin state every 10ms
       * Using debounce method
       */
      void queryInputFromHardware(void)
      {
        GPIO_PinState l_tempInputState;
        /// First store input state at start of debounce
        l_tempInputState = HAL_GPIO_ReadPin(m_inputSensingPort, m_inputSensingPin);
        if(l_tempInputState == m_currentInputState) return; //nothing changed

        HAL_Delay(m_debounceTimeMs);
        /// After debounce, check whether input state at start is correct?
        if(HAL_GPIO_ReadPin(m_inputSensingPort, m_inputSensingPin) == l_tempInputState)
        {
          m_currentInputState = l_tempInputState;
        }
      }

    private:
      GPIO_TypeDef* m_inputSensingPort;
      uint16_t m_inputSensingPin;
      GPIO_PinState m_currentInputState{GPIO_PinState::GPIO_PIN_RESET};

      /*
       * Using debounce time for input state acquiring debounce method
       * Make sure debounce time is under time constraint of the component using this method
       */
      const uint8_t m_debounceTimeMs{2U};  
  };

}//End of namespace Task
#endif
