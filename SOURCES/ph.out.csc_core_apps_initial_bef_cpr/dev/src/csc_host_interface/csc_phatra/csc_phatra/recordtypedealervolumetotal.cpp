//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeDealerVolumeTotal
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypedealervolumetotal.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"

#include "recordtypedealervolumebase.h"

#include <icsc_logger.h>

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

RecordTypeDealerVolumeTotal::RecordTypeDealerVolumeTotal()
{
}

RecordTypeDealerVolumeTotal::~RecordTypeDealerVolumeTotal()
{
}

void RecordTypeDealerVolumeTotal::doProcess( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeDealerVolumeTotal, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );

		nDate tmpDate(record->getInvoiceDateTime().getDate());
		pxDealerVolume dealerVolumne( m_PXVBSession->get(), record->getBranchNo(), record->getUserId(), tmpDate, record->getInvoiceNo().stol());
		
		dealerVolumne.Get(cDBGET_FORUPDATE);

		dealerVolumne.SetOrderNoVSE( record->getCustomerOrderNo() );
		dealerVolumne.SetOrderNoKSC( record->getCSCOrderNo().stol() );
		
        //basar getTime returns time in format hhmmssttt
    		nClock tmpClock(record->getInvoiceDateTime().getTime() / 1000);
		dealerVolumne.SetTimeInVoice( tmpClock );
		dealerVolumne.SetCustomerNo( record->getCustomerNo().stol() );

		nMoney tmpMoney(record->getTurnover().toFloat64());
		dealerVolumne.SetInVoiceVolume( tmpMoney );

		dealerVolumne.Put();
		if( dealerVolumne.IsGoodState() )
		{
			m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
		}
		else
		{
			m_PXVBDBConnection->rollbackTransaction();
			m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - dealer volumne total put failed", record );
		}
	}
	catch( basar::Exception& ex )
	{
		// TODO
		m_CSC_Logger->logBasarException("RecordTypeDealerVolumeTotal::doProcess-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("RecordTypeDealerVolumeTotal::doProcess...-text generic exception caught", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod