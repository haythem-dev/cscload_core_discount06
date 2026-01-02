//----------------------------------------------------------------------------//
/*! \file
 *  \brief  RecordTypeImportInvoiceNo
 *  \author Steffen Heinlein
 *  \date   05.07.2012
 */
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// include section
//----------------------------------------------------------------------------//
#include "recordtypeimportinvoiceno.h"
#include "transactionrecordbaseptr.h"
#include "transactionrecordbase.h"
#include "convhelper.h"

#include <icsc_logger.h>

#include "pvhx01_includes.h"
#include <pxorderprolink.hpp>
//----------------------------------------------------------------------------//
// forward declaration section
//----------------------------------------------------------------------------//
namespace domMod
{
namespace pharmosTransaction
{
namespace processing
{

RecordTypeImportInvoiceNo::RecordTypeImportInvoiceNo()
{
}

RecordTypeImportInvoiceNo::~RecordTypeImportInvoiceNo()
{
}

void RecordTypeImportInvoiceNo::doTransform( const core::TransactionRecordBasePtr source, core::TransactionRecordBasePtr target ) const
{
    try
    {
        basar::VarString cscOrderNo;
        cscOrderNo.format("%d",source->getKbvzPZN());

        target->setCSCOrderNo( cscOrderNo );
        target->setBookingType( source->getKbvzBukz() );

        basar::VarString invoiceno = source->getKbvzET3().substr(0,10);
        target->setInvoiceNo( invoiceno );

        // TODO SK: target->setInvoiceDateTime( source->getKbvzDate() )


    }
    catch( basar::Exception& ex )
    {
        m_CSC_Logger->logBasarException("RecordTypeImportInvoiceNo::doTransform-text basar exception caught", ex, source);
    }
    catch( ... )
    {
        m_CSC_Logger->logGenericException("RecordTypeImportInvoiceNo::doTransform...-text generic exception caught", source );
        //throw;
    }
}

void RecordTypeImportInvoiceNo::process( const core::TransactionRecordBasePtr record ) const
{
    METHODNAME_DEF( RecordTypeImportInvoiceNo, process );
    BLOG_TRACE_METHOD( m_CSC_Logger->getLogger(), fun );

    try
    {
        m_PXVBDBConnection->beginTransaction( pxVerbund::MULTI_RECORD );

        pxOrder order( m_PXVBSession->get(), record->getCSCOrderNo().stol(), cDBGET_FORUPDATE );

        if ( !order.IsGoodState() )
        {
            m_PXVBDBConnection->rollbackTransaction();
            m_CSC_Logger->log(log4cplus::WARN_LOG_LEVEL, "text order was not good state", record );
            return;
        }

        basar::VarString invoiceNoTrimmed = record->getInvoiceNo();
        invoiceNoTrimmed.trim(basar::VarString::FIRST_END); // remove leading/trailing blanks
        invoiceNoTrimmed.erase(0, std::min(invoiceNoTrimmed.find_first_not_of('0'), invoiceNoTrimmed.size() - 1)); // remove leading zeroes
        if (order.RechnungNr() == 0)
        {
            order.SetRechnungNr(record->getInvoiceNo().stol());
            order.SetInvoiceNumber(invoiceNoTrimmed);



            // TODO SK: if CH then
            //              update tenderprogress set invoineno, invoicedate where kdauftragnr=order.KdAuftragNr() and orderdate=order.DateTimeCreated() and invoineno=0
            //          endif
        }
        order.VSEPut();

        pxGenericOrderRemarkList remarklist( m_PXVBSession->get() );
        remarklist.SelectOrderRemarksByOrderNoAndType(order.KdAuftragNr(), eInvoiceNo);
        remarklist.AddOrderRemark(order.KdAuftragNr(), 0, eInvoiceNo, invoiceNoTrimmed, static_cast<short>(remarklist.Entries()));


        if ( order.IsGoodState() )
        {
            // TODO IF COUNTRY RS UND TO ODER PF --> WriteProLink
            pxOrderProLink ProLink(m_PXVBSession->get(), order.KdAuftragNr());
            if (0 == ProLink.Get(cDBGET_FORUPDATE))
            {
                ProLink.SetInvoiceNumber(invoiceNoTrimmed.c_str());
                ProLink.Put();
            }

            m_PXVBDBConnection->commitTransaction( pxVerbund::MULTI_RECORD );
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
        m_CSC_Logger->logBasarException("RecordTypeImportInvoiceNo::process-text basar exception caught", ex, record );
        //throw;
    }
    catch( ... )
    {
        // TODO
        m_CSC_Logger->logGenericException("RecordTypeImportInvoiceNo::process...-text generic exception caught", record );
        //throw;
    }
}

} // end namespace processing
} // end namespace pharmosTransaction
} // end namespace domMod