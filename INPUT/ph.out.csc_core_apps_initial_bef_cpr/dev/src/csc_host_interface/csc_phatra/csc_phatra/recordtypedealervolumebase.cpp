//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeDealerVolume
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypedealervolumebase.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include <convhelper.h>
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

RecordTypeDealerVolumeBase::RecordTypeDealerVolumeBase()
{
}

RecordTypeDealerVolumeBase::~RecordTypeDealerVolumeBase()
{
}

void RecordTypeDealerVolumeBase::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
    try
    {
        basar::VarString customerNo;
        customerNo.format("%d", source->getKbvzPZN());

        target->setCustomerNo( customerNo );

        target->setBookingType( source->getKbvzBukz() );
        target->setCustomerOrderNo( source->getKbvzVerf() );
        target->setTurnover( source->getKbvzWert() / 100 );

        target->setPaymentType( source->getKbvzLgnr() );
        target->setPaymentDate( libcsc_utils::ConvHelper::getDateFor6DigitsDate( source->getKbvzMeng() ) );


        target->setCSCOrderNo( source->getKbvzLgfnr() );

        basar::VarString invoiceno = source->getKbvzET3().substr(0,10);
        target->setInvoiceNo( invoiceno );

        libcsc_utils::TimeParts time = libcsc_utils::ConvHelper::getTimeParts4NumericTime( source->getKbvzTime() );
        basar::Date date = libcsc_utils::ConvHelper::getDateFor6DigitsDate( source->getKbvzDate() );
        basar::DateTime datetime;
        datetime.setDate( date.getYear(), date.getMonth(), date.getDay() );
        datetime.setTime( time.m_Hour, time.m_Minute, time.m_Second );
        target->setInvoiceDateTime( datetime );

        basar::Int32 userid = source->getKbvzGEP().toLong32();
        target->setUserId( userid );
    }
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeDealerVolumeBase::doTransform-text basar exception caught", ex, source);
    }
    catch( ... )
    {
        m_CSC_Logger->logGenericException("RecordTypeDealerVolumeBase::doTransform...-text generic exception caught", source );
        //throw;
    }
}

void RecordTypeDealerVolumeBase::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeDealerVolumeBase, process );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );
    // TODO
    doProcess( record );

    //same for all dealer volumnes:
    try
    {
        m_PXVBDBConnection->beginTransaction( pxVerbund::SINGLE_RECORD );
        pxOrder order( m_PXVBSession->get(), record->getCSCOrderNo().stol(), cDBGET_FORUPDATE );

        if (!order.IsGoodState())
        {
            m_PXVBDBConnection->rollbackTransaction();
            //m_CSC_Logger->log(log4cplus::ERROR_LOG_LEVEL, "text record process pxverbund rollback - pxOrder is not in good state", record ); //maybe normal? -> normal, see pv1serv.cpp, lines 1464 ff
            m_CSC_Logger->log(log4cplus::INFO_LOG_LEVEL, "text dealer volumne base, no order found");
            record->markAsProcessed();
            return;
        }
        basar::VarString invoiceNoTrimmed = record->getInvoiceNo();
        invoiceNoTrimmed.trim(basar::VarString::FIRST_END); // remove leading/trailing blanks
        invoiceNoTrimmed.erase(0, std::min(invoiceNoTrimmed.find_first_not_of('0'), invoiceNoTrimmed.size() - 1)); // remove leading zeroes
        order.SetRechnungNr( record->getInvoiceNo().stol() );
        order.SetInvoiceNumber(invoiceNoTrimmed);

        order.SetPaymentDate(  record->getPaymentDate().getDate() );
        order.SetPaymentType( (record->getPaymentType().c_str())[0] );
        order.VSEPut();

        if (order.IsGoodState())
        {
            m_PXVBDBConnection->commitTransaction( pxVerbund::SINGLE_RECORD );
            record->markAsProcessed();
        }
        else
        {
            m_PXVBDBConnection->rollbackTransaction();
            m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text record process pxverbund rollback - order vseput failed", record );
        }
    }
    catch( basar::Exception& ex )
    {
        // TODO
        m_CSC_Logger->logBasarException("RecordTypeDealerVolumeBase::process-text basar exception caught", ex, record );
        //throw;
    }
    catch( ... )
    {
        // TODO
        m_CSC_Logger->logGenericException("RecordTypeDealerVolumeBase::process...-text generic exception caught", record );
        //throw;
    }
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod