//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeDiscountAccount
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypediscountaccount.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include <convhelper.h>

#include <icsc_logger.h>
#include <pxcstdiscacc.hpp>

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

RecordTypeDiscountAccount::RecordTypeDiscountAccount()
{
}

RecordTypeDiscountAccount::~RecordTypeDiscountAccount()
{
}

void RecordTypeDiscountAccount::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
		
        basar::VarString customerNo;
        customerNo.format("%d", source->getKbvzPZN());
        
        target->setCustomerNo( customerNo );	
		target->setChainNo( source->getKbvzVerf() );
		target->setInvoiceValue( source->getKbvzWert() / 100 );
		target->setDiscAccOperationNo( source->getKbvzMeng() );
		target->setVoucherType( source->getKbvzStat() );

		basar::VarString invoiceno = source->getKbvzET3().substr( 0, 10 );	
		target->setInvoiceNo( invoiceno );

		basar::Date date = libcsc_utils::ConvHelper::getDateFor6DigitsDate( source->getKbvzDate() );
		basar::DateTime datetime;
		datetime.setDate( date.getYear(), date.getMonth(), date.getDay() );
		datetime.setTime( 0, 0, 0 );
		target->setInvoiceDateTime( datetime );

		basar::VarString priority = source->getKbvzLgnr();	
        
        target->setPriority( priority.stoi() );
		
		basar::VarString pricetype("");
		pricetype.itos( source->getKbvzBukz() );
		target->setPriceType( pricetype );
			
		basar::Decimal balance( source->getKbvzLgfnr().stof() / 100 );
		target->setRemainingDiscAccValue( balance );
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeDiscountAccount::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeDiscountAccount::doTransform...-text generic exception caught", source );
		//throw;
	}
}

void RecordTypeDiscountAccount::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeDiscountAccount, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );	

	if ( record->getCustomerNo().stol() == 0 )
	{
		m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text got customer no 0", record);
        record->markAsProcessed();
		return;
	}

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );
		
		nDate tmpDate(record->getInvoiceDateTime().getDate());
		nString tmpInvoiceStr(record->getInvoiceNo().c_str());
		nString tmpVoucherType(record->getVoucherType().c_str());
		pxCstDiscAcc cstDiscAcc( m_PXVBSession->get(), record->getBranchNo(), record->getCustomerNo().stol(), tmpDate, tmpInvoiceStr, tmpVoucherType );
		
		cstDiscAcc.Get(cDBGET_FORUPDATE);
		cstDiscAcc.SetInvoiceAmount( (record->getInvoiceValue().toFloat64() ) );
		cstDiscAcc.SetBalance( record->getRemainingDiscAccValue().toFloat64() );
		cstDiscAcc.SetMainCstNo( record->getChainNo() );
		cstDiscAcc.SetPreisTyp( static_cast<PriceTypeEnum>(atoi(record->getPriceType().c_str())) );
		cstDiscAcc.SetPriority( static_cast<short>(record->getPriority()) );
		cstDiscAcc.SetLfdNr( record->getDiscAccOperationNo() );
		cstDiscAcc.Put();

		if( cstDiscAcc.IsGoodState() )
		{
			m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
            record->markAsProcessed();
		}
		else
		{
			m_PXVBDBConnection->rollbackTransaction();
			m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - calcDiscAcc put failed", record );
		}

	}
	catch( basar::Exception& ex )
	{
		// TODO
		m_CSC_Logger->logBasarException("RecordTypeDiscountAccount::process-text basar exception caught", ex, record );
		//throw;
	}
	catch( ... )
	{
		// TODO
		m_CSC_Logger->logGenericException("RecordTypeDiscountAccount::process...-text generic exception caught", record );
		//throw;
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod