//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Michael Helmich
 *  \date       25.08.2021
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_IMPORTPRICELIST_INFRASTRUCTURE_CMDLINE_IMPORTPRICELISTCMDLINEEVALUATORPTR_H
#define GUARD_IMPORTPRICELIST_INFRASTRUCTURE_CMDLINE_IMPORTPRICELISTCMDLINEEVALUATORPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//
namespace importpricelist
{
    namespace infrastructure
    {
        namespace cmdLine
        {
            class IMPORTPRICELISTCmdLineEvaluator;
            typedef boost::shared_ptr< IMPORTPRICELISTCmdLineEvaluator > IMPORTPRICELISTCmdLineEvaluatorPtr;
        }
    }
}

#endif 
