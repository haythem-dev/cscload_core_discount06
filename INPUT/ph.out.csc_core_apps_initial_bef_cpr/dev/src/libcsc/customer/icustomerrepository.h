#ifndef GUARD_LIBCSC_CUSTOMER_ICUSTOMERREPOSITORY_H
#define GUARD_LIBCSC_CUSTOMER_ICUSTOMERREPOSITORY_H

#include <libbasar_definitions.h>
#include <customer/customercollectionptr.h>
#include <customer/customercondition/customerconditioncollectionptr.h>
#include <customer/tenderinfo/tenderinfocollectionptr.h>
#include <customer/articleinfo/articleinfocollectionptr.h>
#include <customer/articleinfo/articleorderinfoptr.h>
#include <customer/orderinfo/orderinfocollectionptr.h>
#include <customer/orderstatus/orderstatusptr.h>
#include <customer/pricesanddiscounts/pricesanddiscountscollectionptr.h>
#include <customer/payments/paymentscollectionptr.h>
#include <customer/paymentconditions/paymentconditionsptr.h>
#include <customer/turnover/turnoverptr.h>
#include <customer/changedquantities/changedquantitiescollectionptr.h>
#include <customer/discountaccount/discountaccountptr.h>
#include <customer/promotions/promotionscollectionptr.h>
#include <customer/routes/routescollectionptr.h>
#include <customer/tours/tourscollectionptr.h>
#include <customer/tours/weektours/weektourscollectionptr.h>
#include "types/articleinquiryperioddatetypeenum.inc"
#include "types/paymentsfilterenum.inc"

namespace libcsc {
namespace customer {

class ICustomerRepository
{
public:
    virtual ~ICustomerRepository() {};

    virtual CustomerCollectionPtr findCustomer(const basar::Int16 branchNo, const basar::Int32 customerNo,
        bool withTender, bool withCreditLimit, bool withLogisticSurcharge) = 0;

    virtual CustomerConditionCollectionPtr findCustomerConditions(const basar::Int16 branchNo,
        const basar::Int32 customerNoFrom, const basar::Int32 articleNoFrom, const basar::Int32 maxPriceElements,
        const basar::Int32 customerNoFilter) = 0;

    virtual TenderInfoCollectionPtr findTenderInfo(const basar::Int16 branchNo,
        const basar::Int32 customerNo, const basar::VarString& contractNo, const basar::Int32 articleNo) = 0;

    virtual ArticleInfoCollectionPtr findArticleInfo(const basar::Int16 branchNo,
        const basar::Int32 articleNo) = 0;

    virtual std::vector<basar::Int32> findArticleNosByPeriod(const basar::Int16& branchNo, const basar::Int32& positionsPerPage,
        const basar::Int32& beginningArticleNo, const basar::Date& dateFrom, const basar::Date& dateTo, ArticleInquiryPeriodDateTypeEnum dateType) = 0;

    virtual ArticleOrderInfoPtr findArticleOrderInfo(const basar::Int16& branchNo, const basar::Int32& articleNo) = 0;

    virtual OrderInfoCollectionPtr findOrderInfo(const basar::Int16 branchNo,
        const basar::Date& orderDate, const basar::Int32 customerNo, const basar::Int32 articleNo) = 0;

    virtual void changeCreditLimit(const basar::Int32 partnerNo, const basar::Decimal& newLimit) = 0;

    virtual OrderStatusPtr findOrderStatus(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Int32& orderNo, const basar::Date& orderDate) = 0;

    virtual PricesAndDiscountsCollectionPtr findPricesAndDiscounts(
        const basar::Int16& branchNo, const basar::Int32& customerNo) = 0;

    virtual PaymentsCollectionPtr findPayments(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Date& dateFrom, const basar::Date& dateTo, PaymentsFilterEnum filter) = 0;
    
    virtual PaymentConditionsPtr findPaymentConditions(
        const basar::Int16& branchNo, const basar::Int32& customerNo) = 0;

    virtual TurnoverPtr findTurnover(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Date& dateFrom, const basar::Date& dateTo) = 0;

    virtual ChangedQuantitiesCollectionPtr findChangedQuantities(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Int32& orderNo, const basar::Date& dateFrom, const basar::Date& dateTo) = 0;

    virtual DiscountAccountPtr findDiscountAccount(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Date& dateFrom, const basar::Date& dateTo, const bool& accNatRebateGroup) = 0;

    virtual PromotionsCollectionPtr findPromotions(
        const basar::Int16& branchNo, const basar::Int32& customerNo) = 0;

    virtual RoutesCollectionPtr findRoutes(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::Int16& weekday) = 0;

    virtual std::vector<std::string> findTours(
        const basar::Int16& branchNo, const basar::Int32& tourDate) = 0;

    virtual ToursCollectionPtr findCustomerToursInfo(
        const basar::Int16& branchNo, const basar::Int32& tourDate, const std::vector<std::string>& tourIds) = 0;

    virtual WeekToursCollectionPtr findCustomerToursForWeek(const basar::Int16& branchNo, const basar::Int32& customerNo) = 0;
};

} // end namespace customer
} // end namespace libcsc

#endif // GUARD_LIBCSC_CUSTOMER_ICUSTOMERREPOSITORY_H
