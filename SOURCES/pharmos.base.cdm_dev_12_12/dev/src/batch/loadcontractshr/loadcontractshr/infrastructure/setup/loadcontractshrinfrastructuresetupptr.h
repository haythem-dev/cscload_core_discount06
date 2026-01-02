//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       27.01.2009
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

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

#endif 
