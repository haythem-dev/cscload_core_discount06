#include "documenthandler.h"

#include <boost/make_shared.hpp>
#include <boost/lexical_cast.hpp>

#include <parameter/ibranchparametergetterptr.h>
#include <parameter/branchparametergetter.h>

#include <logger/loggerpool.h>

#include <document/componentmanager/documentcomponentmanager.h>
#include <document/deliveryadvice/deliveryadvicerepositoryptr.h>
#include <document/deliveryadvice/deliveryadvicerepository.h>
#include <document/deliveryadvice/deliveryadvice.h>
#include <document/deliveryadvice/deliveryadvicevattotals.h>
#include <document/deliveryadvice/deliveryadviceremarks.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadviceline.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinedetails.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinediscount.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinereturn.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelineextrasat.h>
#include <document/documentarchiveinfo/documentarchiveinforepositoryptr.h>
#include <document/documentarchiveinfo/documentarchiveinforepository.h>
#include <document/documentarchiveinfo/documentarchiveinfoptr.h>
#include <document/documentarchiveinfo/documentarchiveinfo.h>

#include <document/narcoticarchive/narcoticarchiverepositoryptr.h>
#include <document/narcoticarchive/narcoticarchiverepository.h>
#include <document/narcoticarchive/narcoticarchiveptr.h>
#include <document/narcoticarchive/narcoticarchive.h>

#include <document/taxrates/taxratesrepositoryptr.h>
#include <document/taxrates/taxratesrepository.h>
#include <document/taxrates/taxrates.h>
#include "cscservicehelper.h"

#include <pxxmit.hpp>
#include <pxcstbas.hpp>
#include <pxcustomerflags.hpp>
#include <pxarticlecodes.hpp>
#include <types/messagecodeenum.inc>
#include <types/transactiontypeenum.inc>
#include <vector>


namespace csc {
namespace service {

DocumentHandler::DocumentHandler()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::DocumentHandler()");
}

DocumentHandler::~DocumentHandler()
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::~DocumentHandler()");
}

void DocumentHandler::getDeliveryAdvices(
    ::documents::DeliveryAdvicesResponse& _return,
    const ::documents::DeliveryAdvicesRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::getDeliveryAdvices()");

    libcsc::document::DeliveryAdviceInformationFilter filter;
    convertInformationFilter(filter, request.InformationFilter);

    libcsc::document::DeliveryAdviceCollectionPtr coll =
        getSession()->getDocumentComponentManager()->getDeliveryAdviceRepository()->findDeliveryAdvicesByDateRange(
            request.BranchNo,
            request.CustomerNo,
            static_cast<libcsc::document::ConfirmationStatusEnum>(request.ConfirmationStatus),
            Helper::getBasarDateFromCscDate(request.SearchPeriodStart),
            Helper::getBasarDateFromCscDate(request.SearchPeriodEnd),
            filter
        );

    documents::DeliveryAdviceList deliveryAdviceList;
    convertDeliveryAdviceCollection(deliveryAdviceList, *coll, filter);
    _return.__set_DeliveryAdvices(deliveryAdviceList);
    _return.__set_RetValue(Helper::getReturnStructFromError(nError()));
}

void DocumentHandler::getSpecificDeliveryAdvices(
    ::documents::DeliveryAdvicesResponse& _return,
    const ::documents::DeliveryAdviceSpecificRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::getSpecificDeliveryAdvices()");

    libcsc::document::DeliveryAdviceInformationFilter filter;
    libcsc::document::DeliveryAdviceKeyCollection keys;

    convertInformationFilter(filter, request.InformationFilter);
    convertDeliveryAdviceKeys(keys, request.BranchNo, request.CustomerNo, request.RequestedDeliveryAdvices);

    libcsc::document::DeliveryAdviceCollectionPtr coll =
        getSession()->getDocumentComponentManager()->getDeliveryAdviceRepository()->findDeliveryAdvicesByKey(
            keys,
            filter
        );

    documents::DeliveryAdviceList deliveryAdviceList;
    convertDeliveryAdviceCollection(deliveryAdviceList, *coll, filter);
    _return.__set_DeliveryAdvices(deliveryAdviceList);
    _return.__set_RetValue(Helper::getReturnStructFromError(nError()));
}

void DocumentHandler::confirmDeliveryAdviceReceipt(
    ::documents::DeliveryAdviceReceiveConfirmationResponse& _return,
    const ::documents::DeliveryAdviceReceiveConfirmationRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::confirmDeliveryAdviceReceipt()");

    libcsc::document::DeliveryAdviceKeyCollection keys;
    libcsc::document::DeliveryAdviceInformationFilter filter;

    convertDeliveryAdviceKeys(keys, request.BranchNo, request.CustomerNo, request.RequestedDeliveryAdvices);

    libcsc::document::DeliveryAdviceKeyCollection::const_iterator it = keys.begin();
    while (it != keys.end())
    {
        libcsc::document::DeliveryAdvicePtr deliveryAdvice;
        bool incrementRequestCounter = false;
        bool completedOnly = true;
        deliveryAdvice = getSession()->getDocumentComponentManager()->getDeliveryAdviceRepository()->findDeliveryAdvice(*it, filter, incrementRequestCounter, completedOnly);
        if (NULL != deliveryAdvice.get() && deliveryAdvice->isClean())
        {
            if (false == deliveryAdvice->isConfirmed())
            {
                deliveryAdvice->setConfirmed();
                getSession()->getDocumentComponentManager()->getDeliveryAdviceRepository()->saveDeliveryAdvice(deliveryAdvice);
            }
        }
        ++it;
    }
    _return.__set_RetValue(Helper::getReturnStructFromError(nError()));
}

void DocumentHandler::setDocumentInformation(
    ::documents::SetDocumentInformationResponse& _return,
    const ::documents::SetDocumentInformationRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::setDocumentInformation()");

    libcsc::document::DocumentArchiveInfoPtr documentInfo;
    documentInfo = getSession()->getDocumentComponentManager()->getDocumentArchiveInfoRepository()->findDocumentArchiveInfo(
        request.BranchNo,
        request.CustomerNo,
        static_cast<DocumentTypeEnum>(request.DocumentType),
        request.DocumentNo,
        Helper::getIntDateFromCscDate(request.DocumentDate)
    );
    if (NULL == documentInfo.get()) // not yet saved in database
    {
        documentInfo = getSession()->getDocumentComponentManager()->getDocumentArchiveInfoRepository()->createEmptyDocumentArchiveInfo();
        documentInfo->setBranchNo(request.BranchNo);
        documentInfo->setCustomerNo(request.CustomerNo);
        documentInfo->setDocumentType(static_cast<DocumentTypeEnum>(request.DocumentType));
        documentInfo->setDocumentNo(request.DocumentNo);
        documentInfo->setDocumentDate(Helper::getIntDateFromCscDate(request.DocumentDate));
        documentInfo->setDocumentId(request.DocumentGuid);
        documentInfo->setDocumentLink(request.DocumentLink);
        documentInfo->setSentViaMail(false);
        documentInfo->setSentViaFax(false);
    }
    else                                    // already saved in database
    {
        // overwrite document id only if empty before
        if (documentInfo->getDocumentId().empty() && request.__isset.DocumentGuid)
        {
            documentInfo->setDocumentId(request.DocumentGuid);
        }
        // overwrite document link if set from client
        if (request.__isset.DocumentLink)
        {
            documentInfo->setDocumentLink(request.DocumentLink);
        }
        // overwrite SentViaMail if mail was sent
        if (request.__isset.SentViaMail && true == request.SentViaMail)
        {
            documentInfo->setSentViaMail(true);
        }
        // overwrite SentViaFax if fax was sent
        if (request.__isset.SentViaFax && true == request.SentViaFax)
        {
            documentInfo->setSentViaFax(true);
        }
    }
    getSession()->getDocumentComponentManager()->getDocumentArchiveInfoRepository()->saveDocumentArchiveInfo(documentInfo);
    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession().get()));
    _return.__set_SendMail(false);
    _return.__set_SendFax(false);

    pxCustBase customer(getSession().get(), request.BranchNo, request.CustomerNo);
    if (customer.IsGoodState())
    {
        if (false == documentInfo->getSentViaMail())
        {
            if (documentInfo->getDocumentType() == Invoice && customer.Flags().IsMailInvoice())
            {
                _return.__set_SendMail(true);
            }
            if (documentInfo->getDocumentType() == BatchChangeAdvice && customer.Flags().IsMailBatchChangeAdvice())
            {
                _return.__set_SendMail(true);
            }
        }

        if (false == documentInfo->getSentViaFax())
        {
            if (documentInfo->getDocumentType() == Invoice && customer.Flags().IsFaxInvoice())
            {
                _return.__set_SendFax(true);
            }
            if (documentInfo->getDocumentType() == BatchChangeAdvice && customer.Flags().IsFaxBatchChangeAdvice())
            {
                _return.__set_SendFax(true);
            }
        }
    }

    if (true == _return.SendFax || true == _return.SendMail)
    {
        _return.__set_BranchInformation(Helper::getBranchDetails(getSession(), request.BranchNo));
        _return.__set_CustomerInformation(Helper::getCustomerDetails(getSession(), request.BranchNo, request.CustomerNo));
    }
}

void DocumentHandler::getDocumentInformation(
    ::documents::GetDocumentInformationResponse& _return,
    const  ::documents::GetDocumentInformationRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::getDocumentInformation()");

    libcsc::document::DocumentArchiveInfoPtr documentInfo;
    if (request.__isset.DocumentGuid)
    {
        documentInfo = getSession()->getDocumentComponentManager()->getDocumentArchiveInfoRepository()->findDocumentArchiveInfoByGuid(
            request.BranchNo,
            request.CustomerNo,
            request.DocumentGuid
        );
    }
    else
    {
        documentInfo = getSession()->getDocumentComponentManager()->getDocumentArchiveInfoRepository()->findDocumentArchiveInfo(
            request.BranchNo,
            request.CustomerNo,
            static_cast<DocumentTypeEnum>(request.DocumentType),
            request.DocumentNo,
            Helper::getIntDateFromCscDate(request.DocumentDate)
        );
    }

    if (NULL != documentInfo.get())
    {
        _return.__set_BranchNo(documentInfo->getBranchNo());
        _return.__set_CustomerNo(documentInfo->getCustomerNo());
        _return.__set_DocumentType(static_cast<documents::types::DocumentTypeEnum::type>(documentInfo->getDocumentType()));
        _return.__set_DocumentNo(documentInfo->getDocumentNo());
        _return.__set_DocumentDate(Helper::getCscDateFromIntDate(documentInfo->getDocumentDate()));
        _return.__set_DocumentGuid(documentInfo->getDocumentId());
        _return.__set_DocumentLink(documentInfo->getDocumentLink());
        _return.__set_RetValue(Helper::getReturnStructFromError(nError()));
    }
    else
    {
        nError error;
        error.ExternalError(getSession()->CMsgStream(), CMSG_MISC_EXCEPTION, "DocumentArchiveInfo not found!");
        _return.__set_RetValue(Helper::getReturnStructFromError(error));
    }
}

void DocumentHandler::setNarcoticTransactionStatus(
    ::narcotics::SetNarcoticTransactionStatusResponse& _return,
    const ::narcotics::SetNarcoticTransactionStatusRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::setNarcoticArchiveStatus()");

    libcsc::document::NarcoticArchivePtr narcoticArchivePtr;
    narcoticArchivePtr = getSession()->getDocumentComponentManager()->getNarcoticArchiveRepository()->findNarcoticArchiveByContributionVoucherNo(
        request.BranchNo,
        request.ContributionVoucherNo
    );

    if (NULL == narcoticArchivePtr.get()) // not yet saved in database
    {
        nError error;
        error.ExternalError(getSession()->CMsgStream(), CMSG_MISC_EXCEPTION, "NarcoticArchive not found for: " + request.ContributionVoucherNo);
        _return.__set_RetValue(Helper::getReturnStructFromError(error));
    }

    // overwrite document link if set from client
    if (request.__isset.AcknowledgementStatus)
    {
        narcoticArchivePtr->setAcknowledgementStatus(request.AcknowledgementStatus);
    }

    getSession()->getDocumentComponentManager()->getNarcoticArchiveRepository()->updateAcknowledgementStatusSQL(narcoticArchivePtr);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession().get()));
}


void DocumentHandler::getNarcoticTransaction(
    ::narcotics::GetNarcoticTransactionResponse& _return,
    const  ::narcotics::GetNarcoticTransactionRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::getNarcoticTransaction()");

    libcsc::document::NarcoticArchivePtr archiveTransactionInfo;
    if (request.__isset.ContributionVoucherNo)
    {
        archiveTransactionInfo = getSession()->getDocumentComponentManager()->getNarcoticArchiveRepository()->findNarcoticArchiveByContributionVoucherNo(
            request.BranchNo,
            request.ContributionVoucherNo
        );
    }

    if (NULL != archiveTransactionInfo.get())
    {
        _return.__set_BranchNo(archiveTransactionInfo->getBranchNo());
        _return.__set_CustomerSupplierNo(archiveTransactionInfo->getCustomerSupplierNo());

        _return.__set_AcknowledgementStatus(archiveTransactionInfo->getAcknowledgementStatus());
        _return.__set_ContributionVoucherTransferStatus(archiveTransactionInfo->getContributionVoucherTransferStatus());
        _return.__set_DeliveryNoteCopyTransferStatus(archiveTransactionInfo->getDeliveryNoteCopyTransferStatus());
        _return.__set_ArticleNo(archiveTransactionInfo->getArticleNo());
        _return.__set_ContributionVoucherNo(archiveTransactionInfo->getContributionVoucherNo());
        _return.__set_CustomerSupplierNo(archiveTransactionInfo->getCustomerSupplierNo());

        _return.__set_RetValue(Helper::getReturnStructFromError(nError()));
    }
    else
    {
        nError error;
        error.ExternalError(getSession()->CMsgStream(), CMSG_MISC_EXCEPTION, "getNarcoticTransaction nothing found!");
        _return.__set_RetValue(Helper::getReturnStructFromError(error));
    }
}

void DocumentHandler::getDataForBatchAdviceCreation(
    ::documents::BatchAdviceResponse& _return,
    const ::documents::BatchAdviceRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::getDataForBatchAdviceCreation()");

    libcsc::document::DeliveryAdviceCollectionPtr deliveryAdvices;

    deliveryAdvices =
        getSession()->getDocumentComponentManager()->getDeliveryAdviceRepository()->findDeliveryAdvicesForBatchAdviceCreation(request.BranchNo, request.BatchCorrectionOnly);

    if (deliveryAdvices.get() != NULL)
    {
        ::documents::DeliveryAdviceKeyList deliveryAdvicesKeyList;;
        libcsc::document::DeliveryAdviceCollection::const_iterator it = deliveryAdvices->begin();

        while (it != deliveryAdvices->end())
        {
            ::documents::DeliveryAdviceKey deliveryAdviceKey;

            deliveryAdviceKey.__set_BranchNo((*it)->getBranchNo());
            deliveryAdviceKey.__set_CustomerNo((*it)->getCustomerNo());
            deliveryAdviceKey.__set_DeliveryAdviceDate(Helper::getCscDateFromBasarDate((*it)->getDeliveryAdviceDate()));
            deliveryAdviceKey.__set_DeliveryAdviceNo((*it)->getDeliveryAdviceNo());

            deliveryAdvicesKeyList.push_back(deliveryAdviceKey);

            //update deliveryadvicehead, set batchcorrectionadvice 1 "Creation of batch advice started"
            (*it)->setBatchCorrectionAdvice(1);
            getSession()->getDocumentComponentManager()->getDeliveryAdviceRepository()->saveDeliveryAdvice((*it));

            ++it;
        }

        _return.__set_DeliveryAdvices(deliveryAdvicesKeyList);
        _return.__set_BranchInformation(Helper::getBranchDetails(getSession(), request.BranchNo));
        _return.__set_RetValue(Helper::getReturnStructFromError(nError()));
    }
    else
    {
        nError error;
        error.ExternalError(getSession()->CMsgStream(), CMSG_MISC_EXCEPTION, "Delivery advices for batch correction not found!");
        _return.__set_RetValue(Helper::getReturnStructFromError(error));
    }

    if (request.BatchCorrectionOnly)
    {
        deliveryAdvices =
            getSession()->getDocumentComponentManager()->getDeliveryAdviceRepository()->findDeliveryAdvicesForBatchAdviceCreation(request.BranchNo, !request.BatchCorrectionOnly);

        if (deliveryAdvices.get() != NULL)
        {
            libcsc::document::DeliveryAdviceCollection::const_iterator it = deliveryAdvices->begin();

            while (it != deliveryAdvices->end())
            {
                (*it)->setBatchCorrectionAdvice(3);

                getSession()->getDocumentComponentManager()->getDeliveryAdviceRepository()->saveDeliveryAdvice((*it));

                ++it;
            }
        }
    }
}

void DocumentHandler::updateDeliveryAdvices(
    ::documents::UpdateDeliveryAdvicesResponse& _return,
    const ::documents::UpdateDeliveryAdvicesRequest& request)
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::updateDeliveryAdvices()");

    libcsc::document::DeliveryAdviceKeyCollection coll;
    convertToDeliveryAdviceKeyCollection(request.DeliveryAdvices, coll);

    libcsc::document::DeliveryAdviceInformationFilter filter;
    filter.SendLineDiscountInformation = false;
    filter.SendLineInformation = false;
    filter.SendLineReturn = false;
    filter.SendTotals = false;
    filter.SendCustomerInformation = false;

    libcsc::document::DeliveryAdviceCollectionPtr deliveryAdvices =
        getSession()->getDocumentComponentManager()->getDeliveryAdviceRepository()->findDeliveryAdvicesByKey(coll, filter);


    ::documents::DeliveryAdviceUpdateList::const_iterator requestIt = request.DeliveryAdvices.begin();

    while (requestIt != request.DeliveryAdvices.end())
    {
        libcsc::document::DeliveryAdviceCollection::const_iterator it = deliveryAdvices->begin();
        while (it != deliveryAdvices->end())
        {
            if ((*it)->getBranchNo() == (*requestIt).Key.BranchNo &&
                (*it)->getCustomerNo() == (*requestIt).Key.CustomerNo &&
                (*it)->getDeliveryAdviceDate() == Helper::getBasarDateFromCscDate((*requestIt).Key.DeliveryAdviceDate) &&
                (*it)->getDeliveryAdviceNo() == (*requestIt).Key.DeliveryAdviceNo)
            {
                //TODO DZ set confirmed

                (*it)->setBatchCorrectionAdvice((*requestIt).BatchCorrectionAdvice);
                break;
            }

            ++it;
        }

        ++requestIt;
    }

    libcsc::document::DeliveryAdviceCollection::const_iterator it = deliveryAdvices->begin();

    //save deliveryAdvices
    while (it != deliveryAdvices->end())
    {
        getSession()->getDocumentComponentManager()->getDeliveryAdviceRepository()->saveDeliveryAdvice((*it));
        ++it;
    }

    _return.__set_RetValue(Helper::getReturnStructFromError(nError()));
}

void DocumentHandler::convertInformationFilter(
    libcsc::document::DeliveryAdviceInformationFilter& libcscFilter,
    const documents::DeliveryAdviceInformationFilter& thriftFilter) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::convertInformationFilter()");

    libcscFilter.SendTotals = false;
    libcscFilter.SendLineInformation = false;
    libcscFilter.SendLineDiscountInformation = false;
    libcscFilter.SendLinePickingInformation = false;
    libcscFilter.SendLineReturn = false;
    libcscFilter.SendCustomerInformation = false;
    libcscFilter.SendOnlyInvoicedLines = false;

    if (thriftFilter.__isset.SendTotals)
    {
        libcscFilter.SendTotals = thriftFilter.SendTotals;
    }
    if (thriftFilter.__isset.SendLineInformation)
    {
        libcscFilter.SendLineInformation = thriftFilter.SendLineInformation;
    }
    if (thriftFilter.__isset.SendLineDiscountInformation)
    {
        libcscFilter.SendLineDiscountInformation = thriftFilter.SendLineDiscountInformation;
    }
    if (thriftFilter.__isset.SendLinePickingInformation)
    {
        libcscFilter.SendLinePickingInformation = thriftFilter.SendLinePickingInformation;
    }
    if (thriftFilter.__isset.SendLineReturn)
    {
        libcscFilter.SendLineReturn = thriftFilter.SendLineReturn;
    }
    if (thriftFilter.__isset.SendCustomerInformation)
    {
        libcscFilter.SendCustomerInformation = thriftFilter.SendCustomerInformation;
    }
    if (thriftFilter.__isset.SendOnlyInvoicedLines)
    {
        libcscFilter.SendOnlyInvoicedLines = thriftFilter.SendOnlyInvoicedLines;
    }
    if (thriftFilter.__isset.SendLineExtrasAT)
    {
        libcscFilter.SendLineExtrasAT = thriftFilter.SendLineExtrasAT;
    }
}

void DocumentHandler::convertDeliveryAdviceKeys(
    libcsc::document::DeliveryAdviceKeyCollection& keys,
    const basar::Int16& branchNo,
    const basar::Int32& customerNo,
    const ::documents::DeliveryAdviceIdentifierList& identifierList) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::convertDeliveryAdviceKeys()");

    documents::DeliveryAdviceIdentifierList::const_iterator it = identifierList.begin();
    while (it != identifierList.end())
    {
        libcsc::document::DeliveryAdviceKey key;
        key.branchNo = branchNo;
        key.customerNo = customerNo;
        key.deliveryAdviceDate.setInvalid();
        if ((*it).__isset.DeliveryAdviceDate)
        {
            key.deliveryAdviceDate = Helper::getIntDateFromCscDate((*it).DeliveryAdviceDate);
        }
        key.deliveryAdviceNo = (*it).DeliveryAdviceNo;
        if ((*it).__isset.CSCOrderNo)
        {
            key.cscOrderNo = (*it).CSCOrderNo;
        }
        keys.push_back(key);
        ++it;
    }
}

void DocumentHandler::convertDeliveryAdviceCollection(
    ::documents::DeliveryAdviceList& thriftColl,
    const libcsc::document::DeliveryAdviceCollection& libcscColl,
    const libcsc::document::DeliveryAdviceInformationFilter& filter) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::convertDeliveryAdviceCollection()");

    libcsc::document::DeliveryAdviceCollection::const_iterator it = libcscColl.begin();
    while (it != libcscColl.end())
    {
        documents::DeliveryAdvice deliveryAdvice;
        deliveryAdvice.__set_BranchNo((*it)->getBranchNo());
        deliveryAdvice.__set_CustomerNo((*it)->getCustomerNo());
        deliveryAdvice.__set_DeliveryAdviceDate(Helper::getCscDateFromBasarDate((*it)->getDeliveryAdviceDate()));
        deliveryAdvice.__set_DeliveryAdviceNo((*it)->getDeliveryAdviceNo());

        if (true == filter.SendCustomerInformation)
        {
            deliveryAdvice.__set_CustomerInformation(Helper::getCustomerDetails(getSession(), (*it)->getBranchNo(), (*it)->getCustomerNo()));
        }

        deliveryAdvice.__set_PharmosOrderNo((*it)->getPharmosOrderNo());
        deliveryAdvice.__set_CSCOrderNo((*it)->getCscOrderNo());
        deliveryAdvice.__set_Completed((*it)->getCompleted());
        deliveryAdvice.__set_SpecialDocumentType((*it)->getSpecialDocumentType());
        deliveryAdvice.__set_TourId((*it)->getTourId());
        if ((*it)->getDueDate().isValid())
        {
            deliveryAdvice.__set_DueDate(Helper::getCscDateFromBasarDate((*it)->getDueDate()));
        }
        deliveryAdvice.__set_OrderType((*it)->getOrderType());
        deliveryAdvice.__set_PickingType((*it)->getPickingType());
        deliveryAdvice.__set_BookingType((*it)->getBookingType());
        deliveryAdvice.__set_Requested((*it)->getRequested());
        deliveryAdvice.__set_Confirmed((*it)->isConfirmed());
        deliveryAdvice.__set_OrderLabel((*it)->getOrderLabel());
        deliveryAdvice.__set_DocumentGuid((*it)->getDocumentId());
        deliveryAdvice.__set_Cancelled((*it)->getCancelled());
        deliveryAdvice.__set_BatchCorrectionAdviceStatus((*it)->getBatchCorrectionAdvice());
        deliveryAdvice.__set_LineFee((*it)->getLineFee().toFloat64());
        deliveryAdvice.__set_PackageFee((*it)->getPackageFee().toFloat64());
        if (true == filter.SendTotals)
        {
            documents::DeliveryAdviceTotals totals;
            totals.__set_DepositValue((*it)->getDepositValue().toFloat64());
            totals.__set_NetTurnover((*it)->getNetTurnover().toFloat64());
            totals.__set_DiscountRetail((*it)->getDiscountRetail().toFloat64());
            totals.__set_DiscountWholesale((*it)->getDiscountWholesale().toFloat64());
            totals.__set_VatAmount((*it)->getVatAmount().toFloat64());
            totals.__set_LogisticServiceCost((*it)->getLogisticServiceCost().toFloat64());

            documents::DeliveryAdviceVatList vatValues;
            libcsc::document::DeliveryAdviceVatTotalsCollection::const_iterator vatIt = (*it)->getDeliveryAdviceVatTotalsCollection()->begin();
            while (vatIt != (*it)->getDeliveryAdviceVatTotalsCollection()->end())
            {
                documents::DeliveryAdviceVatTotal vatTotal;
                vatTotal.__set_Vat((*vatIt)->getVat());
                vatTotal.__set_VatPercentage((*vatIt)->getVatPercentage().toFloat64());
                vatTotal.__set_NetValue((*vatIt)->getNetValue().toFloat64());
                vatTotal.__set_VatValue((*vatIt)->getVatValue().toFloat64());
                vatTotal.__set_SumLineFee((*vatIt)->getSumLineFee().toFloat64());
                vatTotal.__set_SumPackageFee((*vatIt)->getSumPackageFee().toFloat64());
                vatValues.push_back(vatTotal);
                ++vatIt;
            }
            totals.__set_VatValues(vatValues);
            deliveryAdvice.__set_Totals(totals);
        }

        // head remarks list
        documents::DeliveryAdviceRemarksList headRemarksList;
        libcsc::document::DeliveryAdviceRemarksCollection::const_iterator headRemarksIt = (*it)->getRemarksCollection()->begin();
        while (headRemarksIt != (*it)->getRemarksCollection()->end())
        {
            documents::DeliveryAdviceRemarks headRemark;
            headRemark.__set_RemarkType(static_cast<csc::types::OrderRemarkTypeEnum::type>((*headRemarksIt)->getRemarkType()));
            headRemark.__set_SerialNo((*headRemarksIt)->getSerialNo());
            headRemark.__set_RemarkText((*headRemarksIt)->getRemarkText());
            headRemarksList.push_back(headRemark);
            ++headRemarksIt;
        }
        deliveryAdvice.__set_HeadRemarks(headRemarksList);

        if (true == filter.SendLineInformation)
        {
            documents::DeliveryAdviceLineList lineList;
            libcsc::document::DeliveryAdviceLineCollection::const_iterator lineIt = (*it)->getDeliveryAdviceLineCollection()->begin();
            while (lineIt != (*it)->getDeliveryAdviceLineCollection()->end())
            {
                documents::DeliveryAdviceLine line;
                line.__set_DeliveryAdviceLineNo((*lineIt)->getDeliveryAdvicePosNo());
                line.__set_PharmosOrderLineNo((*lineIt)->getPharmosOrderPosNo());
                line.__set_CSCOrderLineNo((*lineIt)->getCscOrderPosNo());
                line.__set_ArticleNo((*lineIt)->getArticleNo());
                line.__set_ArticleCode((*lineIt)->getArticleCode());
                line.__set_CodeType((*lineIt)->getCodeType());
                line.__set_QtyOrdered((*lineIt)->getQuantityOrdered());
                line.__set_QtyConfirmed((*lineIt)->getQuantityConfirmed());
                line.__set_QtyRebateInKind((*lineIt)->getQuantityRebateInKind());
                line.__set_QtyInvoiced((*lineIt)->getQuantityInvoiced());
                line.__set_LineReference((*lineIt)->getLineReference());
                line.__set_VatPercentage((*lineIt)->getVatPercentage().toFloat64());
                line.__set_Vat((*lineIt)->getVat());
                line.__set_InvoicedPrice((*lineIt)->getInvoicedPrice().toFloat64());
                line.__set_LogisticServiceCost((*lineIt)->getLogisticServiceCost().toFloat64());
                line.__set_MinLogisticServiceCostValue((*lineIt)->getMinLogisticServiceCostValue().toFloat64());
                // TODO linetype???
                line.__set_ArticleName((*lineIt)->getArticleName());
                line.__set_ArticleUnit((*lineIt)->getArticleUnit());
                line.__set_PharmaceuticalForm((*lineIt)->getPharmaceuticalForm());
                if ((*lineIt)->getArticleNo() > 0)
                {
                    pxArticleCodesList codes(getSession().get());
                    codes.SelectByCodeType((*lineIt)->getArticleNo(), 13);
                    if (codes.Entries() > 0)
                    {
                        pxArticleCodes* code = (pxArticleCodes*)codes.At(0);
                        basar::VarString tmp = code->ArticleCode()();
                        tmp.trim(basar::cmnutil::BString::FIRST_END);
                        line.__set_EANCode(tmp);
                    }
                    //basar::VarString tmp = getSession()->ConvertPzn2Ean((*lineIt)->getArticleNo(), 13)();
                    //tmp.trim(basar::cmnutil::BString::FIRST_END);
                    //line.__set_EANCode(tmp);
                }

                line.__set_BasePrice((*lineIt)->getBasePrice().toFloat64());
                line.__set_PharmacySellPrice((*lineIt)->getPharmacySellPrice().toFloat64());
                line.__set_QtyFeeCalculation((*lineIt)->getQuantityFeeCalculation());
                line.__set_PrintedPricePerPiece((*lineIt)->getPrintedPricePerPiece().toFloat64());
                line.__set_LineValue((*lineIt)->getLineValue().toFloat64());
                line.__set_LineFee((*lineIt)->getLineFee().toFloat64());
                line.__set_PackageFee((*lineIt)->getPackageFee().toFloat64());

                // line remarks list
                documents::DeliveryAdviceRemarksList lineRemarksList;
                libcsc::document::DeliveryAdviceRemarksCollection::const_iterator lineRemarksIt = (*lineIt)->getRemarksCollection()->begin();
                while (lineRemarksIt != (*lineIt)->getRemarksCollection()->end())
                {
                    documents::DeliveryAdviceRemarks lineRemark;
                    lineRemark.__set_RemarkType(static_cast<csc::types::OrderRemarkTypeEnum::type>((*lineRemarksIt)->getRemarkType()));
                    lineRemark.__set_SerialNo((*lineRemarksIt)->getSerialNo());
                    lineRemark.__set_RemarkText((*lineRemarksIt)->getRemarkText());
                    lineRemarksList.push_back(lineRemark);
                    ++lineRemarksIt;
                }

                line.__set_LineRemarks(lineRemarksList);

                if (true == filter.SendLineReturn)
                {
                    documents::DeliveryAdviceLineReturnList lineReturnList;
                    libcsc::document::DeliveryAdviceLineReturnCollection::const_iterator lineReturnListIt = (*lineIt)->getReturnCollection()->begin();
                    while (lineReturnListIt != (*lineIt)->getReturnCollection()->end())
                    {
                        documents::DeliveryAdviceLineReturn lineReturn;
                        lineReturn.__set_DeliveryAdvicePosNo((*lineReturnListIt)->getDeliveryAdvicePosNo());
                        lineReturn.__set_BlockedforReturns((*lineReturnListIt)->getBlockedForreturns());
                        lineReturn.__set_Qty_Returned((*lineReturnListIt)->getQuantityReturned());
                        lineReturn.__set_Qty_Return_Rejected((*lineReturnListIt)->getQuantityReturnRejected());
                        lineReturn.__set_Qty_Returned_RebateInKind((*lineReturnListIt)->getQuantityReturnedRebateInKind());
                        lineReturnList.push_back(lineReturn);
                        ++lineReturnListIt;
                    }
                    line.__set_LineReturn(lineReturnList);
                }

                if (true == filter.SendLinePickingInformation)
                {
                    documents::DeliveryAdviceLineDetailList lineDetailList;
                    libcsc::document::DeliveryAdviceLineDetailsCollection::const_iterator lineDetailsIt = (*lineIt)->getDetailsCollection()->begin();
                    while (lineDetailsIt != (*lineIt)->getDetailsCollection()->end())
                    {
                        documents::DeliveryAdviceLineDetail lineDetail;
                        lineDetail.__set_DeliveryLineNo((*lineDetailsIt)->getDeliveryPosNo());
                        lineDetail.__set_QtyDelivery((*lineDetailsIt)->getQuantityDelivery());
                        lineDetail.__set_Batch((*lineDetailsIt)->getBatch());
                        if ((*lineDetailsIt)->getExpiryDate().isValid())
                        {
                            lineDetail.__set_ExpiryDate(Helper::getCscDateFromBasarDate((*lineDetailsIt)->getExpiryDate()));
                        }
                        lineDetail.__set_PackageId((*lineDetailsIt)->getPackageId());
                        lineDetail.__set_TrackingId((*lineDetailsIt)->getTrackingId());
                        lineDetail.__set_QtyLack((*lineDetailsIt)->getQuantityLack());
                        lineDetail.__set_PreCalculatedBatchChanged((*lineDetailsIt)->isPreCalcBatchChanged());
                        lineDetailList.push_back(lineDetail);
                        ++lineDetailsIt;
                    }
                    line.__set_LineDeliveryDetails(lineDetailList);
                }

                if (true == filter.SendLineDiscountInformation)
                {
                    documents::DeliveryAdviceLineDiscountList lineDiscountList;
                    libcsc::document::DeliveryAdviceLineDiscountCollection::const_iterator discountIt = (*lineIt)->getDiscountCollection()->begin();
                    while (discountIt != (*lineIt)->getDiscountCollection()->end())
                    {
                        documents::DeliveryAdviceLineDiscount discount;
                        discount.__set_DiscountMode((*discountIt)->getDiscountMode());
                        discount.__set_Discount((*discountIt)->getDiscount().toFloat64());
                        discount.__set_Origin((*discountIt)->getOrigin());
                        discount.__set_DeleteReason((*discountIt)->getDeleteReason());
                        discount.__set_DiscountValue((*discountIt)->getDiscountValue().toFloat64());
                        discount.__set_DiscountType((*discountIt)->getDiscountType());
                        discount.__set_Hierarchy((*discountIt)->getHierarchy());
                        discount.__set_CalculationBasis((*discountIt)->getCalculationBasis());
                        discount.__set_KindOfDiscount(static_cast<csc::types::KindOfDiscountEnum::type>((*discountIt)->getKindOfDiscount()));
                        lineDiscountList.push_back(discount);
                        ++discountIt;
                    }
                    line.__set_LineDiscounts(lineDiscountList);
                }

                if (true == filter.SendLineExtrasAT) 
                {
                    libcsc::document::DeliveryAdviceLineExtrasATPtr libcscExtrasAT = (*lineIt)->getExtrasAT();

                    documents::DeliveryAdviceLineExtrasAT extrasAT;
                    extrasAT.__set_IsNarcotic(libcscExtrasAT->isNarcotic());
                    extrasAT.__set_IsRX(libcscExtrasAT->isRX());
                    extrasAT.__set_IsPsychotropic(libcscExtrasAT->isPsychotropic());
                    extrasAT.__set_IsVeterinary(libcscExtrasAT->isVeterinary());
                    extrasAT.__set_IsHazardous(libcscExtrasAT->isHazardous());
                    extrasAT.__set_IsReportable(libcscExtrasAT->isReportable());
                    extrasAT.__set_IsShortExpiry(libcscExtrasAT->isShortExpiry());

                    line.__set_ExtrasAT(extrasAT);
                }

                lineList.push_back(line);
                ++lineIt;
            }
            deliveryAdvice.__set_LinesInformation(lineList);
        }

        thriftColl.push_back(deliveryAdvice);
        ++it;
    }
}


void DocumentHandler::convertToDeliveryAdviceKeyCollection(
    const ::documents::DeliveryAdviceUpdateList& thriftColl,
    libcsc::document::DeliveryAdviceKeyCollection& libcscColl) const
{
    LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentHandler::convertToDeliveryAdviceKeyCollection()");

    ::documents::DeliveryAdviceUpdateList::const_iterator it = thriftColl.begin();

    while (it != thriftColl.end())
    {
        libcsc::document::DeliveryAdviceKey deliveryAdvice;
        deliveryAdvice.branchNo = (*it).Key.BranchNo;
        deliveryAdvice.customerNo = (*it).Key.CustomerNo;
        deliveryAdvice.deliveryAdviceDate = Helper::getBasarDateFromCscDate((*it).Key.DeliveryAdviceDate);
        deliveryAdvice.deliveryAdviceNo = (*it).Key.DeliveryAdviceNo;

        libcscColl.push_back(deliveryAdvice);

        ++it;
    }
}

void DocumentHandler::processDeliveryAdvicesCroatia(
    ::documents::DeliveryAdvicesHRResponse& _return,
    const ::documents::DeliveryAdvicesHRRequest& request)
{
    ::documents::DeliveryAdvicesResponse deliveryAdvicesResponse;

    switch (request.RequestType)
    {
    case ::documents::DeliveryAdvicesHRRequestTypeEnum::ByPeriod:
    {
        getDeliveryAdvicesHR(deliveryAdvicesResponse, request.BranchNo, request.CustomerNo, request.PeriodFrom, request.PeriodTo);
        break;
    }
    case ::documents::DeliveryAdvicesHRRequestTypeEnum::ByInvoiceNumber:
    {
        getSpecificDeliveryAdvicesHR(deliveryAdvicesResponse, request.BranchNo, request.CustomerNo, request.DeliveryAdviceNos);
        break;
    }
    case ::documents::DeliveryAdvicesHRRequestTypeEnum::ByReference:
    {
        libcsc::document::DeliveryAdviceRepositoryPtr repo = getSession()->getDocumentComponentManager()->getDeliveryAdviceRepository();
        std::vector<std::string> deliveryAdviceNos = repo->findDnNumbersByReferences(request.BranchNo, request.CustomerNo, request.References);

        getSpecificDeliveryAdvicesHR(deliveryAdvicesResponse, request.BranchNo, request.CustomerNo, deliveryAdviceNos);
        break;
    }
    default:
        throw basar::Exception(basar::ExceptInfo("Thrift DocumentHandler::processDeliveryAdvicesCroatia()", "invalid request type!", __FILE__, __LINE__), "");
    }

    _return.__set_DeliveryAdvicesResp(deliveryAdvicesResponse);

    std::map<int16_t, double> taxratesResp;
    libcsc::document::TaxratesRepositoryPtr taxratesRepo = getSession()->getDocumentComponentManager()->getTaxratesRepository();
    libcsc::document::TaxratesCollectionPtr taxrates = taxratesRepo->getTaxrates();
    libcsc::document::TaxratesCollection::const_iterator itTaxrates = taxrates->begin();
    while (itTaxrates != taxrates->end())
    {
        std::pair<int16_t, double> taxrate((*itTaxrates)->getTaxlevel(), (*itTaxrates)->getSalesTaxrate().toFloat64());
        taxratesResp.insert(taxrate);
        ++itTaxrates;
    }
    _return.__set_Taxrates(taxratesResp);
}

void DocumentHandler::getDeliveryAdvicesHR(::documents::DeliveryAdvicesResponse& deliveryAdvicesResponse,
    const basar::Int16& branchNo, const basar::Int32& customerNo, const csc::base::Date& periodFrom, const csc::base::Date& periodTo)
{
    ::documents::DeliveryAdvicesRequest deliveryAdvicesRequest;
    deliveryAdvicesRequest.BranchNo = branchNo;
    deliveryAdvicesRequest.CustomerNo = customerNo;
    deliveryAdvicesRequest.ConfirmationStatus = ::documents::ConfirmationRequestStatusEnum::ALL_DELIVERY_ADVICES;
    deliveryAdvicesRequest.SearchPeriodStart = periodFrom;
    deliveryAdvicesRequest.SearchPeriodEnd = periodTo;
    deliveryAdvicesRequest.__set_InformationFilter(getInformationFilterHR());
    getDeliveryAdvices(deliveryAdvicesResponse, deliveryAdvicesRequest);
}

void DocumentHandler::getSpecificDeliveryAdvicesHR(::documents::DeliveryAdvicesResponse& deliveryAdvicesResponse,
    const basar::Int16& branchNo, const basar::Int32& customerNo, const std::vector<std::string>& deliveryAdviceNos)
{
    ::documents::DeliveryAdviceSpecificRequest deliveryAdviceSpecificRequest;
    deliveryAdviceSpecificRequest.BranchNo = branchNo;
    deliveryAdviceSpecificRequest.CustomerNo = customerNo;
    deliveryAdviceSpecificRequest.__set_InformationFilter(getInformationFilterHR());
    deliveryAdviceSpecificRequest.__set_RequestedDeliveryAdvices(::documents::DeliveryAdviceIdentifierList());
    std::vector<std::string>::const_iterator itDeliveryAdviceNo = deliveryAdviceNos.begin();
    while (itDeliveryAdviceNo != deliveryAdviceNos.end())
    {
        // TODO Distinct !
        ::documents::DeliveryAdviceIdentifier deliveryAdviceIdentifier;
        deliveryAdviceIdentifier.__set_DeliveryAdviceNo(*itDeliveryAdviceNo);
        deliveryAdviceSpecificRequest.RequestedDeliveryAdvices.push_back(deliveryAdviceIdentifier);
        ++itDeliveryAdviceNo;
    }
    getSpecificDeliveryAdvices(deliveryAdvicesResponse, deliveryAdviceSpecificRequest);
}

::documents::DeliveryAdviceInformationFilter DocumentHandler::getInformationFilterHR() const
{
    ::documents::DeliveryAdviceInformationFilter informationFilter;
    informationFilter.__set_SendLineInformation(true);
    informationFilter.__set_SendLineDiscountInformation(true);
    informationFilter.__set_SendLinePickingInformation(true);
    informationFilter.__set_SendTotals(true);
    return informationFilter;
}


} // namespace service
} // namespace csc
