#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICINGCOLLECTIONPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICINGCOLLECTIONPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace customerInvoice
        {
            class ICustomerInvoicingCollection;
            typedef boost::shared_ptr< ICustomerInvoicingCollection > ICustomerInvoicingCollectionPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_ICUSTOMERINVOICINGCOLLECTIONPTR_H
