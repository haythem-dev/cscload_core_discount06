//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       09.07.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTRELEVANTCALCULATOR_COMPONENTMANAGER_IBTRELEVANTCALCULATORAPPLCOMPMGRPTR_H
#define GUARD_IBTRELEVANTCALCULATOR_COMPONENTMANAGER_IBTRELEVANTCALCULATORAPPLCOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtrelevantcalculator
{
    namespace componentManager
    {
        class ApplCompMgr;
        typedef boost::shared_ptr< ApplCompMgr > ApplCompMgrPtr;
    }
}

#endif //GUARD_IBTRELEVANTCALCULATOR_COMPONENTMANAGER_IBTRELEVANTCALCULATORAPPLCOMPMGRPTR_H
