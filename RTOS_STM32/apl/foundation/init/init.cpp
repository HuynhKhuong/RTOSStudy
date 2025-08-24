#include "init.hpp"
#include "menu/MenuSenderPort.hpp"
#include "net/NetSenderPort.hpp"

/**
 * \brief Initializes the application ports.
 * 
 * \details 
 *  This function initializes all necessary sender ports required for the application.
 *  It should be called during the system startup to ensure that all communication ports
 *  are properly set up before use.
 *
 * \param None
 * \return None
 */
void init(void)
{
    Port::g_menuStateInfoSenderPort_st.init();
    Port::g_menuLedSenderPort_st.init();
    Port::g_netMenuRtcConfigSenderPort_st.init();
    Port::g_menuRTCConfigDataSenderPort_st.init();
}


