#ifndef GUARD_CSC_DELI_INFRASTRUCTURE_CMDLINE_CSC_DELICMDLINEEVALUATORPTR_H
#define GUARD_CSC_DELI_INFRASTRUCTURE_CMDLINE_CSC_DELICMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_deli
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class CSC_DELICmdLineEvaluator;
            typedef boost::shared_ptr< CSC_DELICmdLineEvaluator > CSC_DELICmdLineEvaluatorPtr;
        }
    }
}

#endif // GUARD_CSC_DELI_INFRASTRUCTURE_CMDLINE_CSC_DELICMDLINEEVALUATORPTR_H
