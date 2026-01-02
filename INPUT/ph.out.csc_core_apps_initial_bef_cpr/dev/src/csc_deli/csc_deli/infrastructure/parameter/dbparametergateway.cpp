#include "dbparametergateway.h"

#include <libutil/util.h>
#include <libutil/log4cplus.h>
#include <exceptions/invaliddataexception.h>

namespace csc_deli
{
namespace infrastructure
{
namespace parameter
{
    DBParameterGateway::DBParameterGateway( libutil::infrastructure::parameter::IParameterGatewayPtr paramGateway )
        : m_Logger( libutil::LoggerPool::getLoggerLibUtilDBConnection() ), m_ParameterGateway( paramGateway ), m_AreaId( -1 )
    {
        METHODNAME_DEF( DBParameterGateway, DBParameterGateway );
        BLOG_TRACE_METHOD( m_Logger, fun );
    }

    DBParameterGateway::~DBParameterGateway()
    {
        METHODNAME_DEF( DBParameterGateway, ~DBParameterGateway );
        BLOG_TRACE_METHOD( m_Logger, fun );
    }

    void DBParameterGateway::setAreaId( basar::Int16 areaId )
    {
        m_AreaId = areaId;
    }

    basar::Int16 DBParameterGateway::getAreaId() const
    {
        METHODNAME_DEF( DBParameterGateway, getAreaId );

        if( m_AreaId < 0 )
        {
            basar::VarString reason = "AreaId is invalid!";
            throw libutil::exceptions::InvalidDataException( basar::ExceptInfo( fun, reason, __FILE__, __LINE__ ) );
        }

        return m_AreaId;
    }

    bool DBParameterGateway::getParameterValue( const basar::I18nString& parameterName, basar::I18nString& value ) const
    {
        METHODNAME_DEF( DBParameterGateway, getParameterValue );
        BLOG_TRACE_METHOD( m_Logger, fun );

        return m_ParameterGateway->getParameterValue( parameterName, value );
    }

    bool DBParameterGateway::getParameterValue( const basar::I18nString&, const basar::I18nString& parameterName, basar::I18nString& value ) const
    {
        METHODNAME_DEF( DBParameterGateway, getParameterValue );
        BLOG_TRACE_METHOD( m_Logger, fun );

        basar::I18nString areaId; areaId.itos( getAreaId() ); // ignore first parameter and use areaId instead which was set before
        return m_ParameterGateway->getParameterValue( areaId, parameterName, value );
    }

    bool DBParameterGateway::getParameterValue( const basar::Int16, const basar::I18nString& parameterName, basar::I18nString& value ) const
    {
        METHODNAME_DEF( DBParameterGateway, getParameterValue );
        BLOG_TRACE_METHOD( m_Logger, fun );

        // ignore first parameter and use m_AreaId instead
        return m_ParameterGateway->getParameterValue( getAreaId(), parameterName, value );
    }
        
    bool DBParameterGateway::getParameterValue( const basar::I18nString&, const basar::I18nString& parameter2, 
                                                const basar::I18nString& parameterName,  basar::I18nString& value ) const
    {
        METHODNAME_DEF( DBParameterGateway, getParameterValue );
        BLOG_TRACE_METHOD( m_Logger, fun );

        basar::I18nString areaId; areaId.itos( getAreaId() ); // ignore first parameter and use areaId instead which was set before
        return m_ParameterGateway->getParameterValue( areaId, parameter2, parameterName, value );
    }

} // end namespace parameter
} // end namespace infrastructure
} // end namespace csc_deli
