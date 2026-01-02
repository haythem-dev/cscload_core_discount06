#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace debtLimit
        {
            class IDebtLimit;
            typedef boost::shared_ptr< IDebtLimit > IDebtLimitPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITPTR_H
