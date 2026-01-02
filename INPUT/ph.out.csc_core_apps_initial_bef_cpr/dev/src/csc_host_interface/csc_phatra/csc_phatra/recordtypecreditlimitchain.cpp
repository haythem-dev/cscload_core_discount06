//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimitChain
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypecreditlimitchain.h"
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

RecordTypeCreditLimitChain::RecordTypeCreditLimitChain()
{
}

RecordTypeCreditLimitChain::~RecordTypeCreditLimitChain()
{
}

void RecordTypeCreditLimitChain::doProcess( const core::TransactionRecordBasePtr record ) const
{
	METHODNAME_DEF( RecordTypeCreditLimitChain, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	if ( record->getCustomerNo().stol() == 0 )
	{		
		return;
	}
	try
	{		
		pxCustBase customer( m_PXVBSession->get(), record->getBranchNo(), record->getCustomerNo().stol() );
		if( customer.IsGoodState() )
		{
			m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );
			pxDebitLimit debitLimit( m_PXVBSession->get(), customer.PartnerNr(), DEBIT_LIMIT_TYPE_CHAIN, cDBGET_FORUPDATE);
			
			if( debitLimit.IsGoodState() )
			{
				if ( record->getType() == "K1" )
				{
					debitLimit.SetLimit( nMoney( record->getLimitValue().toFloat64() ) );
				}
				debitLimit.Put();
			}

			if (debitLimit.IsGoodState())
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
		else
		{
			return;
		}
		
		/*
		pxCustBase customer( m_PXVBSession->get(), record->getBranchNo(), record->getCustomerNo().stol() );

		if ( customer.IsGoodState() )
		{
			m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );

			basar::BLong partnernr = customer.PartnerNr();

			if (customer.MainCstNo() > 0) //Chain
			{
				//partnernr = (record->getBranchNo() * 10000000) + customer.MainCstNo();
				partnernr = customer.MainCstNo(); // K1 Creditlmit is maintained in 22 for all BG branches
			}

			//done: bedeutung der '1' hier -> enum [1: debit for chain]
			pxDebitLimit debitLimit( m_PXVBSession->get(), partnernr, DEBIT_LIMIT_TYPE_CHAIN, cDBGET_FORUPDATE);

			if (!debitLimit.IsGoodState())
			{
				debitLimit = pxDebitLimit( m_PXVBSession->get(), customer.PartnerNr() , DEBIT_LIMIT_TYPE_CHAIN, cDBGET_FORUPDATE);                
                if (!debitLimit.IsGoodState())
                {
                    m_PXVBDBConnection->rollbackTransaction();
				    m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - debitLimit is not in good state", record );
				    return;
                }
			}
			if ( record->getType() == "K1" )
			{
				debitLimit.SetLimit( nMoney( record->getLimitValue().toFloat64() ) );
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
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - putting debitLimit failed", record );
			}
		}
		*/
	}
	catch( basar::Exception& ex )
	{
		// TODO
		m_CSC_Logger->logBasarException("RecordTypeCreditLimitChain::doProcess-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("RecordTypeCreditLimitChain::doProcess...-text generic exception caught", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod