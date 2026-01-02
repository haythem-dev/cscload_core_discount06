//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file
 *  \brief
 *  \author 
 *  \date    */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_IUSECASEGETTERPTR_H
#define GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_IUSECASEGETTERPTR_H

#include <boost/shared_ptr.hpp>

namespace fmdrelevantcalculator
{
    namespace componentManager
    {
        class IUseCaseGetter;
        typedef boost::shared_ptr< IUseCaseGetter > IUseCaseGetterPtr;
    }
}

#endif
