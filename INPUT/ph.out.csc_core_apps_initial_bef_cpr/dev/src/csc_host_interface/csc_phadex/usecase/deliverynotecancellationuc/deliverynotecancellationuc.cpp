#include "deliverynotecancellationuc.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include <document/componentmanager/documentcomponentmanager.h>
#include <document/deliveryadvice/deliveryadvicerepositoryptr.h>
#include <document/deliveryadvice/deliveryadvicerepository.h>
#include <domainmodule/phadextransaction/transactionrecord/deliverynotecancellation/deliverynotecancellation.h>
#include <document/deliveryadvice/deliveryadviceptr.h>
#include <document/deliveryadvice/deliveryadvice.h>
#include "document/deliveryadvice/deliveryadviceinformationfilter.h"
#include <exceptions/cscexceptionbase.h>
#include <libbasarcmnutil_date.h>
#include <libbasarcmnutil_logging.h>
#include <libutil/util.h>
#include <pxxmit.hpp>

namespace csc_phadex {
namespace useCase {


DeliveryNoteCancellationUC::DeliveryNoteCancellationUC()
: m_Logger( LoggerPool::getLoggerUseCases() )
{
    METHODNAME_DEF( DeliveryNoteCancellationUC, DeliveryNoteCancellationUC );
    BLOG_TRACE_METHOD( m_Logger, fun );
}

DeliveryNoteCancellationUC::~DeliveryNoteCancellationUC()
{
    METHODNAME_DEF( DeliveryNoteCancellationUC, ~DeliveryNoteCancellationUC );
    BLOG_TRACE_METHOD( m_Logger, fun );
}

void DeliveryNoteCancellationUC::setDeliveryNoteCancellationRecord(csc_phadex::domMod::phadexTransaction::IDeliveryNoteCancellationPtr dncr )
{
    m_DeliveryNoteCancellationRecord = dncr;
}

void DeliveryNoteCancellationUC::injectPxOrderTransmit( pxOrderTransmitPtr xmit )
{
    m_pxOrderTransmit = xmit;
}

void DeliveryNoteCancellationUC::cancelCustomerOrder()
{
    METHODNAME_DEF( cancelCustomerOrder, run );
    BLOG_TRACE_METHOD (m_Logger, fun );
    try
    {

        libcsc::document::DeliveryAdvicePtr ptr;
        libcsc::document::DeliveryAdviceRepositoryPtr deliveryAdviceRepository =
            m_pxOrderTransmit->getDocumentComponentManager()->getDeliveryAdviceRepository();

        libcsc::document::DeliveryAdviceKey key;
        key.branchNo = m_DeliveryNoteCancellationRecord->getBranchno();
        key.customerNo = m_DeliveryNoteCancellationRecord->getCustomerNo();
        key.deliveryAdviceDate = m_DeliveryNoteCancellationRecord->getInvoiceDate();



        basar::VarString invoiceNoTrimmed = m_DeliveryNoteCancellationRecord->getInvoiceNo();
        invoiceNoTrimmed.trim(basar::VarString::FIRST_END); // remove leading/trailing blanks
        invoiceNoTrimmed.erase(0, std::min(invoiceNoTrimmed.find_first_not_of('0'), invoiceNoTrimmed.size() - 1)); // remove leading zeroes
        key.deliveryAdviceNo = invoiceNoTrimmed;

        libcsc::document::DeliveryAdviceInformationFilter filter;
        filter.SendTotals = false;
        filter.SendLineInformation = true;
        filter.SendLinePickingInformation = false;
        filter.SendLineDiscountInformation = false;
        filter.SendLineReturn = false;
        filter.SendCustomerInformation = false;

        libcsc::document::DeliveryAdvicePtr deliveryAdvice = deliveryAdviceRepository->findDeliveryAdvice(key, filter, false, false);
        if (NULL != deliveryAdvice.get())
        {
            if (false == deliveryAdvice->isCancelled() && 1 == m_DeliveryNoteCancellationRecord->getStornoFlag() )
            {
                deliveryAdvice->setCancelled();
                deliveryAdviceRepository->saveDeliveryAdvice(deliveryAdvice);
            }
            else if( true  == deliveryAdvice->isCancelled() && 0 == m_DeliveryNoteCancellationRecord->getStornoFlag() )
            {
                deliveryAdvice->setUnCancelled();
                deliveryAdviceRepository->saveDeliveryAdvice(deliveryAdvice);
            }
        }

    }
    catch (const libcsc::exceptions::CSCExceptionBase& e)
    {
        std::stringstream ss;
        ss << "DeliveryNoteCancellationUC::cancelCustomerOrder(): Error during calculation: " << e.reason().c_str();
        BLOG_ERROR(LoggerPool::getLoggerUseCases(), ss.str());
    }

}

void DeliveryNoteCancellationUC::run()
{
    METHODNAME_DEF( DeliveryNoteCancellationUC, run );
    BLOG_TRACE_METHOD( m_Logger, fun );

     cancelCustomerOrder();

}


} // namespace usecase
} // namespace csc_phadex
