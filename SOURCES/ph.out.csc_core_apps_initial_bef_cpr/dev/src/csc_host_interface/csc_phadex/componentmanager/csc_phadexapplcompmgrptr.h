//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       09.07.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHADEX_COMPONENTMANAGER_CSC_PHADEXAPPLCOMPMGRPTR_H
#define GUARD_CSC_PHADEX_COMPONENTMANAGER_CSC_PHADEXAPPLCOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace csc_phadex
{
    namespace componentManager
    {
        class ApplCompMgr;
        typedef boost::shared_ptr< ApplCompMgr > ApplCompMgrPtr;
    }
}

#endif //GUARD_CSC_PHADEX_COMPONENTMANAGER_CSC_PHADEXAPPLCOMPMGRPTR_H
