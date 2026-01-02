#include "persistence/accessor.h"
#include <persistence/isqlparameterbinder.h>
#include <logger/loggerpool.h>
#include <exceptions/cscexceptionbase.h>
#include <exceptions/persistenceexception.h>
#include <sstream>

namespace libcsc
{
namespace persistence
{
Accessor::Accessor( basar::db::sql::ConnectionRef connection )
: m_Connection( connection )
{
}

Accessor::~Accessor()
{
    if( !m_SelectStatement.isNull() )
    {
        m_SelectStatement.reset();
    }

    if( !m_PrepSelStatement.isNull() )
    {
        if( m_PrepSelStatement.isOpen() )
        {
            m_PrepSelStatement.close();
        }

        m_PrepSelStatement.reset();
    }

    if( !m_PrepExecuteStatement.isNull() )
    {
        if( m_PrepExecuteStatement.isOpen() )
        {
            m_PrepExecuteStatement.close();
        }

        m_PrepExecuteStatement.reset();
    }
}

const basar::db::sql::ResultsetRef Accessor::selectDirty(const basar::VarString& sql)
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "Accessor::selectDirty()" );

    basar::db::sql::ResultsetRef ret;
    try
    {
        m_SelectStatement = m_Connection.createStatement();
        m_SelectStatement.execute("SET ISOLATION TO DIRTY READ;");
        ret = m_SelectStatement.executeQuery(sql);
    }
    catch( const basar::Exception & e )
    {
        std::stringstream ss;
        ss << "Accessor::selectDirty(), Error: " << e.what().c_str();
        BLOG_ERROR( LoggerPool::getLoggerInfrastructure(), ss.str().c_str() );

        throw exceptions::PersistenceException( basar::ExceptInfo( "Accessor::selectDirty()", "select failed!", __FILE__, __LINE__ ) );
    }

    return ret;
}

const basar::db::sql::ResultsetRef Accessor::select(const basar::VarString& sql)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "Accessor::select()");

    basar::db::sql::ResultsetRef ret;
    try
    {
        m_SelectStatement = m_Connection.createStatement();
        ret = m_SelectStatement.executeQuery(sql);
    }
    catch (const basar::Exception& e)
    {
        std::stringstream ss;
        ss << "Accessor::select(), Error: " << e.what().c_str();
        BLOG_ERROR(LoggerPool::getLoggerInfrastructure(), ss.str().c_str());

        throw exceptions::PersistenceException(basar::ExceptInfo("Accessor::select()", "select failed!", __FILE__, __LINE__));
    }

    return ret;
}

const basar::db::sql::ResultsetRef Accessor::select( const basar::VarString & sql, const ISqlParameterBinderPtr parameterBinder )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "Accessor::select()" );

    basar::db::sql::ResultsetRef ret;
    try
    {
        if(m_PrepSelStatement.isNull() || !m_PrepSelStatement.isOpen())
        {
            m_PrepSelStatement = m_Connection.createPreparedStatement(sql);
        }

        parameterBinder->bind( m_PrepSelStatement );

        ret = m_PrepSelStatement.executeQuery();
    }
    catch( const basar::Exception & e )
    {
        std::stringstream ss;
        ss << "Accessor::select(), Error: " << e.what().c_str();
        BLOG_ERROR( LoggerPool::getLoggerInfrastructure(), ss.str().c_str() );

        throw exceptions::PersistenceException( basar::ExceptInfo( "Accessor::select()", "select failed!", __FILE__, __LINE__ ) );
    }

    return ret;
}

const basar::db::sql::ExecuteReturnInfo Accessor::execute( const basar::VarString & sql, const bool flagExcept )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "Accessor::execute()" );

    basar::db::sql::ExecuteReturnInfo ret;
    try
    {
        using namespace basar::db::sql;
        StatementRef statement = m_Connection.createStatement();
        ret = statement.execute( sql, flagExcept );
        m_LastInsertedSerial = ret.m_lastSerial.empty() ? 0 : ret.m_lastSerial.back();
    }
    catch( const basar::Exception & e )
    {
        std::stringstream ss;
        ss << "Accessor::execute(), Error: " << e.what().c_str();
        BLOG_ERROR( LoggerPool::getLoggerInfrastructure(), ss.str().c_str() );

        throw exceptions::PersistenceException( basar::ExceptInfo( "Accessor::execute()", "execute failed!", __FILE__, __LINE__ ) );
    }
    return ret;
}

const basar::db::sql::ExecuteReturnInfo Accessor::execute( const basar::VarString & sql, const ISqlParameterBinderPtr parameterBinder, const bool flagExcept )
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "Accessor::execute()" );

    basar::db::sql::ExecuteReturnInfo ret;
    try
    {
        if(    m_PrepExecuteStatement.isNull()
            || !m_PrepExecuteStatement.isOpen() )
        {
            m_PrepExecuteStatement = m_Connection.createPreparedStatement( sql );
        }

        parameterBinder->bind( m_PrepExecuteStatement );
        ret = m_PrepExecuteStatement.execute( flagExcept );
        if( ret.m_lastSerial.empty() )
        {
            m_LastInsertedSerial = 0;
        }
        else
        {
            m_LastInsertedSerial = ret.m_lastSerial.back();
        }
    }
    catch( const basar::Exception & e )
    {
        std::stringstream ss;
        ss << "Accessor::execute(), Error: " << e.what().c_str();
        BLOG_ERROR( LoggerPool::getLoggerInfrastructure(), ss.str().c_str() );

        throw exceptions::PersistenceException( basar::ExceptInfo( "Accessor::execute()", "prepared execute failed!", __FILE__, __LINE__ ) );
    }
    return ret;
}

basar::Int64 Accessor::getLastInsertedSerial() const
{
    return m_LastInsertedSerial;
}

} // end namespace persistence
} // end namespace libcsc

