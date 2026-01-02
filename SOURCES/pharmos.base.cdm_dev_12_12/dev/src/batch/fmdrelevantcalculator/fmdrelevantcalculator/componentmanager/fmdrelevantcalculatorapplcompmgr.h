//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author 
 *  \date   
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_FMDRELEVANTCALCULATORAPPLCOMPMGR_H
#define GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_FMDRELEVANTCALCULATORAPPLCOMPMGR_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/irunnableptr.h>
#include "infrastructure/cmdline/fmdrelevantcalculatorcmdlineevaluator.h"

#include "infrastructure/mail/imailalertptr.h"

// dm
#include <domainmodule/ifmddeterminationparameterdmptr.h>
#include <domainmodule/ifmdrelevantdmptr.h>

// uc
#include "iusecasegetter.h"

// libutil
#include <libutil/applcomponent.h>
#include <boost/enable_shared_from_this.hpp>
#include <libutil/accessor.h>

//-------------------------------------------------------------------------------------------------//
// forward declaration section
//-------------------------------------------------------------------------------------------------//
namespace basar
{
    namespace db
    {
        namespace aspect
        {
            class ConnectionRef;
        }
    }
}

namespace log4cplus
{
    class Logger;
}

//-------------------------------------------------------------------------------------------------//
// class declaration setcion
//-------------------------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    namespace componentManager
    {
        class ApplCompMgr : public libutil::componentManager::ApplCompMgrBase,
                            public IUseCaseGetter,
                            public boost::enable_shared_from_this< ApplCompMgr >
        {
            public:
                ApplCompMgr();
                virtual ~ApplCompMgr();

				void setCmdLineArguments( const infrastructure::cmdLine::AppArgs& appArgs );
				void injectMailAlert(infrastructure::mail::IMailAlertPtr );

                /////////////////////////////////////////////////////////////////////
                // use case
                /////////////////////////////////////////////////////////////////////
                libutil::useCase::IRunnablePtr                                          getMainUC();
                
            protected:
                virtual void                                                            doClear();

                /////////////////////////////////////////////////////////////////////
                // domain modules
                /////////////////////////////////////////////////////////////////////
				domMod::fmdarticle::IFmdRelevantDMPtr								    getFmdArticleDM();
				domMod::fmddeterminationparameter::IFmdDeterminationParameterDMPtr		getFmdDeterminationParameterDM();

				/////////////////////////////////////////////////////////////////////
				// accessors
				/////////////////////////////////////////////////////////////////////
				libutil::infrastructure::accessor::IAccessorPtr							getFmdDeterminationParameterAccessor();
           
                /////////////////////////////////////////////////////////////////////
                // db connection
                /////////////////////////////////////////////////////////////////////
                libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr   getDBConnection();


				infrastructure::mail::IMailAlertPtr										getMailAlert();

            private:
                ApplCompMgr( const ApplCompMgr& );
                ApplCompMgr& operator=( const ApplCompMgr& );
                
            private:
                ///////////////////////////////////////////////////////////////////
                // member variables
                ///////////////////////////////////////////////////////////////////
                const log4cplus::Logger&                                                m_Logger;

				fmdrelevantcalculator::infrastructure::cmdLine::AppArgs					m_AppArgs;
				infrastructure::mail::IMailAlertPtr										m_MailAlert;
        };

    } // end namnespace componentManager
} // end namnespace fmdrelevantcalculator

#endif
