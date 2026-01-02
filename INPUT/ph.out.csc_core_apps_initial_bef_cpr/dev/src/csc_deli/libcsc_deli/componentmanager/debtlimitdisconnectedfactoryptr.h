#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_DEBTLIMITDISCONNECTEDFACTORYPTR_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_DEBTLIMITDISCONNECTEDFACTORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace componentManager
    {
        class DebtLimitDisconnectedFactory;
        typedef boost::shared_ptr< DebtLimitDisconnectedFactory > DebtLimitDisconnectedFactoryPtr;
    }
}

#endif //GUARD_LIBCSC_DELI_COMPONENTMANAGER_DEBTLIMITDISCONNECTEDFACTORYPTR_H
