#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITCOLLECTIONDMPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITCOLLECTIONDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace debtLimit
        {
            class DebtLimitCollectionDM;
            typedef boost::shared_ptr< DebtLimitCollectionDM > DebtLimitCollectionDMPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_DEBTLIMITCOLLECTIONDMPTR_H
