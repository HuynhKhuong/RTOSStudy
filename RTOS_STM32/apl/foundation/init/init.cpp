#include "init.hpp"
#include "net/NetSenderPort.hpp"

void init(void)
{
  Port::g_netSenderPort_st.init();
}


