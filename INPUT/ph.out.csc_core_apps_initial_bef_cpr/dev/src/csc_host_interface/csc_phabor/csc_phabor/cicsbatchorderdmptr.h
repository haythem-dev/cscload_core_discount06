//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr 
 *  \author		Bjoern Bischof
 *  \date		06.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_CICSBATCHORDERDMPTR_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_CICSBATCHORDERDMPTR_H

//--------------------------------------------------------------------------------------------------//
// include section
//--------------------------------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>

//--------------------------------------------------------------------------------------------------//
// forward declaration section
//--------------------------------------------------------------------------------------------------//

namespace domMod
{
    namespace batchOrder
    {
        namespace preparation
        {
	        class CICSBatchOrderDM;
            typedef boost::shared_ptr< CICSBatchOrderDM > CICSBatchOrderDMPtr;    
        }
    }
}

#endif
