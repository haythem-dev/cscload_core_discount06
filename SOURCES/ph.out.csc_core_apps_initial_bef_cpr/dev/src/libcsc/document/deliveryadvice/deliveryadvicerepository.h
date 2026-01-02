#ifndef GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REPOSITORY_H
#define GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <parameter/ibranchparametergetterptr.h>
#include <document/deliveryadvice/deliveryadviceptr.h>
#include <document/deliveryadvice/deliveryadvicevattotalsptr.h>
#include <document/deliveryadvice/deliveryadviceremarksptr.h>
#include <document/deliveryadvice/deliveryadvicekey.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelineptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinediscountptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinedetailsptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelinereturnptr.h>
#include <document/deliveryadvice/deliveryadvicelineibtlink/deliveryadvicelineibtlinkptr.h>
#include <document/deliveryadvice/deliveryadviceline/deliveryadvicelineextrasatptr.h>
/////////////////////////////////////////////////////////////////////////////////////
// forward declarations
/////////////////////////////////////////////////////////////////////////////////////
namespace basar {
    namespace db {
        namespace sql {
            class ResultsetRef;
        }
    }
}

namespace libcsc {
    namespace document {
        struct DeliveryAdviceInformationFilter;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
// class declaration
/////////////////////////////////////////////////////////////////////////////////////

namespace libcsc {
namespace document {

class DeliveryAdviceRepository
{
public:
    DeliveryAdviceRepository();
    virtual ~DeliveryAdviceRepository();

    virtual void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);
    virtual void injectSelectDeliveryAdviceHeadAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectDeliveryAdviceVatTotalsAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectDeliveryAdviceLinesAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectDeliveryAdviceLineSingleAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectDeliveryAdviceLineRemarksAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectDeliveryAdviceLineDiscountAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectDeliveryAdviceLineDetailsAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectDeliveryAdviceLineReturnAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectDeliveryAdviceLineIbtLinkAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectDnNumbersByReferencesAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectCustomerOrdersAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectCustomerOrderDetailsAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectDeliveryAdviceDetailsAccessor(persistence::IAccessorPtr accessor);
    virtual void injectInsertDeliveryAdviceLineIbtLinkAccessor(persistence::IAccessorPtr accessor);
    virtual void injectSelectDeliveryAdviceLineExtrasATAccessor(persistence::IAccessorPtr accessor);

    virtual void injectUpdateDeliveryAdviceHeadAccessor(persistence::IAccessorPtr accessor);

    void injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter);

    virtual DeliveryAdviceCollectionPtr findDeliveryAdvicesByDateRange(
        const basar::Int16& branchNo,
        const basar::Int32& customerNo,
        const enum ConfirmationStatusEnum& confirmationStatus,
        const basar::Date& searchPeriodStart,
        const basar::Date& searchPeriodEnd,
        const DeliveryAdviceInformationFilter& filter);

    virtual DeliveryAdviceCollectionPtr findDeliveryAdvicesByKey(
        const DeliveryAdviceKeyCollection& keys,
        const DeliveryAdviceInformationFilter& filter
    );

    virtual DeliveryAdvicePtr findDeliveryAdvice(
        const DeliveryAdviceKey& key,
        const DeliveryAdviceInformationFilter& filter,
        const bool& incrementRequestCounter,
        const bool& completedOnly
    );

    virtual std::vector<std::string> findDnNumbersByReferences(
        const basar::Int16& branchNo,
        const basar::Int32& customerNo,
        const std::vector<std::string>& deliveryAdviceReferences);

    virtual DeliveryAdviceCollectionPtr findDeliveryAdvicesForBatchAdviceCreation(const basar::Int16& branchNo, bool batchCorrectionOnly);

    virtual void saveDeliveryAdvice(
        const DeliveryAdvicePtr deliveryAdvice
    );

