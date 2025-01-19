#ifndef __TASK_HPP__
#define __TASK_HPP__


#include "projdefs.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "utils.hpp"

namespace Task
{
  BaseType_t createTasks(void); 

  class TaskHandler
  {
  public:
    TaskHandler(TaskHandle_t const taskHandle,uint16_t const taskCycle, UBaseType_t taskPriority, const char* UserName): 
              m_taskHandle{taskHandle}, m_taskCycleTick{taskCycle}, 
              m_taskPriority{taskPriority},
              m_taskName{UserName[0], UserName[1], UserName[2], UserName[3], UserName[4], 
                         UserName[5], UserName[6], UserName[7], UserName[8], UserName[9]}
    {
      configASSERT( m_taskPriority >= tskIDLE_PRIORITY );
    }

    TaskHandler(uint16_t const taskCycle, UBaseType_t taskPriority, const char* UserName): 
              m_taskCycleTick{taskCycle}, m_taskPriority{taskPriority},
              m_taskName{UserName[0], UserName[1], UserName[2], UserName[3], UserName[4], 
                         UserName[5], UserName[6], UserName[7], UserName[8], UserName[9]}
    {
      configASSERT( m_taskPriority >= tskIDLE_PRIORITY );
    }

    explicit TaskHandler(uint16_t const taskCycle):m_taskCycleTick{taskCycle}, m_taskPriority{tskIDLE_PRIORITY},
                        m_taskName{"*********"}    
    {}

    virtual void run(void* param) = 0;

    const TaskHandle_t getTaskHandle(void) const
    {
        return m_taskHandle;
    }

    BaseType_t setTaskHandle(void) 
    {
        if(!m_isTaskAlive) return pdFAIL; 

        m_taskHandle = xTaskGetHandle(m_taskName);
        return pdPASS;
    }

    const UBaseType_t getTaskPriority(void) 
    {
        if(istaskHandleUsable())
        {
          vTaskSuspendAll();
          m_taskPriority = uxTaskPriorityGet(m_taskHandle);
          xTaskResumeAll();
        }

        return m_taskPriority;
    }

    BaseType_t setTaskPriority(UBaseType_t l_priority) 
    {
        if((l_priority < tskIDLE_PRIORITY) || (!istaskHandleUsable()))
        {
          return pdFAIL;
        }
        vTaskSuspendAll();
        m_taskPriority = l_priority;
        vTaskPrioritySet(m_taskHandle, m_taskPriority);
        xTaskResumeAll();
        return pdPASS;
    }

    BaseType_t deleteTask(void) 
    { 
        if(!istaskHandleUsable()) return pdFAIL;

        vTaskDelete(m_taskHandle);
        m_isTaskAlive = false;
        m_taskHandle = nullptr;
        return pdPASS;
    }

    const char* getTaskName(void) 
    { 
        return m_taskName;
    }

  protected:
    TaskHandle_t m_taskHandle{nullptr}; ///member to keep the control block of Task
    TickType_t m_currentWakeTimeTick{0U}; ///default WakeTime, shall be updated in task handler
    bool m_isTaskAlive{true};
    uint16_t m_taskCycleTick; 
    UBaseType_t m_taskPriority;
    char m_taskName[10U];
  private:
    inline bool istaskHandleUsable(void)
    {
      return ((m_taskHandle != nullptr)&&(m_isTaskAlive));
    }
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

}//End of namespace Task
#endif
