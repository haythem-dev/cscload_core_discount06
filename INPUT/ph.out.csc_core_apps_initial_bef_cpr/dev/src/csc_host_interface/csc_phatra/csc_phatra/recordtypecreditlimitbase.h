//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimitBase
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITBASE_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITBASE_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypebase.h"

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
	  
class RecordTypeCreditLimitBase : public core::RecordTypeBase
{
    public:	
        RecordTypeCreditLimitBase();
        ~RecordTypeCreditLimitBase();             
		
		void					process( const core::TransactionRecordBasePtr record ) const;		
		virtual void			doProcess( const core::TransactionRecordBasePtr record ) const = 0;
	
	protected:
		enum DebitLimitType{ DEBIT_LIMIT_TYPE_CHAIN = 1, DEBIT_LIMIT_TYPE_NON_CHAIN = 2};

		enum DebitLimitBookingType{ DEBIT_LIMIT_INCREASE = 1, DEBIT_LIMIT_DECREASE =  2};
	
    private:
        RecordTypeCreditLimitBase( const RecordTypeCreditLimitBase& );
		RecordTypeCreditLimitBase& operator= ( const RecordTypeCreditLimitBase& );

		void							doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECREDITLIMITBASE_H

