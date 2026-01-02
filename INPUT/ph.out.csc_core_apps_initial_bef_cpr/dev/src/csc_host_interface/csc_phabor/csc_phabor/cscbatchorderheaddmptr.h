//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr 
 *  \author		Bjoern Bischof
 *  \date		06.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_CSCBATCHORDERHEADDMPTR_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PROCESSING_CSCBATCHORDERHEADDMPTR_H

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
        namespace processing
        {
	        class CSCBatchOrderHeadDM;
            typedef boost::shared_ptr< CSCBatchOrderHeadDM > CSCBatchOrderHeadDMPtr;    
        }
    }
}

#endif
