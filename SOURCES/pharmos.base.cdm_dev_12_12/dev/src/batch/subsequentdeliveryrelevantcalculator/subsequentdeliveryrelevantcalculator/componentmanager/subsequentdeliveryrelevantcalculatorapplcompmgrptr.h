//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief
 *  \author     Michael Helmich
 *  \date       14.10.2021
 *  \version    00.00.00.01 first version
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_APPLCOMPMGRPTR_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_APPLCOMPMGRPTR_H

#include <boost/shared_ptr.hpp>

namespace subsequentdeliveryrelevantcalculator
{
    namespace componentManager
    {
        class ApplCompMgr;
        typedef boost::shared_ptr< ApplCompMgr > ApplCompMgrPtr;
    }
}

#endif //GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_COMPONENTMANAGER_APPLCOMPMGRPTR_H
