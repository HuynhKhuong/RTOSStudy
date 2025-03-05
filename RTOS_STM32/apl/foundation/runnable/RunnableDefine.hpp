#ifndef RUNNABLE_DEFINE_HPP
#define RUNNABLE_DEFINE_HPP

///\note global namespace to be used in different context
class RunnableInf
{
public:
  RunnableInf() = default;
  void run()
  {
    m_txCustomerHook();
    m_customerRun();
    m_rxCustomerHook();
  }

  virtual void init() = 0;

protected:
  virtual void m_rxCustomerHook(void) = 0;
  virtual void m_txCustomerHook(void) = 0;
  virtual void m_customerRun(void) = 0;
};

#endif

