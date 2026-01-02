//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeInvoiceCancellation
 *  \author Steffen Heinlein
 *  \date   14.02.2014
 */
//----------------------------------------------------------------------------//
#ifndef GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEINVOICECANCELLATION_H
#define GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEINVOICECANCELLATION_H

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include <libbasarcmnutil.h> 
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

class RecordTypeInvoiceCancellation : public core::RecordTypeBase
{
	friend class core::RecordTypeFactory;
    public:	
        RecordTypeInvoiceCancellation();
        ~RecordTypeInvoiceCancellation();           

		void					process( const core::TransactionRecordBasePtr record ) const;			

    private:
        RecordTypeInvoiceCancellation( const RecordTypeInvoiceCancellation& );
		RecordTypeInvoiceCancellation& operator= ( const RecordTypeInvoiceCancellation& );		

		void					doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const;		

		void					injectRecordProcessHelper( RecordProcessHelperPtr );

		RecordProcessHelperPtr	m_RecordProcessHelperPtr;		
};

} // end namespace core
} // end namespace pharmosTransaction
} // end namespace domMod

#endif // GUARD_DOMMOD_PHARMOSTRANSACTION_PROCESSING_RECORDTYPEINVOICECANCELLATION_H

