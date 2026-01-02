#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_ICUSTOMERORDERCOLLECTIONFINDERPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_ICUSTOMERORDERCOLLECTIONFINDERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace customerOrder
        {
            class ICustomerOrderCollectionFinder;
            typedef boost::shared_ptr< ICustomerOrderCollectionFinder > ICustomerOrderCollectionFinderPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_ICUSTOMERORDERCOLLECTIONFINDERPTR_H
