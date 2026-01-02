//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     
 *  \date       
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LOADCONTRACTSHR_COMPONENTMANAGER_LOADCONTRACTSHRAPPLCOMPMGRPTR_H
#define GUARD_LOADCONTRACTSHR_COMPONENTMANAGER_LOADCONTRACTSHRAPPLCOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace loadcontractshr
{
    namespace componentManager
    {
        class ApplCompMgr;
        typedef boost::shared_ptr< ApplCompMgr > ApplCompMgrPtr;
    }
}

#endif //GUARD_LOADCONTRACTSHR_COMPONENTMANAGER_LOADCONTRACTSHRAPPLCOMPMGRPTR_H
