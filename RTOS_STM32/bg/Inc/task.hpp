#ifndef __TASK_HPP__
#define __TASK_HPP__

#include "utils.hpp"

namespace Task
{
  BaseType_t createTasks(void); 
  extern TaskHandle_t taskHandle1;
  extern TaskHandle_t taskHandle2;

  class TaskHandler
  {
  public:
    explicit TaskHandler(TaskHandle_t const taskHandle): m_taskHandle(taskHandle)
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

}//End of namespace Task
#endif
