//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
// global
#include "csc_deliapplcompmgr.h"
#include "loggerpool/libcsc_deli_loggerpool.h"
#include "csc_deliinfo/csc_deli_info.h"

// uc
#include "usecase/mainucptr.h"
#include "usecase/mainuc.h"
#include "usecase/debtlimitbatchucptr.h"
#include "usecase/debtlimitbatchuc.h"

// libcsc_deli
#include <componentmanager/libcsc_deliapplcompmgr.h>

// libutil
#include <libutil/util.h>
#include <libutil/dbconnection.h>

// basar
#include <libbasarcmnutil_logging.h>
#include <libbasardbsql_databaseinfo.h>
#include <libbasarlogin.h>
#include <libbasardbsql.h>
#include <libbasarproperty.h>

#include <boost/make_shared.hpp>

//----------------------------------------------------------------------------//
// class definition setcion
//----------------------------------------------------------------------------//
namespace csc_deli
{
namespace componentManager
{
    ApplCompMgr::ApplCompMgr()
    : m_Logger( libcsc_deli::LoggerPool::getLoggerCsc_deli() )
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

    /*
    void ApplCompMgr::injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr parameterGateway )
	{
		m_ParameterGateway = parameterGateway;
	}

    libutil::infrastructure::parameter::IParameterGatewayPtr ApplCompMgr::getParameterGateway()
    {
        CHECK_INSTANCE_EXCEPTION( m_ParameterGateway.get() );
        return m_ParameterGateway;
    }
    */

    void ApplCompMgr::injectDBConnectionPool( libcsc_deli::infrastructure::connectionPool::IConnectionPoolGetterPtr connectionPool )
    {
        m_ConnectionPool = connectionPool;
    }

    libcsc_deli::componentManager::ApplCompMgrPtr ApplCompMgr::getLIBCSC_DELIApplCompMgr()
    {
        METHODNAME_DEF( ApplCompMgr, getLIBCSC_DELIApplCompMgr )
        BLOG_TRACE_METHOD( m_Logger, fun );

        if( 0 == m_LIBCSC_DELIApplCompMgr.get() )
        {
            m_LIBCSC_DELIApplCompMgr = boost::make_shared< libcsc_deli::componentManager::ApplCompMgr >();
            m_LIBCSC_DELIApplCompMgr->injectDBConnectionPool( getDBConnectionPool() );
            m_LIBCSC_DELIApplCompMgr->injectParameterGateway( getParameterGateway() );
            m_LIBCSC_DELIApplCompMgr->setSession( getSession() );
        }

        return m_LIBCSC_DELIApplCompMgr;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // <UC getting>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    libutil::useCase::IRunnablePtr ApplCompMgr::getMainUC()
    {
        METHODNAME_DEF( ApplCompMgr, getMainUC )
        BLOG_TRACE_METHOD( m_Logger, fun );

        csc_deli::useCase::MainUCPtr mainUC = boost::make_shared< csc_deli::useCase::MainUC >();
        mainUC->injectUseCaseGetter( shared_from_this() );

        return mainUC;
    }
        
    libutil::useCase::IRunnablePtr ApplCompMgr::getDebtLimitBatchUC()
    {
        METHODNAME_DEF( ApplCompMgr, getDebtLimitBatchUC )
        BLOG_TRACE_METHOD( m_Logger, fun );
        
        csc_deli::useCase::DebtLimitBatchUCPtr uc = boost::make_shared< csc_deli::useCase::DebtLimitBatchUC >();
        uc->injectCustomerInvoicingCollection( getLIBCSC_DELIApplCompMgr()->getCustomerInvoicingCollection() );
        uc->injectDebtLimitImporter( getLIBCSC_DELIApplCompMgr()->getDebtLimitImporter() );
        uc->injectCustomerTurnoverExporter( getLIBCSC_DELIApplCompMgr()->getCustomerTurnoverExporter() );
        uc->injectCremaMailCleaner( getLIBCSC_DELIApplCompMgr()->getCremaMailCleaner() );

        return uc;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // </UC getting>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // <OTHERS>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    libcsc_deli::infrastructure::connectionPool::IConnectionPoolGetterPtr ApplCompMgr::getDBConnectionPool()
    {
        METHODNAME_DEF( ApplCompMgr, getDBConnectionPool )
        BLOG_TRACE_METHOD( m_Logger, fun );

        CHECK_INSTANCE_EXCEPTION( m_ConnectionPool.get() );
        return m_ConnectionPool;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // </OTHERS>
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

} // end namnespace componentManager
} // end namespace csc_deli
