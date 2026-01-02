#ifndef GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_TURNOVERDMPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_TURNOVERDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace turnover
        {
            class TurnoverDM;
            typedef boost::shared_ptr< TurnoverDM > TurnoverDMPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_TURNOVERDMPTR_H
