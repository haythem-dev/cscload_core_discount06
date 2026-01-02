//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       28.07.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTORDERIMPORT_COMPONENTMANAGER_IBTORDERIMPORTINFRASTRUCTURECOMPMGRPTR_H
#define GUARD_IBTORDERIMPORT_COMPONENTMANAGER_IBTORDERIMPORTINFRASTRUCTURECOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtorderimport
{
    namespace componentManager
    {
        class InfrastructureCompMgr;
        typedef boost::shared_ptr< InfrastructureCompMgr > InfrastructureCompMgrPtr;
    }
}

#endif //GUARD_IBTORDERIMPORT_COMPONENTMANAGER_IBTORDERIMPORTINFRASTRUCTURECOMPMGRPTR_H
