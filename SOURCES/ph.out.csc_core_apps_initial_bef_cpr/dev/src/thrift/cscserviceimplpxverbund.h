#ifndef GUARD_CSCSERVICE_IMPL_PXVERBUND
#define GUARD_CSCSERVICE_IMPL_PXVERBUND

#include "cscbase_types.h"
#include "csccallback_types.h"
#include "cscorder_types.h"
#include "cscinquiry_types.h"
#include "documentarchiveinformation_types.h"
#include "narcoticsarchive_types.h"
#include "deliveryadvice_types.h"
#include "cscmsv3_types.h"
#include "csccustomer_types.h"
#include "returns_types.h"
#include "shipmenttracking_types.h"

#include <pxordertransmitptr.h>
#include "csclibtothrifthandlerbase.h"
#include "cremahandlerptr.h"
#include "callbackhandlerptr.h"
#include "returnshandlerptr.h"
#include "documenthandlerptr.h"
#include "inquirybulkhandlerptr.h"
#include "inquiryhandlerptr.h"
#include "orderhandlerptr.h"
#include "msv3handlerptr.h"
#include "shipmenttrackinghandlerptr.h"
#include "customerhandlerptr.h"


namespace csc {
namespace service {

class CscServiceImplPxVerbund
{
public:
    CscServiceImplPxVerbund();
    virtual ~CscServiceImplPxVerbund();

    void setParentPort(const int32_t port);

    // base
    void processOpenSession(
        csc::base::SessionResponse& _return,
        const csc::base::SessionRequest& request);

    void processCloseSession(
        csc::base::SessionResponse& _return);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // log helper, only for test environment
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void setExplainOn(
        );

    void setExplainOff(
        );

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // batch
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void processPlaceNewOrder(
        csc::order::PlaceOrderResponse& _return,
        const csc::order::PlaceOrderRequest& request);

    void processArticleInquiry(
        csc::inquiry::ArticleInquiryResponse& _return,
        const csc::inquiry::ArticleInquiryRequest& request);

    void processArticleAvailabilityBulk(
        csc::inquiry::ArticleAvailabilityBulkResponse& _return,
        const csc::inquiry::ArticleAvailabilityBulkRequest& request);

    void processArticleAvailabilityBulkRange(
        csc::inquiry::ArticleAvailabilityBulkRangeResponse& _return,
        const csc::inquiry::ArticleAvailabilityBulkRangeRequest& request);

    void processArticleStockBulk(
        csc::inquiry::ArticleStockBulkResponse& _return,
        const csc::inquiry::ArticleStockBulkRequest& request);

    void processArticleStockDetails(
        ::csc::inquiry::ArticleStockDetailsResponse& _return,
        const  ::csc::inquiry::ArticleStockDetailsRequest& request);

    void processArticleInquiryCroatia(
        csc::inquiry::ArticleInquiryResponse& _return,
        const csc::inquiry::ArticleInquiryHRRequest& request);

    void findSubsequentDeliveryArticleQtyAggregation( ::csc::customer::SubsequentDeliveryArticleQtyAggregationResponse& _return, const ::csc::customer::SubsequentDeliveryRequest& request );
    void findSubsequentDeliveries(::csc::customer::SubsequentDeliveryResponse& _return, const csc::customer::SubsequentDeliveryRequest& request);
    void adjustSubsequentDeliveries(::csc::customer::SubsequentDeliveryAdjustmentResponse& _return, const csc::customer::SubsequentDeliveryAdjustmentRequest& request);
    void findCustomerArticlePrices(::csc::customer::CustomerArticlePricesResponse& _return, const ::csc::customer::CustomerArticlePricesRequest& request);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // MSV3
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void getXmlInfoLevel(
        ::csc::msv3::XmlInfoLevelResponse& _return,
        const ::csc::msv3::XmlInfoLevelRequest& request);

    void getMsv3ContractData(
        ::csc::msv3::Msv3ContractDataResponse& _return,
        const csc::msv3::Msv3ContractDataRequest& request);

