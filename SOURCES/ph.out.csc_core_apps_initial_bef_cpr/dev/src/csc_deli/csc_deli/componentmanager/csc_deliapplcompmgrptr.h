#ifndef GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIAPPLCOMPMGRPTR_H
#define GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIAPPLCOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace csc_deli
{
    namespace componentManager
    {
        class ApplCompMgr;
        typedef boost::shared_ptr< ApplCompMgr > ApplCompMgrPtr;
    }
}

#endif //GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIAPPLCOMPMGRPTR_H
