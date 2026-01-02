
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECUSTOMERRETURNPTR_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECUSTOMERRETURNPTR_H
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
            class RecordTypeCustomerReturn;
            typedef boost::shared_ptr< RecordTypeCustomerReturn > RecordTypeCustomerReturnPtr;
        }
    }
}

#endif //#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECUSTOMERRETURNPTR_H

