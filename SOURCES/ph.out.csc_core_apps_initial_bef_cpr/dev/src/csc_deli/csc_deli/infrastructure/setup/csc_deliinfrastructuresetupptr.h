#ifndef GUARD_LIBUTIL_INFRASTRUCTURE_INFRASTRUCTURE_SETUP_PTR_H
#define GUARD_LIBUTIL_INFRASTRUCTURE_INFRASTRUCTURE_SETUP_PTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace libutil
{
    namespace infrastructure
    {
        class InfrastructureSetup;
        typedef boost::shared_ptr< InfrastructureSetup > InfrastructureSetupPtr;
    }
}

#endif // GUARD_LIBUTIL_INFRASTRUCTURE_INFRASTRUCTURE_SETUP_PTR_H
