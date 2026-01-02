//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       13.07.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_CMDLINE_LONGTERMLACKLOADERCMDLINEEVALUATORPTR_H
#define GUARD_LONGTERMLACKLOADER_INFRASTRUCTURE_CMDLINE_LONGTERMLACKLOADERCMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace longtermlackloader
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class LONGTERMLACKLOADERCmdLineEvaluator;
            typedef boost::shared_ptr< LONGTERMLACKLOADERCmdLineEvaluator > LONGTERMLACKLOADERCmdLineEvaluatorPtr;
        }
    }
}

#endif 
