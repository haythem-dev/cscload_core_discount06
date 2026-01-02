#ifndef GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_ICREMAMAILCLEANERDMPTR_H
#define GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_ICREMAMAILCLEANERDMPTR_H

#include <boost/shared_ptr.hpp>

namespace libcsc_deli
{
    namespace domMod
    {
        namespace cremaMail
        {
            class ICremaMailCleaner;
            typedef boost::shared_ptr< ICremaMailCleaner > ICremaMailCleanerPtr;
        }
    }
}

#endif // GUARD_LIBCSC_DELI_DOMMOD_CREMAMAIL_ICREMAMAILCLEANERDMPTR_H
