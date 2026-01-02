#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_LIBCSC_DELIAPPLCOMPMGRPTR_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_LIBCSC_DELIAPPLCOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace componentManager
    {
        class ApplCompMgr;
        typedef boost::shared_ptr< ApplCompMgr > ApplCompMgrPtr;
    }
}

#endif //GUARD_LIBCSC_DELI_COMPONENTMANAGER_LIBCSC_DELIAPPLCOMPMGRPTR_H
