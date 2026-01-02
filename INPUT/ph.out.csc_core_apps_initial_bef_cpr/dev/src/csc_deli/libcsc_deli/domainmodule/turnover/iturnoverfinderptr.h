#ifndef GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ITURNOVERFINDERPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ITURNOVERFINDERPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace turnover
        {
            class ITurnoverFinder;
            typedef boost::shared_ptr< ITurnoverFinder > ITurnoverFinderPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_TURNOVER_ITURNOVERFINDERPTR_H
