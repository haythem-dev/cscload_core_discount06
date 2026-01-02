#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEGOODSINPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEGOODSINPTR_H
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
            class RecordTypeGoodsIn;
            typedef boost::shared_ptr< RecordTypeGoodsIn > RecordTypeGoodsInPtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEGOODSINPTR_H

