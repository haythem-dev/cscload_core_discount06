#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_ICUSTOMERFINDERPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_ICUSTOMERFINDERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace customer
        {
            class ICustomerFinder;
            typedef boost::shared_ptr< ICustomerFinder > ICustomerFinderPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_ICUSTOMERFINDERPTR_H
