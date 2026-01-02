//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       13.07.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IBTORDERIMPORT_INFRASTRUCTURE_CMDLINE_IBTORDERIMPORTCMDLINEEVALUATORPTR_H
#define GUARD_IBTORDERIMPORT_INFRASTRUCTURE_CMDLINE_IBTORDERIMPORTCMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace ibtorderimport
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class IBTORDERIMPORTCmdLineEvaluator;
            typedef boost::shared_ptr< IBTORDERIMPORTCmdLineEvaluator > IBTORDERIMPORTCmdLineEvaluatorPtr;
        }
    }
}

#endif 
