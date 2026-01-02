#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_IDBCONNECTIONFACTORYCONSTPTR_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_IDBCONNECTIONFACTORYCONSTPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace infrastructure
    {
        namespace connectionPool
        {
            class IDBConnectionFactory;
            typedef boost::shared_ptr< IDBConnectionFactory const > IDBConnectionFactoryConstPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_IDBCONNECTIONFACTORYCONSTPTR_H
