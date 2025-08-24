#ifndef RTCRUNNABLE_HPP
#define RTCRUNNABLE_HPP

#include "runnable/RunnableDefine.hpp"

namespace RTC{

class RTCRunnable:public RunnableInf
{
public:
  RTCRunnable(void);

  void run(void)
  {
    RunnableInf::run();
  }

  void init(void) override
  {
  }


protected:
  void m_rxCustomerHook(void) override;
  void m_txCustomerHook(void) override;
  void m_customerRun(void) override;

};

extern RTCRunnable* g_myRTCRunnable_st;

}//end of namespace RTC

#endif

