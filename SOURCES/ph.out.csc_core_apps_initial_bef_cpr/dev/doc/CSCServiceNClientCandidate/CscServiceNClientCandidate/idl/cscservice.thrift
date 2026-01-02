include "cscbase.thrift"
include "csccallback.thrift"
include "cscinquiry.thrift"
include "cscmsv3.thrift"
include "cscorder.thrift"
include "documentarchiveinformation.thrift"
include "deliveryadvice.thrift"
include "returns.thrift"
include "csctypes.thrift"
include "trackandtrace.thrift"


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
		),					// attention, only for TEST! do NOT call it in PROD environment!

	oneway void
		setExplainOff(
		),					// attention, only for TEST! do NOT call it in PROD environment!
}

service CscServiceBatch extends CscServiceBase
{
	cscorder.PlaceOrderResponse
		placeNewOrder(
			1: cscorder.PlaceOrderRequest request,
		),

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
	// CustomerReturns
	/////////////////////////////////////////////////////////////

	returns.ReturnsResponse
		processReturnsRequest(
			1: returns.ReturnsRequest	request,
		),

	/////////////////////////////////////////////////////////////
	// Track and Trace
	/////////////////////////////////////////////////////////////

    //trackandtrace.TNTDeliveryInformationResponse
    //    getTNTDeliveryInformation(
    //        1: trackandtrace.TNTDeliveryInformationRequest,
    //    ),

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
	// MSV3
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

	cscorder.CloseOrderResponse
		closeOrder(
			1: cscorder.CloseOrderRequest request,
		),
}
