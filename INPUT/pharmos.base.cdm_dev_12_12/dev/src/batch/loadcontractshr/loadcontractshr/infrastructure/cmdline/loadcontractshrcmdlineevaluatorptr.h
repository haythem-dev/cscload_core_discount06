//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       13.07.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LOADCONTRACTSHR_INFRASTRUCTURE_CMDLINE_LOADCONTRACTSHRCMDLINEEVALUATORPTR_H
#define GUARD_LOADCONTRACTSHR_INFRASTRUCTURE_CMDLINE_LOADCONTRACTSHRCMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace loadcontractshr
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class LoadContractsHrCmdLineEvaluator;
            typedef boost::shared_ptr< LoadContractsHrCmdLineEvaluator > LoadContractsHrCmdLineEvaluatorPtr;
        }
    }
}

#endif 
