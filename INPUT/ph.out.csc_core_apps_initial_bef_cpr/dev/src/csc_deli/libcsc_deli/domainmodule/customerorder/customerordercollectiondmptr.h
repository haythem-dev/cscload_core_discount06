#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_CUSTOMERORDERCOLLECTIONDMPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_CUSTOMERORDERCOLLECTIONDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace customerOrder
        {
            class CustomerOrderCollectionDM;
            typedef boost::shared_ptr< CustomerOrderCollectionDM > CustomerOrderCollectionDMPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMERORDER_CUSTOMERORDERCOLLECTIONDMPTR_H
