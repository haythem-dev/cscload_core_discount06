#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITIMPORTERPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITIMPORTERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace debtLimit
        {
            class IDebtLimitImporter;
            typedef boost::shared_ptr< IDebtLimitImporter > IDebtLimitImporterPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITIMPORTERPTR_H
