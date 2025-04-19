#ifndef LEDMODEMANAGER_HPP
#define LEDMODEMANAGER_HPP

#include <stdint.h>
#include "foundation_utils.hpp"
#include "HWman/led.hpp"
extern "C"
{
#include "main.h"
}

namespace Led 
{
  class LedModeInf
  {
    public:
      ~LedModeInf() = default;
      LedModeInf() = default;

      virtual void blink(void) = 0;

    private:
      
      LedModeInf(const LedModeInf&) = delete;
      LedModeInf(LedModeInf&&) = delete;
      LedModeInf& operator=(LedModeInf&) = delete;
      LedModeInf& operator=(LedModeInf&&) = delete;
  };

  class LedModeAllBlink: public LedModeInf
  {
    public:
      ~LedModeAllBlink() = default;

      static LedModeInf& getSingleton(void) 
      {
        static LedModeAllBlink m_mainProcessor{};
        return m_mainProcessor;
      }

      void blink(void) override
      {
        for (auto led : m_ledList) 
        {
          led.blinkLED();
        }
      }

    private:
      LedModeAllBlink() = default;
      LedModeAllBlink(const LedModeAllBlink&) = delete;
      LedModeAllBlink(LedModeAllBlink&&) = delete;
      LedModeAllBlink& operator=(LedModeAllBlink&) = delete;
      LedModeAllBlink& operator=(LedModeAllBlink&&) = delete;
      
      vfc::array<ComplexDriver::LEDHandler, 4U> m_ledList
      {{
        {LD3_GPIO_Port, LD3_Pin},
        {LD4_GPIO_Port, LD4_Pin},
        {LD5_GPIO_Port, LD5_Pin},
        {LD6_GPIO_Port, LD6_Pin}
      }};
  };

  class LedModePairBlink1: public LedModeInf
  {
    public:
      ~LedModePairBlink1() = default;

      void blink(void) override
      {
        ///first setup 
        static bool isFirstCalled{true};
        if(isFirstCalled)
        {
          for(auto singleHandler: m_ledList[0U])
          {
            singleHandler.driveLED(0U); ///reset
          }

          for(auto singleHandler: m_ledList[1U])
          {
            singleHandler.driveLED(1U); ///set
          }
          isFirstCalled = false;
        }
        else
        {
          for(auto subLedList: m_ledList)
          {
            for(auto singleHandler: subLedList)
            {
              singleHandler.blinkLED(); 
            } 
          }
        }
        
      }

      static LedModeInf& getSingleton(void) 
      {
        static LedModePairBlink1 m_mainProcessor{};
        return m_mainProcessor;
      }

    private:
      LedModePairBlink1() = default;
      LedModePairBlink1(const LedModePairBlink1&) = delete;
      LedModePairBlink1(LedModePairBlink1&&) = delete;
      LedModePairBlink1& operator=(LedModePairBlink1&) = delete;
      LedModePairBlink1& operator=(LedModePairBlink1&&) = delete;

      vfc::array<vfc::array<ComplexDriver::LEDHandler, 2U>,2U> m_ledList
      {{
        {{
            {LD3_GPIO_Port, LD3_Pin},
            {LD5_GPIO_Port, LD5_Pin}          
        }},
        {{
            {LD4_GPIO_Port, LD4_Pin},
            {LD6_GPIO_Port, LD6_Pin}
        }}
      }};
  };

  class LedModePairBlink2: public LedModeInf
  {
    public:
      ~LedModePairBlink2() = default;

      void blink(void) override
      {
        ///first setup 
        static bool isFirstCalled{true};
        if(isFirstCalled)
        {
          for(auto singleHandler: m_ledList[0U])
          {
            singleHandler.driveLED(0U); ///reset
          }

          for(auto singleHandler: m_ledList[1U])
          {
            singleHandler.driveLED(1U); ///set
          }
          isFirstCalled = false;
        }
        else
        {
          for(auto subLedList: m_ledList)
          {
            for(auto singleHandler: subLedList)
            {
              singleHandler.blinkLED(); 
            } 
          }
        }
      }
      

      static LedModeInf& getSingleton(void) 
      {
        static LedModePairBlink2 m_mainProcessor{};
        return m_mainProcessor;
      }

