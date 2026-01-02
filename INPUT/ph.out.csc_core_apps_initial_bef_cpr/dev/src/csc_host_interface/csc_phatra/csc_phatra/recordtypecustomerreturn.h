//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCustomerReturn
 *  \author Steffen Heinlein
 *  \date   09.07.2012
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECUSTOMERRETURN_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECUSTOMERRETURN_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypebase.h"
#include "recordtypefactory.h"

#include "recordprocesshelperptr.h"
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

class RecordTypeCustomerReturn : public core::RecordTypeBase
{
	friend class core::RecordTypeFactory;
    public:	
        RecordTypeCustomerReturn();
        ~RecordTypeCustomerReturn();             
		
		virtual void					process( const core::TransactionRecordBasePtr record ) const;		

    private:
        RecordTypeCustomerReturn( const RecordTypeCustomerReturn& );
		RecordTypeCustomerReturn& operator= ( const RecordTypeCustomerReturn& );

		void 							injectRecordProcessHelper( RecordProcessHelperPtr ptr);
		
		virtual void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;

		RecordProcessHelperPtr	m_RecordProcessHelperPtr;
};

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPECUSTOMERRETURN_H

