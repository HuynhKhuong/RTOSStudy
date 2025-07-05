#ifndef LEDSTATE_HPP
#define LEDSTATE_HPP

#include "../MenuStateMachine.hpp"

namespace Menu
{

  enum class LedStateSubEvent : uint8_t
  {
    LED_CMD_1 = 0U,
    LED_CMD_2,
    LED_CMD_3,
    LED_CMD_4,
    MAXIMUM_LED_CMD
  };

  // Concrete States
  class LedState : public StateInf 
  {
    public:
      using UniqueIdType = StateInf::UniqueIdType; 
			
			static StateInf* getInstance(void)
			{
				static LedState g_singleton{};
				return &g_singleton;
			}

      void eventListener(const uint8_t& eventType) override; 
      void run(void) override;
      void updateState(void) override;

    private:
  

      LedState():StateInf{static_cast<UniqueIdType>(MainStateIdList::LedMenu)}
      {/*do nothing*/}

      ~LedState() = default;

      ///Sender port for informing TBD
  };
}//End of namespace Menu

#endif
