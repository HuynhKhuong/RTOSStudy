#ifndef LEDRUNNABLE_HPP
#define LEDRUNNABLE_HPP

#include "led/LedModeManager.hpp"
#include "runnable/RunnableDefine.hpp"

namespace LedCom {

class LedRunnable:public RunnableInf
{
public:
    LedRunnable(void);

    void run(void)
    {
        RunnableInf::run();
    }

    void init(void) override
    {/*do nothing*/}


protected:
    void m_rxCustomerHook(void) override;
    void m_txCustomerHook(void) override;
    void m_customerRun(void) override;

    Led::LedManager m_ledModeManager{};
};

extern LedRunnable* g_myLedRunnable_st;

}//end of namespace LedCom

#endif

