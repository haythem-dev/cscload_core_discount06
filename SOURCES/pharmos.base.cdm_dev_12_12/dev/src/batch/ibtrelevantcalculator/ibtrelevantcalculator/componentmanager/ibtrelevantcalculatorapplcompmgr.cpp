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
#include "ibtrelevantcalculatorapplcompmgr.h"
#include "loggerpool/ibtrelevantcalculator_loggerpool.h"

// uc
#include "usecase/mainucptr.h"
#include "usecase/mainuc.h"

//dommod
#include "domainmodule/ibtarticledmptr.h"
#include "domainmodule/ibtarticledm.h"

#include "domainmodule/ibtrelevantparameterdmptr.h"
#include "domainmodule/ibtrelevantparameterdm.h"

#include "domainmodule/ibtrelevantbranchparameterdmptr.h"
#include "domainmodule/ibtrelevantbranchparameterdm.h"

#include "infrastructure/accessor/ibtexcludeparameteracc_definitions.h"
#include <infrastructure/accessor/ibtexcludeparameteracc.h>

#include "infrastructure/accessor/ibtbrancharticlerelevanceacc_definitions.h"
#include <infrastructure/accessor/ibtbrancharticlerelevanceacc.h>

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
namespace ibtrelevantcalculator
{
    namespace componentManager
    {
        ApplCompMgr::ApplCompMgr()
			: m_Logger( ibtrelevantcalculator::LoggerPool::getLoggerIbtrelevantcalculator() )
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

            ibtrelevantcalculator::useCase::MainUCPtr mainUC = ibtrelevantcalculator::useCase::MainUCPtr( new ibtrelevantcalculator::useCase::MainUC );
            mainUC->injectUseCaseGetter      ( shared_from_this() );
			mainUC->injectMailAlert(getMailAlert());

			mainUC->injectIbtRelevantParameterDM(getIbtRelevantParameterDM());
			mainUC->injectIbtRelevantBranchParameterDM(getIbtRelevantBranchParameterDM());
			mainUC->injectIbtArticleDM(getIbtArticleDM());

			return mainUC;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </UC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		domMod::ibtArticle::IIbtArticleDMPtr ApplCompMgr::getIbtArticleDM()
		{
			domMod::ibtArticle::IbtArticleDMPtr p = 
				domMod::ibtArticle::IbtArticleDMPtr(new domMod::ibtArticle::IbtArticleDM(LoggerPool::getLoggerDomModules()));
			
			p->injectDbConnection(getDBConnection()); // no accessor, only prepared statements
			p->setChangeUser(m_AppArgs.m_UserName);
			p->setBranchNo(m_AppArgs.m_BranchNo);

			return p;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		domMod::ibtRelevantParameter::IIbtRelevantParameterDMPtr ApplCompMgr::getIbtRelevantParameterDM()
		{
			METHODNAME_DEF( ApplCompMgr, getIbtRelevantParameterDM )
			BLOG_TRACE_METHOD( m_Logger, fun );

			domMod::ibtRelevantParameter::IbtRelevantParameterDMPtr p = 
				domMod::ibtRelevantParameter::IbtRelevantParameterDMPtr(new domMod::ibtRelevantParameter::IbtRelevantParameterDM(LoggerPool::getLoggerDomModules()));
			
			p->injectAccessor(getIbtRelevantParameterAccessor()); 
			p->setBranchNo(m_AppArgs.m_BranchNo);

			return p;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		domMod::ibtRelevantBranchParameter::IIbtRelevantBranchParameterDMPtr ApplCompMgr::getIbtRelevantBranchParameterDM()
		{
			METHODNAME_DEF( ApplCompMgr, getIbtRelevantBranchParameterDM )
			BLOG_TRACE_METHOD( m_Logger, fun );
			
				domMod::ibtRelevantBranchParameter::IbtRelevantBranchParameterDMPtr p = 
				domMod::ibtRelevantBranchParameter::IbtRelevantBranchParameterDMPtr(new domMod::ibtRelevantBranchParameter::IbtRelevantBranchParameterDM(LoggerPool::getLoggerDomModules()));
			
			p->injectAccessor(getIbtRelevantBranchParameterAccessor()); 
			p->setBranchNo(m_AppArgs.m_BranchNo);

			return p;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getIbtRelevantBranchParameterAccessor()
		{
			METHODNAME_DEF( ApplCompMgr, getIbtRelevantBranchParameterAccessor )
			BLOG_TRACE_METHOD( m_Logger, fun );

			infrastructure::accessor::ibtbrancharticlerelevanceparam::SelectIbtBranchArticleRelevanceParam(); // pseudo reference
			libutil::infrastructure::accessor::IAccessorPtr accessor = libutil::infrastructure::accessor::AccessorProxyPtr(
				new libutil::infrastructure::accessor::AccessorProxy( infrastructure::accessor::ibtbrancharticlerelevanceparam::lit::IBT_BRANCH_ARTICLE_RELEVANCE_PARAM_ACC, getDBConnection()->getCurrentConnection() ));
										
			return accessor;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getIbtRelevantParameterAccessor()
		{
			METHODNAME_DEF( ApplCompMgr, getIbtRelevantParameterAccessor )
			BLOG_TRACE_METHOD( m_Logger, fun );

			infrastructure::accessor::ibtexcludeparameter::SelectIbtExcludeParamByBranch(); // pseudo reference
			libutil::infrastructure::accessor::IAccessorPtr accessor = libutil::infrastructure::accessor::AccessorProxyPtr(
				new libutil::infrastructure::accessor::AccessorProxy( infrastructure::accessor::ibtexcludeparameter::lit::IBT_EXCLUSION_CRITERIA_ACC, getDBConnection()->getCurrentConnection() ));
										
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
} // end namnespace ibtrelevantcalculator