    // for phadex
    DeliveryAdviceLineIbtLinkCollectionPtr findCustomerOrders(const basar::UInt16 shuttleBranchNo, const basar::UInt32 shuttleOrderNo) const;
    bool findCustomerOrderDetails(DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const;
    bool findDeliveryAdviceDetails4CustomerOrder(DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const;

    DeliveryAdviceLineIbtLinkCollectionPtr findShuttleOrders(
        const basar::UInt16 branchNo, const basar::UInt32 customerNo, const basar::UInt32 cscOrderNo) const;
    bool findShuttleOrderDetails(DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const;
    bool findDeliveryAdviceDetails4ShuttleOrder(DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const;
    DeliveryAdviceLineDetailsCollectionPtr findIbtPickingData(
        DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const;

    void saveDeliveryAdviceLineIbtLink(DeliveryAdviceLineIbtLinkPtr deliveryAdviceLineIbtLink) const;
    // for phadex

private:
    DeliveryAdvicePtr buildDeliveryAdvice(
        const basar::db::sql::ResultsetRef resultset,
        const DeliveryAdviceInformationFilter& filter,
        const bool& incrementRequestCounter
    );

    DeliveryAdvicePtr buildDeliveryAdviceKeysOnly(const basar::db::sql::ResultsetRef resultset);

    DeliveryAdviceVatTotalsCollectionPtr findDeliveryAdviceVatTotals(
        const DeliveryAdvicePtr& deliveryAdvice);

    DeliveryAdviceRemarksCollectionPtr findDeliveryAdviceHeadRemarks(
        const DeliveryAdvicePtr& deliveryAdvice);

    DeliveryAdviceLineCollectionPtr findDeliveryAdviceLines(
        const DeliveryAdvicePtr& deliveryAdvice,
        const DeliveryAdviceInformationFilter& filter);

    DeliveryAdviceLinePtr findDeliveryAdviceLineIbt(
        const DeliveryAdviceLineIbtLinkPtr& ibtLink,
        const DeliveryAdviceInformationFilter& filter);

    DeliveryAdviceRemarksCollectionPtr findDeliveryAdviceLineRemarks(
        const DeliveryAdviceLinePtr& deliveryAdviceLine, basar::Int32 cscOrderno);

    DeliveryAdviceLineDiscountCollectionPtr findDeliveryAdviceLineDiscounts(
        const DeliveryAdviceLinePtr& deliveryAdviceLine);

    DeliveryAdviceLineDetailsCollectionPtr findDeliveryAdviceLineDetails(
        const DeliveryAdviceLinePtr& deliveryAdviceLine);

    DeliveryAdviceLineDetailsCollectionPtr findDeliveryAdviceLineDetails(
        const DeliveryAdviceLineIbtLinkPtr& deliveryAdviceLineIbtLink);

    DeliveryAdviceLineReturnCollectionPtr findDeliveryAdviceLineReturn(
        const DeliveryAdviceLinePtr& deliveryAdviceLine);

    DeliveryAdviceLineIbtLinkPtr findDeliveryAdviceLineIbtLink(
        const DeliveryAdviceLinePtr& deliveryAdviceLine, basar::Int32 cscOrderNo);

    DeliveryAdviceLineIbtLinkCollectionPtr createEmptyDeliveryAdviceLineIbtLinks() const;
    DeliveryAdviceLineIbtLinkPtr createEmptyDeliveryAdviceLineIbtLink() const;

    DeliveryAdviceLineExtrasATPtr findDeliveryAdviceLineExtrasAT(const DeliveryAdviceLinePtr& deliveryAdviceLine);

    persistence::ITransactionFactoryPtr m_TransactionFactory;

    persistence::IAccessorPtr m_SelectDeliveryAdviceHeadAccessor;
    persistence::IAccessorPtr m_SelectDeliveryAdviceVatTotalsAccessor;
    persistence::IAccessorPtr m_SelectDeliveryAdviceLinesAccessor;
    persistence::IAccessorPtr m_SelectDeliveryAdviceLineSingleAccessor;
    persistence::IAccessorPtr m_SelectDeliveryAdviceLineRemarksAccessor;
    persistence::IAccessorPtr m_SelectDeliveryAdviceLineDiscountAccessor;
    persistence::IAccessorPtr m_SelectDeliveryAdviceLineDetailsAccessor;
    persistence::IAccessorPtr m_SelectDeliveryAdviceLineReturnAccessor;
    persistence::IAccessorPtr m_SelectDeliveryAdviceLineIbtLinkAccessor;
    persistence::IAccessorPtr m_SelectDnNumbersByReferencesAccessor;
    persistence::IAccessorPtr m_SelectCustomerOrdersAccessor;
    persistence::IAccessorPtr m_SelectCustomerOrderDetailsAccessor;
    persistence::IAccessorPtr m_SelectDeliveryAdviceDetailsAccessor;
    persistence::IAccessorPtr m_InsertDeliveryAdviceLineIbtLinkAccessor;
    persistence::IAccessorPtr m_SelectDeliveryAdviceLineExtrasATAccessor;
    persistence::IAccessorPtr m_UpdateDeliveryAdviceHeadAccessor;

    parameter::IBranchParameterGetterPtr m_BranchParameterGetter;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DELIVERYADVICE_REPOSITORY_H
