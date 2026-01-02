#include <signal.h>
#include <errno.h>
#include "csc_signalhandler.h"

//--------------------------------------------------------------------------------------------------//
// extern definition section
//--------------------------------------------------------------------------------------------------//
#include "externdef.h" //be sure to include this in your implementation


namespace libcsc_utils
{
    CSC_SignalHandler::CSC_SignalHandler()
    {
    }



    void CSC_SignalHandler::setupSignalHandling()
    {
#ifndef WIN32
        //cheap signal handling
        struct sigaction act;
        act.sa_handler = ::handleSIG; //handleSIG is defined in "externdef.h"

        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;

        sigaction(SIGINT, &act, 0); //register handling of SIGINT
        sigaction(SIGTERM, &act, 0); //register handling of SIGTERM - same handler as above
#else
        signal((int) SIGINT, ::handleSIG);
        signal((int) SIGTERM, ::handleSIG);
#endif

    }

}