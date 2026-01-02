#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICEGETTERPTR_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICEGETTERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace componentManager
    {
        class ICustomerInvoiceGetter;
        typedef boost::shared_ptr< ICustomerInvoiceGetter > ICustomerInvoiceGetterPtr;
    }
}

#endif //GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICEGETTERPTR_H
