#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICEFLAGPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICEFLAGPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace customerInvoice
        {
            class ICustomerInvoiceFlag;
            typedef boost::shared_ptr< ICustomerInvoiceFlag > ICustomerInvoiceFlagPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICEFLAGPTR_H
