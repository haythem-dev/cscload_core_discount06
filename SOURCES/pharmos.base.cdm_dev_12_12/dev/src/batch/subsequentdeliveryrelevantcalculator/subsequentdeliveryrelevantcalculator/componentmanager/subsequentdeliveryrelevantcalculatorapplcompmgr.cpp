//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   14.10.2022
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
// global
#include "subsequentdeliveryrelevantcalculatorapplcompmgr.h"
#include "loggerpool/subsequentdeliveryrelevantcalculator_loggerpool.h"

// uc
#include "usecase/mainucptr.h"
#include "usecase/mainuc.h"


//dommod
#include "domainmodule/article/articledm.h"
#include "domainmodule/subsequentdeliveryconfig/subsequentdeliveryconfigdm.h"

#include "infrastructure/accessor/article/articleacc.h"
#include "infrastructure/accessor/deliveryparam/deliveryparamacc.h"
#include "infrastructure/accessor/subsequentdeliveryconfig/subsequentdeliveryconfigacc.h"

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
// class definition section
//----------------------------------------------------------------------------//
namespace subsequentdeliveryrelevantcalculator
{
    namespace componentManager
    {
        ApplCompMgr::ApplCompMgr()
			: m_Logger( subsequentdeliveryrelevantcalculator::LoggerPool::getLoggerSubsequentdeliveryrelevantcalculator() )
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

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // <UC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        libutil::useCase::IRunnablePtr ApplCompMgr::getMainUC()
        {
            METHODNAME_DEF( ApplCompMgr, getMainUC )
            BLOG_TRACE_METHOD( m_Logger, fun );

			subsequentdeliveryrelevantcalculator::useCase::MainUCPtr mainUC = subsequentdeliveryrelevantcalculator::useCase::MainUCPtr( new subsequentdeliveryrelevantcalculator::useCase::MainUC );
            mainUC->injectUseCaseGetter      ( shared_from_this() );

			mainUC->injectArticleDM(getArticleDM());
			mainUC->injectDeliveryParamDM(getDeliveryParamDM());
			mainUC->injectSubsequentDeliveryConfigDM(getSubsequentDeliveryConfigDM());

			// tell use case which branchno was specified on the command line
			mainUC->setBranchNo(m_AppArgs.m_BranchNo);
			mainUC->setCalcDate(m_AppArgs.m_CalcDate);
			mainUC->setCalcTime(m_AppArgs.m_CalcTime);

#ifdef ABORTTEST
			mainUC->setAbortType(m_AppArgs.m_AbortType);
			mainUC->setAbortArticleNo(m_AppArgs.m_AbortArticleNo);
#endif

			return mainUC;
        }
  
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </UC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		domMod::article::ArticleDMPtr ApplCompMgr::getArticleDM()
		{
			METHODNAME_DEF(ApplCompMgr, getArticleDM)
			BLOG_TRACE_METHOD(m_Logger, fun);

			domMod::article::ArticleDMPtr articleDM =
				domMod::article::ArticleDMPtr(new domMod::article::ArticleDM(LoggerPool::getLoggerDomModules()));

			articleDM->injectDbConnection(getDBConnection());
			articleDM->injectAccessor(getArticleAccessor());

			return articleDM;
		}

		domMod::deliveryparam::DeliveryParamDMPtr ApplCompMgr::getDeliveryParamDM()
		{
			METHODNAME_DEF(ApplCompMgr, getDeliveryParamDM)
				BLOG_TRACE_METHOD(m_Logger, fun);

			domMod::deliveryparam::DeliveryParamDMPtr deliveryParamDM =
				domMod::deliveryparam::DeliveryParamDMPtr(new domMod::deliveryparam::DeliveryParamDM(LoggerPool::getLoggerDomModules()));

			deliveryParamDM->injectDbConnection(getDBConnection());
			deliveryParamDM->injectAccessor(getDeliveryParamAccessor());

			return deliveryParamDM;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		domMod::subsequentdeliveryconfig::SubsequentDeliveryConfigDMPtr ApplCompMgr::getSubsequentDeliveryConfigDM()
		{
			METHODNAME_DEF(ApplCompMgr, getSubsequentDeliveryConfigDM)
			BLOG_TRACE_METHOD(m_Logger, fun);

			domMod::subsequentdeliveryconfig::SubsequentDeliveryConfigDMPtr subsequentDeliveryConfigDM =
				domMod::subsequentdeliveryconfig::SubsequentDeliveryConfigDMPtr(new domMod::subsequentdeliveryconfig::SubsequentDeliveryConfigDM(LoggerPool::getLoggerDomModules()));

			subsequentDeliveryConfigDM->injectDbConnection(getDBConnection());
			subsequentDeliveryConfigDM->injectAccessor(getSubsequentDeliveryConfigAccessor());

			return subsequentDeliveryConfigDM;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getArticleAccessor()
		{
			METHODNAME_DEF(ApplCompMgr, getArticleAccessor)
			BLOG_TRACE_METHOD(m_Logger, fun);

			libutil::infrastructure::accessor::IAccessorPtr articleAcc = libutil::infrastructure::accessor::AccessorProxyPtr(
				new libutil::infrastructure::accessor::AccessorProxy(infrastructure::accessor::article::lit::ArticleAcc, getDBConnection()->getCurrentConnection()));

			return articleAcc;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getDeliveryParamAccessor()
		{
			METHODNAME_DEF(ApplCompMgr, getDeliveryParamAccessor)
				BLOG_TRACE_METHOD(m_Logger, fun);

			libutil::infrastructure::accessor::IAccessorPtr deliveryParamAcc = libutil::infrastructure::accessor::AccessorProxyPtr(
				new libutil::infrastructure::accessor::AccessorProxy(infrastructure::accessor::deliveryparam::lit::DeliveryParamAcc, getDBConnection()->getCurrentConnection()));

			return deliveryParamAcc;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getSubsequentDeliveryConfigAccessor()
		{
			METHODNAME_DEF(ApplCompMgr, getSubsequentDeliveryConfigAccessor)
			BLOG_TRACE_METHOD(m_Logger, fun);

			libutil::infrastructure::accessor::IAccessorPtr articleAcc = libutil::infrastructure::accessor::AccessorProxyPtr(
				new libutil::infrastructure::accessor::AccessorProxy(infrastructure::accessor::subsequentdeliveryconfig::lit::SubsequentDeliveryConfigAcc, getDBConnection()->getCurrentConnection()));

			return articleAcc;
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
    } // end namnespace componentManager
} // end namnespace subsequentdeliveryrelevantcalculator
