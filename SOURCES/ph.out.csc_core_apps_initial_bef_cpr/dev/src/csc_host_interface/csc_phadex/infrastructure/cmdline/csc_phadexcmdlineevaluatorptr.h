//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       13.07.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHADEX_INFRASTRUCTURE_CMDLINE_CSC_PHADEXCMDLINEEVALUATORPTR_H
#define GUARD_CSC_PHADEX_INFRASTRUCTURE_CMDLINE_CSC_PHADEXCMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phadex
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class CSC_PHADEXCmdLineEvaluator;
            typedef boost::shared_ptr< CSC_PHADEXCmdLineEvaluator > CSC_PHADEXCmdLineEvaluatorPtr;
        }
    }
}

#endif 
