#ifndef GUARD_CSC_DELI_INFRASTRUCTURE_SETUP_ICSC_DELILOGINGETTERCONSTPTR_H
#define GUARD_CSC_DELI_INFRASTRUCTURE_SETUP_ICSC_DELILOGINGETTERCONSTPTR_H

#include <boost/shared_ptr.hpp>

namespace csc_deli
{
    namespace infrastructure
    {
        namespace setup
        {
            class ICSC_DELILoginGetter;
            typedef boost::shared_ptr< ICSC_DELILoginGetter const> ICSC_DELILoginGetterConstPtr;
        }
    }
}

#endif
