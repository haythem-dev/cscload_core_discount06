//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr 
 *  \author		Bjoern Bischof
 *  \date		06.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_BATCHORDERTRANSFORMERPTR_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_CORE_BATCHORDERTRANSFORMERPTR_H

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
	        class BatchOrderTransformer;
            typedef boost::shared_ptr< BatchOrderTransformer > BatchOrderTransformerPtr;    

        }
    }
}

#endif
