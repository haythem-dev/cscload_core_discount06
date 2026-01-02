//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeReturnPredeliveredArticle
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypereturnpredeliveredarticle.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include <convhelper.h>

#include <icsc_logger.h>
//#include <pxpredel.hpp>

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

/*RecordTypeReturnPredeliveredArticle::RecordTypeReturnPredeliveredArticle()
{
}

RecordTypeReturnPredeliveredArticle::~RecordTypeReturnPredeliveredArticle()
{
}

void RecordTypeReturnPredeliveredArticle::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		target->setArticleNo( source->getKbvzPZN() );
		target->setBookingType( source->getKbvzBukz() );
		target->setQuantity( source->getKbvzMeng() );

        basar::VarString invoiceNo;
        invoiceNo.format("%d", source->getKbvzTime());

		target->setInvoiceNo( invoiceNo );
		
		basar::Date date = libcsc_utils::ConvHelper::getDateFor6DigitsDate( source->getKbvzDate() );
		basar::DateTime datetime;
		datetime.setDate( date.getYear(), date.getMonth(), date.getDay() );
		datetime.setTime( 0, 0, 0 );
		target->setInvoiceDateTime( datetime );

		basar::VarString customerno = source->getKbvzET3();
		target->setCustomerNo( customerno );
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("text generic exception", source );
		//throw;
	}
}

void RecordTypeReturnPredeliveredArticle::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeReturnPredeliveredArticle, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );

		pxArtPreDeliveryList artPreDeliveryList( m_PXVBSession->get() );

		artPreDeliveryList.Select( record->getBranchNo(), record->getCustomerNo().stol(), record->getArticleNo() );

		if (artPreDeliveryList.Entries())
		{
			artPreDeliveryList.ReduceDeliveryQty( record->getQuantity(), record->getInvoiceNo().stol(), nDate(record->getInvoiceDateTime().getDate()) );
		}

		if (artPreDeliveryList.IsGoodState())
		{
			m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );
            record->markAsProcessed();
		}
		else
		{
			m_PXVBDBConnection->rollbackTransaction();
			m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - artPreDiliveryList not in good state", record );
		}
	}
	catch( basar::Exception& ex )
	{
		// TODO
		m_CSC_Logger->logBasarException("text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("text generic exception caught", record );
		//throw;
	}
}*/

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod