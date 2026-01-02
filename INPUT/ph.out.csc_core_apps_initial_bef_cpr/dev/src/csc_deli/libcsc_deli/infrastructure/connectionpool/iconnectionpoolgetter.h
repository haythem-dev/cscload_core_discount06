#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOLGETTER_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOLGETTER_H

#include <libutil/dbconnection.h>
#include <libbasar_definitions.h>
#include <vector>

namespace libcsc_deli
{
namespace infrastructure
{
namespace connectionPool
{

    class IConnectionPoolGetter
    {
    public:
        virtual ~IConnectionPoolGetter() {}

        virtual libutil::infrastructure::db::dbConnection::IDBConnectionPtr getConnection( const basar::VarString& name ) = 0;

        typedef std::vector< basar::VarString > ConnectionNameCollection;
        virtual const ConnectionNameCollection&                             getConnectionNames() const                    = 0;
    };

} // end namespace connectionPool
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOLGETTER_H