    void processPrepareMSV3Transmission(
        ::csc::msv3::Msv3TransmissionPreparationResponse& _return,
        const ::csc::msv3::Msv3TransmissionPreparationRequest& request);

    void processMSV3OrderStatus(
        ::csc::msv3::Msv3OrderStatusResponse& _return,
        const ::csc::msv3::Msv3OrderStatusRequest& request);

    void processPostProcessMSV3Transmission (
        const ::csc::msv3::Msv3TransmissionPostProcessingRequest& request);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Callback
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void processGetCallback(
        callback::GetCallbackResponse& _return,
        callback::GetCallbackRequest const& request);

    void processGetCallbackDivisions(
        callback::CallbackDivisionInquiryResponse& _return,
        callback::CallbackDivisionInquiryRequest const& request);

    void processGetCallbackReasons(
        callback::CallbackReasonInquiryResponse& _return,
        callback::CallbackReasonInquiryRequest const& request);

    void porcessGetCallbackStatuses(
		callback::CallbackStatusInquiryResponse& _return,
		callback::CallbackStatusInquiryRequest const& request);
	void processGetCallbackStatusVisibility(
		callback::CallbackStatusVisibilityInquiryResponse& _return,
		callback::CallbackStatusVisibilityInquiryRequest const& request);
    void processFindCallbackCustomers(
        callback::FindCustomersResponse& _return,
        callback::FindCustomersRequest const& request);

    void processWriteNewCallbackCritPos(
        callback::NewCallbackCritPosResponse& _return,
        const callback::NewCallbackCritPosRequest& request);

    void processWriteNewCallback(
        callback::NewCallbackResponse& _return,
        const callback::NewCallbackRequest& request);

    void processFindCallbacks(
        callback::FindCallbacksResponse& _return,
        const callback::FindCallbacksRequest& request);

    void processGetCallbackDivisionAndReasonName(
        callback::GetCallbackDivisionAndReasonNameResponse& _return,
        const callback::GetCallbackDivisionAndReasonNameRequest& request);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Documents
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void getDeliveryAdvices(
        ::documents::DeliveryAdvicesResponse& _return,
        const ::documents::DeliveryAdvicesRequest& request);

    void getSpecificDeliveryAdvices(
        ::documents::DeliveryAdvicesResponse& _return,
        const ::documents::DeliveryAdviceSpecificRequest& request);

    void getDataForBatchAdviceCreation(
        ::documents::BatchAdviceResponse& _return,
        const ::documents::BatchAdviceRequest& request);

    void updateDeliveryAdvices(
        ::documents::UpdateDeliveryAdvicesResponse & _return,
        const ::documents::UpdateDeliveryAdvicesRequest& request);

    void confirmDeliveryAdviceReceipt(
        ::documents::DeliveryAdviceReceiveConfirmationResponse& _return,
        const  ::documents::DeliveryAdviceReceiveConfirmationRequest& request);

    void setDocumentInformation(
        ::documents::SetDocumentInformationResponse& _return,
        const  ::documents::SetDocumentInformationRequest& request);

    void getDocumentInformation(
        ::documents::GetDocumentInformationResponse& _return,
        const  ::documents::GetDocumentInformationRequest& request);

    void setNarcoticTransactionStatus(
        ::narcotics::SetNarcoticTransactionStatusResponse& _return,
        const  ::narcotics::SetNarcoticTransactionStatusRequest& request);

    void getNarcoticTransaction(
        ::narcotics::GetNarcoticTransactionResponse& _return,
        const  ::narcotics::GetNarcoticTransactionRequest& request);
  

