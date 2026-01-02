#ifndef GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_CREMAMAILCLEANUPDMPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_CREMAMAILCLEANUPDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace cremaMail
        {
            class CremaMailCleanupDM;
            typedef boost::shared_ptr< CremaMailCleanupDM > CremaMailCleanupDMPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_CREMAMAILCLEANUPDMPTR_H