    private:
      LedModePairBlink2() = default;
      LedModePairBlink2(const LedModePairBlink2&) = delete;
      LedModePairBlink2(LedModePairBlink2&&) = delete;
      LedModePairBlink2& operator=(LedModePairBlink2&) = delete;
      LedModePairBlink2& operator=(LedModePairBlink2&&) = delete;
      vfc::array<vfc::array<ComplexDriver::LEDHandler, 2U>,2U> m_ledList
      {{
        {{
            {LD3_GPIO_Port, LD3_Pin},
            {LD6_GPIO_Port, LD6_Pin}          
        }},
        {{
            {LD4_GPIO_Port, LD4_Pin},
            {LD5_GPIO_Port, LD5_Pin}
        }}
      }};
  };

  class LedModeBlinkCircle: public LedModeInf
  {
    public:
      ~LedModeBlinkCircle() = default;

      void blink(void) override
      {
        static uint8_t s_currentLedIndex_u8{0U};

        uint8_t l_index_u8{0U};
        for(auto singleHandler: m_ledList)
        {
          if(l_index_u8 == s_currentLedIndex_u8)
          {
            singleHandler.driveLED(1U); ///set
          }                           
          else
          {
            singleHandler.driveLED(0U); ///reset
          }
          l_index_u8++;
        }

        s_currentLedIndex_u8 = (++s_currentLedIndex_u8 == 5U)?0U:s_currentLedIndex_u8; 
      }

      static LedModeInf& getSingleton(void) 
      {
        static LedModeBlinkCircle m_mainProcessor{};
        return m_mainProcessor;
      }

    private:
      LedModeBlinkCircle() = default;
      LedModeBlinkCircle(const LedModeBlinkCircle&) = delete;
      LedModeBlinkCircle(LedModeBlinkCircle&&) = delete;
      LedModeBlinkCircle& operator=(LedModeBlinkCircle&) = delete;
      LedModeBlinkCircle& operator=(LedModeBlinkCircle&&) = delete;

      vfc::array<ComplexDriver::LEDHandler, 4U> m_ledList
      {{
        {LD3_GPIO_Port, LD3_Pin},
        {LD4_GPIO_Port, LD4_Pin},
        {LD5_GPIO_Port, LD5_Pin},
        {LD6_GPIO_Port, LD6_Pin}
      }};
  };

  class LedModeStop: public LedModeInf
  {
    public:
      ~LedModeStop() = default;

      void blink(void) override
      {
        for(auto led:m_ledList)
        {
          led.driveLED(0U);
        }
      }

      static LedModeInf& getSingleton(void) 
      {
        static LedModeStop m_mainProcessor{};
        return m_mainProcessor;
      }

    private:
      LedModeStop() = default;
      LedModeStop(const LedModeStop&) = delete;
      LedModeStop(LedModeStop&&) = delete;
      LedModeStop& operator=(LedModeStop&) = delete;
      LedModeStop& operator=(LedModeStop&&) = delete;

      vfc::array<ComplexDriver::LEDHandler, 4U> m_ledList
      {{
        {LD3_GPIO_Port, LD3_Pin},
        {LD4_GPIO_Port, LD4_Pin},
        {LD5_GPIO_Port, LD5_Pin},
        {LD6_GPIO_Port, LD6_Pin}
      }};
  };

  class LedManager
  {
    public:
      LedManager(void) 
      {
        ///Init all singletons to be used
        static_cast<void>(LedModeAllBlink::getSingleton());
        static_cast<void>(LedModePairBlink1::getSingleton());
        static_cast<void>(LedModePairBlink2::getSingleton());
        static_cast<void>(LedModeBlinkCircle::getSingleton());
        static_cast<void>(LedModeStop::getSingleton());
        setLedMode(10U); ///not defined index for default set 
      }

      ~LedManager() = default;
      
      void blink(void);
      void setLedMode(uint8_t index_u8); 

    private: 
      LedManager(const LedManager&) = delete;
      LedManager(LedManager&&) = delete;
      LedManager& operator=(LedManager&) = delete;
      LedManager& operator=(LedManager&&) = delete;

      LedModeInf* m_currentLedMode{nullptr};
  };
}

#endif

