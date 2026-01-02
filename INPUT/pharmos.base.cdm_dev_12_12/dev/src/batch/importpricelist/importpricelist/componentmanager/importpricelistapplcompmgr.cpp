//----------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author Michael Helmich
 *  \date   25.08.2021
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
// global
#include "importpricelistapplcompmgr.h"
#include "loggerpool/importpricelist_loggerpool.h"

// uc
#include "usecase/mainucptr.h"
#include "usecase/mainuc.h"


//dommod
#include "domainmodule/articlecodes/articlecodesdm.h"
#include "domainmodule/pricedata/pricedatadm.h"
#include "domainmodule/pricelist2pharmacygroup/pricelist2pharmacygroupdm.h"
#include "domainmodule/pricelistproc/pricelistprocdm.h"

#include "infrastructure/accessor/articlecodes/articlecodesacc.h"
#include "infrastructure/accessor/pricedata/pricedataacc.h"
#include "infrastructure/accessor/pricelist2pharmacygroup/pricelist2pharmacygroupacc.h"
#include "infrastructure/accessor/pricelistproc/pricelistprocacc.h"

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
namespace importpricelist
{
    namespace componentManager
    {
        ApplCompMgr::ApplCompMgr()
			: m_Logger( importpricelist::LoggerPool::getLoggerImportpricelist() )
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

            importpricelist::useCase::MainUCPtr mainUC = importpricelist::useCase::MainUCPtr( new importpricelist::useCase::MainUC );
            mainUC->injectUseCaseGetter      ( shared_from_this() );

			mainUC->injectPriceDataDM(getPriceDataDM());
			mainUC->injectPriceList2PharmacyGroupDM(getPriceList2PharmacyGroupDM());
			mainUC->injectPriceListProcDM(getPriceListProcDM());
			mainUC->injectArticleCodesDM(getArticleCodesDM());

			mainUC->setInputFileName(m_AppArgs.m_InputFile);
			mainUC->setProcDate(m_AppArgs.m_ProcDate);
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
		domMod::pricedata::PriceDataDMPtr ApplCompMgr::getPriceDataDM()
		{
			METHODNAME_DEF(ApplCompMgr, getPriceDataDM)
		    BLOG_TRACE_METHOD(m_Logger, fun);

			domMod::pricedata::PriceDataDMPtr priceDataDM =
				domMod::pricedata::PriceDataDMPtr(new domMod::pricedata::PriceDataDM(LoggerPool::getLoggerDomModules()));
			
			priceDataDM->injectDbConnection(getDBConnection());
			priceDataDM->injectAccessor(getPriceDataAccessor());

			return priceDataDM;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		domMod::pricelist2pharmacygroup::PriceList2PharmacyGroupDMPtr ApplCompMgr::getPriceList2PharmacyGroupDM()
		{
			METHODNAME_DEF(ApplCompMgr, getPriceList2PharmacyGroupDM)
			BLOG_TRACE_METHOD(m_Logger, fun);

			domMod::pricelist2pharmacygroup::PriceList2PharmacyGroupDMPtr priceList2PharmacyGroupDM =
				domMod::pricelist2pharmacygroup::PriceList2PharmacyGroupDMPtr(new domMod::pricelist2pharmacygroup::PriceList2PharmacyGroupDM(LoggerPool::getLoggerDomModules()));

			priceList2PharmacyGroupDM->injectDbConnection(getDBConnection());
			priceList2PharmacyGroupDM->injectAccessor(getPriceList2PharmacyGroupAccessor());

			return priceList2PharmacyGroupDM;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		domMod::pricelistproc::PriceListProcDMPtr ApplCompMgr::getPriceListProcDM()
		{
			METHODNAME_DEF(ApplCompMgr, getPriceListProcDM)
			BLOG_TRACE_METHOD(m_Logger, fun);

			domMod::pricelistproc::PriceListProcDMPtr priceListProcDM =
				domMod::pricelistproc::PriceListProcDMPtr(new domMod::pricelistproc::PriceListProcDM(LoggerPool::getLoggerDomModules()));

			priceListProcDM->injectDbConnection(getDBConnection());
			priceListProcDM->injectAccessor(getPriceListProcAccessor());

			return priceListProcDM;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		domMod::articlecodes::ArticleCodesDMPtr ApplCompMgr::getArticleCodesDM()
		{
			METHODNAME_DEF(ApplCompMgr, getArticleCodesDM)
			BLOG_TRACE_METHOD(m_Logger, fun);

			domMod::articlecodes::ArticleCodesDMPtr articleCodesDM =
				domMod::articlecodes::ArticleCodesDMPtr(new domMod::articlecodes::ArticleCodesDM(LoggerPool::getLoggerDomModules()));

			articleCodesDM->injectDbConnection(getDBConnection());
			articleCodesDM->injectAccessor(getArticleCodesAccessor());

			return articleCodesDM;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getPriceDataAccessor()
		{
			METHODNAME_DEF( ApplCompMgr, getPriceDataAccessor )
			BLOG_TRACE_METHOD( m_Logger, fun );

			libutil::infrastructure::accessor::IAccessorPtr priceDataAcc = libutil::infrastructure::accessor::AccessorProxyPtr(
				new libutil::infrastructure::accessor::AccessorProxy( infrastructure::accessor::pricedata::lit::PriceDataAcc, getDBConnection()->getCurrentConnection() ));
										
			return priceDataAcc;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getPriceList2PharmacyGroupAccessor()
		{
			METHODNAME_DEF(ApplCompMgr, getPriceList2PharmacyGroupAccessor)
			BLOG_TRACE_METHOD(m_Logger, fun);

			libutil::infrastructure::accessor::IAccessorPtr priceList2PharmacyGroupAcc = libutil::infrastructure::accessor::AccessorProxyPtr(
				new libutil::infrastructure::accessor::AccessorProxy(infrastructure::accessor::pricelist2pharmacygroup::lit::PriceList2PharmacyGroupAcc, getDBConnection()->getCurrentConnection()));

			return priceList2PharmacyGroupAcc;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getPriceListProcAccessor()
		{
			METHODNAME_DEF(ApplCompMgr, getPriceListProcAccessor)
			BLOG_TRACE_METHOD(m_Logger, fun);

			libutil::infrastructure::accessor::IAccessorPtr priceListProcAcc = libutil::infrastructure::accessor::AccessorProxyPtr(
				new libutil::infrastructure::accessor::AccessorProxy(infrastructure::accessor::pricelistproc::lit::PriceListProcAcc, getDBConnection()->getCurrentConnection()));

			return priceListProcAcc;
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getArticleCodesAccessor()
		{
			METHODNAME_DEF(ApplCompMgr, getArticleCodesAccessor)
			BLOG_TRACE_METHOD(m_Logger, fun);

			libutil::infrastructure::accessor::IAccessorPtr articleCodesAcc = libutil::infrastructure::accessor::AccessorProxyPtr(
				new libutil::infrastructure::accessor::AccessorProxy(infrastructure::accessor::articlecodes::lit::ArticleCodesAcc, getDBConnection()->getCurrentConnection()));

			return articleCodesAcc;
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
} // end namnespace importpricelist
