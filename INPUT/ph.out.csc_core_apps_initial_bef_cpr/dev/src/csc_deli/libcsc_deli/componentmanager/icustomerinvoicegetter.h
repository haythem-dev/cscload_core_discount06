#ifndef GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICEGETTER_H
#define GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICEGETTER_H

#include "domainmodule/customerinvoice/icustomerinvoiceptr.h"

//-------------------------------------------------------------------------------------------------//
// interface declaration section
//-------------------------------------------------------------------------------------------------//
namespace libcsc_deli
{
namespace componentManager
{
    class ICustomerInvoiceGetter
    {
    public:
        virtual ~ICustomerInvoiceGetter() {}

        virtual domMod::customerInvoice::ICustomerInvoicePtr                            getCustomerInvoice() = 0;
    };

} // end namnespace componentManager
} // end namnespace libcsc_deli

#endif // GUARD_LIBCSC_DELI_COMPONENTMANAGER_ICUSTOMERINVOICEGETTER_H
