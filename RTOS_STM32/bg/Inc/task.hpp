#ifndef __TASK_HPP__
#define __TASK_HPP__


#include "projdefs.h"
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

    TaskHandle_t getTaskHandle(void) 
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
       * isInputClicked checks if there is a single rise from released to pressed state
       * of the input
       */
      bool isInputClicked(void)
      {
        bool returnVal; 
        static GPIO_PinState l_preInputState{senseInput()};
        GPIO_PinState l_curInputState{senseInput()};

        if((isInputPressed(l_preInputState) == false) && 
            (isInputPressed(l_curInputState) == true))
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
      static const bool isInputPressed(const GPIO_PinState inputState) 
      {
          return (inputState == GPIO_PinState::GPIO_PIN_RESET);
      } 

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
