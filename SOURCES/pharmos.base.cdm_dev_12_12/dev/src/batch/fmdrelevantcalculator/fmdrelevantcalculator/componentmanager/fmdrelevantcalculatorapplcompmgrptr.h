//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     
 *  \date       
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_FMDRELEVANTCALCULATORAPPLCOMPMGRPTR_H
#define GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_FMDRELEVANTCALCULATORAPPLCOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace fmdrelevantcalculator
{
    namespace componentManager
    {
        class ApplCompMgr;
        typedef boost::shared_ptr< ApplCompMgr > ApplCompMgrPtr;
    }
}

#endif //GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_FMDRELEVANTCALCULATORAPPLCOMPMGRPTR_H
