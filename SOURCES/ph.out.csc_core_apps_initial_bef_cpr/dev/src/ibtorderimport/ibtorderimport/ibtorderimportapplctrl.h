    //------------------------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  application class (main) for IBTORDERIMPORT component (singleton)
 *  \author
 *  \date
 */
//------------------------------------------------------------------------------------------------------------------//
#ifndef GUARD_IBTORDERIMPORTAPPLCTRL_H
#define GUARD_IBTORDERIMPORTAPPLCTRL_H

//------------------------------------------------------------------------------------------------------------------//
// include section
//------------------------------------------------------------------------------------------------------------------//
#include "componentmanager/ibtorderimportinfrastructurecompmgrptr.h"

// basar
#include <libbasarcmnutil.h>

#include <isignalreceiver.h>
#include <csc_signalhandler.h>

//------------------------------------------------------------------------------------------------------------------//
// class declaration section
//------------------------------------------------------------------------------------------------------------------//
namespace ibtorderimport
{
    class ApplCtrlImpl : public libcsc_utils::ISignalReceiver
    {
        //--------------------------------------------------------------------------------------------------//
        // friends
        //--------------------------------------------------------------------------------------------------//
        friend class basar::cmnutil::Singleton<ApplCtrlImpl>;

        public:
            ~ApplCtrlImpl();

            void                                                    init( int argc, char *argv[] );
            void                                                    run();
            void                                                    shutdown();
			void													receiveSignal(int sig);
			
        private:
            //---------------------------------------------------------//
            // member methods
            //---------------------------------------------------------//
            ApplCtrlImpl                ();
            ApplCtrlImpl                ( const ApplCtrlImpl& );
            ApplCtrlImpl & operator =   ( const ApplCtrlImpl& );

            const log4cplus::Logger&                                getLogger() const;

            void                                                    createInfrastructureCM( int argc, char *argv[] );
            void                                                    deleteInfrastructureCM();
            componentManager::InfrastructureCompMgrPtr              getInfrastructureCM();

			void													processingSleep();
			
			//---------------------------------------------------------//
            // member variables
            //---------------------------------------------------------//
            const log4cplus::Logger&                                m_Logger;
            componentManager::InfrastructureCompMgrPtr              m_InfrastructureCM;

			libcsc_utils::CSC_SignalHandler							m_SignalHandler;
			bool													m_ExitGracefull;
			
    };

    //---------------------------------------------------------------------------------------//
    /*! \brief  derived class from IBTORDERIMPORTApplBase.
                This is a final class. Singleton
    *  \note    class is necessary for dll exporting Singleton\<IBTORDERIMPORTApplBase\>  */
    class ApplCtrl : public basar::cmnutil::Singleton< ApplCtrlImpl >
    {
        private:
            ApplCtrl            ();
            ApplCtrl                        ( const ApplCtrl& r );
            ApplCtrl &          operator =  ( const ApplCtrl& r );
    };

}    // end namespace ibtorderimport

#endif //end GUARD_IBTORDERIMPORTAPPLCTRL_H
