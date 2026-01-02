//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr 
 *  \author		Bjoern Bischof
 *  \date		06.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_CICSBATCHORDERHEADDMPTR_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_CICSBATCHORDERHEADDMPTR_H

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
	        class CICSBatchOrderHeadDM;
            typedef boost::shared_ptr< CICSBatchOrderHeadDM > CICSBatchOrderHeadDMPtr;    
        }
    }
}

#endif
