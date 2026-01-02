#include "cscserviceimplpxverbund.h"
#include "cscservicehelper.h"

#include <pxxmit.hpp>
#include <pxbranch.hpp>
#include <pxdevice.hpp>
#include <pxorder.hpp>

#include "callbackhandler.h"
#include "msv3handler.h"
#include "inquiryhandler.h"
#include "inquirybulkhandler.h"
#include "orderhandler.h"
#include "documenthandler.h"
#include "returnshandler.h"

#include "articleinquiryperioddatetypeenum_types.h"

#include <logger/loggerpool.h>

#include <boost/make_shared.hpp>
#include <boost/type_traits/is_base_of.hpp>

#ifdef WIN32
#include <process.h> /* for getpid() */
#endif


namespace csc {
namespace service {

CscServiceImplPxVerbund::CscServiceImplPxVerbund() : m_ParentPort(0)
{
}

CscServiceImplPxVerbund::~CscServiceImplPxVerbund()
{
}

void CscServiceImplPxVerbund::setParentPort(const int32_t port)
{
    m_ParentPort = port;
}


void CscServiceImplPxVerbund::processOpenSession(
    csc::base::SessionResponse& _return,
    const csc::base::SessionRequest& request)
{
    basar::VarString iniFile = getenv("INI_PATH");
    if (iniFile.empty())
    {
        iniFile = "../ini";
    }
    iniFile += "/cscservice.ini";

    m_Session = boost::make_shared<pxOrderTransmit>(iniFile);
    if (false == m_Session->IsGoodState())
    {
        _return.__set_RetValue(Helper::getReturnStructFromError(*m_Session));
        return;
    }

    m_Session->Device()->Name(request.DeviceName.c_str());
    if ("CSCBATCH" == request.DeviceName || "ABBA" == request.DeviceName)
    {
        m_Session->Device()->Type(pxDVC_FILE);
    }
    else
    {
        m_Session->Device()->Type(pxDVC_DCT_SERIAL);
    }
    m_Session->PersonnelNo(request.Uid);
    m_Session->SetTransmissionType(pxOrderTransmit::tDCT_Serial);
    m_Session->SetSubDeviceType(request.DeviceName.c_str());

    _return.__set_RetValue(Helper::getReturnStructFromError(*m_Session));
    _return.__set_Pid(getpid());
    char hostn[80];
    gethostname(hostn, 79);
    _return.__set_ServerName(hostn);
    _return.__set_ServerPort(m_ParentPort);
}

void CscServiceImplPxVerbund::processCloseSession(
    csc::base::SessionResponse& _return)
{
    m_Session.reset();

    csc::base::ReturnStruct retValue;
    retValue.__set_ErrorMessage("");
    retValue.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_OK);
    _return.__set_RetValue(retValue);
    _return.__set_Pid(getpid());
    char hostn[80];
    gethostname(hostn, 79);
    _return.__set_ServerName(hostn);
    _return.__set_ServerPort(m_ParentPort);
}

//--------------------------------------------------------------------------------------------------
// log helper, only for test environment
//--------------------------------------------------------------------------------------------------

void CscServiceImplPxVerbund::setExplainOn()
{
    m_Session->nDBSetExplainOn();
}

void CscServiceImplPxVerbund::setExplainOff()
{
    m_Session->nDBSetExplainOff();
}

//--------------------------------------------------------------------------------------------------
// Order
//--------------------------------------------------------------------------------------------------
void CscServiceImplPxVerbund::processPlaceNewOrder(
    csc::order::PlaceOrderResponse& _return,
    const  csc::order::PlaceOrderRequest& request)
{
    m_Session->SetTransmissionType(pxOrderTransmit::tDCT_Serial); // TODO FN Laut Ysi "Krükke"

	// check if its a special OCP Orders (France only)
    bool isOCPOrder = (request.OpenRequest.__isset.OCPChannelID && request.OpenRequest.__isset.OCPFreightCost && request.OpenRequest.__isset.OCPCarriageFree);
    // and set if current Order is OCP (FR)
    m_Session->SetIsOCPOrder(isOCPOrder);

    // open order
    csc::order::OpenOrderResponse openResponse;
    this->processOrderOpen(openResponse, request.OpenRequest);
    _return.__set_OpenOrder(openResponse);
    if (openResponse.RetValue.ErrorCode != csc::types::MessageCodeEnum::CMSG_OK)
    {
        _return.__set_RetValue(openResponse.RetValue);
        return;
    }

    // iterate through pos
    csc::order::OrderPositionResponseList responsePositionList;

    pxOrder* order = m_Session->Order();
    pxOrderItem* orderitem = NULL;
    csc::order::OrderPositionRequestList::const_iterator it;
    for (it = request.Positions.begin(); it != request.Positions.end(); ++it)
    {
        const csc::order::OrderPositionRequest& positionRequest = *it;
        csc::order::OrderPositionResponse positionResponse;
        this->processOrderPosition(positionResponse, positionRequest);
        if (isOCPOrder && order != NULL)
        {
        	// if its an OCP order and the order item was processed successfully
            if ((orderitem = (pxOrderItem*)order->ItemList()->Last()) != NULL)
            {
            	// store for each order item the OCP informations into the order remarks
                orderitem->setOCPOrderInfo(request.OpenRequest.OCPChannelID, positionRequest.OCPOfferID, request.OpenRequest.OCPFreightCost, request.OpenRequest.OCPCarriageFree);
            }
        }
        responsePositionList.push_back(positionResponse);
    }
    _return.__set_Positions(responsePositionList);

    csc::order::CloseOrderResponse closeResponse;
    _return.__set_CloseOrder(closeResponse);
    this->processOrderClose(_return, request.CloseRequest);
    _return.__set_RetValue(_return.CloseOrder.RetValue);
}

void CscServiceImplPxVerbund::processOrderOpen(
    csc::order::OpenOrderResponse& _return,
    const csc::order::OpenOrderRequest& request)
{
    getOrderHandler()->processOrderOpen(_return, request);

    if (_return.RetValue.ErrorCode != csc::types::MessageCodeEnum::CMSG_OK)
        return;

    if (true == m_Session->IsSubDeviceTypeOf(MSV3))
    {
        getMSV3Handler()->postProcessOrderOpen(_return, request);
    }
}

void CscServiceImplPxVerbund::processOrderClose(
    csc::order::PlaceOrderResponse& _return,
    const csc::order::CloseOrderRequest& request)
{
    if (true == m_Session->IsSubDeviceTypeOf(MSV3))
    {
        getMSV3Handler()->preProcessOrderClose(_return.CloseOrder);
        if (true == _return.__isset.RetValue)
            return;
    }

    getOrderHandler()->processOrderClose(_return, request);

    if (true == m_Session->IsSubDeviceTypeOf(MSV3))
    {
        getMSV3Handler()->postProcessOrderClose(_return.CloseOrder);
    }
}


void CscServiceImplPxVerbund::processOrderPosition(
        csc::order::OrderPositionResponse& _return,
        const csc::order::OrderPositionRequest& request)
{
    switch (request.PosType)
    {
        case csc::types::PositionTypeEnum::TypeTextOnly:
            getOrderHandler()->processOrderTextPosition(_return, request);
            break;
        case csc::types::PositionTypeEnum::TypeDispoItem:
            getOrderHandler()->processOrderDispoPosition(_return, request);
            break;
        case csc::types::PositionTypeEnum::TypeProductStocked:
            getOrderHandler()->processOrderProductPosition(_return, request);
            if (true == m_Session->IsSubDeviceTypeOf(MSV3))
            {
                getMSV3Handler()->postProcessOrderProductPosition(_return);
            }
            break;
        default:
            break;
    }
}

void CscServiceImplPxVerbund::isArticleExportPermitted(
    csc::order::ArticleExportPermittedResponse& _return,
    const  csc::order::ArticleExportPermittedRequest& request)
{
    getOrderHandler()->isArticleExportPermitted(_return, request);
}

//--------------------------------------------------------------------------------------------------
// Inquiry
//--------------------------------------------------------------------------------------------------
void CscServiceImplPxVerbund::processArticleInquiry(
    ::csc::inquiry::ArticleInquiryResponse& _return,
    const  ::csc::inquiry::ArticleInquiryRequest& request)
{
    m_Session->SetTransmissionType(pxOrderTransmit::tDCT_Serial); // TODO FN Laut Ysi "Krükke"

    // open info order
    this->processArticleInquiryOpen(_return, request);
    if (_return.RetValue.ErrorCode != 0)
        return;

    // iterate through pos
    inquiry::ArticleInquiryPositionResponseList responseList;

    inquiry::ArticleInquiryPositionRequestList::const_iterator it;
    for (it = request.Positions.begin(); it != request.Positions.end(); ++it)
    {
        const csc::inquiry::ArticleInquiryPositionRequest& posRequest = *it;
        inquiry::ArticleInquiryPositionResponse posResponse;

        this->processArticleInquiryPosition(posResponse, posRequest);

        responseList.push_back(posResponse);
    }
    _return.__set_Positions(responseList);

    // close order
    this->processArticleInquiryClose(_return, request);
}

void CscServiceImplPxVerbund::processArticleInquiryOpen(
    inquiry::ArticleInquiryResponse& response,
    const inquiry::ArticleInquiryRequest& request)
{
    getInquiryHandler()->processArticleInquiryOpen(response, request);
}

void CscServiceImplPxVerbund::processArticleInquiryPosition(
    inquiry::ArticleInquiryPositionResponse& response,
    const inquiry::ArticleInquiryPositionRequest request)
{
    getInquiryHandler()->processArticleInquiryPosition(response, request);
    if (true == m_Session->IsSubDeviceTypeOf(MSV3))
    {
        getMSV3Handler()->postProcessOrderArticleInquiryPosition(response);
    }
}

void CscServiceImplPxVerbund::processArticleInquiryClose(
    inquiry::ArticleInquiryResponse& response,
    const inquiry::ArticleInquiryRequest& request)
{
    getInquiryHandler()->processArticleInquiryClose(response, request);
}

void CscServiceImplPxVerbund::processArticleInquiryCroatia(
    csc::inquiry::ArticleInquiryResponse& _return,
    const csc::inquiry::ArticleInquiryHRRequest& request)
{
    if (!request.ArticleInquiryReq.Positions.empty())
    {
        processArticleInquiry(_return, request.ArticleInquiryReq);
        return;
    }

    // No positions = byPeriod
    csc::inquiry::ArticleInquiryRequest request_;
    request_.__set_Positions(csc::inquiry::ArticleInquiryPositionRequestList());
    std::vector<basar::Int32> articleNos = getInquiryHandler()->findArticleNosByPeriodHR(request);
    std::vector<basar::Int32>::const_iterator iter = articleNos.begin();
    while (iter != articleNos.end())
    {
        std::stringstream ss;
        ss << *iter;
        csc::inquiry::ArticleInquiryPositionRequest pos;
        pos.__set_ArticleCode(ss.str());
        pos.__set_QuantityOrdered(1);
        request_.Positions.push_back(pos);
        ++iter;
    }
    request_.BranchNo = request.ArticleInquiryReq.BranchNo;
    request_.CustomerNo = request.ArticleInquiryReq.CustomerNo;
    processArticleInquiry(_return, request_);
}

//--------------------------------------------------------------------------------------------------
// Inquiry bulk
//--------------------------------------------------------------------------------------------------
void CscServiceImplPxVerbund::processArticleAvailabilityBulk(
    csc::inquiry::ArticleAvailabilityBulkResponse& _return,
    const csc::inquiry::ArticleAvailabilityBulkRequest& request)
{
    getInquiryBulkHandler()->processArticleAvailabilityBulk(_return, request);
}

void CscServiceImplPxVerbund::processArticleAvailabilityBulkRange(
    csc::inquiry::ArticleAvailabilityBulkRangeResponse& _return,
    const csc::inquiry::ArticleAvailabilityBulkRangeRequest& request)
{
    getInquiryBulkHandler()->processArticleAvailabilityBulkRange(_return, request);
}

void CscServiceImplPxVerbund::processArticleStockBulk(
    csc::inquiry::ArticleStockBulkResponse& _return,
    const csc::inquiry::ArticleStockBulkRequest& request)
{
    getInquiryBulkHandler()->processArticleStockBulk(_return, request);
}

void CscServiceImplPxVerbund::processArticleStockDetails(
    ::csc::inquiry::ArticleStockDetailsResponse& _return,
    const  ::csc::inquiry::ArticleStockDetailsRequest& request)
{
    getInquiryBulkHandler()->processArticleStockDetails(_return, request);
}

//--------------------------------------------------------------------------------------------------
// MSV3
//--------------------------------------------------------------------------------------------------
void CscServiceImplPxVerbund::getXmlInfoLevel(::csc::msv3::XmlInfoLevelResponse& _return, const ::csc::msv3::XmlInfoLevelRequest& request)
{
    getMSV3Handler()->getXmlInfoLevel(_return, request);
}


void CscServiceImplPxVerbund::getMsv3ContractData(::csc::msv3::Msv3ContractDataResponse& _return, const csc::msv3::Msv3ContractDataRequest& request)
{
    getMSV3Handler()->getMsv3ContractData(_return, request);
}


void CscServiceImplPxVerbund::processPrepareMSV3Transmission(
    csc::msv3::Msv3TransmissionPreparationResponse& _return,
    const csc::msv3::Msv3TransmissionPreparationRequest& request)
{
    getMSV3Handler()->processPrepareMSV3Transmission(_return, request);
}

void CscServiceImplPxVerbund::processMSV3OrderStatus(
    ::csc::msv3::Msv3OrderStatusResponse& _return,
    const ::csc::msv3::Msv3OrderStatusRequest& request)
{
    getMSV3Handler()->processMSV3OrderStatus(_return, request);
}

void CscServiceImplPxVerbund::processPostProcessMSV3Transmission(
    const ::csc::msv3::Msv3TransmissionPostProcessingRequest& request)
{
    getMSV3Handler()->processPostProcessMSV3Transmission(request);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Documents
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CscServiceImplPxVerbund::getDeliveryAdvices(
    ::documents::DeliveryAdvicesResponse& _return,
    const ::documents::DeliveryAdvicesRequest& request)
{
    getDocumentHandler()->getDeliveryAdvices(_return, request);
}

void CscServiceImplPxVerbund::getSpecificDeliveryAdvices(
    ::documents::DeliveryAdvicesResponse& _return,
    const ::documents::DeliveryAdviceSpecificRequest& request)
{
    getDocumentHandler()->getSpecificDeliveryAdvices(_return, request);
}

void CscServiceImplPxVerbund::getDataForBatchAdviceCreation(
    ::documents::BatchAdviceResponse& _return,
    const ::documents::BatchAdviceRequest& request)
{
    getDocumentHandler()->getDataForBatchAdviceCreation(_return, request);
}

void CscServiceImplPxVerbund::updateDeliveryAdvices(
    ::documents::UpdateDeliveryAdvicesResponse& _return,
    const ::documents::UpdateDeliveryAdvicesRequest& request)
{
    getDocumentHandler()->updateDeliveryAdvices(_return, request);
}

void CscServiceImplPxVerbund::confirmDeliveryAdviceReceipt(
    ::documents::DeliveryAdviceReceiveConfirmationResponse& _return,
    const ::documents::DeliveryAdviceReceiveConfirmationRequest& request)
{
    getDocumentHandler()->confirmDeliveryAdviceReceipt(_return, request);
}

void CscServiceImplPxVerbund::setDocumentInformation(
    ::documents::SetDocumentInformationResponse& _return,
    const  ::documents::SetDocumentInformationRequest& request)
{
    getDocumentHandler()->setDocumentInformation(_return, request);
}

void CscServiceImplPxVerbund::getDocumentInformation(
    ::documents::GetDocumentInformationResponse& _return,
    const  ::documents::GetDocumentInformationRequest& request)
{
    getDocumentHandler()->getDocumentInformation(_return, request);
}

void CscServiceImplPxVerbund::setNarcoticTransactionStatus(
    ::narcotics::SetNarcoticTransactionStatusResponse& _return,
    const  ::narcotics::SetNarcoticTransactionStatusRequest& request)
{
    getDocumentHandler()->setNarcoticTransactionStatus(_return, request);
}

void CscServiceImplPxVerbund::getNarcoticTransaction(
    ::narcotics::GetNarcoticTransactionResponse& _return,
    const  ::narcotics::GetNarcoticTransactionRequest& request)
{
    getDocumentHandler()->getNarcoticTransaction(_return, request);
}


void CscServiceImplPxVerbund::processDeliveryAdvicesCroatia(
    ::documents::DeliveryAdvicesHRResponse& _return,
    const ::documents::DeliveryAdvicesHRRequest& request)
{
    getDocumentHandler()->processDeliveryAdvicesCroatia(_return, request);
}

//--------------------------------------------------------------------------------------------------
// Customer returns
//--------------------------------------------------------------------------------------------------
void CscServiceImplPxVerbund::processReturnsRequest(
    ::csc::returns::ReturnsResponse& _return,
    const ::csc::returns::ReturnsRequest& request)
{
    getReturnsHandler()->processReturnsRequest(_return, request);
}

//--------------------------------------------------------------------------------------------------
// Shipment Tracking info
//--------------------------------------------------------------------------------------------------
void CscServiceImplPxVerbund::getShipmentTracking(
    warehouse::shipmenttracking::ShipmentTrackingResponse& _return,
    const warehouse::shipmenttracking::ShipmentTrackingRequest & request)
{
    getShipmentTrackingHandler()->getShipmentTracking(_return, request);
}

//--------------------------------------------------------------------------------------------------
// Customer
//--------------------------------------------------------------------------------------------------
void CscServiceImplPxVerbund::processCustomerDetails(
    csc::customer::CustomerDetailsResponse& _return,
    const csc::customer::CustomerDetailsRequest& request)
{
    getCustomerHandler()->processCustomerDetails(_return, request);
}

void CscServiceImplPxVerbund::processCustomerConditionsSerbia(
    csc::customer::CustomerConditionsResponse& _return,
    const csc::customer::CustomerConditionsRequest& request)
{
    getCustomerHandler()->processCustomerConditionsSerbia(_return, request);
}

void CscServiceImplPxVerbund::processTenderInfoSerbia(
    csc::customer::TenderInfoResponse& _return,
    const csc::customer::TenderInfoRequest& request)
{
    getCustomerHandler()->processTenderInfoSerbia(_return, request);
}

void CscServiceImplPxVerbund::processArticleInfoSerbia(
    csc::customer::ArticleInfoResponse& _return,
    const ::csc::customer::ArticleInfoRequest& request)
{
    getCustomerHandler()->processArticleInfoSerbia(_return, request);
}

void CscServiceImplPxVerbund::processOrderInfoSerbia(
    csc::customer::OrderInfoResponse& _return,
    const ::csc::customer::OrderInfoRequest& request)
{
    getCustomerHandler()->processOrderInfoSerbia(_return, request);
}

void CscServiceImplPxVerbund::processChangeCreditLimit(
    ::csc::customer::ChangeCreditLimitResponse& _return,
    const ::csc::customer::ChangeCreditLimitRequest& request)
{
    getCustomerHandler()->processChangeCreditLimit(_return, request);
}

void CscServiceImplPxVerbund::processOrderStatusBulgaria(
    csc::customer::OrderStatusResponse& _return,
    const ::csc::customer::OrderStatusRequest& request)
{
    getCustomerHandler()->processOrderStatusBulgaria(_return, request);
}

void CscServiceImplPxVerbund::processPricesAndDiscountsBulgaria(
    csc::customer::PricesAndDiscountsResponse& _return,
    const ::csc::customer::PricesAndDiscountsRequest& request)
{
    getCustomerHandler()->processPricesAndDiscountsBulgaria(_return, request);
}

void CscServiceImplPxVerbund::processPaymentsBulgaria(
    csc::customer::PaymentsResponse& _return,
    const ::csc::customer::PaymentsRequest& request)
{
    getCustomerHandler()->processPaymentsBulgaria(_return, request);
}

void CscServiceImplPxVerbund::processPaymentConditionsBulgaria(
    csc::customer::PaymentConditionsResponse& _return,
    const ::csc::customer::PaymentConditionsRequest& request)
{
    getCustomerHandler()->processPaymentConditionsBulgaria(_return, request);
}

void CscServiceImplPxVerbund::processTurnoverBulgaria(
    csc::customer::TurnoverResponse& _return,
    const ::csc::customer::TurnoverRequest& request)
{
    getCustomerHandler()->processTurnoverBulgaria(_return, request);
}

void CscServiceImplPxVerbund::processChangedQuantitiesBulgaria(
    csc::customer::ChangedQuantitiesResponse& _return,
    const ::csc::customer::ChangedQuantitiesRequest& request)
{
    getCustomerHandler()->processChangedQuantitiesBulgaria(_return, request);
}

void CscServiceImplPxVerbund::processDiscountAccountBulgaria(
    csc::customer::DiscountAccountResponse& _return,
    const ::csc::customer::DiscountAccountRequest& request)
{
    getCustomerHandler()->processDiscountAccountBulgaria(_return, request);
}

void CscServiceImplPxVerbund::processPromotionsBulgaria(
    csc::customer::PromotionsResponse& _return,
    const ::csc::customer::PromotionsRequest& request)
{
    getCustomerHandler()->processPromotionsBulgaria(_return, request);
}

void CscServiceImplPxVerbund::processRoutesBulgaria(
    csc::customer::RoutesResponse& _return,
    const ::csc::customer::RoutesRequest& request)
{
    getCustomerHandler()->processRoutesBulgaria(_return, request);
}


void CscServiceImplPxVerbund::processGetTourIDs(
    csc::customer::CustomerTourIDsResponse& _return,
    const csc::customer::CustomerTourIDsRequest& request)
{
    getCustomerHandler()->processGetTourIDs(_return, request);
}


void CscServiceImplPxVerbund::processGetCustomerIDFsByTourId(
    csc::customer::CustomerIDFsByTourIdResponse& _return,
    const csc::customer::CustomerIDFsByTourIdRequest& request)
{
    getCustomerHandler()->processGetCustomerIDFsByTourId(_return, request);
}

void CscServiceImplPxVerbund::processGetCustomerToursForWeek(
    csc::customer::CustomerToursForWeekResponse& _return,
    const csc::customer::CustomerToursForWeekRequest& request)
{
    getCustomerHandler()->processGetCustomerToursForWeek(_return, request);
}

//--------------------------------------------------------------------------------------------------
// Customer Article Prices
//--------------------------------------------------------------------------------------------------
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-parameter"
void CscServiceImplPxVerbund::findCustomerArticlePrices(::csc::customer::CustomerArticlePricesResponse& _return, const ::csc::customer::CustomerArticlePricesRequest& request)
{
    getCustomerHandler()->findCustomerArticlePrices(_return, request);
}
//#pragma GCC diagnostic pop

//--------------------------------------------------------------------------------------------------
// Customer Subsequent Deliveries
//--------------------------------------------------------------------------------------------------
void CscServiceImplPxVerbund::findSubsequentDeliveryArticleQtyAggregation( ::csc::customer::SubsequentDeliveryArticleQtyAggregationResponse& _return, const ::csc::customer::SubsequentDeliveryRequest& request )
{
    getCustomerHandler()->findSubsequentDeliveryArticleQtyAggregation(_return, request);
}
//--------------------------------------------------------------------------------------------------
void CscServiceImplPxVerbund::findSubsequentDeliveries(::csc::customer::SubsequentDeliveryResponse& _return, const csc::customer::SubsequentDeliveryRequest& request)
{
    getCustomerHandler()->findSubsequentDeliveries(_return, request);
}

//--------------------------------------------------------------------------------------------------
void CscServiceImplPxVerbund::adjustSubsequentDeliveries(::csc::customer::SubsequentDeliveryAdjustmentResponse& _return, const csc::customer::SubsequentDeliveryAdjustmentRequest& request)
{
    getCustomerHandler()->adjustSubsequentDeliveries(_return, request);
}

//--------------------------------------------------------------------------------------------------
// Callback
//--------------------------------------------------------------------------------------------------
void CscServiceImplPxVerbund::processGetCallback(callback::GetCallbackResponse& _return, callback::GetCallbackRequest const& request)
{
    getCallbackHandler()->processGetCallback(_return, request);
}

void CscServiceImplPxVerbund::processGetCallbackDivisions(callback::CallbackDivisionInquiryResponse& _return, callback::CallbackDivisionInquiryRequest const& request)
{
    getCallbackHandler()->processGetCallbackDivisions(_return, request);
}

void CscServiceImplPxVerbund::processGetCallbackReasons(callback::CallbackReasonInquiryResponse& _return, callback::CallbackReasonInquiryRequest const& request)
{
    getCallbackHandler()->processGetCallbackReasons(_return, request);
}

void CscServiceImplPxVerbund::porcessGetCallbackStatuses(callback::CallbackStatusInquiryResponse& _return, callback::CallbackStatusInquiryRequest const& request)
{
	getCallbackHandler()->processGetCallbackStatuses(_return, request);
}

void CscServiceImplPxVerbund::processGetCallbackStatusVisibility(callback::CallbackStatusVisibilityInquiryResponse& _return, const callback::CallbackStatusVisibilityInquiryRequest& request)
{
	getCallbackHandler()->processGetCallbackStatusVisibility(_return, request);
}

void CscServiceImplPxVerbund::processFindCallbackCustomers(callback::FindCustomersResponse& _return, callback::FindCustomersRequest const& request)
{
    getCallbackHandler()->processFindCustomers(_return, request);
}

void CscServiceImplPxVerbund::processWriteNewCallbackCritPos(callback::NewCallbackCritPosResponse& _return, const callback::NewCallbackCritPosRequest& request)
{
    getCallbackHandler()->processWriteNewCallbackCritPos(_return, request);
}

void CscServiceImplPxVerbund::processWriteNewCallback(callback::NewCallbackResponse& _return, const callback::NewCallbackRequest& request)
{
    getCallbackHandler()->processWriteNewCallback(_return, request);
}

void CscServiceImplPxVerbund::processFindCallbacks(callback::FindCallbacksResponse& _return, const callback::FindCallbacksRequest& request)
{
    getCallbackHandler()->processFindCallbacks(_return, request);
}

void CscServiceImplPxVerbund::processGetCallbackDivisionAndReasonName(callback::GetCallbackDivisionAndReasonNameResponse& _return, const callback::GetCallbackDivisionAndReasonNameRequest& request)
{
    getCallbackHandler()->processGetCallbackDivisionAndReasonName(_return, request);
}


//--------------------------------------------------------------------------------------------------
// Factory methods: Get or Create specific Handler
//--------------------------------------------------------------------------------------------------

CallbackHandlerPtr CscServiceImplPxVerbund::getCallbackHandler()
{
    return GetOrCreateCscLibToThriftHandler<CallbackHandler>(m_CallbackHandler);
}

MSV3HandlerPtr CscServiceImplPxVerbund::getMSV3Handler()
{
    return GetOrCreateCscLibToThriftHandler<MSV3Handler>(m_MSV3Handler);
}

InquiryHandlerPtr CscServiceImplPxVerbund::getInquiryHandler()
{
    return GetOrCreateCscLibToThriftHandler<InquiryHandler>(m_InquiryHandler);
}

InquiryBulkHandlerPtr CscServiceImplPxVerbund::getInquiryBulkHandler()
{
    return GetOrCreateCscLibToThriftHandler<InquiryBulkHandler>(m_InquiryBulkHandler);
}

OrderHandlerPtr CscServiceImplPxVerbund::getOrderHandler()
{
    return GetOrCreateCscLibToThriftHandler<OrderHandler>(m_OrderHandler);
}

DocumentHandlerPtr CscServiceImplPxVerbund::getDocumentHandler()
{
    return GetOrCreateCscLibToThriftHandler<DocumentHandler>(m_DocumentHandler);
}

ReturnsHandlerPtr CscServiceImplPxVerbund::getReturnsHandler()
{
    return GetOrCreateCscLibToThriftHandler<ReturnsHandler>(m_ReturnsHandler);
}

ShipmentTrackingHandlerPtr CscServiceImplPxVerbund::getShipmentTrackingHandler()
{
    return GetOrCreateCscLibToThriftHandler<ShipmentTrackingHandler>(m_ShipmentTrackingHandler);
}

CustomerHandlerPtr CscServiceImplPxVerbund::getCustomerHandler()
{
    return GetOrCreateCscLibToThriftHandler<CustomerHandler>(m_CustomerHandler);
}

CremaHandlerPtr CscServiceImplPxVerbund::getCremaHandler()
{
    return GetOrCreateCscLibToThriftHandler<CremaHandler>(m_CremaHandler);
}

//--------------------------------------------------------------------------------------------------
// Crema
//--------------------------------------------------------------------------------------------------

void CscServiceImplPxVerbund::processOpenCremaOrder(
    csc::crema::OpenCremaOrderResponse& _return,
    const ::csc::crema::OpenCremaOrderRequest& request)
{
    getCremaHandler()->processOpenCremaOrder(_return, request);
}

void CscServiceImplPxVerbund::processCremaUserSuggestion(
    csc::crema::UserSuggestionResponse& _return,
    const ::csc::crema::UserSuggestionRequest& request)
{
    getCremaHandler()->processUserSuggestion(_return, request);
}

void CscServiceImplPxVerbund::processOpenCremaOrders(
    csc::crema::OpenCremaOrdersResponse& _return,
    const ::csc::crema::OpenCremaOrdersRequest& request)
{
    getCremaHandler()->processOpenCremaOrders(_return, request);
}

void CscServiceImplPxVerbund::processFinishedTodayCremaOrders(
    csc::crema::FinishedTodayCremaOrdersResponse& _return,
    const ::csc::crema::FinishedTodayCremaOrdersRequest& request)
{
    getCremaHandler()->processFinishedTodayCremaOrders(_return, request);
}

void CscServiceImplPxVerbund::processCremaLastDecision(
    csc::crema::LastDecisionResponse& _return,
    const ::csc::crema::LastDecisionRequest& request)
{
    getCremaHandler()->processLastDecision(_return, request);
}

void CscServiceImplPxVerbund::processFinishCremaOrder(
    csc::crema::FinishOrderResponse& _return,
    const ::csc::crema::FinishOrderRequest& request)
{
    getCremaHandler()->processFinishOrder(_return, request);
}

//--------------------------------------------------------------------------------------------------
// Generic Factory Method: Get or Create Handler
//--------------------------------------------------------------------------------------------------

//NOTE: this workaround is necessary, because of AIX today (08.11.2019):
// See: Static assert in C
// https://stackoverflow.com/questions/3385515/static-assert-in-c
//   especially:
//   https://stackoverflow.com/a/3385694/3426897
#define STATIC_ASSERT(COND, NAME) typedef char static_assertion_##NAME[(COND)?1:-1]

template <class T>
boost::shared_ptr<T> CscServiceImplPxVerbund::GetOrCreateCscLibToThriftHandler(boost::shared_ptr<T>& handlerPtr)
{
    // Doing a compiler time check: T must inherit from Base (CscServiceImplPxVerbund) to allow T*->Base* conversion!

    //NOTE: the following did not work, because of AIX old compiler as of today (08.11.2019):
    // See: force template <class> to be derived from BaseClassA?
    // https://stackoverflow.com/questions/4984502/force-template-class-to-be-derived-from-baseclassa
    //   concretely:
    //   https://stackoverflow.com/a/53118489/3426897
    //static_assert(boost::is_base_of<CscLibToThriftHandlerBase, T>::value, "T must derive from csc::service::CscLibToThriftHandlerBase");

    // So, solved the check like this:
    STATIC_ASSERT((boost::is_base_of<CscLibToThriftHandlerBase, T>::value), is_base_of_condition_err);

    // Do the usefull stuff:
    if (NULL == handlerPtr.get())
    {
        handlerPtr = boost::make_shared<T>();
        handlerPtr->injectSession(m_Session);
    }

    return handlerPtr;
}

} // namespace service
} // namespace csc
