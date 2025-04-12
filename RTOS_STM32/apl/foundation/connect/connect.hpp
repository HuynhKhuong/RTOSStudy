#ifndef CONNECT_HPP
#define CONNECT_HPP


///\note  Keep at global namespace to be used as background setup 
///\brief This function performs
///       Connect sender port to mempool (sender port comprises of mempools)
///       Connect receiver port to mempool (for explicit release)
///       Connect sender port to receiver port (via queue handler) 
void connect(void);

#endif

