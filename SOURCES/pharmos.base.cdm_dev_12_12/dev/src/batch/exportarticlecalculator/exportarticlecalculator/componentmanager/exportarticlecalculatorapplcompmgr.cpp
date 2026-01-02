//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Bjoern Bischof
 *  \date   08.07.2013
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
// global
#include "exportarticlecalculatorapplcompmgr.h"
#include "loggerpool/exportarticlecalculator_loggerpool.h"

// uc
#include "usecase/mainucptr.h"
#include "usecase/mainuc.h"

//dommod
#include "domainmodule/exportarticledmptr.h"
#include "domainmodule/exportarticledm.h"

#include "domainmodule/exportexclusionparameterdmptr.h"
#include "domainmodule/exportexclusionparameterdm.h"

#include "infrastructure/accessor/exportexclusionparameteracc_definitions.h"
#include <infrastructure/accessor/exportexclusionparameteracc.h>

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
namespace exportarticlecalculator
{
    namespace componentManager
    {
        ApplCompMgr::ApplCompMgr()
			: m_Logger( exportarticlecalculator::LoggerPool::getLoggerExportarticlecalculator() )
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

            exportarticlecalculator::useCase::MainUCPtr mainUC = exportarticlecalculator::useCase::MainUCPtr( new exportarticlecalculator::useCase::MainUC );
            mainUC->injectUseCaseGetter      ( shared_from_this() );
			mainUC->injectMailAlert(getMailAlert());

			mainUC->injectExportExclusionParameterDM(getExportExclusionParameterDM());
			mainUC->injectExportArticleDM(getExportArticleDM());

			return mainUC;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </UC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		domMod::exportarticle::IExportArticleDMPtr ApplCompMgr::getExportArticleDM()
		{
			domMod::exportarticle::ExportArticleDMPtr p = 
				domMod::exportarticle::ExportArticleDMPtr(new domMod::exportarticle::ExportArticleDM(LoggerPool::getLoggerDomModules()));
			
			p->injectDbConnection(getDBConnection()); // no accessor, only prepared statements
			p->setBranchNo(m_AppArgs.m_BranchNo);
			p->setCountry(m_AppArgs.m_Country);
			p->setDateFrom(m_AppArgs.m_DateFrom);

			return p;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		domMod::exportexclusionparameter::IExportExclusionParameterDMPtr ApplCompMgr::getExportExclusionParameterDM()
		{
			domMod::exportexclusionparameter::ExportExclusionParameterDMPtr p = 
				domMod::exportexclusionparameter::ExportExclusionParameterDMPtr(new domMod::exportexclusionparameter::ExportExclusionParameterDM(LoggerPool::getLoggerDomModules()));
			
			p->injectAccessor(getExportExclusionParameterAccessor()); 
			p->setBranchNo(m_AppArgs.m_BranchNo);
			p->setCountry (m_AppArgs.m_Country);

			return p;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getExportExclusionParameterAccessor()
		{
			METHODNAME_DEF( ApplCompMgr, getExportExclusionParameterAccessor )
			BLOG_TRACE_METHOD( m_Logger, fun );

			infrastructure::accessor::exportexclusionparameter::SelectExportExclusionParamByCountry(); // pseudo reference
			libutil::infrastructure::accessor::IAccessorPtr accessor = libutil::infrastructure::accessor::AccessorProxyPtr(
				new libutil::infrastructure::accessor::AccessorProxy( infrastructure::accessor::exportexclusionparameter::lit::EXPORT_EXCLUSION_CRITERIA_ACC, getDBConnection()->getCurrentConnection() ));
										
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
} // end namnespace exportarticlecalculator
