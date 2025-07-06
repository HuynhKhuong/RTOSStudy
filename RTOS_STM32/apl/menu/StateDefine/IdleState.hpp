#ifndef IDLESTATE_HPP
#define IDLESTATE_HPP

#include "../MenuStateMachine.hpp"

namespace Menu
{
  // Concrete States
  class IdleState : public StateInf 
  {
    public:
      using UniqueIdType = StateInf::UniqueIdType; 
			
			static StateInf* getInstance(void)
			{
				static IdleState g_singleton{};
				return &g_singleton;
			}

      void eventListener(const uint32_t& eventType) override;
      void run(void) override;
      void updateState(void) override;

    private:
      IdleState():StateInf{static_cast<UniqueIdType>(MainStateIdList::MainMenu)}
      {/*do nothing*/}

      ~IdleState() = default;
  };
}//End of namespace Menu

#endif
