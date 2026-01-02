//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimitCustomerReturn
 *  \author Steffen Heinlein
 *  \date   06.03.2013
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITCUSTOMERRETURN_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITCUSTOMERRETURN_H

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

class RecordTypeCreditLimitCustomerReturn : public processing::RecordTypeCreditLimitBase
{
    public:	
        RecordTypeCreditLimitCustomerReturn();
        ~RecordTypeCreditLimitCustomerReturn();             
		
		virtual void					doProcess( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeCreditLimitCustomerReturn( const RecordTypeCreditLimitCustomerReturn& );
		RecordTypeCreditLimitCustomerReturn& operator= ( const RecordTypeCreditLimitCustomerReturn& );		

		void							setCreditLimitNonChain( const core::TransactionRecordBasePtr record ) const;
		void							setCreditLimitChain( const core::TransactionRecordBasePtr record ) const;
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITCUSTOMERRETURN_H

