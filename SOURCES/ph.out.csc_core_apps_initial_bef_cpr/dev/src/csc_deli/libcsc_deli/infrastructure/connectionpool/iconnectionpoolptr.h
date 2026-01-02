#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOLPTR_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOLPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace infrastructure
    {
        namespace connectionPool
        {
            class IConnectionPool;
            typedef boost::shared_ptr< IConnectionPool > IConnectionPoolPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOLPTR_H
