#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_CONNECTIONPOOLPTR_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_CONNECTIONPOOLPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace infrastructure
    {
        namespace connectionPool
        {
            class ConnectionPool;
            typedef boost::shared_ptr< ConnectionPool > ConnectionPoolPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_CONNECTIONPOOLPTR_H
