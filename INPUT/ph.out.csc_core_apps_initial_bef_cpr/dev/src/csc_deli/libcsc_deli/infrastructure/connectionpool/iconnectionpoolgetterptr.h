#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOLGETTERPTR_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOLGETTERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace infrastructure
    {
        namespace connectionPool
        {
            class IConnectionPoolGetter;
            typedef boost::shared_ptr< IConnectionPoolGetter > IConnectionPoolGetterPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOLGETTERPTR_H
