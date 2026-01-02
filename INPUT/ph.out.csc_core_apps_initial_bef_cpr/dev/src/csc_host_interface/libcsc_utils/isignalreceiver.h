//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  inherit from this class to be informed about the reception of a signal
 *  \author Marco Köppendörfer
 *  \date   04.10.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_SIGNALRECEIVERBASE_H
#define GUARD_LIBCSC_UTILS_SIGNALRECEIVERBASE_H

#include <signal.h> //convenience, allows clients to use SIGNAME instead of magic numbers

namespace libcsc_utils
{
    class ISignalReceiver
    {
        public:
            virtual void receiveSignal(int signal) = 0;
    };
}

#endif

