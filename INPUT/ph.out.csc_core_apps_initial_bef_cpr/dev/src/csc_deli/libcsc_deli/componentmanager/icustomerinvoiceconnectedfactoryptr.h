#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICECONNECTEDFACTORYPTR_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICECONNECTEDFACTORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace componentManager
    {
        class ICustomerInvoiceConnectedFactory;
        typedef boost::shared_ptr< ICustomerInvoiceConnectedFactory > ICustomerInvoiceConnectedFactoryPtr;
    }
}

#endif //GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICECONNECTEDFACTORYPTR_H
