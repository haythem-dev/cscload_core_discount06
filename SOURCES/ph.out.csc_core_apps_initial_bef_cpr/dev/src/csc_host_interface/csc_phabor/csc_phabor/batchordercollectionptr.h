//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr 
 *  \author		Bjoern Bischof
 *  \date		06.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_BATCHORDERCOLLECTIONPTR_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_BATCHORDERCOLLECTIONPTR_H

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
        namespace core
        {
	        class BatchOrderCollection;
            typedef boost::shared_ptr< BatchOrderCollection > BatchOrderCollectionPtr;    
        }
    }
}

#endif
