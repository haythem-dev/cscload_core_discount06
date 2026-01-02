//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       28.07.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTRELEVANTCALCULATOR_COMPONENTMANAGER_IBTRELEVANTCALCULATORINFRASTRUCTURECOMPMGRPTR_H
#define GUARD_IBTRELEVANTCALCULATOR_COMPONENTMANAGER_IBTRELEVANTCALCULATORINFRASTRUCTURECOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace ibtrelevantcalculator
{
    namespace componentManager
    {
        class InfrastructureCompMgr;
        typedef boost::shared_ptr< InfrastructureCompMgr > InfrastructureCompMgrPtr;
    }
}

#endif //GUARD_IBTRELEVANTCALCULATOR_COMPONENTMANAGER_IBTRELEVANTCALCULATORINFRASTRUCTURECOMPMGRPTR_H
