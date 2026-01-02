#include "msv3handler.h"
#include "msv3orderlabelprocessor.h"
#include "cscservicehelper.h"
#include "cscmsv3_constants.h"

#include <boost/make_shared.hpp>
#include <logger/loggerpool.h>
#include <exceptions/sqlduplicateexception.h>
#include <libbasarcmnutil_datetime.h>
#include <libbasarcmnutil_timespan.h>
#include <libbasar_pkgversion.h>
#include <pxxmit.hpp>
#include <pxbranch.hpp>
#include <pxcstbas.hpp>
#include <pxcustomerflags.hpp>
#include <pxoeparm.hpp>
#include <pxcstot.hpp>
#include <pxstktra.hpp>
#include <pxorder.hpp>
#include <pxorderperiod.hpp>
#include <pxeventreason.hpp>
#include <types/messagecodeenum.inc>


#include <msv3/componentmanager/msv3componentmanager.h>

#include <msv3/transmissionresponse/transmissionresponserepository.h>
#include <msv3/transmissionresponse/transmissionresponseptr.h>
#include <msv3/transmissionresponse/transmissionresponse.h>

#include <msv3/orderresponse/orderresponserepository.h>
#include <msv3/orderresponse/orderresponseptr.h>
#include <msv3/orderresponse/orderresponse.h>

#include <msv3/customerdata/customerdatarepository.h>
#include <msv3/customerdata/customerdataptr.h>
#include <msv3/customerdata/customerdata.h>

namespace csc {
namespace service {

MSV3Handler::MSV3Handler()
{
}

MSV3Handler::~MSV3Handler()
{
}

//-----------------------------------------------------------------------------
// MSV3 preprocessing for a complete transmission
//-----------------------------------------------------------------------------
void MSV3Handler::processPrepareMSV3Transmission(
    msv3::Msv3TransmissionPreparationResponse& _return,
    const msv3::Msv3TransmissionPreparationRequest& request)
{
    getSession()->SetIgnoreOrderPeriodDDfromDB(request.BranchNo);

    if (request.__isset.BranchNo)
    {
        csc::base::ReturnStruct branchCheckResult = Helper::checkBranch(getSession(), request.BranchNo);
        if (branchCheckResult.ErrorCode != nError().ErrorNumber())
        {
            _return.__set_RetValue(branchCheckResult);
            return;
        }
    }
    basar::Int16 AlterVZ = 0;
    AlterVZ = getSession()->CustomerRouting(request.CustomerNo);
    if (AlterVZ > 0)
    {
        _return.__set_BranchNo(AlterVZ);
    }
    else
    {
        _return.__set_BranchNo(request.BranchNo);
    }
    _return.__set_CustomerNo(request.CustomerNo);

    if (false == getSession()->IsNewOrder(_return.BranchNo))
    {
        csc::base::ReturnStruct retVal;
        retVal.__set_ErrorMessage("OpenOrder Out of Time");
        retVal.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION);
        _return.__set_RetValue(retVal);
        return;
    }

    // setze Kunde
    pxCustBase* customer = getSession()->CustomerId(_return.CustomerNo, _return.BranchNo);
    if (customer == NULL)
    {
        _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
        return;
    }

    if (request.__isset.InternalHash && request.__isset.InternalHashCheckTime)
    {
        basar::DateTime now = basar::DateTime::getCurrent();
        now -= basar::TimeSpan(request.InternalHashCheckTime, basar::TimeSpan::TSUNIT_MIN);
        libcsc::msv3::TransmissionResponsePtr transmissionResponse =
            getMSV3ComponentManager()->getTransmissionResponseRepository()->findByInternalHash(
                request.BranchNo, request.CustomerNo, request.InternalHash, now);
        if (transmissionResponse.get() != NULL)
        {
            csc::base::ReturnStruct retVal;
            getSession()->ExternalError(getSession()->CMsgStream(), CMSG_XMIT_MSV3_DUPLICATE_TRANSMISSION, request.InternalHash.c_str());
            _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
            return;
        }
    }


    libcsc::msv3::TransmissionResponsePtr transmissionResponse =
        getMSV3ComponentManager()->getTransmissionResponseRepository()->createEmptyTransmissionResponse();

