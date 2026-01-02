#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_CONNECTIONPOOL_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_CONNECTIONPOOL_H

#include "iconnectionpool.h"
#include "idbconnectionfactoryconstptr.h"

#include <libbasar_definitions.h>
#include <map>

namespace log4cplus
{
    class Logger;
}

namespace libcsc_deli
{
namespace infrastructure
{
namespace connectionPool
{

    class ConnectionPool : public IConnectionPool
    {
    public:
        ConnectionPool();
        ~ConnectionPool();

        void                                                        injectDBConnectionFactory( IDBConnectionFactoryConstPtr );

        // from IConnectionPool interface
        void                                                        createConnection( const basar::VarString& name, basar::Int16 areaId );

        void                                                        connect();
        void                                                        disconnect();
        
        void                                                        terminateConnection( const basar::VarString& name );
        void                                                        terminateAll();

        // from IConnectionPoolGetter interface
        libutil::infrastructure::db::dbConnection::IDBConnectionPtr getConnection( const basar::VarString& name );
        const ConnectionNameCollection&                             getConnectionNames() const;

    private:
        // forbidden
        ConnectionPool( const ConnectionPool& );
        ConnectionPool& operator = ( const ConnectionPool& );

        IDBConnectionFactoryConstPtr                                getDBConnectionFactory() const;

    private:
        const log4cplus::Logger&                                    m_Logger;

        typedef std::map< basar::VarString, libutil::infrastructure::db::dbConnection::IDBConnectionPtr > DBConnectionCollection;
        DBConnectionCollection                                      m_DBConnectionCollection;
        ConnectionNameCollection                                    m_ConnectionNameCollection;

        IDBConnectionFactoryConstPtr                                m_DBConnectionFactory;
    };

} // end namespace connectionPool
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_CONNECTIONPOOL_H