    void processDeliveryAdvicesCroatia(
        ::documents::DeliveryAdvicesHRResponse& _return,
        const ::documents::DeliveryAdvicesHRRequest& request);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Customer returns
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void processReturnsRequest(
        ::csc::returns::ReturnsResponse& _return,
        const ::csc::returns::ReturnsRequest& request);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Shipment tracking
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void getShipmentTracking(
        warehouse::shipmenttracking::ShipmentTrackingResponse& _return,
        const warehouse::shipmenttracking::ShipmentTrackingRequest & request);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Customer
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void processCustomerDetails(
        csc::customer::CustomerDetailsResponse& _return,
        const csc::customer::CustomerDetailsRequest& request);

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
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // maybe needed for online later...
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void processOrderOpen(
        csc::order::OpenOrderResponse& _return,
        const csc::order::OpenOrderRequest& request);

    void processOrderPosition(
        csc::order::OrderPositionResponse& response,
        const csc::order::OrderPositionRequest& request);

    void processOrderClose(
        csc::order::PlaceOrderResponse& _return,
        const csc::order::CloseOrderRequest& request);

    void isArticleExportPermitted(
        csc::order::ArticleExportPermittedResponse& _return,
        const  csc::order::ArticleExportPermittedRequest& request);

    void processArticleInquiryOpen(
        inquiry::ArticleInquiryResponse& response,
        const inquiry::ArticleInquiryRequest& request);

    void processArticleInquiryPosition(
        inquiry::ArticleInquiryPositionResponse& response,
        const inquiry::ArticleInquiryPositionRequest request);

    void processArticleInquiryClose(
        inquiry::ArticleInquiryResponse& response,
        const inquiry::ArticleInquiryRequest& request);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Crema
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void processOpenCremaOrder(
        csc::crema::OpenCremaOrderResponse& _return,
        const ::csc::crema::OpenCremaOrderRequest& request);

    void processCremaUserSuggestion(
        csc::crema::UserSuggestionResponse& _return,
        const ::csc::crema::UserSuggestionRequest& request);

    void processOpenCremaOrders(
        csc::crema::OpenCremaOrdersResponse& _return,
        const ::csc::crema::OpenCremaOrdersRequest& request);

    void processFinishedTodayCremaOrders(
        csc::crema::FinishedTodayCremaOrdersResponse& _return,
        const ::csc::crema::FinishedTodayCremaOrdersRequest& request);

    void processCremaLastDecision(
        csc::crema::LastDecisionResponse& _return,
        const ::csc::crema::LastDecisionRequest& request);

    void processFinishCremaOrder(
        csc::crema::FinishOrderResponse& _return,
        const ::csc::crema::FinishOrderRequest& request);


private:
    MSV3HandlerPtr              getMSV3Handler();
    InquiryHandlerPtr           getInquiryHandler();
    InquiryBulkHandlerPtr       getInquiryBulkHandler();
    CallbackHandlerPtr          getCallbackHandler();
    OrderHandlerPtr             getOrderHandler();
    DocumentHandlerPtr          getDocumentHandler();
    ReturnsHandlerPtr           getReturnsHandler();
    ShipmentTrackingHandlerPtr  getShipmentTrackingHandler();
    CustomerHandlerPtr          getCustomerHandler();
    CremaHandlerPtr             getCremaHandler();

    template <class T>
    boost::shared_ptr<T>        GetOrCreateCscLibToThriftHandler(boost::shared_ptr<T>& handlerPtr);

private:
    pxOrderTransmitPtr          m_Session;
    MSV3HandlerPtr              m_MSV3Handler;
    InquiryHandlerPtr           m_InquiryHandler;
    InquiryBulkHandlerPtr       m_InquiryBulkHandler;
    CallbackHandlerPtr          m_CallbackHandler;
    OrderHandlerPtr             m_OrderHandler;
    DocumentHandlerPtr          m_DocumentHandler;
    ReturnsHandlerPtr           m_ReturnsHandler;
    ShipmentTrackingHandlerPtr  m_ShipmentTrackingHandler;
    CustomerHandlerPtr          m_CustomerHandler;
    CremaHandlerPtr             m_CremaHandler;
    int32_t                     m_ParentPort;
};


} // namespace service
} // namespace csc

#endif // GUARD_CSCSERVICE_IMPL_PXVERBUND
