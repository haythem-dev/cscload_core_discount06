#ifndef GUARD_CSC_DELI_COMPONENTMANAGER_IUSECASEGETTERPTR_H
#define GUARD_CSC_DELI_COMPONENTMANAGER_IUSECASEGETTERPTR_H

#include <boost/shared_ptr.hpp>

namespace csc_deli
{
    namespace componentManager
    {
        class IUseCaseGetter;
        typedef boost::shared_ptr< IUseCaseGetter > IUseCaseGetterPtr;
    }
}

#endif // GUARD_CSC_DELI_COMPONENTMANAGER_IUSECASEGETTERPTR_H
