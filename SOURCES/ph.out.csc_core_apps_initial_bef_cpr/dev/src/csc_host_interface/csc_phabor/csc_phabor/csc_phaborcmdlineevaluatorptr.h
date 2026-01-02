//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHABOR_CMDLINE_CMDLINEEVALUATORPTR_H
#define GUARD_CSC_PHABOR_CMDLINE_CMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phabor
{
    namespace cmdLine
    {
        class CSC_PhaborCmdLineEvaluator;
        typedef boost::shared_ptr<csc_phabor::cmdLine::CSC_PhaborCmdLineEvaluator> CSC_PhaborCmdLineEvaluatorPtr;
    }
}

#endif // end GUARD_CSC_PHABOR_CMDLINE_CMDLINEEVALUATORPTR_H
