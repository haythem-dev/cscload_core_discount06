//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author 
 *  \date   
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
// global
#include "fmdrelevantcalculatorapplcompmgr.h"
#include "loggerpool/fmdrelevantcalculator_loggerpool.h"

// uc
#include "usecase/mainucptr.h"
#include "usecase/mainuc.h"

//dommod
#include "domainmodule/fmdrelevantdmptr.h"
#include "domainmodule/fmdrelevantdm.h"

#include "domainmodule/fmddeterminationparameterdmptr.h"
#include "domainmodule/fmddeterminationparameterdm.h"

#include "infrastructure/accessor/fmddeterminationparameteracc_definitions.h"
#include <infrastructure/accessor/fmddeterminationparameteracc.h>

// libutil
#include <libutil/util.h>
#include <libutil/dbconnection.h>

// basar
#include <libbasarcmnutil_logging.h>
#include <libbasardbsql_databaseinfo.h>
#include <libbasarlogin.h>
#include <libbasardbsql.h>
#include <libbasarproperty.h>

//----------------------------------------------------------------------------//
// class definition setcion
//----------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    namespace componentManager
    {
        ApplCompMgr::ApplCompMgr()
			: m_Logger( fmdrelevantcalculator::LoggerPool::getLoggerFmdRelevantcalculator() )
        {
            METHODNAME_DEF( ApplCompMgr, ApplCompMgr )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }

        ApplCompMgr::~ApplCompMgr()
        {
            METHODNAME_DEF( ApplCompMgr, ~ApplCompMgr )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }

        void ApplCompMgr::doClear()
        {
            METHODNAME_DEF( ApplCompMgr, doClear )
            BLOG_TRACE_METHOD( m_Logger, fun );
        }

		void ApplCompMgr::injectMailAlert( infrastructure::mail::IMailAlertPtr mailAlert )
		{
			METHODNAME_DEF( ApplCompMgr, injectMailAlert )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_MailAlert = mailAlert;
		}

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // <UC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        libutil::useCase::IRunnablePtr ApplCompMgr::getMainUC()
        {
            METHODNAME_DEF( ApplCompMgr, getMainUC )
            BLOG_TRACE_METHOD( m_Logger, fun );

            fmdrelevantcalculator::useCase::MainUCPtr mainUC = fmdrelevantcalculator::useCase::MainUCPtr( new fmdrelevantcalculator::useCase::MainUC );
            mainUC->injectUseCaseGetter      ( shared_from_this() );
			mainUC->injectMailAlert(getMailAlert());

			mainUC->injectFmdDeterminationParameterDM(getFmdDeterminationParameterDM());
			mainUC->injectFmdRelevantDM(getFmdArticleDM());

			return mainUC;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </UC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		domMod::fmdarticle::IFmdRelevantDMPtr ApplCompMgr::getFmdArticleDM()
		{
			domMod::fmdarticle::FmdRelevantDMPtr p =
				domMod::fmdarticle::FmdRelevantDMPtr(new domMod::fmdarticle::FmdRelevantDM(LoggerPool::getLoggerDomModules()));
			
			p->injectDbConnection(getDBConnection()); // no accessor, only prepared statements
			p->setBranchNo(m_AppArgs.m_BranchNo);

			return p;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		domMod::fmddeterminationparameter::IFmdDeterminationParameterDMPtr ApplCompMgr::getFmdDeterminationParameterDM()
		{
			domMod::fmddeterminationparameter::FmdDeterminationParameterDMPtr p =
				domMod::fmddeterminationparameter::FmdDeterminationParameterDMPtr(new domMod::fmddeterminationparameter::FmdDeterminationParameterDM(LoggerPool::getLoggerDomModules()));

			p->injectAccessor(getFmdDeterminationParameterAccessor());

			return p;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getFmdDeterminationParameterAccessor()
		{
			METHODNAME_DEF( ApplCompMgr, getFmdDeterminationParameterAccessor )
			BLOG_TRACE_METHOD( m_Logger, fun );

			infrastructure::accessor::fmddeterminationparameter::SelectFmdDeterminationParam(); // pseudo reference
			libutil::infrastructure::accessor::IAccessorPtr accessor = libutil::infrastructure::accessor::AccessorProxyPtr(
				new libutil::infrastructure::accessor::AccessorProxy( infrastructure::accessor::fmddeterminationparameter::lit::FMD_DETERMINATION_CRITERIA_ACC, getDBConnection()->getCurrentConnection() ));
										
			return accessor;
		}

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr ApplCompMgr::getDBConnection()
        {
            METHODNAME_DEF( ApplCompMgr, getDBConnection() )
            BLOG_TRACE_METHOD( m_Logger, fun );

            return getDBConnectionData();
        }

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void ApplCompMgr::setCmdLineArguments( const infrastructure::cmdLine::AppArgs& appArgs )
		{
			METHODNAME_DEF( ApplCompMgr, setCmdLineArgurments )
			BLOG_TRACE_METHOD( m_Logger, fun );

			m_AppArgs = appArgs;
		}
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		infrastructure::mail::IMailAlertPtr	ApplCompMgr::getMailAlert()
		{
			return m_MailAlert;
		}
        
    } // end namnespace componentManager
} // end namnespace fmdrelevantcalculator