    // insert transmission into orderresponses
    transmissionResponse->setBranchNo(request.BranchNo);
    transmissionResponse->setCustomerNo(request.CustomerNo);
    transmissionResponse->setTransmissionGuid(request.TransmissionGuid);
    transmissionResponse->setTransmissionSupportId(request.TransmissionSupportId);

    transmissionResponse->setIsOffer(false);
    msv3::Msv3OrderPreparationRequestMap::const_iterator it = request.MSV3Orders.begin();
    if (it != request.MSV3Orders.end())
    {
        if (it->first == msv3::Msv3OrderTypeEnum::RUECKNAHME)
            transmissionResponse->setIsOffer(true);
    }
    transmissionResponse->setResponseAsXml("");
    transmissionResponse->setCreationDate(basar::DateTime::getCurrent().getDate());
    transmissionResponse->setCreationTime(basar::DateTime::getCurrent().getTime() / 1000);
    if (request.__isset.InternalHash)
    {
        transmissionResponse->setInternalHash(request.InternalHash);
    }
    else
    {
        transmissionResponse->setInternalHash("");
    }
    try
    {
        getMSV3ComponentManager()->getTransmissionResponseRepository()->saveTransmissionResponse(transmissionResponse);
    }
    catch (const libcsc::exceptions::SqlDuplicateException&)
    {
        csc::base::ReturnStruct retVal;
        getSession()->ExternalError(getSession()->CMsgStream(), CMSG_XMIT_MSV3_DUPLICATE_TRANSMISSION, request.TransmissionGuid.c_str());
        _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
        return;
    }


    pxOrderPeriod orderperiod(getSession().get());
    orderperiod = getSession()->getMSV3OrderPeriod();
    _return.__set_OrderPeriodId(orderperiod.ID());

