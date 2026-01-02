#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_IDBCONNECTIONFACTORY_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_IDBCONNECTIONFACTORY_H

#include <libutil/dbconnection.h>

namespace libcsc_deli
{
namespace infrastructure
{
namespace connectionPool
{

    class IDBConnectionFactory
    {
    public:
        virtual ~IDBConnectionFactory() {}

        virtual libutil::infrastructure::db::dbConnection::IDBConnectionPtr getDBConnection( basar::Int16 areaId ) const = 0;
    };

} // end namespace connectionPool
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_IDBCONNECTIONFACTORY_H
