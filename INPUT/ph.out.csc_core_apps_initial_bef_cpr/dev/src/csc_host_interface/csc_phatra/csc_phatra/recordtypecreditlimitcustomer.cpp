//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimitCustomer
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypecreditlimitcustomer.h"
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

RecordTypeCreditLimitCustomer::RecordTypeCreditLimitCustomer()
{
}

RecordTypeCreditLimitCustomer::~RecordTypeCreditLimitCustomer()
{
}

void RecordTypeCreditLimitCustomer::doProcess( const core::TransactionRecordBasePtr record ) const
{
	METHODNAME_DEF( RecordTypeCreditLimitCustomer, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	if ( record->getCustomerNo().stol() == 0 )
	{
		m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text got customer no 0", record);
		return;
	}

	try
	{
		pxCustBase customer( m_PXVBSession->get(), record->getBranchNo(), record->getCustomerNo().stol() );

		if ( customer.IsGoodState() )
		{
			m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );

			basar::BLong partnernr = customer.PartnerNr();
			
			//todo: bedeutung der '2' hier? -> enum [2: debit for non-chain-customer]
			pxDebitLimit debitLimit( m_PXVBSession->get(), partnernr, DEBIT_LIMIT_TYPE_NON_CHAIN, cDBGET_FORUPDATE);

			if (!debitLimit.IsGoodState())
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - debitlimit is not in good state", record );
				return;
			}
			if ( record->getType() == "K2" )
			{
				debitLimit.SetLimit( nMoney ( record->getLimitValue().toFloat64() ) );
			}

			debitLimit.Put();

			if (debitLimit.IsGoodState())
			{
				m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
                record->markAsProcessed();
			}
			else
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - debitlimit put failed", record );
			}
		}
	}
	catch( basar::Exception& ex )
	{
		// TODO 
		m_CSC_Logger->logBasarException("RecordTypeCreditLimitCustomer::doProcess-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("RecordTypeCreditLimitCustomer::doProcess...-text generic exception caught", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod