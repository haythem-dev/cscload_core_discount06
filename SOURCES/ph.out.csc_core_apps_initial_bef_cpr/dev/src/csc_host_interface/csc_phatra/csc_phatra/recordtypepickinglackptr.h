
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEPICKINGLACKPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEPICKINGLACKPTR_H
//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <boost/shared_ptr.hpp>


//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
    namespace pharmosTransaction
    {
		namespace processing
        {
            class RecordTypePickingLack;
            typedef boost::shared_ptr< RecordTypePickingLack > RecordTypePickingLackPtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEPICKINGLACKPTR_H

