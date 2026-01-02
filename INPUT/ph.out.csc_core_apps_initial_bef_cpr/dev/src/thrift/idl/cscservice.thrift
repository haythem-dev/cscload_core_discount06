include "cscbase.thrift"
include "csccallback.thrift"
include "cscinquiry.thrift"
include "cscmsv3.thrift"
include "cscorder.thrift"
include "documentarchiveinformation.thrift"
include "narcoticsarchive.thrift"
include "deliveryadvice.thrift"
include "returns.thrift"
include "csccustomer.thrift"
include "csctypes.thrift"
include "shipmenttracking.thrift"
include "crema.thrift"


namespace cpp csc.service
namespace csharp Csc.Service


service CscServiceBase
{
    cscbase.SessionResponse
        openSession(
            1: cscbase.SessionRequest request,
        ),

    cscbase.SessionResponse
        closeSession(
        ),

    oneway void
        setExplainOn(
        ),                  // attention, only for TEST! do NOT call it in PROD environment!

    oneway void
        setExplainOff(
        ),                  // attention, only for TEST! do NOT call it in PROD environment!
}

service CscServiceBatch extends CscServiceBase
{
    /////////////////////////////////////////////////////////////
    // Order
    /////////////////////////////////////////////////////////////
    cscorder.PlaceOrderResponse
        placeNewOrder(
            1: cscorder.PlaceOrderRequest request,
        ),

    cscorder.ArticleExportPermittedResponse
        isArticleExportPermitted(
            1: cscorder.ArticleExportPermittedRequest request,
        ),

    /////////////////////////////////////////////////////////////
    // Product availability
    /////////////////////////////////////////////////////////////
    cscinquiry.ArticleInquiryResponse
        getArticleInquiry(
            1: cscinquiry.ArticleInquiryRequest request,
        ),

    cscinquiry.ArticleAvailabilityBulkResponse
        getArticleAvaliabilityBulk(
            1: cscinquiry.ArticleAvailabilityBulkRequest request,
        ),

    cscinquiry.ArticleAvailabilityBulkRangeResponse
        getArticleAvaliabilityBulkRange(
            1: cscinquiry.ArticleAvailabilityBulkRangeRequest request,
        ),

    cscinquiry.ArticleStockBulkResponse
        getArticleStockBulk(
            1: cscinquiry.ArticleStockBulkRequest request,
        ),

    cscinquiry.ArticleStockDetailsResponse
        getArticleStockDetails(
            1: cscinquiry.ArticleStockDetailsRequest request,
        ),

    /////////////////////////////////////////////////////////////
    // DocumentService
    /////////////////////////////////////////////////////////////
    documentarchiveinformation.SetDocumentInformationResponse
        setDocumentInformation(
            1: documentarchiveinformation.SetDocumentInformationRequest request,
        ),

    documentarchiveinformation.GetDocumentInformationResponse
        getDocumentInformation(
            1: documentarchiveinformation.GetDocumentInformationRequest request,
        ),

    /////////////////////////////////////////////////////////////
    // Narcotic
    /////////////////////////////////////////////////////////////

    
    narcoticsarchive.GetNarcoticTransactionResponse
        getNarcoticTransaction(
            1: narcoticsarchive.GetNarcoticTransactionRequest request,
        ),

    narcoticsarchive.SetNarcoticTransactionStatusResponse
        setNarcoticTransactionStatus(
            1: narcoticsarchive.SetNarcoticTransactionStatusRequest request,
        ),

    /////////////////////////////////////////////////////////////
    // Customer Article Prices
    /////////////////////////////////////////////////////////////
    csccustomer.CustomerArticlePricesResponse
        findCustomerArticlePrices(
            1: csccustomer.CustomerArticlePricesRequest request,
    ),

    /////////////////////////////////////////////////////////////
    // Customer Subsequent Delivery
    /////////////////////////////////////////////////////////////
    csccustomer.SubsequentDeliveryArticleQtyAggregationResponse
        findSubsequentDeliveryArticleQtyAggregation(
            1: csccustomer.SubsequentDeliveryRequest request,
        ),

    csccustomer.SubsequentDeliveryResponse
        findSubsequentDeliveries(
            1: csccustomer.SubsequentDeliveryRequest request,
        ),

    csccustomer.SubsequentDeliveryAdjustmentResponse
        adjustSubsequentDeliveries(
            1: csccustomer.SubsequentDeliveryAdjustmentRequest request,
        ),


    /////////////////////////////////////////////////////////////
    // CustomerReturns
    /////////////////////////////////////////////////////////////

    returns.ReturnsResponse
        processReturnsRequest(
            1: returns.ReturnsRequest   request,
        ),

    /////////////////////////////////////////////////////////////
    // Shipment Tracking / Track and Trace
    /////////////////////////////////////////////////////////////

    shipmenttracking.ShipmentTrackingResponse
        getShipmentTracking(
            1: shipmenttracking.ShipmentTrackingRequest request,
        ),
		
    /////////////////////////////////////////////////////////////
    // MSV3 DeliveryAdvice
    /////////////////////////////////////////////////////////////

    deliveryadvice.DeliveryAdvicesResponse
        getDeliveryAdvices(
            1: deliveryadvice.DeliveryAdvicesRequest request,
        ),

    deliveryadvice.DeliveryAdvicesResponse
        getSpecificDeliveryAdvices(
            1: deliveryadvice.DeliveryAdviceSpecificRequest request,
        ),

    deliveryadvice.DeliveryAdviceReceiveConfirmationResponse
        confirmDeliveryAdviceReceipt(
            1: deliveryadvice.DeliveryAdviceReceiveConfirmationRequest request,
        ),

    deliveryadvice.BatchAdviceResponse
        getDataForBatchAdviceCreation(
            1: deliveryadvice.BatchAdviceRequest request,
        ),

    deliveryadvice.UpdateDeliveryAdvicesResponse
        updateDeliveryAdvices(
            1: deliveryadvice.UpdateDeliveryAdvicesRequest request,
        ),

    /////////////////////////////////////////////////////////////
    // MSV3 Deutschland
    /////////////////////////////////////////////////////////////

    cscmsv3.XmlInfoLevelResponse
        getXmlInfoLevel(
            1: cscmsv3.XmlInfoLevelRequest request,
        ),

    cscmsv3.Msv3ContractDataResponse
        getMsv3ContractData(
            1: cscmsv3.Msv3ContractDataRequest request,
        ),

    cscmsv3.Msv3TransmissionPreparationResponse
        prepareMSV3Transmission(
            1: cscmsv3.Msv3TransmissionPreparationRequest request,
        ),

    oneway void
        postProcessMSV3Transmission(
            1: cscmsv3.Msv3TransmissionPostProcessingRequest request,
        ),

    cscmsv3.Msv3OrderStatusResponse
        getMSV3OrderStatus(
            1: cscmsv3.Msv3OrderStatusRequest request,
        ),

    /////////////////////////////////////////////////////////////
    // XML Serbien
    /////////////////////////////////////////////////////////////
    csccustomer.CustomerDetailsResponse
        getCustomerDetails(
            1: csccustomer.CustomerDetailsRequest request,
        ),

    csccustomer.CustomerConditionsResponse
        getCustomerConditionsSerbia(
            1: csccustomer.CustomerConditionsRequest request,
        ),

    csccustomer.TenderInfoResponse
        getTenderInfoSerbia(
            1: csccustomer.TenderInfoRequest request,
        ),

    csccustomer.ArticleInfoResponse
        getArticleInfoSerbia(
            1: csccustomer.ArticleInfoRequest request,
        ),

    csccustomer.OrderInfoResponse
        getOrderInfoSerbia(
            1: csccustomer.OrderInfoRequest request,
        ),

    csccustomer.ChangeCreditLimitResponse
        changeCreditLimit(
            1: csccustomer.ChangeCreditLimitRequest request,
        ),

    /////////////////////////////////////////////////////////////
    // XML Bulgaria
    /////////////////////////////////////////////////////////////
    csccustomer.OrderStatusResponse
        getOrderStatusBulgaria(
            1: csccustomer.OrderStatusRequest request,
        ),

    csccustomer.PricesAndDiscountsResponse
        getPricesAndDiscountsBulgaria(
            1: csccustomer.PricesAndDiscountsRequest request,
        ),

    csccustomer.PaymentsResponse
        getPaymentsBulgaria(
            1: csccustomer.PaymentsRequest request,
        ),

    csccustomer.PaymentConditionsResponse
        getPaymentConditionsBulgaria(
            1: csccustomer.PaymentConditionsRequest request,
        ),

    csccustomer.TurnoverResponse
        getTurnoverBulgaria(
            1: csccustomer.TurnoverRequest request,
        ),

    csccustomer.ChangedQuantitiesResponse
        getChangedQuantitiesBulgaria(
            1: csccustomer.ChangedQuantitiesRequest request,
        ),

    csccustomer.DiscountAccountResponse
        getDiscountAccountBulgaria(
            1: csccustomer.DiscountAccountRequest request,
        ),

    csccustomer.PromotionsResponse
        getPromotionsBulgaria(
            1: csccustomer.PromotionsRequest request,
        ),

    csccustomer.RoutesResponse
        getRoutesBulgaria(
            1: csccustomer.RoutesRequest request,
        ),

    /////////////////////////////////////////////////////////////
    // XML Croatia
    /////////////////////////////////////////////////////////////
    deliveryadvice.DeliveryAdvicesHRResponse
        getDeliveryAdvicesCroatia(
            1: deliveryadvice.DeliveryAdvicesHRRequest request,
        ),

    cscinquiry.ArticleInquiryResponse
        getArticleInquiryCroatia(
            1: cscinquiry.ArticleInquiryHRRequest request,
        ),

    /////////////////////////////////////////////////////////////
    // Callback
    /////////////////////////////////////////////////////////////
    csccallback.GetCallbackResponse
        getCallback(
            1: csccallback.GetCallbackRequest request,
        ),

    csccallback.CallbackDivisionInquiryResponse
        getCallbackDivisions(
            1: csccallback.CallbackDivisionInquiryRequest request,
        ),

    csccallback.CallbackReasonInquiryResponse
        getCallbackReasons(
            1: csccallback.CallbackReasonInquiryRequest request,
        ),
    csccallback.CallbackStatusInquiryResponse
        getCallbackStatuses(
			1: csccallback.CallbackStatusInquiryRequest request,
		),
	csccallback.CallbackStatusVisibilityInquiryResponse
	    getCallbackStatusVisibility(
		    1: csccallback.CallbackStatusVisibilityInquiryRequest request,
		),
    csccallback.NewCallbackCritPosResponse
        writeNewCallbackCritPos(
            1: csccallback.NewCallbackCritPosRequest request,
        ),

    csccallback.NewCallbackResponse
        writeNewCallback(
            1: csccallback.NewCallbackRequest request,
        ),

    csccallback.FindCustomersResponse
        findCustomers(
            1: csccallback.FindCustomersRequest request,
        ),

    csccallback.FindCallbacksResponse
        findCallbacks(
            1: csccallback.FindCallbacksRequest request,
        ),

    csccallback.GetCallbackDivisionAndReasonNameResponse
        GetCallbackDivisionAndReasonName(
            1: csccallback.GetCallbackDivisionAndReasonNameRequest request,
        ),

    /////////////////////////////////////////////////////////////
    // Crema
    /////////////////////////////////////////////////////////////
    crema.OpenCremaOrderResponse
        getOpenCremaOrder(
            1: crema.OpenCremaOrderRequest request,
        ),

    crema.UserSuggestionResponse
        getCremaUserSuggestion(
            1: crema.UserSuggestionRequest request,
        ),

    crema.OpenCremaOrdersResponse
        getOpenCremaOrders(
            1: crema.OpenCremaOrdersRequest request,
        ),

    crema.FinishedTodayCremaOrdersResponse
        getFinishedTodayCremaOrders(
            1: crema.FinishedTodayCremaOrdersRequest request,
        ),

    crema.LastDecisionResponse
        saveCremaLastDecision(
            1: crema.LastDecisionRequest request,
        ),

    crema.FinishOrderResponse
        finishCremaOrder(
            1: crema.FinishOrderRequest request,
        ),

    /////////////////////////////////////////////////////////////
    // Customer Tours
    /////////////////////////////////////////////////////////////
    csccustomer.CustomerTourIDsResponse
        processGetTourIDs(
            1: csccustomer.CustomerTourIDsRequest request,
        ),

    csccustomer.CustomerIDFsByTourIdResponse
        processGetCustomerIDFsByTourId(
            1: csccustomer.CustomerIDFsByTourIdRequest request,
        ),

    csccustomer.CustomerToursForWeekResponse
        processGetCustomerToursForWeek(
            1: csccustomer.CustomerToursForWeekRequest request,
        ),
}

service CscServiceOnline extends CscServiceBase
{
    cscorder.OpenOrderResponse
        openOrder(
            1: cscorder.OpenOrderRequest request,
        ),

    cscorder.OrderPositionResponse
        addPosition(
            1: cscorder.OrderPositionRequest request,
        ),

    cscorder.PlaceOrderResponse
        closeOrder(
            1: cscorder.CloseOrderRequest request,
        ),
}
