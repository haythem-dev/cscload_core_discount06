//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       09.07.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTORDERIMPORT_COMPONENTMANAGER_IBTORDERIMPORTAPPLCOMPMGRPTR_H
#define GUARD_IBTORDERIMPORT_COMPONENTMANAGER_IBTORDERIMPORTAPPLCOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtorderimport
{
    namespace componentManager
    {
        class ApplCompMgr;
        typedef boost::shared_ptr< ApplCompMgr > ApplCompMgrPtr;
    }
}

#endif //GUARD_IBTORDERIMPORT_COMPONENTMANAGER_IBTORDERIMPORTAPPLCOMPMGRPTR_H
