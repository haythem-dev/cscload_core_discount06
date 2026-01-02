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
#include "longtermlackloaderapplcompmgr.h"
#include "loggerpool/longtermlackloader_loggerpool.h"
#include "longtermlackloaderversion/longtermlackloader_version.h"
// uc
#include "mainucptr.h"
#include "mainuc.h"

// libutil
#include <libutil/util.h>
#include <libutil/dbconnection.h>

// basar
#include <libbasarcmnutil_logging.h>
#include <libbasardbsql_databaseinfo.h>
#include <libbasarlogin.h>
#include <libbasardbsql.h>
#include <libbasarproperty.h>

#include "infrastructure/accessor/longtermlackpgk/longtermlackacc.h"
#include "infrastructure/accessor/longtermlackpgk/longtermlackacc_definitions.h"

//----------------------------------------------------------------------------//
// class definition setcion
//----------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace componentManager
    {
        ApplCompMgr::ApplCompMgr()
        : m_Logger( infrastructure::LoggerPool::getLoggerLongTermLackLoader() )
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

        void ApplCompMgr::injectDBConnection( libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr dbConnectionDataGetter )
        {
            METHODNAME_DEF(ApplCompMgr, ~ApplCompMgr)
            BLOG_TRACE_METHOD(getLogger(), fun);

            m_DBConnectionDataGetter = dbConnectionDataGetter;
        }

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // <UC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        libutil::useCase::IRunnablePtr ApplCompMgr::getMainUC()
        {
            METHODNAME_DEF( ApplCompMgr, getMainUC )
            BLOG_TRACE_METHOD( m_Logger, fun );

            //longtermlackloader::useCase::MainUCPtr mainUC = longtermlackloader::useCase::MainUCPtr( new longtermlackloader::useCase::MainUC );
            longtermlackloader::useCase::MainUCPtr mainUC( new longtermlackloader::useCase::MainUC );
            mainUC->injectLongTermLackAccesssor( getLongTermLackAccesssor() );
            mainUC->injectDBSelectionParameterGateway( getParameterGateway() );
            mainUC->injectSession( getSession() );

            return mainUC;
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </UC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // <ACC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        libutil::infrastructure::accessor::IAccessorPtr ApplCompMgr::getLongTermLackAccesssor()
        {
            METHODNAME_DEF(ApplCompMgr, getLongTermLackAccesssor)
            BLOG_TRACE_METHOD(getLogger(), fun);

            libutil::infrastructure::accessor::IAccessorPtr accessor = libutil::infrastructure::accessor::AccessorProxyPtr(
                new libutil::infrastructure::accessor::AccessorProxy(   infrastructure::accessor::longtermlack::lit::LONG_TERM_LACK_ACC, 
                                                                        getDBConnectionDataGetter()->getCurrentConnection() 
                )
            );
            return accessor;
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </ACC getting>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // <OTHERS>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        libutil::infrastructure::db::dbConnection::IDBConnectionDataGetterPtr ApplCompMgr::getDBConnectionDataGetter()
        {
            METHODNAME_DEF(ApplCompMgr, getDBConnectionDataGetter)
            BLOG_TRACE_METHOD(getLogger(), fun);

            return m_DBConnectionDataGetter;
        }

        const log4cplus::Logger& ApplCompMgr::getLogger() const
        {
            METHODNAME_DEF( ApplCompMgr, getSession )
            BLOG_TRACE_METHOD( m_Logger, fun );

            return m_Logger;
        }
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // </OTHERS>
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    } // end namnespace componentManager
} // end namnespace longtermlackloader
