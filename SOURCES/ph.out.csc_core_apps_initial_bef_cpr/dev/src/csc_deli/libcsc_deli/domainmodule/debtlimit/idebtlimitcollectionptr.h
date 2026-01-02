#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITCOLLECTIONPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITCOLLECTIONPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace debtLimit
        {
            class IDebtLimitCollection;
            typedef boost::shared_ptr< IDebtLimitCollection > IDebtLimitCollectionPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITCOLLECTIONPTR_H
