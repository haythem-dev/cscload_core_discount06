#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_CUSTOMERINVOICECONNECTEDFACTORYPTR_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_CUSTOMERINVOICECONNECTEDFACTORYPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace componentManager
    {
        class CustomerInvoiceConnectedFactory;
        typedef boost::shared_ptr< CustomerInvoiceConnectedFactory > CustomerInvoiceConnectedFactoryPtr;
    }
}

#endif //GUARD_LIBCSC_DELI_COMPONENTMANAGER_CUSTOMERINVOICECONNECTEDFACTORYPTR_H
