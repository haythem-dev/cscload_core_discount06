//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Bischof Bjoern
 *  \date       28.07.2013
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_FMDRELEVANTCALCULATORINFRASTRUCTURECOMPMGRPTR_H
#define GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_FMDRELEVANTCALCULATORINFRASTRUCTURECOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace fmdrelevantcalculator
{
    namespace componentManager
    {
        class InfrastructureCompMgr;
        typedef boost::shared_ptr< InfrastructureCompMgr > InfrastructureCompMgrPtr;
    }
}

#endif //GUARD_FMDRELEVANTCALCULATOR_COMPONENTMANAGER_FMDRELEVANTCALCULATORINFRASTRUCTURECOMPMGRPTR_H
