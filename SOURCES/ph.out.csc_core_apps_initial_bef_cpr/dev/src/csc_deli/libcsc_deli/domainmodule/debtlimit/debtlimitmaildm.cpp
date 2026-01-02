#include "debtlimitmaildm.h"

#include "infrastructure/parameter/areamapper.h"
#include "infrastructure/parameter/parameterkeys.h"
#include "loggerpool/libcsc_deli_loggerpool.h"

#include <pxsessioninitialization.h>
#include <sessionfactory.h>
#include <cremamailhandler.h>
#include <exceptions/cscexceptionbase.h>

#include <libutil/dbconnection.h> // DBSRV_PARAMETERNAME...
#include <boost/make_shared.hpp>

namespace libcsc_deli
{
namespace domMod
{
namespace debtLimit
{

    const libutil::misc::ClassInfo& DebtLimitMailDM::getClassInfo()
    {
        static const libutil::misc::ClassInfo info( "DebtLimitMailDM", libutil::misc::Version( 1, 0, 0, 0 ) );
        return info;
    }

    DebtLimitMailDM::DebtLimitMailDM() 
        : m_Logger( libcsc_deli::LoggerPool::getLoggerDomModules() )
    {
        METHODNAME_DEF( DebtLimitMailDM, DebtLimitMailDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    DebtLimitMailDM::~DebtLimitMailDM()
    {
        METHODNAME_DEF( DebtLimitMailDM, ~DebtLimitMailDM )
        BLOG_TRACE_METHOD( getLogger(), fun );
    }

    const log4cplus::Logger& DebtLimitMailDM::getLogger() const
    {
        return m_Logger;
    }

    void DebtLimitMailDM::injectParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr parameterGateway )
    {
        m_ParameterGateway = parameterGateway;
    }

    libutil::infrastructure::parameter::IParameterGatewayPtr DebtLimitMailDM::getParameterGateway()
    {
        CHECK_INSTANCE_EXCEPTION( m_ParameterGateway.get() );
        return m_ParameterGateway;
    }

    void DebtLimitMailDM::injectConnection( basar::db::sql::ConnectionRef connection )
    {
        m_Connection = connection;
    }

    basar::db::sql::ConnectionRef DebtLimitMailDM::getConnection()
    {
        return m_Connection;
    }

    void DebtLimitMailDM::setSession( libutil::infrastructure::session::ISessionPtr session )
    {
        m_Session = session;
    }

    libutil::infrastructure::session::ISessionPtr DebtLimitMailDM::getSession()
    {
        CHECK_INSTANCE_EXCEPTION( m_Session.get() );
        return m_Session;
    }

    PxSessionPtr DebtLimitMailDM::getPxSession()
    {
        if( m_PxSession.get() == 0 )
        {
            basar::I18nString dbServerName, dbName, msgFile;
            getParameterGateway()->getParameterValue( getSession()->getUser()->getAreaID(), libutil::infrastructure::db::dbConnection::DBSRV_PARAMETERNAME, 
                                                      dbServerName );
            getParameterGateway()->getParameterValue( getSession()->getUser()->getAreaID(), libutil::infrastructure::db::dbConnection::DB_PARAMETERNAME,
                                                      dbName );
            getParameterGateway()->getParameterValue( getSession()->getUser()->getAreaID(), infrastructure::parameter::MSG_FILE, msgFile );

            pxSessionInitialization pxSessInit;
            pxSessInit.setDBInformation( dbServerName, dbName );
            pxSessInit.setDevice( pxDVC_DCT_SERIAL, infrastructure::parameter::DEVICENAME );
            pxSessInit.setMessageFileName( msgFile );

            m_PxSession = SessionFactory( getConnection() ).create( pxSessInit );
        }

        return m_PxSession;
    }

    PxCremaMailHandlerPtr DebtLimitMailDM::getPxCremaMailHandler()
    {
        // important: store session as long as cremamailhandler is in use
        if( m_PxCremaMailHandler.get() == 0 )
        {
            m_PxCremaMailHandler =  boost::make_shared< CremaMailHandler >( getPxSession().get() );
        }

        return m_PxCremaMailHandler;
    }

    void DebtLimitMailDM::processCremaMails( basar::Int32 partnerNo )
    {
        METHODNAME_DEF( DebtLimitMailDM, processCremaMails )
        BLOG_TRACE_METHOD( getLogger(), fun );

        try
        {
            getPxCremaMailHandler()->processWarningMailRequest( partnerNo );
        }
        catch( libcsc::exceptions::CSCExceptionBase& e )
        {
            BLOG_WARN( getLogger(), "Exception occurred while trying to send mails!" );
            BLOG_WARN( getLogger(), e.reason() );
        }
    }

} // end namespace debtLimit
} // end namespace domMod
} // end namespace libcsc_deli
