//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeInvoiceCancellation
 *  \author Steffen Heinlein
 *  \date   14.02.2014
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypeinvoicecancellation.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"

#include "recordprocesshelper.h"

#include <icsc_logger.h>
#include <convhelper.h>

#include "pvhx01_includes.h"
//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeInvoiceCancellation::RecordTypeInvoiceCancellation()
{
}

RecordTypeInvoiceCancellation::~RecordTypeInvoiceCancellation()
{
}

void RecordTypeInvoiceCancellation::injectRecordProcessHelper( RecordProcessHelperPtr ptr)
{
	m_RecordProcessHelperPtr = ptr;
}

void RecordTypeInvoiceCancellation::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
    METHODNAME_DEF( RecordTypeInvoiceCancellation, doTransform );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
	try
	{		
		target->setBookingType( source->getKbvzBukz() );
		target->setArticleNo( source->getKbvzPZN() );
		target->setQuantity( std::abs(source->getKbvzMeng()) );	//! \note store absolute quantity, +/- is triggered by record type)

		basar::VarString cscOrderNo;
        cscOrderNo.format("%d",source->getKbvzKSCAnr()); 
		target->setCSCOrderNo( cscOrderNo );
		
		libcsc_utils::TimeParts time = libcsc_utils::ConvHelper::getTimeParts4NumericTime( source->getKbvzTime() );
		basar::Date date = libcsc_utils::ConvHelper::getDateFor6DigitsDate( source->getKbvzDate() );
		basar::DateTime datetime;
		datetime.setDate( date.getYear(), date.getMonth(), date.getDay() );
		datetime.setTime( time.m_Hour, time.m_Minute, time.m_Second );
		target->setInvoiceDateTime( datetime );		

		// just for information
		target->setBatch( source->getKbvzET3() );		
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeInvoiceCancellation::doTransform-text basar exception caught", ex, source);
    }
	catch(...)
	{
		m_CSC_Logger->logGenericException("RecordTypeInvoiceCancellation::doTransform...-text generic exception caught", source );
		//throw;
	}
}

void RecordTypeInvoiceCancellation::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeInvoiceCancellation, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		// update tender progress
		//m_RecordProcessHelperPtr->updateTenderProgress( record );				
		record->markAsProcessed(); 		
	}
	catch( basar::Exception& ex )
	{		
		m_CSC_Logger->logBasarException("RecordTypeInvoiceCancellation::process : text basar exception caught", ex, record );		
	}
	catch( ... )
	{		
		m_CSC_Logger->logGenericException("RecordTypeInvoiceCancellation::process... : text generic exception caught", record );		
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod