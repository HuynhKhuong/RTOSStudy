#ifndef RUNNABLE_DEFINE_HPP
#define RUNNABLE_DEFINE_HPP

///\note global namespace to be used in different context
class RunnableInf
{
public:
  RunnableInf() = default;
  void run()
  {
	m_rxCustomerHook();
    m_customerRun();
    m_txCustomerHook();
  }

  virtual void init() = 0;

protected:
  ///\brief from runnable perspective, rxCustomerHook provides user intervention
  ///		to handle incoming messages before processing its services
  ///\note	as its design purpose, it must be called before run
  virtual void m_rxCustomerHook(void) = 0;

  ///\brief from runnable perspective, txCustomerHook provides user intervention
  ///		to handle its outputs before after processing its services
  ///\note	as its design purpose, it must be called after run
  virtual void m_txCustomerHook(void) = 0;

  ///\brief main function for runnable to process its services
  ///\note	as its design purpose, it must be called cyclically
  virtual void m_customerRun(void) = 0;
};

#endif

