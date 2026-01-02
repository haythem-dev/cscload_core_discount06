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
#include "loadcontractshrapplcompmgr.h"
#include "loggerpool/loadcontractshr_loggerpool.h"

// uc
#include "usecase/mainucptr.h"
#include "usecase/mainuc.h"

//dommod
#include "domainmodule/loadcontractshrdmptr.h"
#include "domainmodule/loadcontractshrdm.h"

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
namespace loadcontractshr
{
    namespace componentManager
    {
        ApplCompMgr::ApplCompMgr()
			: m_Logger( loadcontractshr::LoggerPool::getLoggerLoadContractsHr() )
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
            loadcontractshr::useCase::MainUCPtr mainUC = loadcontractshr::useCase::MainUCPtr( new loadcontractshr::useCase::MainUC );
            mainUC->injectUseCaseGetter      ( shared_from_this() );
			mainUC->injectMailAlert(getMailAlert());
			mainUC->injectLoadContractsHrDM(getLoadContractsHrDM());
			return mainUC;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </UC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		domMod::loadcontractshrdm::ILoadContractsHrDMPtr ApplCompMgr::getLoadContractsHrDM()
		{
			domMod::loadcontractshrdm::LoadContractsHrDMPtr p =
				domMod::loadcontractshrdm::LoadContractsHrDMPtr(new domMod::loadcontractshrdm::LoadContractsHrDM(LoggerPool::getLoggerDomModules()));
			
			p->injectDbConnection(getDBConnection()); // no accessor, only prepared statements
			p->setPath(m_AppArgs.m_Path);
			p->setMode(m_AppArgs.m_Mode);

			return p;
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
} // end namnespace loadcontractshr
