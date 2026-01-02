//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       13.07.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_CMDLINE_EXPORTARTICLECALCULATORCMDLINEEVALUATORPTR_H
#define GUARD_EXPORTARTICLECALCULATOR_INFRASTRUCTURE_CMDLINE_EXPORTARTICLECALCULATORCMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace exportarticlecalculator
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class EXPORTARTICLECALCULATORCmdLineEvaluator;
            typedef boost::shared_ptr< EXPORTARTICLECALCULATORCmdLineEvaluator > EXPORTARTICLECALCULATORCmdLineEvaluatorPtr;
        }
    }
}

#endif 
