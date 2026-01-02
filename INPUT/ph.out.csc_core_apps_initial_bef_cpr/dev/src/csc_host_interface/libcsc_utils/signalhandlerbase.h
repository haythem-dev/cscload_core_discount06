//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  base class for reception and forwarding of system signals, be sure to implement your signal handling and isignalreceiver to be able to register for signal reception
 *  \author Marco Köppendörfer
 *  \date   04.10.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_LIBCSC_UTILS_SIGNALHANDLERBASE_H
#define GUARD_LIBCSC_UTILS_SIGNALHANDLERBASE_H

//#ifdef WIN32
//    #pragma warning( push )
//    #pragma warning( disable: 4675 4996 )
//        #include <boost/signals2.hpp>
//    #pragma warning( pop )
//#else
//        #include <boost/signals2.hpp>
//#endif

#include "isignalreceiver.h"



namespace libcsc_utils
{
    class SignalHandlerBase
    {
        //friend class basar::cmnutil::Singleton<SignalHandlerBase>;
    
        public:

            SignalHandlerBase();
            
            void registerSignalReceiver(ISignalReceiver& receiverToRegister);

            virtual void setupSignalHandling() = 0;

            static void handleSignals(int sig);

            //boost::signals2::signal<void (int)> mysignal;
        
        private:
            SignalHandlerBase(const SignalHandlerBase&);
			SignalHandlerBase& operator=(const SignalHandlerBase&);
            
    };

 //   class SignalHandler : public basar::cmnutil::Singleton<SignalHandlerBase> 
 //   {
	//friend class dummy;			//!< prevents pedantic compiler warning

 //   private:
	//    /*! \brief standard constructor \n \throw no-throw */
	//    SignalHandler();
	//    /*! \brief copy constructor \n \throw no-throw */
	//    SignalHandler( const SignalHandler & r );
	//    /*! \brief assign operator \n \throw no-throw */
	//    SignalHandler & operator = ( const SignalHandler & r );	
 //   };
}

#endif

