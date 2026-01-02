//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Michael Helmich
 *  \date       14.10.2022
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_INFRASTRUCTURECOMPMGRPTR_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_INFRASTRUCTURECOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace subsequentdeliveryrelevantcalculator
{
    namespace componentManager
    {
        class InfrastructureCompMgr;
        typedef boost::shared_ptr< InfrastructureCompMgr > InfrastructureCompMgrPtr;
    }
}

#endif //GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_INFRASTRUCTURECOMPMGRPTR_H
