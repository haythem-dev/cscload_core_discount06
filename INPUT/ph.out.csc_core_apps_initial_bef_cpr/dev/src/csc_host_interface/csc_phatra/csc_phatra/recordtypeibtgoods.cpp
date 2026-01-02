//----------------------------------------------------------------------------//
/*! \file	
 *  \brief  RecordTypeIBTGoods
 *  \author Martin Zöphel
 *  \date   27.10.2014
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypeibtgoods.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include <convhelper.h>
#include <icsc_logger.h>
#include "pxtoteinfoptr.h"
#include "pvhx01_includes.h"

#include <iostream>

//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeIBTGoods::RecordTypeIBTGoods()
{
}

RecordTypeIBTGoods::~RecordTypeIBTGoods()
{
}

void RecordTypeIBTGoods::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
	try
	{
        m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "Entered VB doTransform");
		target->setBranchNo( source->getKbvzFil() );

        libcsc_utils::TimeParts time = libcsc_utils::ConvHelper::getTimeParts4NumericTime( source->getKbvzTime() );
		basar::Date date = libcsc_utils::ConvHelper::getDateFor6DigitsDate( source->getKbvzDate() );
		basar::DateTime datetime;
		datetime.setDate( date.getYear(), date.getMonth(), date.getDay() );
		datetime.setTime( time.m_Hour, time.m_Minute, time.m_Second );
		target->setInvoiceDateTime( datetime );

		target->setStorageLocation( source->getKbvzBatch() );

		basar::VarString cscOrderNo;
        cscOrderNo.format("%d",source->getKbvzKSCAnr()); 
		target->setCSCOrderNo( cscOrderNo );
        
        m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "VB set new values");
		target->setIbtBranchNo( source->getKbvzMFil() );
		target->setBatch( source->getKbvzET3() );
        m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "Leave VB doTransform");
	}
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeIBTGoods::doTransform-text basar exception caught", ex, source);
    }
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeIBTGoods::doTransform...-text generic exception caught", source );		
	}
}

void RecordTypeIBTGoods::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeIBTGoods, process );
	BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

	try
	{
		m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );

        nString type("IBT");//for now we only have this type
        nString tourid = record->getBatch().c_str();
		pxToteInfoPtr toteInfo = pxToteInfoPtr( new
            pxToteInfo( m_PXVBSession->get(), type, record->getBranchNo(), record->getStorageLocation().stol(), record->getCSCOrderNo().stol(), 
            record->getInvoiceDateTime().getDate(), record->getIbtBranchNo(), tourid ));

		if ( toteInfo->IsGoodState() )	
		{
			toteInfo->InsertData();

			if ( !toteInfo->IsGoodState() )
			{
				m_PXVBDBConnection->rollbackTransaction();
			}
			else
			{
				m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );
                record->markAsProcessed();
			}			
		}
		else
        {
            m_PXVBDBConnection->rollbackTransaction();
        }
	}
	catch( basar::Exception& ex )
	{
		m_CSC_Logger->logBasarException("RecordTypeIBTGoods::process-text basar exception caught", ex, record );
	}
	catch( ... )
	{
		m_CSC_Logger->logGenericException("RecordTypeIBTGoods::process...-text generic exception", record );
	}
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod