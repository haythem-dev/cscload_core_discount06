//--------------------------------------------------------------------------------------------------//
/*! \file 
 *  \brief      
 *  \author     Bischof Bjoern
 *  \date       16.06.2015
 *  \version    00.00.00.01 first version
 */ 
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_CSC_PHADEX_INFRASTRUCTURE_PARAMETER_DBPARAMETERPTR_H
#define GUARD_CSC_PHADEX_INFRASTRUCTURE_PARAMETER_DBPARAMETERPTR_H

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
		namespace parameter
        {
            class DBParameter;
            typedef boost::shared_ptr< DBParameter  > DBParameterPtr;
        }
    }
}

#endif 
