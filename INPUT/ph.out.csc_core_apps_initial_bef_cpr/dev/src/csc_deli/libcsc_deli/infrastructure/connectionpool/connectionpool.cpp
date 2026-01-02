#include "connectionpool.h"

#include "idbconnectionfactory.h"

#include <exception/dbconnectionexception.h>
#include <exception/duplicatenameexception.h>
#include <exception/namenotfoundexception.h>

#include <libbasarcmnutil_exceptions.h>

#include <libutil/util.h>
#include <libutil/log4cplus.h>

namespace libcsc_deli
{
namespace infrastructure
{
namespace connectionPool
{
    ConnectionPool::ConnectionPool() : m_Logger( libutil::LoggerPool::getLoggerLibUtilDBConnection() )
    {
    }

    ConnectionPool::~ConnectionPool()
    {
        terminateAll();
    }

    void ConnectionPool::injectDBConnectionFactory( IDBConnectionFactoryConstPtr dbConnectionFactory )
    {
        m_DBConnectionFactory = dbConnectionFactory;
    }

    IDBConnectionFactoryConstPtr ConnectionPool::getDBConnectionFactory() const
    {
        CHECK_INSTANCE_EXCEPTION( m_DBConnectionFactory.get() );
        return m_DBConnectionFactory;
    }

    void ConnectionPool::createConnection( const basar::VarString& name, basar::Int16 areaId )
    {
        METHODNAME_DEF( ConnectionPool, createConnection );
        BLOG_TRACE_METHOD( m_Logger, fun );

        if( m_DBConnectionCollection.find( name ) != m_DBConnectionCollection.end() )
        {
            basar::VarString reason = "Connection name '" + name + "' already exists!";
            throw libcsc_deli::exceptions::DuplicateNameException( basar::ExceptInfo( fun, reason, __FILE__, __LINE__ ) );
        }

        libutil::infrastructure::db::dbConnection::IDBConnectionPtr dbConnection = getDBConnectionFactory()->getDBConnection( areaId );
        m_DBConnectionCollection[ name ] = dbConnection;
        m_ConnectionNameCollection.push_back( name );
    }

    void ConnectionPool::connect()
    {
        METHODNAME_DEF( ConnectionPool, connect );
        BLOG_TRACE_METHOD( m_Logger, fun );

        if( m_DBConnectionCollection.empty() )
        {
            basar::VarString reason = "No connections defined!";
            throw libcsc_deli::exceptions::DBConnectionException( basar::ExceptInfo( fun, reason, __FILE__, __LINE__ ) );
        }

        for( DBConnectionCollection::iterator it = m_DBConnectionCollection.begin(); it != m_DBConnectionCollection.end(); ++it )
        {
            it->second->connect();
        }
    }

    void ConnectionPool::disconnect()
    {
        METHODNAME_DEF( ConnectionPool, disconnect );
        BLOG_TRACE_METHOD( m_Logger, fun );

        for( DBConnectionCollection::iterator it = m_DBConnectionCollection.begin(); it != m_DBConnectionCollection.end(); ++it )
        {
            it->second->disconnect();
        }
    }

    void ConnectionPool::terminateConnection( const basar::VarString& name )
    {
        getConnection( name )->disconnect();
        m_DBConnectionCollection.erase( name );
    }

    void ConnectionPool::terminateAll()
    {
        for( DBConnectionCollection::iterator it = m_DBConnectionCollection.begin(); it != m_DBConnectionCollection.end(); )
        {
            it->second->disconnect();
            m_DBConnectionCollection.erase( it++ ); // old c++ 98 syntax: increment and return previous iterator
        }
    }

    libutil::infrastructure::db::dbConnection::IDBConnectionPtr ConnectionPool::getConnection( const basar::VarString& name )
    {
        METHODNAME_DEF( ConnectionPool, getConnection );

        DBConnectionCollection::const_iterator it = m_DBConnectionCollection.find( name );
        if( it == m_DBConnectionCollection.end() )
        {
            basar::VarString reason = "Connection with name '" + name + "' not found!";
            throw libcsc_deli::exceptions::NameNotFoundException( basar::ExceptInfo( fun, reason, __FILE__, __LINE__ ) );
        }

        return it->second;
    }

    const ConnectionPool::ConnectionNameCollection& ConnectionPool::getConnectionNames() const
    {
        return m_ConnectionNameCollection;
    }

} // end namespace connectionPool
} // end namespace infrastructure
} // end namespace libcsc_deli
