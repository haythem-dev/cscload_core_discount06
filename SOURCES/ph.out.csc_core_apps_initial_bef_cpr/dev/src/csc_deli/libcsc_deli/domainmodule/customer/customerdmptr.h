#ifndef GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_CUSTOMERDMPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_CUSTOMERDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace customer
        {
            class CustomerDM;
            typedef boost::shared_ptr< CustomerDM > CustomerDMPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_CUSTOMER_CUSTOMERDMPTR_H
