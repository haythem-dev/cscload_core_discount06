#ifndef GUARD_CSC_SERVICE_DOCUMENTHANDLER_H
#define GUARD_CSC_SERVICE_DOCUMENTHANDLER_H

#include <pxordertransmitptr.h>
#include <document/deliveryadvice/deliveryadviceinformationfilter.h>
#include <document/deliveryadvice/deliveryadvicekey.h>
#include <document/deliveryadvice/deliveryadviceptr.h>
#include "documentarchiveinformation_types.h"
#include "narcoticsarchive_types.h"
#include "deliveryadvice_types.h"
#include "csclibtothrifthandlerbase.h"

namespace csc {
namespace service {

class DocumentHandler : public CscLibToThriftHandlerBase
{
public:
    DocumentHandler();
    virtual ~DocumentHandler();

    void getDeliveryAdvices(
        ::documents::DeliveryAdvicesResponse& _return,
        const ::documents::DeliveryAdvicesRequest& request);

    void getSpecificDeliveryAdvices(
        ::documents::DeliveryAdvicesResponse& _return,
        const ::documents::DeliveryAdviceSpecificRequest& request);

    void confirmDeliveryAdviceReceipt(
        ::documents::DeliveryAdviceReceiveConfirmationResponse& _return,
        const ::documents::DeliveryAdviceReceiveConfirmationRequest& request);

    void setDocumentInformation(
        ::documents::SetDocumentInformationResponse& _return,
        const ::documents::SetDocumentInformationRequest& request);

    void getDocumentInformation(
        ::documents::GetDocumentInformationResponse& _return,
        const ::documents::GetDocumentInformationRequest& request);

    void setNarcoticTransactionStatus(
        ::narcotics::SetNarcoticTransactionStatusResponse& _return,
        const ::narcotics::SetNarcoticTransactionStatusRequest& request);

    void getNarcoticTransaction(
        ::narcotics::GetNarcoticTransactionResponse& _return,
        const ::narcotics::GetNarcoticTransactionRequest& request);

    void getDataForBatchAdviceCreation(
        ::documents::BatchAdviceResponse& _return,
        const ::documents::BatchAdviceRequest& request);

    void updateDeliveryAdvices(
        ::documents::UpdateDeliveryAdvicesResponse& _return,
        const ::documents::UpdateDeliveryAdvicesRequest& request);

    void processDeliveryAdvicesCroatia(
        ::documents::DeliveryAdvicesHRResponse& _return,
        const ::documents::DeliveryAdvicesHRRequest& request);

private:
    void convertInformationFilter(
        libcsc::document::DeliveryAdviceInformationFilter& libcscFilter,
        const ::documents::DeliveryAdviceInformationFilter& thriftFilter) const;

    void convertDeliveryAdviceKeys(
        libcsc::document::DeliveryAdviceKeyCollection& keys,
        const basar::Int16& branchNo,
        const basar::Int32& customerNo,
        const ::documents::DeliveryAdviceIdentifierList& identifierList) const;

    void convertDeliveryAdviceCollection(
        ::documents::DeliveryAdviceList& thriftColl,
        const libcsc::document::DeliveryAdviceCollection& libcscColl,
        const libcsc::document::DeliveryAdviceInformationFilter& libcscFilter) const;

    void convertToDeliveryAdviceKeyCollection(
        const ::documents::DeliveryAdviceUpdateList& thriftColl,
        libcsc::document::DeliveryAdviceKeyCollection& libcscColl) const;

    void getSpecificDeliveryAdvicesHR(::documents::DeliveryAdvicesResponse& deliveryAdvicesResponse,
        const basar::Int16& branchNo, const basar::Int32& customerNo, const std::vector<std::string>& deliveryAdviceNos);

    void getDeliveryAdvicesHR(::documents::DeliveryAdvicesResponse& deliveryAdvicesResponse,
        const basar::Int16& branchNo, const basar::Int32& customerNo, const csc::base::Date& periodFrom, const csc::base::Date& periodTo);

    ::documents::DeliveryAdviceInformationFilter getInformationFilterHR() const;
};

} // namespace service
} // namespace csc

#endif // GUARD_CSC_SERVICE_DOCUMENTHANDLER_H
