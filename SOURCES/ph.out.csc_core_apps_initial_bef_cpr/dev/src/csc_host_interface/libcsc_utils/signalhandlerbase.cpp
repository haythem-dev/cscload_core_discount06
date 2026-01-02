
#ifdef WIN32
    #pragma warning( push )
    #pragma warning( disable: 4503 4512 4996 )
#endif
#include <boost/bind.hpp>
#include <boost/signals2.hpp>
#include "signalhandlerbase.h"
#include "setupsignalhandlingexception.h"

namespace libcsc_utils
{   
    static boost::signals2::signal<void (int)> mysignal;

    SignalHandlerBase::SignalHandlerBase()
    {
    }

    void SignalHandlerBase::registerSignalReceiver(ISignalReceiver& receiverToRegister)
    {
        boost::signals2::connection con = mysignal.connect(boost::bind(&ISignalReceiver::receiveSignal, boost::ref(receiverToRegister), _1));
        
        if (!con.connected())
        {
            throw libcsc_utils::SetupSignalHandlingException( basar::ExceptInfo("SignalHandlerBase::registerSignalReceiver", "failed registering signal receiver!", __FILE__, __LINE__) );
        }
    }

    void SignalHandlerBase::handleSignals(int sig)
    {     
        mysignal(sig);
    }
}

#ifdef WIN32
    #pragma warning( pop )
#endif
