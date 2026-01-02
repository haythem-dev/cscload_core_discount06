#ifndef GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITMAILPROCESSORPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITMAILPROCESSORPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace debtLimit
        {
            class IDebtLimitMailProcessor;
            typedef boost::shared_ptr< IDebtLimitMailProcessor > IDebtLimitMailProcessorPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_DEBTLIMIT_IDEBTLIMITMAILPROCESSORPTR_H
