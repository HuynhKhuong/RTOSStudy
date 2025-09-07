#ifndef COMBUSINPUTNOTIFY_HPP
#define COMBUSINPUTNOTIFY_HPP

namespace NetCom
{
    ///\brief Notify mechanism offered by each Rx message  
    ///\details This notify shall be invoked when
    ///         - New message comes
    ///         - layout check & security check on the message passed
    ///\note User should use this function to process corresponding signals
    ///      Or to deliver onto other SWCs
    void s_LEDControlMsgNotif_Rx(void);
    void s_RTCControlMsgNotif_Rx(void);
}

#endif

