//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       13.07.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_IBTRELEVANTCALCULATORCMDLINEEVALUATORPTR_H
#define GUARD_IBTRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_IBTRELEVANTCALCULATORCMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace ibtrelevantcalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class IBTRELEVANTCALCULATORCmdLineEvaluator;
            typedef boost::shared_ptr< IBTRELEVANTCALCULATORCmdLineEvaluator > IBTRELEVANTCALCULATORCmdLineEvaluatorPtr;
        }
    }
}

#endif 
