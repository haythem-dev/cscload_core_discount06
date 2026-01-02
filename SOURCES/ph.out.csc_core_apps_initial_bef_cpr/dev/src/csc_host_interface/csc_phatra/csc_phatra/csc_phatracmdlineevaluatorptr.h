//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHATRA_CMDLINE_CMDLINEEVALUATORPTR_H
#define GUARD_CSC_PHATRA_CMDLINE_CMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_phatra
{
    namespace cmdLine
    {
        class CSC_PhatraCmdLineEvaluator;
        typedef boost::shared_ptr<csc_phatra::cmdLine::CSC_PhatraCmdLineEvaluator> CSC_PhatraCmdLineEvaluatorPtr;
    }
}

#endif // end GUARD_CSC_PHATRA_CMDLINE_CMDLINEEVALUATORPTR_H

