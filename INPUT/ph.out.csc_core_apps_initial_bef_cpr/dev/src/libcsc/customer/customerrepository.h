#ifndef GUARD_LIBCSC_CUSTOMER_CUSTOMERREPOSITORY_H
#define GUARD_LIBCSC_CUSTOMER_CUSTOMERREPOSITORY_H

#include <customer/icustomerrepository.h>
#include <parameter/ibranchparametergetterptr.h>
#include <persistence/iaccessorptr.h>


namespace libcsc {
namespace customer {

class CustomerRepository : public ICustomerRepository
{
public:
    CustomerRepository();
    virtual ~CustomerRepository();

    void injectFindAccessor(persistence::IAccessorPtr accessor);

    void injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter);

    virtual CustomerCollectionPtr findCustomer(const basar::Int16 branchNo, const basar::Int32 customerNo,
        bool withTender, bool withCreditLimit, bool withLogisticSurcharge);

    virtual CustomerConditionCollectionPtr findCustomerConditions(const basar::Int16 branchNo,
        const basar::Int32 customerNoFrom, const basar::Int32 articleNoFrom, const basar::Int32 maxPriceElements,
        const basar::Int32 customerNoFilter);

    virtual TenderInfoCollectionPtr findTenderInfo(const basar::Int16 branchNo,
        const basar::Int32 customerNo, const basar::VarString& contractNo, const basar::Int32 articleNo);

    virtual ArticleInfoCollectionPtr findArticleInfo(const basar::Int16 branchNo, const basar::Int32 articleNo);

    virtual std::vector<basar::Int32> findArticleNosByPeriod(const basar::Int16& branchNo, const basar::Int32& positionsPerPage,
        const basar::Int32& beginningArticleNo, const basar::Date& dateFrom, const basar::Date& dateTo, ArticleInquiryPeriodDateTypeEnum dateType);

    virtual ArticleOrderInfoPtr findArticleOrderInfo(const basar::Int16& branchNo, const basar::Int32& articleNo);

    virtual OrderInfoCollectionPtr findOrderInfo(const basar::Int16 branchNo,
        const basar::Date& orderDate, const basar::Int32 customerNo, const basar::Int32 articleNo);

    virtual void changeCreditLimit(const basar::Int32 partnerNo, const basar::Decimal& newLimit);

    virtual OrderStatusPtr findOrderStatus(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Int32& orderNo, const basar::Date& orderDate);

    virtual PricesAndDiscountsCollectionPtr findPricesAndDiscounts(
        const basar::Int16& branchNo, const basar::Int32& customerNo);

    virtual PaymentsCollectionPtr findPayments(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Date& dateFrom, const basar::Date& dateTo, PaymentsFilterEnum filter);

    virtual PaymentConditionsPtr findPaymentConditions(
        const basar::Int16& branchNo, const basar::Int32& customerNo);

    virtual TurnoverPtr findTurnover(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Date& dateFrom, const basar::Date& dateTo);

    virtual ChangedQuantitiesCollectionPtr findChangedQuantities(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Int32& orderNo, const basar::Date& dateFrom, const basar::Date& dateTo);

    virtual DiscountAccountPtr findDiscountAccount(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Date& dateFrom, const basar::Date& dateTo, const bool& accNatRebateGroup);

    virtual PromotionsCollectionPtr findPromotions(
        const basar::Int16& branchNo, const basar::Int32& customerNo);

    virtual RoutesCollectionPtr findRoutes(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Int16& weekday);

    virtual std::vector<std::string> findTours(
        const basar::Int16& branchNo, const basar::Int32& tourDate);

    virtual ToursCollectionPtr findCustomerToursInfo(
        const basar::Int16& branchNo, const basar::Int32& tourDate, const std::vector<std::string>& tourIds);

    virtual WeekToursCollectionPtr findCustomerToursForWeek(const basar::Int16& branchNo, const basar::Int32& customerNo);

private:
    parameter::IBranchParameterGetterPtr m_BranchParameterGetter;
    persistence::IAccessorPtr m_FindAccessor;

    CustomerRepository& operator=(const CustomerRepository&);
   
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_CUSTOMERREPOSITORY_H
