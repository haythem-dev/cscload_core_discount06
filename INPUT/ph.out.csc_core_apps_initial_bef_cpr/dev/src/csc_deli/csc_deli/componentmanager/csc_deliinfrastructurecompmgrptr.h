#ifndef GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIINFRASTRUCTURECOMPMGRPTR_H
#define GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIINFRASTRUCTURECOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace csc_deli
{
    namespace componentManager
    {
        class InfrastructureCompMgr;
        typedef boost::shared_ptr< InfrastructureCompMgr > InfrastructureCompMgrPtr;
    }
}

#endif //GUARD_CSC_DELI_COMPONENTMANAGER_CSC_DELIINFRASTRUCTURECOMPMGRPTR_H
