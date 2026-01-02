//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  class for catching specific signals
 *  \author Marco Köppendörfer
 *  \date   04.10.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_CSC_SIGNALHANDLER_H
#define GUARD_LIBCSC_UTILS_CSC_SIGNALHANDLER_H


#include "signalhandlerbase.h"

namespace libcsc_utils
{
    class CSC_SignalHandler : public SignalHandlerBase
    {
        public:

            CSC_SignalHandler();
            
            void setupSignalHandling();

        private:
            CSC_SignalHandler(const CSC_SignalHandler&);
			CSC_SignalHandler& operator=(const CSC_SignalHandler&);

    };
}

#endif

