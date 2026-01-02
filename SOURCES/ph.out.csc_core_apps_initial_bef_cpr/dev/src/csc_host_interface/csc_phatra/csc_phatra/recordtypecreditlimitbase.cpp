//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimitBase
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypecreditlimitbase.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "convhelper.h"

#include <icsc_logger.h>
//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeCreditLimitBase::RecordTypeCreditLimitBase()
{
}

RecordTypeCreditLimitBase::~RecordTypeCreditLimitBase()
{
}

void RecordTypeCreditLimitBase::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		basar::VarString customerNo;
        customerNo.format("%d", source->getKbvzPZN());        
        target->setCustomerNo( customerNo );			

		target->setBookingType( source->getKbvzBukz() );	
		target->setDebitValue( source->getKbvzWert() / 100 );
		target->setLimitValue( source->getKbvzWert() );		

		// K1 & K2: flag for "List 5" in KBVZ-STAT! currently not needed for processing!
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeCreditLimitBase::doTransform-text basar exception caught", ex, source);
    }
	catch(...)
	{
		m_CSC_Logger->logGenericException("RecordTypeCreditLimitBase::doTransform...-text generic exception caught", source );
		//throw;
	}
}

void RecordTypeCreditLimitBase::process( const core::TransactionRecordBasePtr record ) const
{
	// TODO
    METHODNAME_DEF( RecordTypeCreditLimitBase, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	doProcess( record );
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod