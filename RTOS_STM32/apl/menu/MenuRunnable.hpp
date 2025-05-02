#ifndef MENURUNNABLE_HPP
#define MENURUNNABLE_HPP

#include "menu/MenuStateMachine.hpp"
#include "runnable/RunnableDefine.hpp"
#include "StateDefine/LedState.hpp"
#include "StateDefine/IdleState.hpp"

///\brief Menu runnable handles overall state management
///       State Management of the entire system are represented as numerical code system
///       In further development, in case it is required to be user friendly, an UI encoding should be developed 
///       compositioning this Runnable

namespace Menu
{
class MenuRunnable:public RunnableInf
{
public:
  MenuRunnable(void);

  void run(void)
  {
    RunnableInf::run();
  }

  void init(void) override
  {
    ///Should perform receiver/sender port connection here

    ///perform init for all singletons
    static_cast<void>(LedState::getInstance());
    static_cast<void>(IdleState::getInstance());

    g_machine_st.setState(IdleState::getInstance());
  }


protected:
  void m_rxCustomerHook(void) override;
  void m_txCustomerHook(void) override;
  void m_customerRun(void) override;
};

extern MenuRunnable* g_myMenuRunnable_st;

}//end of namespace MenuCom

#endif

