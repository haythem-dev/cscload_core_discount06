#ifndef GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOL_H
#define GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOL_H

#include "iconnectionpoolgetter.h"

namespace libcsc_deli
{
namespace infrastructure
{
namespace connectionPool
{

    class IConnectionPool : public IConnectionPoolGetter
    {
    public:
        virtual ~IConnectionPool() {}

        virtual void                                                        createConnection   ( const basar::VarString& name, basar::Int16 areaId ) = 0;

        virtual void                                                        connect()                                                                = 0;
        virtual void                                                        disconnect()                                                             = 0;
        
        virtual void                                                        terminateConnection( const basar::VarString& name )                      = 0;
        virtual void                                                        terminateAll()                                                           = 0;
    };

} // end namespace connectionPool
} // end namespace infrastructure
} // end namespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_INFRASTRUCTURE_CONNECTIONPOOL_ICONNECTIONPOOL_H
