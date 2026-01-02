
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEINVOICECANCELLATIONPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEINVOICECANCELLATIONPTR_H
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
            class RecordTypeInvoiceCancellation;
            typedef boost::shared_ptr< RecordTypeInvoiceCancellation > RecordTypeInvoiceCancellationPtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEINVOICECANCELLATIONPTR_H

