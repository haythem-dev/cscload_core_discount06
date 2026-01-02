#include "transactionrecordmapper.h"
#include "loggerpool/csc_phadex_loggerpool.h"
#include "componentmanager/csc_phadexapplcompmgr.h"
#include "domainmodule/unknownrecordtypeexception.h"
#include <domainmodule/phadextransaction/transactionrecord/transactionrecordtypeenum.h>
#include <domainmodule/phadextransaction/transactionrecord/tenderinvoicecancellation/tenderinvoicecancellationrecord.h>
#include <usecase/tendercancellationuc/tendercancellationuc.h>
#include <domainmodule/phadextransaction/phadextransactiondm.h>

#include <usecase/narcprintupdateuc/narcprintupdateuc.h>
#include <domainmodule/phadextransaction/transactionrecord/narcprintupdate/narcprintupdate.h>

#include <usecase/deliverynotecompleteduc/deliverynotecompleteduc.h>
#include <usecase/deliverynotecompleteduc/ideliverynotecompleteducptr.h>
#include <domainmodule/phadextransaction/transactionrecord/deliverynotecompleted/deliverynotecompleted.h>

#include <usecase/deliverynotecancellationuc/deliverynotecancellationuc.h>
#include <usecase/deliverynotecancellationuc/ideliverynotecancellationucptr.h>
#include <domainmodule/phadextransaction/transactionrecord/deliverynotecancellation/deliverynotecancellation.h>

#include <usecase/blockedarticleuc/blockedarticleuc.h>
#include <usecase/blockedarticleuc/iblockedarticleucptr.h>
#include <domainmodule/phadextransaction/transactionrecord/blockedarticlerecord/blockedarticlerecord.h>

#include <usecase/documentprintinfouc/documentprintinfouc.h>
#include <usecase/documentprintinfouc/idocumentprintinfoucptr.h>
#include <domainmodule/phadextransaction/transactionrecord/documentprintinfo/documentprintinfo.h>

#include <usecase/sapreferencenouc/sapreferencenouc.h>
#include <usecase/sapreferencenouc/isapreferencenoucptr.h>
#include <domainmodule/phadextransaction/transactionrecord/sapreferencenorecord/sapreferencenorecord.h>

