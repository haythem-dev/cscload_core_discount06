//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimitGroup
 *  \author Steffen Heinlein
 *  \date   20.01.2015
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypecreditlimitgroup.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"

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

RecordTypeCreditLimitGroup::RecordTypeCreditLimitGroup()
{
}

RecordTypeCreditLimitGroup::~RecordTypeCreditLimitGroup()
{
}

void RecordTypeCreditLimitGroup::doProcess( const core::TransactionRecordBasePtr record ) const
{
	METHODNAME_DEF( RecordTypeCreditLimitGroup, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	if( record->getType() != "KG" )
	{
		return;
	}

	if( record->getCustomerNo().stol() == 0 )
	{
		return;
	}
	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );
		pxDebitLimit debitlimit( m_PXVBSession->get(), record->getCustomerNo().stol(), DEBIT_LIMIT_TYPE_CHAIN, cDBGET_FORUPDATE);
		if( debitlimit.IsGoodState() )
		{						
			debitlimit.SetLimit( nMoney( record->getLimitValue().toFloat64() ) );			
			debitlimit.Put();
		}

		if (debitlimit.IsGoodState())
		{
			m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
			record->markAsProcessed();
		}
		else
		{
			m_PXVBDBConnection->rollbackTransaction();
			m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - putting debitLimit failed", record );
		}			
	}
	catch( basar::Exception& ex )
	{		
		m_CSC_Logger->logBasarException("RecordTypeCreditLimitGroup::doProcess-text basar exception caught", ex, record );		
	}
	catch( ... )
	{		
		m_CSC_Logger->logGenericException("RecordTypeCreditLimitGroup::doProcess...-text generic exception caught", record );		
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod