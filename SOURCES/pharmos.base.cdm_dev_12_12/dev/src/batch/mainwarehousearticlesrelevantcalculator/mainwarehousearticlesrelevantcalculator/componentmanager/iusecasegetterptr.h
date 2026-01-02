#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IUSECASEGETTERPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_COMPONENTMANAGER_IUSECASEGETTERPTR_H

#include <boost/shared_ptr.hpp>

namespace mainwarehousearticlesrelevantcalculator
{
    namespace componentManager
    {
        class IUseCaseGetter;
        typedef boost::shared_ptr< IUseCaseGetter > IUseCaseGetterPtr;
    }
}

#endif
