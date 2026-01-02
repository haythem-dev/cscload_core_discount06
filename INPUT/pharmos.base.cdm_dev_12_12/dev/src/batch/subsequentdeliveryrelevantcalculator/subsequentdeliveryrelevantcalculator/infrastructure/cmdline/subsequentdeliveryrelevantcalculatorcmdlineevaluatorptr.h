//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Michael Helmich
 *  \date       14.10.2022
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_CMDLINEEVALUATORPTR_H
#define GUARD_SUBSEQUENTDELIVERYRELEVANTCALCULATOR_INFRASTRUCTURE_CMDLINE_CMDLINEEVALUATORPTR_H

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
            class SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator;
            typedef boost::shared_ptr< SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluator > SUBSEQUENTDELIVERYRELEVANTCALCULATORCmdLineEvaluatorPtr;
        }
    }
}

#endif 
