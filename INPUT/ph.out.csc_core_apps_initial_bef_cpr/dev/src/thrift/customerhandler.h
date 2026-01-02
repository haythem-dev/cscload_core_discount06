#ifndef GUARD_CUSTOMERHANDLER_H
#define GUARD_CUSTOMERHANDLER_H

#include "csclibtothrifthandlerbase.h"
#include "csccustomer_types.h"
#include <libbasar_definitions.h>
#include <customer/icustomerrepositoryptr.h>
#include <boost/scoped_ptr.hpp>


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Forward declaration section
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace pxVerbund
{
    namespace subsequentDelivery
    {
        class pxDeliveryPosList;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class declaration section
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace csc {
namespace service {

class CustomerHandler : public CscLibToThriftHandlerBase
{
public:
	CustomerHandler();
	virtual ~CustomerHandler();

	void processCustomerDetails(
		::csc::customer::CustomerDetailsResponse& _return,
		const ::csc::customer::CustomerDetailsRequest& request);

    void findSubsequentDeliveryArticleQtyAggregation( ::csc::customer::SubsequentDeliveryArticleQtyAggregationResponse& _return, const ::csc::customer::SubsequentDeliveryRequest& request );
    void findSubsequentDeliveries                   ( ::csc::customer::SubsequentDeliveryResponse& _return, const csc::customer::SubsequentDeliveryRequest& request                        );
    void adjustSubsequentDeliveries                 ( ::csc::customer::SubsequentDeliveryAdjustmentResponse& _return, const csc::customer::SubsequentDeliveryAdjustmentRequest& request    );
    void findCustomerArticlePrices                  ( ::csc::customer::CustomerArticlePricesResponse& _return, const ::csc::customer::CustomerArticlePricesRequest& request                );

	void findCustomerDetails(
        ::csc::customer::CustomerDetailsResponse& _return,
        const basar::Int16 branchNo, const basar::Int32 customerNo,
        bool withTender, bool withCreditLimit, bool withLogisticSurcharge);

	void processCustomerConditionsSerbia(
		csc::customer::CustomerConditionsResponse& _return,
		const csc::customer::CustomerConditionsRequest& request);

	void processTenderInfoSerbia(
		csc::customer::TenderInfoResponse& _return,
		const csc::customer::TenderInfoRequest& request);

	void processArticleInfoSerbia(
		csc::customer::ArticleInfoResponse& _return,
		const ::csc::customer::ArticleInfoRequest& request);

	void processOrderInfoSerbia(
		csc::customer::OrderInfoResponse& _return,
		const ::csc::customer::OrderInfoRequest& request);

	void processChangeCreditLimit(
		::csc::customer::ChangeCreditLimitResponse& _return,
		const ::csc::customer::ChangeCreditLimitRequest& request);

    void processOrderStatusBulgaria(
        csc::customer::OrderStatusResponse& _return,
        const ::csc::customer::OrderStatusRequest& request);

    void processPricesAndDiscountsBulgaria(
        csc::customer::PricesAndDiscountsResponse& _return,
        const ::csc::customer::PricesAndDiscountsRequest& request);

    void processPaymentsBulgaria(
        csc::customer::PaymentsResponse& _return,
        const ::csc::customer::PaymentsRequest& request);

    void processPaymentConditionsBulgaria(
        csc::customer::PaymentConditionsResponse& _return,
        const ::csc::customer::PaymentConditionsRequest& request);

    void processTurnoverBulgaria(
        csc::customer::TurnoverResponse& _return,
        const ::csc::customer::TurnoverRequest& request);

    void processChangedQuantitiesBulgaria(
        csc::customer::ChangedQuantitiesResponse& _return,
        const ::csc::customer::ChangedQuantitiesRequest& request);

    void processDiscountAccountBulgaria(
        csc::customer::DiscountAccountResponse& _return,
        const ::csc::customer::DiscountAccountRequest& request);

    void processPromotionsBulgaria(
        csc::customer::PromotionsResponse& _return,
        const ::csc::customer::PromotionsRequest& request);

    void processRoutesBulgaria(
        csc::customer::RoutesResponse& _return,
        const ::csc::customer::RoutesRequest& request);

    void processGetTourIDs(
        csc::customer::CustomerTourIDsResponse& _return,
        const csc::customer::CustomerTourIDsRequest& request);

    void processGetCustomerIDFsByTourId(
        csc::customer::CustomerIDFsByTourIdResponse& _return,
        const csc::customer::CustomerIDFsByTourIdRequest& request);

    void processGetCustomerToursForWeek(
        csc::customer::CustomerToursForWeekResponse& _return,
        const csc::customer::CustomerToursForWeekRequest& request);

private:
    bool    isSubsequentDeliveryKeySet( const csc::customer::SubsequentDeliveryKey& subsequentDeliveryKey ) const;
    long    convertToInternalArticleNo( const std::string& articleCode ) const;

    typedef boost::scoped_ptr< ::pxVerbund::subsequentDelivery::pxDeliveryPosList >  SubsequentDeliveryScopedPtr;
    void    populateSubDelCollection( SubsequentDeliveryScopedPtr& coll,
                                      csc::customer::SubsequentDeliveryArticleQtyAggregation& subsequent_DeliveryArticleQtyAggregation );
};

} // namespace service
} // namespace csc

#endif // GUARD_CUSTOMERHANDLER_H
