#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_IDEBTLIMITDISCONNECTEDFACTORYPTR_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_IDEBTLIMITDISCONNECTEDFACTORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace componentManager
    {
        class IDebtLimitDisconnectedFactory;
        typedef boost::shared_ptr< IDebtLimitDisconnectedFactory > IDebtLimitDisconnectedFactoryPtr;
    }
}

#endif //GUARD_LIBCSC_DELI_COMPONENTMANAGER_IDEBTLIMITDISCONNECTEDFACTORYPTR_H
