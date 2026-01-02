//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       13.07.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_FMDRELEVANTCALCULATORCMDLINEEVALUATORPTR_H
#define GUARD_FMDRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_FMDRELEVANTCALCULATORCMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace fmdrelevantcalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class FMDRELEVANTCALCULATORCmdLineEvaluator;
            typedef boost::shared_ptr< FMDRELEVANTCALCULATORCmdLineEvaluator > FMDRELEVANTCALCULATORCmdLineEvaluatorPtr;
        }
    }
}

#endif 
