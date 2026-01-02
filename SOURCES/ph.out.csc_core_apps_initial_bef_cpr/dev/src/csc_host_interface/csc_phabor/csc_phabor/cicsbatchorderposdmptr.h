//--------------------------------------------------------------------------------------------------//
/*! \file
 *  \brief		shared ptr 
 *  \author		Bjoern Bischof
 *  \date		06.07.2012
 */
//--------------------------------------------------------------------------------------------------//

#ifndef GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_CICSBATCHORDERPOSDMPTR_H
#define GUARD_DOMMOD_PHARMOSBATCHORDER_PREPARATION_CICSBATCHORDERPOSDMPTR_H

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
	        class CICSBatchOrderPosDM;
            typedef boost::shared_ptr< CICSBatchOrderPosDM > CICSBatchOrderPosDMPtr;    

        }
    }
}

#endif