    // iterate through order types
    msv3::Msv3OrderPreparationResponseMap responseMap;
    for (it = request.MSV3Orders.begin(); it != request.MSV3Orders.end(); ++it)
    {
        msv3::Msv3OrderPreparationResponseList orderResponseList;
        this->processPrepareMSV3OrderType(orderResponseList, it->first, it->second, _return.OrderPeriodId, transmissionResponse->getId());
        responseMap.insert(
            std::pair<msv3::Msv3OrderTypeEnum::type, msv3::Msv3OrderPreparationResponseList>(it->first, orderResponseList)
        );
    }
    _return.__set_MSV3Orders(responseMap);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
}

//-----------------------------------------------------------------------------
// MSV3 preprocessing for a specific order type (contains a list of orders with
// that order type)
//-----------------------------------------------------------------------------
void MSV3Handler::processPrepareMSV3OrderType(
    msv3::Msv3OrderPreparationResponseList& _return,
    const msv3::Msv3OrderTypeEnum::type ordertype,
    const msv3::Msv3OrderPreparationRequestList& requestList,
    const long orderperiodid,
    const long transmissionid)
{
    basar::VarString cscOrderType = msv3::g_cscmsv3_constants.Msv3ToCSCOrderTypeMap.find(ordertype)->second;
    bool orderTypeNotAllowed = (false == getSession()->isOrderTypeAllowedForMSV3(cscOrderType.c_str()));
    getSession()->ClearError(); // session might be in "not good state"

    MSV3OrderLabelProcessor orderLabelProcessor;
    orderLabelProcessor.init(getSession().get(), cscOrderType, orderperiodid);

    // iterate through order requests
    msv3::Msv3OrderPreparationRequestList::const_iterator it;
    for (it = requestList.begin(); it != requestList.end(); ++it)
    {
        const msv3::Msv3OrderPreparationRequest& orderRequest = *it;
        msv3::Msv3OrderPreparationResponse orderPrepResponse;

        orderPrepResponse.__set_GebindeId(orderRequest.GebindeId);
        orderPrepResponse.__set_OrderSupportId(orderRequest.OrderSupportId);
        orderPrepResponse.__set_OrderGuid(orderRequest.OrderGuid);
        orderPrepResponse.__set_OrderLabel(orderRequest.OrderLabel);

        // 1. check order type allowed?
        if (true == orderTypeNotAllowed)
        {
            nError error;
            error.ExternalError(getSession()->CMsgStream(), CMSG_XMIT_MSV3_ORDERTYPE_NOT_ALLOWED);
            orderPrepResponse.__set_RetValue(Helper::getReturnStructFromError(error));
            _return.push_back(orderPrepResponse);
            continue;
        }

        // 2. check for duplicate order
        libcsc::msv3::OrderResponsePtr orderResponse =
            getMSV3ComponentManager()->getOrderResponseRepository()->createEmptyOrderResponse();
        //  getMSV3ComponentManager()->getOrderResponseRepository()->findOrderResponse(orderRequest.OrderGuid);
        //if (orderResponse->getId().isClean())
        //{
        //  nError error;
        //  error.ExternalError(getSession()->CMsgStream(), CMSG_XMIT_MSV3_DUPLICATE_ORDER, orderRequest.OrderGuid.c_str());
        //  orderPrepResponse.__set_RetValue(Helper::getReturnStructFromError(error));
        //  _return.push_back(orderPrepResponse);
        //  continue;
        //}

        // 3. insert into table orderresponsesuuid
        orderResponse->setBundleId(orderPrepResponse.GebindeId);
        orderResponse->setOrderSupportId(orderPrepResponse.OrderSupportId);
        orderResponse->setOrderUuid(orderPrepResponse.OrderGuid);
        orderResponse->setTransmissionId(transmissionid);
        orderResponse->setCscOrderNo(-1);
        orderResponse->setOrderLabel(orderPrepResponse.OrderLabel);
        try
        {
            getMSV3ComponentManager()->getOrderResponseRepository()->saveOrderResponse(orderResponse);
        }
        catch (const libcsc::exceptions::SqlDuplicateException&)
        {
            nError error;
            error.ExternalError(getSession()->CMsgStream(), CMSG_XMIT_MSV3_DUPLICATE_ORDER, orderRequest.OrderGuid.c_str());
            orderPrepResponse.__set_RetValue(Helper::getReturnStructFromError(error));
            _return.push_back(orderPrepResponse);
            continue;
        }

        // 4. check order label
        basar::VarString label = orderLabelProcessor.processLabel(orderRequest.OrderLabel);
        orderPrepResponse.__set_OrderLabel(label);
        if (orderPrepResponse.OrderLabel != orderRequest.OrderLabel)
        {
            orderPrepResponse.__set_OriginalOrderLabel(orderRequest.OrderLabel);
        }
        orderPrepResponse.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
        _return.push_back(orderPrepResponse);
    }
}

//-----------------------------------------------------------------------------
// MSV3 post processing after all orders of a transmissin were placed.
// Saves the generated MSV3 XML response in tabel orderresponses.
//-----------------------------------------------------------------------------
void MSV3Handler::processPostProcessMSV3Transmission(
    const msv3::Msv3TransmissionPostProcessingRequest& request)
{
    //getSession()->nDBBeginTransaction(cDBTransSet);

    // 1. update orderresponses
    libcsc::msv3::TransmissionResponsePtr transmissionResponse =
        getMSV3ComponentManager()->getTransmissionResponseRepository()->findTransmissionResponse(request.TransmissionGuid);
    if (0 != transmissionResponse.get())
    {
        transmissionResponse->setResponseAsXml(request.XmlResponse);
        getMSV3ComponentManager()->getTransmissionResponseRepository()->saveTransmissionResponse(transmissionResponse);
    }

    msv3::Msv3OrderPostProcessingRequestList::const_iterator it;
    for (it = request.MSV3Orders.begin(); it != request.MSV3Orders.end(); ++it)
    {
        const msv3::Msv3OrderPostProcessingRequest& orderRequest = *it;
        libcsc::msv3::OrderResponsePtr orderResponse =
            getMSV3ComponentManager()->getOrderResponseRepository()->findOrderResponse(orderRequest.OrderGuid);
        orderResponse->setCscOrderNo(orderRequest.OrderNo);
        getMSV3ComponentManager()->getOrderResponseRepository()->saveOrderResponse(orderResponse);
    }
    //getSession()->nDBCommit(cDBTransSet);
}


void MSV3Handler::processMSV3OrderStatus(
    msv3::Msv3OrderStatusResponse& _return,
    const msv3::Msv3OrderStatusRequest& request)
{
    _return.__set_TransmissionGuid(request.TransmissionGuid);

    libcsc::msv3::TransmissionResponsePtr transmissionResponse =
        getMSV3ComponentManager()->getTransmissionResponseRepository()->findTransmissionResponse(request.TransmissionGuid);

    if (0 != transmissionResponse.get())
    {
        _return.__set_XmlResponse(transmissionResponse->getResponseAsXml());
        _return.__set_IsOffer(transmissionResponse->getIsOffer());
    }
    //  boost::shared_ptr<pxTransmissionResponse>(new pxTransmissionResponse(getSession().get(), request.TransmissionGuid));
}

//-----------------------------------------------------------------------------
// MSV3 hook called during normal order processing. Called after booking of a
// position.
//-----------------------------------------------------------------------------
void MSV3Handler::postProcessOrderArticleInquiryPosition( order::OrderPositionResponse& _return )
{
    const pxOrderEntryParamPtr param = getSession()->getOrderEntryParam(getSession()->Branch()->FilialNr());

    this->postProcessMSV3DeliveryTime(_return);

    // MSV3: Wenn Verbundware sowieso über nächste Normaltour geliefert wird, als No zurückmelden(Wettbewerbsgründe)
    _return.__set_IbtQuantityAsNormal(false);
    if( true == param->IsIBTNormalTourActive() && 0 == _return.QuantityDelivered ) // Parameter muss gesetzt sein und es darf kein Teilverbund sein!
    {
        if( 0 < (_return.QuantityInterBranch + _return.QuantityInterBranchPossible) )
        {
            if (_return.TourInfo.TourId == _return.TourInfo.TourIdIbt && _return.TourInfo.TourDate == _return.TourInfo.TourDateIbt)
            {
                // melde Verbundmenge als normale Lieferung
                if( _return.QuantityInterBranch > 0 )
                    _return.__set_QuantityDelivered(_return.QuantityDelivered + _return.QuantityInterBranch);
                else
                    _return.__set_QuantityDelivered(_return.QuantityDelivered + _return.QuantityInterBranchPossible);
                _return.__set_QuantityInterBranchPossible(0);
                _return.__set_QuantityInterBranch(0);
                _return.__set_BranchNoIbt(0);
                _return.__set_IbtQuantityAsNormal(true);

                // IBT Tourdaten löschen
                postProcessMSV3ResetIBTTourInformation( _return );
            }
        }
    }
}

//-----------------------------------------------------------------------------
// MSV3 hook called during normal order processing. Called after booking of a
// position.
//-----------------------------------------------------------------------------
void MSV3Handler::postProcessOrderProductPosition( order::OrderPositionResponse& _return )
{
    const pxOrderEntryParamPtr param = getSession()->getOrderEntryParam(getSession()->Branch()->FilialNr());

    this->postProcessMSV3DeliveryTime(_return);

    // MSV3: Wenn Verbundware sowieso über nächste Normaltour geliefert wird, als No zurückmelden(Wettbewerbsgründe)
    _return.__set_IbtQuantityAsNormal(false);
    if (true == param->IsIBTNormalTourActive() &&                   // Parameter muss gesetzt sein
        0 < _return.QuantityInterBranch &&  // Verbundmenge > 0
        0 == _return.QuantityDelivered)     // nur wenn gesamte Menge über Verbund geliefert wird
    {
        if (_return.TourInfo.TourId == _return.TourInfo.TourIdIbt && _return.TourInfo.TourDate == _return.TourInfo.TourDateIbt)
        {
            // melde Verbundmenge als normale Lieferung
            _return.__set_QuantityDelivered(_return.QuantityDelivered + _return.QuantityInterBranch);
            _return.__set_QuantityInterBranch(0);
            _return.__set_QuantityInterBranchPossible(0);
            _return.__set_BranchNoIbt(0);
            _return.__set_IbtQuantityAsNormal(true);

            // IBT Tourdaten löschen
            postProcessMSV3ResetIBTTourInformation( _return );
        }
    }
}

//-----------------------------------------------------------------------------
// MSV3 hook called during normal order processing. Called after booking of a
// position.
//-----------------------------------------------------------------------------
void MSV3Handler::postProcessMSV3ResetIBTTourInformation( order::OrderPositionResponse& _return )
{
    // IBT Tourdaten löschen
    if (true == _return.__isset.TourInfo)
    {
        if (true == _return.TourInfo.__isset.TourIdIbt)             // TourIdIbt
        {
            _return.TourInfo.__set_TourIdIbt(std::string());
            _return.TourInfo.__isset.TourIdIbt = false;
        }
        if (true == _return.TourInfo.__isset.TourDateIbt)           // TourDateIbt
        {
            _return.TourInfo.__set_TourDateIbt(csc::base::Date());
            _return.TourInfo.__isset.TourDateIbt = false;
        }
        if (true == _return.TourInfo.__isset.TourDepartureDateIbt)          // TourDepartureDateIbt
        {
            _return.TourInfo.__set_TourDepartureDateIbt(csc::base::DateTime());
            _return.TourInfo.__isset.TourDepartureDateIbt = false;
        }
        if (true == _return.TourInfo.__isset.DeliveryDateIbt)       // DeliveryDateIbt
        {
            _return.TourInfo.__set_DeliveryDateIbt(csc::base::DateTime());
            _return.TourInfo.__isset.DeliveryDateIbt = false;
        }
        if (true == _return.TourInfo.__isset.DeliveryTimeBufferIbt) // DeliveryTimeBufferIbt
        {
            _return.TourInfo.__set_DeliveryTimeBufferIbt(0);
            _return.TourInfo.__isset.DeliveryTimeBufferIbt = false;
        }
        if (true == _return.TourInfo.__isset.IbtType)               // IbtType
        {
            _return.TourInfo.__set_IbtType(0);
            _return.TourInfo.__isset.IbtType = false;
        }
    }
}

//-----------------------------------------------------------------------------
// MSV3 hook called during normal order processing. Called after booking of a
// position.
//-----------------------------------------------------------------------------
void MSV3Handler::postProcessMSV3DeliveryTime( order::OrderPositionResponse& _return )
{
    const pxOrderEntryParamPtr param = getSession()->getOrderEntryParam(getSession()->Branch()->FilialNr());

    // reset delivery time information, when parameter "SendMSV3DeliveryTime" is not set.
    if (false == param->IsSendMSV3DeliveryTime() &&
        true == _return.__isset.TourInfo)
    {
        if (true == _return.TourInfo.__isset.DeliveryDate)
        {
            _return.TourInfo.__set_DeliveryDate(csc::base::DateTime());
            _return.TourInfo.__isset.DeliveryDate = false;
        }
        if (true == _return.TourInfo.__isset.DeliveryTimeBuffer)
        {
            _return.TourInfo.__set_DeliveryTimeBuffer(0);
            _return.TourInfo.__isset.DeliveryTimeBuffer = false;
        }
        if (true == _return.TourInfo.__isset.DeliveryDateIbt)
        {
            _return.TourInfo.__set_DeliveryDateIbt(csc::base::DateTime());
            _return.TourInfo.__isset.DeliveryDateIbt = false;
        }
        if (true == _return.TourInfo.__isset.DeliveryTimeBufferIbt)
        {
            _return.TourInfo.__set_DeliveryTimeBufferIbt(0);
            _return.TourInfo.__isset.DeliveryTimeBufferIbt = false;
        }
    }
}

//-----------------------------------------------------------------------------
// MSV3 hook called during normal order processing. Called after open order.
//-----------------------------------------------------------------------------
void MSV3Handler::postProcessOrderOpen(
    order::OpenOrderResponse& _return,
    const order::OpenOrderRequest& request)
{
    if( NULL != getSession()->Order()  )
    {
        _return.__set_MSV3OrderLabel(getSession()->Order()->OrderLabel()());

        // set an event if the order label has been changed to the default of the order type due to limitation of custom order labels
        if (request.__isset.MSV3OrderLabel && request.__isset.MSV3OriginalOrderLabel && request.MSV3OrderLabel != request.MSV3OriginalOrderLabel)
        {
            getSession()->Order()->WriteOrderLabelChangedToDefaultEvent();
        }
    }
}

//-----------------------------------------------------------------------------
// MSV3 hook called during normal order processing. Called before close order.
//-----------------------------------------------------------------------------
void MSV3Handler::preProcessOrderClose(
    order::CloseOrderResponse& _return)
{
    if (true == getSession()->Order()->StockTrans().IsDebit() && // nur wenn Bestand abgebucht wird, nicht bei z.B. RK!
        false == getSession()->Order()->OrderType().isPartialDeliveryAllowed())
    {
        if (getSession()->Order()->AnzPosDafueFehler() > 0)
        {
            getSession()->Order()->SetEventCode(pxEventReason::MSV3CancelledPartialDelivery);
            getSession()->CancelTransmission();
            getSession()->ExternalError(getSession()->CMsgStream(), CMSG_XMIT_MSV3_ORDER_CANCELLED_LACK);
            _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
        }
    }
}

//-----------------------------------------------------------------------------
// MSV3 hook called during normal order processing. Called after close order.
//-----------------------------------------------------------------------------
void MSV3Handler::postProcessOrderClose(
    order::CloseOrderResponse& _return)
{
    const pxOrderEntryParamPtr param = getSession()->getOrderEntryParam(getSession()->Branch()->FilialNr());

    // reset delivery time information, when parameter "SendMSV3DeliveryTime" is not set.
    if (false == param->IsSendMSV3DeliveryTime())
    {
        if (true == _return.__isset.TourInfo)
        {
            if (true == _return.TourInfo.__isset.DeliveryDate)
            {
                _return.TourInfo.__set_DeliveryDate(csc::base::DateTime());
                _return.TourInfo.__isset.DeliveryDate = false;
            }
            if (true == _return.TourInfo.__isset.DeliveryTimeBuffer)
            {
                _return.TourInfo.__set_DeliveryTimeBuffer(0);
                _return.TourInfo.__isset.DeliveryTimeBuffer = false;
            }
            if (true == _return.TourInfo.__isset.DeliveryDateIbt)
            {
                _return.TourInfo.__set_DeliveryDateIbt(csc::base::DateTime());
                _return.TourInfo.__isset.DeliveryDateIbt = false;
            }
            if (true == _return.TourInfo.__isset.DeliveryTimeBufferIbt)
            {
                _return.TourInfo.__set_DeliveryTimeBufferIbt(0);
                _return.TourInfo.__isset.DeliveryTimeBufferIbt = false;
            }
        }
    }
}

//-----------------------------------------------------------------------------
// MSV3 contract data
//-----------------------------------------------------------------------------
void MSV3Handler::getMsv3ContractData(
    msv3::Msv3ContractDataResponse& _return,
    const msv3::Msv3ContractDataRequest& request)
{
    pxCustBase customer(getSession().get(), request.BranchNo, request.CustomerNo);
    if (false == customer.IsGoodState())
    {
        _return.__set_RetValue(Helper::getReturnStructFromError(customer));
        return;
    }

    _return.__set_BranchNo(request.BranchNo);
    _return.__set_CustomerNo(request.CustomerNo);
    _return.__set_ReturnsOfferAgreement(false);
    _return.__set_SpecificProductAvailabilityAgreement(customer.XMLInfoLevel() - '0' > 1);
    _return.__set_BulkProductAvailabilityAgreement(true);
    _return.__set_ArticleSubstitutionAgreement(false == customer.Flags().IsNoSubstitution());

    basar::Date validFromDate = customer.MSV3CfgChangeDate();

    // order periods
    pxOrderPeriodList orderPeriods(getSession().get());
    orderPeriods.SelectByBranchNoCustomerNo(request.BranchNo, request.CustomerNo);
    msv3::Msv3OrderPeriodList opl;
    pxOrderPeriodListIter iter(orderPeriods);
    pxOrderPeriod* orderPeriod;

    basar::VarString tmpTourId;

    while (NULL != (orderPeriod = (pxOrderPeriod*)++iter))
    {
        tmpTourId = orderPeriod->TourID()();

        msv3::Msv3OrderPeriod op;
        op.__set_Weekday(static_cast<csc::types::WeekDayEnum::type>(orderPeriod->WeekDay()));
        op.__set_MainOrderTime(Helper::getCscTimeFromInt(orderPeriod->MainTime() * 100));
        op.__set_OrderPeriodEndTime(Helper::getCscTimeFromInt(orderPeriod->ToTime() * 100));
        op.__set_OrderPeriodStartTime(Helper::getCscTimeFromInt(orderPeriod->FromTime() * 100));
        op.__set_TourId(tmpTourId);
        opl.push_back(op);
        if (orderPeriod->ChangeDate().isValid())
        {
            if (false == validFromDate.isValid() || validFromDate < orderPeriod->ChangeDate())
            {
                validFromDate = orderPeriod->ChangeDate();
            }
        }
    }
    _return.__set_OrderPeriodList(opl);

    // oder periods special day
    msv3::Msv3OrderPeriodSpecialDayList opsl;
    _return.__set_OrderPeriodSpecialDayList(opsl);

    // customers order types
    msv3::Msv3OrderTypeInformationList otl;
    pxCustOrderType* orderType;
    pxCustOrderTypeListIter it(*customer.OrderTypeList());
    while (NULL != (orderType = (pxCustOrderType*)++it))
    {
        if (msv3::g_cscmsv3_constants.CSCToMsv3OrderTypeMap.find(orderType->KdAuftragArt()()) != msv3::g_cscmsv3_constants.CSCToMsv3OrderTypeMap.end())
        {
            msv3::Msv3OrderTypeInformation ot;
            ot.__set_OrderType(msv3::g_cscmsv3_constants.CSCToMsv3OrderTypeMap.find(orderType->KdAuftragArt()())->second);
            ot.__set_Msv3Permission(orderType->isAllowedForMSV3());
            ot.__set_AllowedOrderLabels(orderType->OrderLabelCount());
            ot.__set_OnlyCompleteDeliveryForBundle(false == orderType->isPartialDeliveryAllowed());
            otl.push_back(ot);
        }
        if (msv3::g_cscmsv3_constants.CscOrderType_RUECKNAHME == orderType->KdAuftragArt()())
        {
            _return.__set_ReturnsOfferAgreement(true);
        }
    }
    _return.__set_OrderTypeList(otl);
    _return.__set_ValidFromDate(Helper::getCscDateFromBasarDate(validFromDate));
    _return.__set_RetValue(Helper::getReturnStructFromError(customer));
}

//-----------------------------------------------------------------------------
// MSV3 info level
//-----------------------------------------------------------------------------
void MSV3Handler::getXmlInfoLevel(
    msv3::XmlInfoLevelResponse& _return,
    const msv3::XmlInfoLevelRequest& request)
{
    try
    {
        _return.__set_BranchNo(request.BranchNo);
        _return.__set_CustomerNo(request.CustomerNo);
        _return.__set_WithArticleReservation(false);

        libcsc::msv3::CustomerDataPtr customerData = getMSV3ComponentManager()->getCustomerDataRepository()->findCustomerData(request.BranchNo, request.CustomerNo);

        csc::types::XMLInfoLevelEnum::type infolevel = static_cast<csc::types::XMLInfoLevelEnum::type>(customerData->getInfoLevel());
        _return.__set_XmlInfoLevel(infolevel);

        if( infolevel == csc::types::XMLInfoLevelEnum::Reservation )
        {
            _return.__set_WithArticleReservation(true);
        }


        csc::base::ReturnStruct retVal;
        retVal.__set_ErrorMessage("");
        retVal.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_OK);
        _return.__set_RetValue(retVal);
    }
    catch (...)
    {
        csc::base::ReturnStruct retVal;
        retVal.__set_ErrorMessage("Unexpected exception in MSV3Handler::getXmlInfoLevel");
        retVal.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION);
        _return.__set_RetValue(retVal);
    }
}

libcsc::msv3::MSV3ComponentManagerPtr MSV3Handler::getMSV3ComponentManager()
{
    if (NULL == m_MSV3ComponentManager.get())
    {
        m_MSV3ComponentManager = boost::make_shared<libcsc::msv3::MSV3ComponentManager>();
        m_MSV3ComponentManager->injectConnection(getSession()->GetConnection());
        m_MSV3ComponentManager->injectTransactionHandler(getSession().get());
    }
    return m_MSV3ComponentManager;
}

} // namespace service
} // namespace csc
