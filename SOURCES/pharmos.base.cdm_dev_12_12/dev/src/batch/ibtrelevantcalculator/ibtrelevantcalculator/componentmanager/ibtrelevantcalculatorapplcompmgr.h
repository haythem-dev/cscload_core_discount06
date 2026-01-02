//-------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   08.07.2013
 */
//-------------------------------------------------------------------------------------------------//
#ifndef GUARD_IBTRELEVANTCALCULATOR_COMPONENTMANAGER_IBTRELEVANTCALCULATORAPPLCOMPMGR_H
#define GUARD_IBTRELEVANTCALCULATOR_COMPONENTMANAGER_IBTRELEVANTCALCULATORAPPLCOMPMGR_H

//-------------------------------------------------------------------------------------------------//
// include section
//-------------------------------------------------------------------------------------------------//
#include <libutil/irunnableptr.h>
#include "infrastructure/cmdline/ibtrelevantcalculatorcmdlineevaluator.h"

#include "infrastructure/mail/imailalertptr.h"

// dm
#include <domainmodule/iibtrelevantparameterdmptr.h>
#include <domainmodule/iibtarticledmptr.h>
#include <domainmodule/iibtrelevantbranchparameterdmptr.h>
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
namespace ibtrelevantcalculator
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
				domMod::ibtArticle::IIbtArticleDMPtr									getIbtArticleDM();
				domMod::ibtRelevantParameter::IIbtRelevantParameterDMPtr				getIbtRelevantParameterDM();
				domMod::ibtRelevantBranchParameter::IIbtRelevantBranchParameterDMPtr	getIbtRelevantBranchParameterDM();
				/////////////////////////////////////////////////////////////////////
				// accessors
				/////////////////////////////////////////////////////////////////////
				libutil::infrastructure::accessor::IAccessorPtr							getIbtRelevantParameterAccessor();
				libutil::infrastructure::accessor::IAccessorPtr							getIbtRelevantBranchParameterAccessor();
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

				ibtrelevantcalculator::infrastructure::cmdLine::AppArgs					m_AppArgs;
				infrastructure::mail::IMailAlertPtr										m_MailAlert;
        };

    } // end namnespace componentManager
} // end namnespace ibtrelevantcalculator

#endif