namespace csc_phadex
{
namespace useCase
{
TransactionRecordMapper::TransactionRecordMapper()
:m_Logger( csc_phadex::LoggerPool::getLoggerDomModules() )
{
}

TransactionRecordMapper::~TransactionRecordMapper()
{
}

void TransactionRecordMapper::injectUseCaseGetter( csc_phadex::componentManager::IUseCaseGetterPtr useCaseGetter )
{
    m_UseCaseGetter = useCaseGetter;
}

libutil::useCase::IRunnablePtr TransactionRecordMapper::map( csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord )
{
    METHODNAME_DEF( TransactionRecordMapper, map );
    BLOG_TRACE_METHOD( m_Logger, fun );

    using namespace csc_phadex::domMod::phadexTransaction;
    libutil::useCase::IRunnablePtr runnablePtr = libutil::useCase::IRunnablePtr();

    switch( transactionRecord->getRecordType() )
    {
        case TRT_TENDER_CANCELLATION:
        {
            runnablePtr = getTenderCancellationUC( transactionRecord );
            break;
        }
        case TRT_NARCOTICS_PRINT_UPDATE:
        {
            runnablePtr = getNarcPrintUpdateUC( transactionRecord );
            break;
        }
        case TRT_DELIVERY_ADVICE_COMPLETED:
        {
            runnablePtr = getDeliveryNoteCompletedUC( transactionRecord );
            break;
        }
        case TRT_DELIVERY_INVOICE_CANCELLATION:
        {
            runnablePtr = getDeliveryNoteCancellationUC( transactionRecord );
            break;
        }
        case TRT_BLOCKED_ARTICLES:
        {
            runnablePtr = getBlockedArticleUC(transactionRecord);
            break;
        }
        case TRT_DOCUMENT_PRINT_INFO:
        {
            runnablePtr = getDocumentPrintInfoUC(transactionRecord);
            break;
        }
        case TRT_SAP_REFERENCE_NO:
        {
            runnablePtr = getSAPReferenceNoUC(transactionRecord);
            break;
        }
        default:
        {
            std::stringstream ss;
            ss << "Unknown RecordType " << transactionRecord->getRecordType() ;
            throw csc_phadex::exception::UnknownRecordTypeException( basar::ExceptInfo( fun, ss.str().c_str(), __FILE__, __LINE__ ) );
        }
    }
    return runnablePtr;
}

libutil::useCase::IRunnablePtr TransactionRecordMapper::getTenderCancellationUC( csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord )
{
    using namespace csc_phadex::domMod::phadexTransaction;

    ITenderCancellationUCPtr uc = m_UseCaseGetter->getTenderCancellationUC();
    ITenderInvoiceCancellationRecordPtr tc( new TenderInvoiceCancellationRecord( transactionRecord ) );
    uc->setTenderInvoiceCancellationRecord( tc );
    return uc;
}

libutil::useCase::IRunnablePtr TransactionRecordMapper::getNarcPrintUpdateUC( csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord )
{
    using namespace csc_phadex::domMod::phadexTransaction;

    INarcPrintUpdateUCPtr narcPrintUpdateUC = m_UseCaseGetter->getNarcPrintUpdateUC();
    INarcPrintUpdatePtr narcPrintUpdate( new NarcPrintUpdate( transactionRecord ) );
    narcPrintUpdateUC->setNarcPrintUpdate( narcPrintUpdate );
    return narcPrintUpdateUC;
}

libutil::useCase::IRunnablePtr TransactionRecordMapper::getDeliveryNoteCompletedUC( csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord )
{
    using namespace csc_phadex::domMod::phadexTransaction;

    IDeliveryNoteCompletedUCPtr uc = m_UseCaseGetter->getDeliveryNoteCompletedUC();

    IDeliveryNoteCompletedPtr deliveryNoteCompleted( new DeliveryNoteCompleted( transactionRecord ) );
    uc->setDeliveryNoteCompletedRecord( deliveryNoteCompleted );
    return uc;
}

libutil::useCase::IRunnablePtr TransactionRecordMapper::getDeliveryNoteCancellationUC( csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord )
{
    using namespace csc_phadex::domMod::phadexTransaction;

    IDeliveryNoteCancellationUCPtr uc = m_UseCaseGetter->getDeliveryNoteCancellationUC();

    IDeliveryNoteCancellationPtr deliveryNoteCancelled( new DeliveryNoteCancellation( transactionRecord ) );
    uc->setDeliveryNoteCancellationRecord( deliveryNoteCancelled );
    return uc;
}

libutil::useCase::IRunnablePtr TransactionRecordMapper::getBlockedArticleUC(csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord)
{
    using namespace csc_phadex::domMod::phadexTransaction;

    IBlockedArticleUCPtr uc = m_UseCaseGetter->getBlockedArticleUC();

    IBlockedArticleRecordPtr blockedArticle(new BlockedArticleRecord(transactionRecord));
    uc->setBlockedArticleRecord(blockedArticle);
    return uc;
}

libutil::useCase::IRunnablePtr TransactionRecordMapper::getDocumentPrintInfoUC(csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord)
{
    using namespace csc_phadex::domMod::phadexTransaction;

    IDocumentPrintInfoUCPtr uc = m_UseCaseGetter->getDocumentPrintInfoUC();

    IDocumentPrintInfoPtr documentPrintInfo(new DocumentPrintInfo(transactionRecord));
    uc->setDocumentPrintInfo(documentPrintInfo);
    return uc;
}

libutil::useCase::IRunnablePtr TransactionRecordMapper::getSAPReferenceNoUC(csc_phadex::domMod::phadexTransaction::IPhadexTransactionPtr transactionRecord)
{
    using namespace csc_phadex::domMod::phadexTransaction;

    ISAPReferenceNoUCPtr uc = m_UseCaseGetter->getSAPReferenceNoUC();
    ISAPReferenceNoRecordPtr record(new SAPReferenceNoRecord(transactionRecord));
    uc->setSAPReferenceNoRecord(record);
    return uc;
}


} // namespace useCase
} // namespace csc_phadex
