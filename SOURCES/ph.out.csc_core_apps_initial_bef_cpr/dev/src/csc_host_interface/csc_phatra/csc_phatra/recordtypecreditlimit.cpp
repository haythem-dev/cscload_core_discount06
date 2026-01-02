//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeCreditLimit
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypecreditlimit.h"
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

RecordTypeCreditLimit::RecordTypeCreditLimit()
{
}

RecordTypeCreditLimit::~RecordTypeCreditLimit()
{
}

void RecordTypeCreditLimit::doProcess( const core::TransactionRecordBasePtr record ) const
{
	METHODNAME_DEF( RecordTypeCreditLimit, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	if ( record->getCustomerNo().stol() == 0 )
	{
		m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text got customer no 0", record);
		return;
	}

	if( processNonChain(record) && processChain(record) )
	{
		record->markAsProcessed();
	}
}

bool RecordTypeCreditLimit::processNonChain( const core::TransactionRecordBasePtr record ) const
{
	METHODNAME_DEF( RecordTypeCreditLimit, processNonChain );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		pxCustBase customer( m_PXVBSession->get(), record->getBranchNo(), record->getCustomerNo().stol() );
		if ( customer.IsGoodState() )
		{												
			basar::BLong partnernr = customer.PartnerNr();
			m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );
			pxDebitLimit debitLimit( m_PXVBSession->get(), partnernr, DEBIT_LIMIT_TYPE_NON_CHAIN, cDBGET_FORUPDATE);
			if (!debitLimit.IsGoodState())
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - debitlimit non chain not in good state", record );					
				return false;
			}

			if ( record->getBookingType() == DEBIT_LIMIT_INCREASE )
			{
				debitLimit.IncreaseSumDebitSide( nMoney( record->getDebitValue().toFloat64() ) );
			}
			else if ( record->getBookingType() == DEBIT_LIMIT_DECREASE )
			{
				debitLimit.DecreaseSumDebitSide( nMoney( record->getDebitValue().toFloat64() ) );
			}

			debitLimit.Put();		
			if (debitLimit.IsGoodState())
			{
				m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
				return true;
			}
			else
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - debitlimit non chain put failed", record );
				return false;
			}			
		}
	}
	catch( basar::Exception& ex )
	{		
		m_CSC_Logger->logBasarException("RecordTypeCreditLimit::processNonChain-text basar exception caught", ex, record );		
	}
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeCreditLimit::processNonChain...-text generic exception caught", record );
	}
	return false;
}

bool RecordTypeCreditLimit::processChain( const core::TransactionRecordBasePtr record ) const
{
	METHODNAME_DEF( RecordTypeCreditLimit, processChain );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		pxCustBase customer( m_PXVBSession->get(), record->getBranchNo(), record->getCustomerNo().stol() );

		if ( customer.IsGoodState() )
		{												
			basar::BLong partnernr = customer.PartnerNr();
			m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );

			if (customer.MainCstNo() > 0) //Chain
			{					
				partnernr = customer.MainCstNo();
			}				

			pxDebitLimit* debitLimit = new pxDebitLimit( m_PXVBSession->get(), partnernr, DEBIT_LIMIT_TYPE_CHAIN, cDBGET_FORUPDATE);								
			if (!debitLimit->IsGoodState())
			{
				if( NULL != debitLimit )
				{
					delete debitLimit;
					debitLimit = NULL;
				}
                
				//try other partnernr
				partnernr = customer.PartnerNr();				
				debitLimit = new pxDebitLimit( m_PXVBSession->get(), partnernr, DEBIT_LIMIT_TYPE_CHAIN, cDBGET_FORUPDATE);
				if ( !debitLimit->IsGoodState() )
				{
					if( NULL != debitLimit )
					{
						delete debitLimit;
						debitLimit = NULL;
					}

					m_PXVBDBConnection->rollbackTransaction();
    				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - debitlimit chain not in good state", record );					
		    		return false;
				}
			}

			if ( record->getBookingType() == DEBIT_LIMIT_INCREASE )
			{
				debitLimit->IncreaseSumDebitSide( nMoney( record->getDebitValue().toFloat64() ) );
			}
			else if ( record->getBookingType() == DEBIT_LIMIT_DECREASE )
			{
				debitLimit->DecreaseSumDebitSide( nMoney( record->getDebitValue().toFloat64() ) );
			}

			debitLimit->Put();
			if (debitLimit->IsGoodState())
			{
				m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );

				delete debitLimit;
				debitLimit = NULL;

				return true;
			}
			else
			{
				m_PXVBDBConnection->rollbackTransaction();
				m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - debitlimit chain put failed", record );

				delete debitLimit;
				debitLimit = NULL;

				return false;
			}			
		}
	}
	catch( basar::Exception& ex )
	{
		// TODO Alerting, Mailing, Exception-Handling! Es muﬂ hier sofort reagiert werden! Daten zum Record mit ausgeben!!!
		m_CSC_Logger->logBasarException("RecordTypeCreditLimit::processChain-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeCreditLimit::processChain...-text generic exception caught", record );
		// TODO Alerting, Mailing, Exception-Handling! Es muﬂ hier sofort reagiert werden! Daten zum Record mit ausgeben!!!
		//throw;
	}
	return false;
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod
