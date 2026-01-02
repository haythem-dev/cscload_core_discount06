//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       13.07.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_MAINWAREHOUSEARTICLESRELEVANTCALCULATORCMDLINEEVALUATORPTR_H
#define GUARD_MAINWAREHOUSEARTICLESRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_MAINWAREHOUSEARTICLESRELEVANTCALCULATORCMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace mainwarehousearticlesrelevantcalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator;
            typedef boost::shared_ptr< MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluator > MAINWAREHOUSEARTICLESRELEVANTCALCULATORCmdLineEvaluatorPtr;
        }
    }
}

#endif 
