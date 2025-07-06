#ifndef MENUSTATEMACHINE_HPP
#define MENUSTATEMACHINE_HPP

#include "EventDefine.hpp"

namespace Menu
{
  enum class MainStateIdList: uint32_t
  {
    LedMenu = 0U,
    RTCMenu,
    MainMenu
  };

  // Abstract State
  class StateInf 
  {
    public:
      using UniqueIdType = uint32_t;
			
      StateInf(const uint32_t uniqueId_u32): m_uniqueId_u32{uniqueId_u32}
      {}
      ~StateInf() = default;

      virtual void eventListener(const uint32_t& eventType) = 0;
      virtual void run(void) = 0;
      virtual void updateState(void) = 0;

    private:
      uint32_t m_uniqueId_u32; ///for debug purpose
  };

  // Context (StateMachine)
  class StateMachine 
  {
    public:
      StateMachine() = default; //: state() {}

      void run(void);

      ///\brief  SetState is exposed as an providing port for state to 
      ///        trigger set next state to the machine
      void setState(StateInf* toSwitchState_ptr) 
      {
        if(toSwitchState_ptr == nullptr) return;
        m_currentState = toSwitchState_ptr;
      }
      

      void setRawEventId(const uint32_t rawEventId_u32)
      {
        m_rawEventId_u32 = rawEventId_u32;
        m_isNewEvent_bo = true;
      }

      
    private:
      StateInf* m_currentState{nullptr};
      bool m_isNewEvent_bo{false};
      uint32_t m_rawEventId_u32{static_cast<uint32_t>(EventType::DEFAULT)};
  };

  class SwitchStateEngine
  {
    public: 
      static void switchState(StateInf* toSwitchState_ptr, StateMachine* parentStateMachine_ptr)
      {
        if((toSwitchState_ptr == nullptr)||(parentStateMachine_ptr == nullptr))
        {
          return;
        }

        parentStateMachine_ptr->setState(toSwitchState_ptr);
        toSwitchState_ptr->updateState();
      }
  };

  extern StateMachine g_machine_st; 

}//end of namespace Menu

#endif
    
