#ifndef GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVERCOLLECTIONLOADERPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVERCOLLECTIONLOADERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace turnover
        {
            class ICustomerTurnoverCollectionLoader;
            typedef boost::shared_ptr< ICustomerTurnoverCollectionLoader > ICustomerTurnoverCollectionLoaderPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ICUSTOMERTURNOVERCOLLECTIONLOADERPTR_H
