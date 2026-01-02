#ifndef GUARD_CSC_DELI_INFRASTRUCTURE_PARAMETER_DBPARAMETERGATEWAYPTR_H
#define GUARD_CSC_DELI_INFRASTRUCTURE_PARAMETER_DBPARAMETERGATEWAYPTR_H

#include <boost/shared_ptr.hpp>

namespace csc_deli
{
    namespace infrastructure
    {
        namespace parameter
        {
            class DBParameterGateway;
            typedef boost::shared_ptr< DBParameterGateway > DBParameterGatewayPtr;
        }
    }
}

#endif // GUARD_CSC_DELI_INFRASTRUCTURE_PARAMETER_DBPARAMETERGATEWAYPTR_H
