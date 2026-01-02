//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       28.07.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHADEX_COMPONENTMANAGER_CSC_PHADEXINFRASTRUCTURECOMPMGRPTR_H
#define GUARD_CSC_PHADEX_COMPONENTMANAGER_CSC_PHADEXINFRASTRUCTURECOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
    namespace componentManager
    {
        class InfrastructureCompMgr;
        typedef boost::shared_ptr< InfrastructureCompMgr > InfrastructureCompMgrPtr;
    }
}

#endif //GUARD_CSC_PHADEX_COMPONENTMANAGER_CSC_PHADEXINFRASTRUCTURECOMPMGRPTR_H
