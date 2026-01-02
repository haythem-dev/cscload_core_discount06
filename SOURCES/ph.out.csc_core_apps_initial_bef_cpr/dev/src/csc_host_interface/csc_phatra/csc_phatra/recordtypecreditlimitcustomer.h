//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimitCustomer
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITCUSTOMER_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITCUSTOMER_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypecreditlimitbase.h"

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// class declaration setcion
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

class RecordTypeCreditLimitCustomer : public processing::RecordTypeCreditLimitBase
{
    public:	
        RecordTypeCreditLimitCustomer();
        ~RecordTypeCreditLimitCustomer();             
		
		virtual void					doProcess( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeCreditLimitCustomer( const RecordTypeCreditLimitCustomer& );
		RecordTypeCreditLimitCustomer& operator= ( const RecordTypeCreditLimitCustomer& );		
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITCUSTOMER_H

