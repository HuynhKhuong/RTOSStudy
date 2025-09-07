#ifndef COMQUERY_HPP_INCLUDED
#define COMQUERY_HPP_INCLUDED

namespace NetCom{

/// \brief netComRxMainFunction handles polling messages status from message handlers configured by user
///        And notify via configured callback functions
/// \note  This function should be called cyclically to achieve polling behaviour
void netComRxMainFunction(void);


/// \brief netComTxMainFunction handles polling messages status triggered from application entities 
///        trigger sending to lowerlayers
/// \note  This function should be called cyclically to achieve polling behaviour
void netComTxMainFunction(void);

}//end of namespace NetCom

#endif

