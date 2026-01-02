//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief  
 *  \author  
 *  \date    */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_Corpha_CMDLINE_CMDLINEEVALUATORPTR_H
#define GUARD_CSC_Corpha_CMDLINE_CMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace csc_corpha
{
    namespace cmdLine
    {
        class CSC_CorphaCmdLineEvaluator;
        typedef boost::shared_ptr<csc_corpha::cmdLine::CSC_CorphaCmdLineEvaluator> CSC_CorphaCmdLineEvaluatorPtr;
    }
}

#endif // end GUARD_CSC_Corpha_CMDLINE_CMDLINEEVALUATORPTR_H
