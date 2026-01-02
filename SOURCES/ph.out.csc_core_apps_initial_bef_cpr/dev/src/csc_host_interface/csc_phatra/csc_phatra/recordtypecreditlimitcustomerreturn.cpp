//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimitCustomerReturn
 *  \author Steffen Heinlein
 *  \date   06.03.2013
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypecreditlimitcustomerreturn.h"
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

RecordTypeCreditLimitCustomerReturn::RecordTypeCreditLimitCustomerReturn()
{
}

RecordTypeCreditLimitCustomerReturn::~RecordTypeCreditLimitCustomerReturn()
{
}

void RecordTypeCreditLimitCustomerReturn::doProcess( const core::TransactionRecordBasePtr record ) const
{
	METHODNAME_DEF( RecordTypeCreditLimitCustomerReturn, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	if ( record->getCustomerNo().stol() == 0 )
	{
		m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text got customer no 0", record);
		return;
	}

	setCreditLimitNonChain( record );
	setCreditLimitChain( record );	

	record->markAsProcessed();
}

void RecordTypeCreditLimitCustomerReturn::setCreditLimitNonChain( const core::TransactionRecordBasePtr record ) const
{
	METHODNAME_DEF( RecordTypeCreditLimitCustomerReturn, setCreditLimitNonChain );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		nMoney SumReturns;

		SumReturns = nMoney( record->getDebitValue().toFloat64() );
		
		pxCustBase customer( m_PXVBSession->get(), record->getBranchNo(), record->getCustomerNo().stol() );
		if( customer.IsGoodState() )
		{						
			m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );
			pxDebitLimit debtlimit( m_PXVBSession->get(), customer.PartnerNr(), DEBIT_LIMIT_TYPE_NON_CHAIN, cDBGET_FORUPDATE );
			if( !debtlimit.IsGoodState() )
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "GU text record process pxverbund rollback - debitlimit non chain not in good state", record );
				return;
			}
			if ( record->getBookingType() == DEBIT_LIMIT_INCREASE )
			{
				debtlimit.IncreaseSumReturns( SumReturns );
			}
			else if ( record->getBookingType() == DEBIT_LIMIT_DECREASE )
			{
				debtlimit.DecreaseSumReturns( SumReturns );
			}				
			debtlimit.Put();
			if( debtlimit.IsGoodState() )
			{
				m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
			}
			else
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "GU text record process pxverbund rollback - debitlimit non chain put failed", record );
			}			
		}
	}
	catch( basar::Exception& ex )
	{		
		m_CSC_Logger->logBasarException("GU NonChain text basar exception caught", ex, record );		
	}
	catch( ... )
	{		
		m_CSC_Logger->logGenericException("GU NonChain text generic exception caught", record );		
	}
}

void RecordTypeCreditLimitCustomerReturn::setCreditLimitChain( const core::TransactionRecordBasePtr record ) const
{
	METHODNAME_DEF( RecordTypeCreditLimitCustomerReturn, setCreditLimitChain );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		long partnernr = 0;
		nMoney SumReturns;

		SumReturns = nMoney( record->getDebitValue().toFloat64() );
		
		pxCustBase customer( m_PXVBSession->get(), record->getBranchNo(), record->getCustomerNo().stol() );
		if( customer.IsGoodState() )
		{						     
			m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );
			
			partnernr = customer.PartnerNr();
			if ( customer.MainCstNo() > 0 )     // Kette
			{				
				partnernr = customer.MainCstNo(); // K1 Creditlmit is maintained in 22 for all BG branches
			}						

			pxDebitLimit* debtlimit = new pxDebitLimit( m_PXVBSession->get(), partnernr, DEBIT_LIMIT_TYPE_CHAIN, cDBGET_FORUPDATE);							
			if( !debtlimit->IsGoodState() )
			{
				partnernr = customer.PartnerNr();
				debtlimit = new pxDebitLimit( m_PXVBSession->get(), partnernr, DEBIT_LIMIT_TYPE_CHAIN, cDBGET_FORUPDATE);							
			}

			if( debtlimit->IsGoodState() )
			{
				if ( record->getBookingType() == DEBIT_LIMIT_INCREASE )
				{
					debtlimit->IncreaseSumReturns(SumReturns);
				}
				else if ( record->getBookingType() == DEBIT_LIMIT_DECREASE )
				{
					debtlimit->DecreaseSumReturns(SumReturns);
				}
				debtlimit->Put();
				if( debtlimit->IsGoodState() )
				{
					m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
				}
				else
				{
					m_PXVBDBConnection->rollbackTransaction();
					m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "GU text record process pxverbund rollback - debitlimit non chain put failed", record );
				}
			}
			else
			{
				m_PXVBDBConnection->rollbackTransaction();
			}
		}        
	}
	catch( basar::Exception& ex )
	{		
		m_CSC_Logger->logBasarException("GU NonChain text basar exception caught", ex, record );		
	}
	catch( ... )
	{		
		m_CSC_Logger->logGenericException("GU NonChain text generic exception caught", record );		
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod
