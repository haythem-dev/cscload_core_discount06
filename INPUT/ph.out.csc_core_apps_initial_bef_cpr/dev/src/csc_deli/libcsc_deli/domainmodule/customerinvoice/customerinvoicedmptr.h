#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_CUSTOMERINVOICEDMPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_CUSTOMERINVOICEDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace customerInvoice
        {
            class CustomerInvoiceDM;
            typedef boost::shared_ptr< CustomerInvoiceDM > CustomerInvoiceDMPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERINVOICE_CUSTOMERINVOICEDMPTR_H
