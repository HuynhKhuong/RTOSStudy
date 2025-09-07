#ifndef RTCSTATE_HPP
#define RTCSTATE_HPP

#include "MenuStateMachine.hpp"

namespace Menu
{
  enum class RTCEventID : uint8_t 
  {
      CONFIGTIME = 0U,
      CONFIGDATE,
      REPORT,
      MAXIMUM_RTC_EVENT
  };

  // Concrete States
  class RTCState : public StateInf 
  {
    public:
      using UniqueIdType = StateInf::UniqueIdType; 
			
	  static StateInf* getInstance(void)
	  {
		static RTCState g_singleton{};
		return &g_singleton;
	  }

      void eventListener(const uint32_t& eventType) override; 
      void run(void) override;
      void updateState(void) override;

    private:
      RTCState():StateInf{static_cast<UniqueIdType>(MainStateIdList::RTCMenu)}
      {/*do nothing*/}

      ~RTCState() = default; 
  };
}

#endif

