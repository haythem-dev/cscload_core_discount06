#include "orderhandler.h"
#include "cscservicehelper.h"

#include <sstream>
#include <boost/lexical_cast.hpp>
#ifdef WIN32
#include <process.h> /* for getpid() */
#endif

#include <pxxmit.hpp>
#include <pxbranch.hpp>
#include <pxcstbas.hpp>
#include <pxcustomerflags.hpp>
#include <pxcstot.hpp>
#include <pxorder.hpp>
#include <pxordervalues.hpp>
#include <pxitem.hpp>
#include <pxartbas.hpp>
#include <pxarticlecodes.hpp>
#include <pxarticleinfo.hpp>
#include <pxarticletext.hpp>
#include <pxcountrycodes.hpp>
#include <pxxmldefs.h>
#include <pxtxtdoc.hpp>
#include <pxpromotions.hpp>
#include <types/messagecodeenum.inc>
#include <pxbase/pxconstants.hpp>
#include "tourassignmentutil.hpp"
#include <base/irunnable.h>

namespace csc {
namespace service {

OrderHandler::OrderHandler()
{
}

OrderHandler::~OrderHandler()
{
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
void OrderHandler::processOrderOpen(
    order::OpenOrderResponse& _return,
    const order::OpenOrderRequest& request)
{
    if (request.__isset.InternalOrderReference)
    {
        _return.__set_InternalOrderReference(request.InternalOrderReference);
    }

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
    if (false == request.__isset.NoCustomerRouting || false == request.NoCustomerRouting)
    {
        AlterVZ = getSession()->CustomerRouting(request.CustomerNo);
    }
    if (AlterVZ > 0)
    {
        _return.__set_BranchNo(AlterVZ);
    }
    else
    {
        _return.__set_BranchNo(request.BranchNo);
    }

    basar::Int32 customerNo = getSession()->getCustomerSpecialsUWIDFNr(_return.BranchNo, request.CustomerNo, request.OrderType.c_str());
    if (customerNo == 0)
    {
        _return.__set_CustomerNo(request.CustomerNo);
    }
    else
    {
        _return.__set_CustomerNo(customerNo);
    }

    if (false == getSession()->IsNewOrder(_return.BranchNo))
    {
        csc::base::ReturnStruct retVal;
        retVal.__set_ErrorMessage("OpenOrder Out of Time");
        retVal.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_MISC_EXCEPTION);
        _return.__set_RetValue(retVal);
        return;
    }

    if (getSession()->isBulgaria())
    {
        if (request.__isset.Reference)
        {
            // TODO ganz doll:
            char REMARKS[31];
            strncpy(REMARKS, request.Reference.c_str(), 30);
            basar::Int32 rc = pxCheckReferenceNr(getSession().get(), _return.BranchNo, _return.CustomerNo, REMARKS);
            if (rc != 0)
            {
                csc::base::ReturnStruct retVal;
                retVal.__set_ErrorMessage(REMARKS);
                retVal.__set_ErrorCode(static_cast<csc::types::MessageCodeEnum::type>(rc));
                _return.__set_RetValue(retVal);
                return;
            }
        }
    }

    // setze Kunde
    pxCustBase* customer = getSession()->CustomerId(_return.CustomerNo, _return.BranchNo);
    if (customer == NULL)
    {
        _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
        return;
    }

    int ShipmentType = 0;
    int BookingType = 0;
    if (request.__isset.ShipmentType)
        ShipmentType = boost::lexical_cast<int>(request.ShipmentType);
    if (request.__isset.BookingType)
        BookingType = boost::lexical_cast<int>(request.BookingType);

    if (request.__isset.ProformaOrder && true == request.ProformaOrder)
    {
        if (getSession()->NewOrderProforma() == NULL)
        {
            _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
            return;
        }
    }
    else if (request.__isset.MSV3OrderLabel) // MSV3 order
    {
        if (getSession()->OrderTypeMSV3_2(request.OrderType, request.MSV3OrderLabel, ShipmentType, BookingType, request.MSV3OrderPeriodId) == NULL)
        {
            _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
            return;
        }
    }
    else if (request.__isset.ShipmentType || request.__isset.BookingType)
    {
        if (request.__isset.DeliveryTour)
        {
            if (getSession()->SubOrderType(request.OrderType.c_str(), request.Reference.c_str(), static_cast<char>(ShipmentType) + '0', static_cast<char>(BookingType) + '0',
                static_cast<OriginTypeEnum>(request.OriginType), request.SubOrderType.c_str(), request.DeliveryDate, request.DeliveryTour.c_str()) == NULL)
            {
                _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
                return;
            }
        }
        else
        {
            if (getSession()->SubOrderType(request.OrderType.c_str(), request.Reference.c_str(), static_cast<char>(ShipmentType) + '0', static_cast<char>(BookingType) + '0',
                static_cast<OriginTypeEnum>(request.OriginType), request.SubOrderType.c_str(), request.DeliveryDate) == NULL)
            {
                _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
                return;
            }
        }
    }
    else
    {
        if (getSession()->SubOrderType(request.OrderType.c_str(), request.SubOrderType.c_str(), request.DeliveryDate) == NULL)
        {
            _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
            return;
        }
    }

    if (false == getSession()->Order()->IsGoodState())
    {
        _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()->Order()));
        if (_return.RetValue.ErrorCode != csc::types::MessageCodeEnum::CMSG_ORD_ROUTE_NOMORE) // TODO really?
        {
            return;
        }
        if (false == getSession()->isBulgaria())
        {
            if (request.__isset.Reference)
            {
                if (request.__isset.CheckDouble && true == request.CheckDouble)
                {
                    // TODO ganz doll:
                    char REMARKS[31];
                    strncpy(REMARKS, request.Reference.c_str(), 30);
                    basar::Int32 rc = pxCheckReferenceNr(getSession().get(), _return.BranchNo, _return.CustomerNo, REMARKS);
                    if (rc != 0)
                    {
                        csc::base::ReturnStruct retVal;
                        retVal.__set_ErrorMessage(REMARKS);
                        retVal.__set_ErrorCode(static_cast<csc::types::MessageCodeEnum::type>(rc));
                        _return.__set_RetValue(retVal);
                        getSession()->SetDoubleOrder();
                    }
                }
                getSession()->Order()->SetReferenceNr(request.Reference.c_str());
            }
        }
        else
        {
            if (request.__isset.Reference)
            {
                getSession()->Order()->SetReferenceNr(request.Reference.c_str());
                basar::Int32 rc = pxInsertReferenceNr(getSession().get(),
                    getSession()->Order()->Customer()->Vertriebszentrum(),
                    getSession()->Order()->Customer()->KundenNr(),
                    getSession()->Order()->ReferenceNr());
                if (rc != 0)
                {
                    csc::base::ReturnStruct retVal;
                    retVal.__set_ErrorMessage(getSession()->Order()->ErrorMsg());
                    retVal.__set_ErrorCode(static_cast<csc::types::MessageCodeEnum::type>(rc));
                    _return.__set_RetValue(retVal);
                    return;
                }
            }
        }

        _return.__set_PharmacyName(getSession()->Order()->Customer()->NameApo()());
        _return.__set_OrderNo(getSession()->Order()->KdAuftragNr());
        return;
    }

    if (false == getSession()->isBulgaria())
    {
        if (request.__isset.Reference)
        {
            if (request.__isset.CheckDouble && true == request.CheckDouble)
            {
                // TODO ganz doll:
                char REMARKS[31];
                strncpy(REMARKS, request.Reference.c_str(), 30);
                basar::Int32 rc = pxCheckReferenceNr(getSession().get(), _return.BranchNo, _return.CustomerNo, REMARKS);
                if (rc != 0)
                {
                    csc::base::ReturnStruct retVal;
                    retVal.__set_ErrorMessage(REMARKS);
                    retVal.__set_ErrorCode(static_cast<csc::types::MessageCodeEnum::type>(rc));
                    _return.__set_RetValue(retVal);
                    getSession()->SetDoubleOrder();
                }
            }
            getSession()->Order()->SetReferenceNr(request.Reference.c_str());
            // HACK SERBIA XMLReference!!!
            if (getSession()->isSerbia())
            {
                getSession()->Order()->SetXMLReferenceNo(request.Reference.c_str());
            }
            // HACK SERBIA XMLReference!!!
        }
    }
    else
    {
        if (request.__isset.Reference)
        {
            getSession()->Order()->SetReferenceNr(request.Reference.c_str());
            basar::Int32 rc = pxInsertReferenceNr(getSession().get(),
                getSession()->Order()->Customer()->Vertriebszentrum(),
                getSession()->Order()->Customer()->KundenNr(),
                getSession()->Order()->ReferenceNr());
            if (rc != 0)
            {
                csc::base::ReturnStruct retVal;
                retVal.__set_ErrorMessage(getSession()->Order()->ErrorMsg());
                retVal.__set_ErrorCode(static_cast<csc::types::MessageCodeEnum::type>(rc));
                _return.__set_RetValue(retVal);
                return;
            }
        }
    }

    // set flag for special treatment in monthly discounts (France! - AET1 Bit 9, PMR888)
    if (request.__isset.TurnoverOrigin && request.TurnoverOrigin)
    {
        getSession()->Order()->SetTurnOverOrigin();
    }

    // set origin type and origin branch
    if (request.__isset.OriginBranchNo)
    {
        getSession()->Order()->HerkunftFiliale(request.OriginBranchNo);
    }
    if (request.__isset.OriginType)
    {
        getSession()->Order()->BatchSchreiben(static_cast<OriginTypeEnum>(request.OriginType));
        if (getSession()->Order()->BatchSchreiben() == cORTYPE_TRANSFER || getSession()->Order()->BatchSchreiben() == cORTYPE_BATCH_TRANSFER)
        {
            short valutaMonthAuto = getSession()->Order()->OrderType().ValMonthsAuto();
            if (request.__isset.DeferredPaymentDate)
            {
                basar::Date valueDate(request.DeferredPaymentDate.Year, request.DeferredPaymentDate.Month, request.DeferredPaymentDate.Day);
                valueDate.addMonths(valutaMonthAuto);
                getSession()->Order()->ValDate(valueDate);
                getSession()->Order()->SetDatumValutaBatch(getSession()->Order()->DatumValuta());
            }
            else
            {
                if (valutaMonthAuto > 0)
                {
                    getSession()->Order()->ValDateMonAuto(valutaMonthAuto);
                }
            }
        }
    }
    if (pxConstants::NullDate != getSession()->Order()->DatumValuta())
    {
        getSession()->Order()->SetDatumValutaBatch(getSession()->Order()->DatumValuta());
        if (getSession()->isBulgaria())
        {
            getSession()->Order()->SetOrderWithTimeForPayment();
        }
    }

    // set order text
    if (request.__isset.OrderText)
    {
        getSession()->Order()->Bemerkungen(request.OrderText.c_str());
    }

    // set order head texts
    if (request.__isset.HeadTexts)
    {
        std::vector<std::string>::const_iterator it = request.HeadTexts.begin();
        while (it != request.HeadTexts.end())
        {
            std::string text = *it;
            getSession()->Order()->HeadText()->NewLine(text.c_str());
            ++it;
        }
    }

    // set callback
    if (request.__isset.CallBack && true == request.CallBack)
    {
        getSession()->CallBack();
    }

    // set cash order (BG)
    if (request.__isset.IsCashOrder && true == request.IsCashOrder)
    {
        getSession()->Order()->SetChangedToCashOrder();
        getSession()->Order()->SetOrderToCash();
    }

    // narc license (BG)
    if (request.__isset.NarcoticsLicenseParam)
    {
        getSession()->Order()->SetBTMFormularNr(request.NarcoticsLicenseParam.NarcoticsDate, request.NarcoticsLicenseParam.NarcoticsLicense.c_str());
    }

    // rebate order (BG)
    if (request.__isset.RebateOrderParam)
    {
        getSession()->Order()->CancelRebateOrder();
        getSession()->Order()->SetROChain(request.RebateOrderParam.ROChain);
        getSession()->Order()->SetRODateFrom(request.RebateOrderParam.RODateFrom);
        getSession()->Order()->SetRODateTo(request.RebateOrderParam.RODateTo);
        if (getSession()->Order()->SyncCstDiscAccVse() == 0)
        {
            _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()->Order()));
        }
    }

    // set delayed delivery tour (BG)
    if (request.__isset.DeliveryTour && request.__isset.DeliveryDate)
    {
        if (getSession()->Order()->IsValidRoute(request.DeliveryTour.c_str()))
        {
            getSession()->Order()->getTourAssignmentUtil()->resetInjections();
            getSession()->Order()->getTourAssignmentUtil()->injectDesiredTourId(request.DeliveryTour.c_str());
            getSession()->Order()->getTourAssignmentUtil()->assignTour();
        }
        else
        {
            getSession()->Order()->SetNextValidRoute(request.DeliveryTour.c_str());
        }
    }

    // Tender no (RS)
    if (request.__isset.TenderNo)
    {
        getSession()->Order()->SetTenderNo(request.TenderNo);
    }

    // order relation numbers
    if (request.__isset.OrderRelationNumbers)
    {
        std::vector<csc::order::OrderRelationNumber>::const_iterator it = request.OrderRelationNumbers.begin();
        while (it != request.OrderRelationNumbers.end())
        {
            csc::order::OrderRelationNumber relNo = *it;
            switch (relNo.RelationType)
            {
            case eIVCVoucherNo:
                getSession()->Order()->setIVCVoucherNo(relNo.RelationNo);
                break;
            case eOriginalInvoiceNo:
                getSession()->Order()->setOriginalInvoiceNo(relNo.RelationNo);
                break;
            case ePurchaseOrderNo:
                getSession()->Order()->setPurchaseOrderNo(relNo.RelationNo);
                break;
            default:
                break;
            }
            ++it;
        }
    }

    // SWITZERLAND: SWIMP-CH-OR SPECIFIC:
    if (request.__isset.PharmacyOrderNo || request.__isset.PharmacyCustomerNo)
    {
        // SWIMP-CH-OR specific: XML Request XPath: /customerOrder/orderHeader/orderDetails/@PharmacyOrderNo --> IFX DB: KdAuftragInfo.KdAuftragBestellNr
        nString pharmacyOrderNo;
        if (request.__isset.PharmacyOrderNo)
        {
            basar::VarString tmpStr = request.PharmacyOrderNo;
            tmpStr.trim(basar::cmnutil::BString::FIRST_END);    // trim whitespace from the start and from the end and then check:
            if (!tmpStr.empty() &&
                tmpStr.find_first_not_of('0') != std::string::npos
                )
            {
                pharmacyOrderNo = tmpStr.c_str();
                pharmacyOrderNo.Trim(9);
            }
        }

        // SWIMP-CH-OR specific: XML Request XPath: /customerOrder/orderHeader/orderDetails/@PharmacyCustomerNo --> IFX DB: KdAuftragInfo.IdfNrIntern
        long pharmacyCustomerNo = 0;
        if (request.__isset.PharmacyCustomerNo)
        {
            pharmacyCustomerNo = request.PharmacyCustomerNo;
        }

        if (!pharmacyOrderNo.IsEmpty() || pharmacyCustomerNo > 0)
        {
            // The rest is unused up to now (22.07.2021):
            nString customerTour;
            nString typeOfDispatch;
            long pharmacyProcessId = 0;

            // create new pxCustOrderInfo and fill fill the optional (or default) request values for: PharmacyOrderNo and PharmacyCustomerNo
            getSession()->NewCustOrderInfoPolymed(pharmacyOrderNo, pharmacyCustomerNo, customerTour, typeOfDispatch, pharmacyProcessId);

            // Fill the CscOrderNo in the new pxCustOrderInfo and write to IFX DB: KdAuftragInfo
            getSession()->PutCustOrderInfo(getSession()->Order()->KdAuftragNr());
        }
    }

    _return.__set_PharmacyName(getSession()->Order()->Customer()->NameApo()());
    _return.__set_OrderNo(getSession()->Order()->KdAuftragNr());
    _return.__set_Pid(getpid());
    _return.__set_OrderType(getSession()->Order()->KdAuftragArt()());
    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()->Order()));
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
void OrderHandler::processOrderClose(
    order::PlaceOrderResponse& _return,
    const order::CloseOrderRequest& request)
{
    if (request.__isset.CloseMode)
    {
        switch (request.CloseMode)
        {
        case csc::order::OrderCloseMode::CLOSE_MODE_CLOSE:
            break;
        case csc::order::OrderCloseMode::CLOSE_MODE_POSTPONE:
            if (getSession()->Order()->BatchSchreiben() == cORTYPE_UNKNOWN ||
                getSession()->Order()->BatchSchreiben() == cORTYPE_TRANSFER) // UE
            {
                getSession()->SetNotCloseOrder();
            }
            break;
        case csc::order::OrderCloseMode::CLOSE_MODE_CANCEL:
            if (getSession()->CancelTransmission())
            {
                _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
            }
            return;

        case csc::order::OrderCloseMode::CLOSE_MODE_CLOSE_INTERNET:
            if (false == getSession()->Order()->IsCallBack())
                getSession()->Order()->ClearProblemClearance();
            getSession()->Order()->ClearDefferedForInternet();
            getSession()->Order()->SetAuftragVomXML();
            break;
        case csc::order::OrderCloseMode::CLOSE_MODE_POSTPONE_INTERNET:
            getSession()->SetNotCloseOrder();
            getSession()->Order()->SetDefferedForInternet();
            getSession()->Order()->SetAuftragVomXML();
            break;
        case csc::order::OrderCloseMode::CLOSE_MODE_CLOSE_DEBTLIMIT:
            break;
        case csc::order::OrderCloseMode::CLOSE_MODE_POSTPONE_DEBTLIMIT:
            break;
        default:
            break;
        }
    }
    if (request.__isset.CalculateRangeRebates && true == request.CalculateRangeRebates) // Proforma Order
    {
        getSession()->EndProforma();
        updateProforma(_return.Positions);
    }

    _return.CloseOrder.__set_BranchNo(getSession()->Order()->FilialNr());
    _return.CloseOrder.__set_CustomerNo(getSession()->Order()->Customer()->KundenNr());
    _return.CloseOrder.__set_OrderNo(getSession()->Order()->KdAuftragNr());
    _return.CloseOrder.__set_OrderType(getSession()->Order()->OrderType().KdAuftragArt()());

    if (false == getSession()->Order()->ReferenceNr().IsEmpty())
    {
        if (false == getSession()->Session()->isBulgaria())
        {
            basar::Int32 rc = pxInsertReferenceNr(getSession().get(),
                getSession()->Order()->Customer()->Vertriebszentrum(),
                getSession()->Order()->Customer()->KundenNr(),
                getSession()->Order()->ReferenceNr());
            if (rc != 0)
            {
                csc::base::ReturnStruct retVal;
                retVal.__set_ErrorMessage(getSession()->Order()->ErrorMsg());
                retVal.__set_ErrorCode(static_cast<csc::types::MessageCodeEnum::type>(rc));
                _return.__set_RetValue(retVal);
                return;
            }
        }
    }

    order::TourInformation tourInfo = Helper::getOrderDeliveryInformation(getSession()->Order());
    _return.CloseOrder.__set_TourInfo(tourInfo);

    _return.CloseOrder.__set_OrderValue(getSession()->Order()->WertLieferung());
    _return.CloseOrder.__set_OrderLines(getSession()->Order()->AnzPos());
    _return.CloseOrder.__set_TextLines(getSession()->Order()->AnzAlphaText());  //nase von ohne bestand auf alpha, bitte prüfen
    _return.CloseOrder.__set_LackLines(getSession()->Order()->AnzPosDafueFehler());
    if (   getSession()->Order()->Customer()->IsCreditLimited()
        && (getSession()->Order()->Customer()->HasDebitLimitK1() || getSession()->Order()->Customer()->HasDebitLimitK2()) )
    {
        _return.CloseOrder.__set_RemainingCreditLimit(getSession()->Order()->Customer()->RestCreditLimit());
    }
    if (getSession()->Order()->OrderValues())
    {
        csc::order::OrderValuesResponse orderValues;
        orderValues.__set_OrdValFtaxFS(getSession()->Order()->OrderValues()->OrdValFtaxFS());
        orderValues.__set_OrdValFtaxFSDisc(getSession()->Order()->OrderValues()->OrdValFtaxFSDisc());
        orderValues.__set_OrdValFtaxHF(getSession()->Order()->OrderValues()->OrdValFtaxHF());
        orderValues.__set_OrdValFtaxHFDisc(getSession()->Order()->OrderValues()->OrdValFtaxHFDisc());
        orderValues.__set_OrdValFtaxRS(getSession()->Order()->OrderValues()->OrdValFtaxRS());
        orderValues.__set_OrdValFtaxRSDisc(getSession()->Order()->OrderValues()->OrdValFtaxRSDisc());

        orderValues.__set_OrdValLtaxFS(getSession()->Order()->OrderValues()->OrdValLtaxFS());
        orderValues.__set_OrdValLtaxFSDisc(getSession()->Order()->OrderValues()->OrdValLtaxFSDisc());
        orderValues.__set_OrdValLtaxHF(getSession()->Order()->OrderValues()->OrdValLtaxHF());
        orderValues.__set_OrdValLtaxHFDisc(getSession()->Order()->OrderValues()->OrdValLtaxHFDisc());
        orderValues.__set_OrdValLtaxRS(getSession()->Order()->OrderValues()->OrdValLtaxRS());
        orderValues.__set_OrdValLtaxRSDisc(getSession()->Order()->OrderValues()->OrdValLtaxRSDisc());

        orderValues.__set_OrdValNtaxFS(getSession()->Order()->OrderValues()->OrdValNtaxFS());
        orderValues.__set_OrdValNtaxFSDisc(getSession()->Order()->OrderValues()->OrdValNtaxFSDisc());
        orderValues.__set_OrdValNtaxHF(getSession()->Order()->OrderValues()->OrdValNtaxHF());
        orderValues.__set_OrdValNtaxHFDisc(getSession()->Order()->OrderValues()->OrdValNtaxHFDisc());
        orderValues.__set_OrdValNtaxRS(getSession()->Order()->OrderValues()->OrdValNtaxRS());
        orderValues.__set_OrdValNtaxRSDisc(getSession()->Order()->OrderValues()->OrdValNtaxRSDisc());

        orderValues.__set_TaxValFtaxFS(getSession()->Order()->OrderValues()->TaxValFtaxFS());
        orderValues.__set_TaxValFtaxFSDisc(getSession()->Order()->OrderValues()->TaxValFtaxFSDisc());
        orderValues.__set_TaxValFtaxHF(getSession()->Order()->OrderValues()->TaxValFtaxHF());
        orderValues.__set_TaxValFtaxHFDisc(getSession()->Order()->OrderValues()->TaxValFtaxHFDisc());
        orderValues.__set_TaxValFtaxRS(getSession()->Order()->OrderValues()->TaxValFtaxRS());
        orderValues.__set_TaxValFtaxRSDisc(getSession()->Order()->OrderValues()->TaxValFtaxRSDisc());

        orderValues.__set_TaxValLtaxFS(getSession()->Order()->OrderValues()->TaxValLtaxFS());
        orderValues.__set_TaxValLtaxFSDisc(getSession()->Order()->OrderValues()->TaxValLtaxFSDisc());
        orderValues.__set_TaxValLtaxHF(getSession()->Order()->OrderValues()->TaxValLtaxHF());
        orderValues.__set_TaxValLtaxHFDisc(getSession()->Order()->OrderValues()->TaxValLtaxHFDisc());
        orderValues.__set_TaxValLtaxRS(getSession()->Order()->OrderValues()->TaxValLtaxRS());
        orderValues.__set_TaxValLtaxRSDisc(getSession()->Order()->OrderValues()->TaxValLtaxRSDisc());

        orderValues.__set_TaxValNtaxFS(getSession()->Order()->OrderValues()->TaxValNtaxFS());
        orderValues.__set_TaxValNtaxFSDisc(getSession()->Order()->OrderValues()->TaxValNtaxFSDisc());
        orderValues.__set_TaxValNtaxHF(getSession()->Order()->OrderValues()->TaxValNtaxHF());
        orderValues.__set_TaxValNtaxHFDisc(getSession()->Order()->OrderValues()->TaxValNtaxHFDisc());
        orderValues.__set_TaxValNtaxRS(getSession()->Order()->OrderValues()->TaxValNtaxRS());
        orderValues.__set_TaxValNtaxRSDisc(getSession()->Order()->OrderValues()->TaxValNtaxRSDisc());

        _return.CloseOrder.__set_OrderValues(orderValues);
    }

    PriceTypeEnum priceType = RETAIL_PRICE;
    if (getSession()->Order()->CountPriceTypeItems(FREESALE_PRICE))
    {
        priceType = FREESALE_PRICE;
    }
    else if (getSession()->Order()->CountPriceTypeItems(HEALTHFUND_PRICE))
    {
        priceType = HEALTHFUND_PRICE;
    }

    if (   getSession()->Order()->Customer()->IsCashPayer(priceType, getSession()->Order())
        || getSession()->Order()->isCashOrder() )
    {
        _return.CloseOrder.__set_IsCashPayer(true);
    }
    else
    {
        _return.CloseOrder.__set_IsCashPayer(false);
    }

    csc::base::ReturnStruct retVal;
    if (getSession()->Order()->IsSendOrderDouble())
    {
        retVal.__set_ErrorMessage(getSession()->GetMessageText(CMSG_ORD_DOUBLE_ORDER)());
        retVal.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_ORD_DOUBLE_ORDER);
    }
    if (getSession()->Order()->IsChangedToCashOrder())
    {
        retVal.__set_ErrorMessage(getSession()->GetMessageText(CMSG_ORD_CHANGED_TO_CASHORDER)());
        retVal.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_ORD_CHANGED_TO_CASHORDER);
        _return.CloseOrder.__set_IsCashPayer(true);
    }

    if (getSession()->isCroatia())
    {
        libcsc::base::IRunnablePtr uc = getSession()->getCSCOrderComponentManager()->saveCSCCallplanUC(
            getSession()->Order()->FilialNr(), getSession()->Order()->Customer()->KundenNr(), atoi(getSession()->Order()->TourId()) / 100);
        uc->run();
    }

    if (getSession()->End() != 0)
    {
        _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
        return;
    }

    if (!retVal.__isset.ErrorCode)
    {
        retVal = Helper::getReturnStructFromError(nError());
    }
    _return.CloseOrder.__set_PostponeReason(GetOrderZugrund(getSession().get(), _return.CloseOrder.OrderNo)());
    _return.CloseOrder.__set_RetValue(retVal);
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
void OrderHandler::isArticleExportPermitted(
    csc::order::ArticleExportPermittedResponse& _return,
    const  csc::order::ArticleExportPermittedRequest& request)
{
    bool isExportPermitted = getSession()->isExportPermitted(request.BranchNo, request.CustomerNo, request.ArticleNo);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
    _return.__set_ExportPermitted(isExportPermitted);
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
void OrderHandler::processOrderTextPosition(
    order::OrderPositionResponse& _return,
    const order::OrderPositionRequest& request)
{
    pxOrderItem* orderitem = getSession()->NewOrderTextItem(request.PositionText.c_str());

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
    _return.__set_OrderNo(orderitem->Order().KdAuftragNr());
    _return.__set_PositionNo(orderitem->PosNr());
    _return.__set_PositionText(orderitem->Bemerkungen()());

    if (request.__isset.InternalPosReference)
    {
        _return.__set_InternalPosReference(request.InternalPosReference);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
void OrderHandler::processOrderDispoPosition(
    order::OrderPositionResponse& _return,
    const order::OrderPositionRequest& request)
{
    tDISPOITEM di;
    di.Bezeichnung = request.ArticleName.c_str();
    di.Einheit = request.ArticleUnit.c_str();
    di.Darreichform = request.ArticleHandout.c_str();
    di.Bemerkungen = request.PositionText.c_str();
    di.PreisEKApo = request.PriceAep;
    di.PreisEKGrosso = request.PriceEKGrosso;
    di.MengeBestellt = request.QuantityOrdered;
    di.TaxPflichtig = true; //TODO check kann in gui eingestellt werden, alter code setzt aber immer 1
    di.WarenGruppeEigen = "99999";
    di.UrsprungAuftragnr = request.OriginOrderNo;
    di.UrsprungPosnr = request.OriginPositionNo;
    di.GebuehrBearb = request.Postage;
    di.MWSTSchluessel = (request.TaxRate == 1) ? HALFTAX : FULLTAX;

    pxOrderItem* orderitem = getSession()->Order()->NewOrderItem_15(di, pxOrderItem::PurchaseOrder);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
    _return.__set_OrderNo(orderitem->Order().KdAuftragNr());
    _return.__set_PositionNo(orderitem->PosNr());

    if (request.__isset.InternalPosReference)
    {
        _return.__set_InternalPosReference(request.InternalPosReference);
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
void OrderHandler::processOrderProductPosition(
    order::OrderPositionResponse& _return,
    const order::OrderPositionRequest& request)
{
    basar::Int32 articleNo = 0;
    pxArticleCodes ArtCode(getSession().get(), request.ArticleCode.c_str());
    if (ArtCode.Get())
    {
    }
    else
    {
        articleNo = ArtCode.ArticleNo();
    }
    order::ArticleInformation articleOrdered;
    articleOrdered.__set_ArticleNo(articleNo);
    articleOrdered.__set_ArticleCode(request.ArticleCode);
    _return.__set_QuantityOrdered(request.QuantityOrdered);

    _return.__set_XmlLineReference(request.XmlLineReference);
    if (request.__isset.InternalPosReference)
    {
        _return.__set_InternalPosReference(request.InternalPosReference);
    }

    if (getSession()->IsSubDeviceTypeOf(MSV3))
    {
        char koart[2], buchart[2];
        sprintf(koart, "%c", getSession()->Order()->KoArt());
        sprintf(buchart, "%c", getSession()->Order()->BuchArt());
        getSession()->OrderTypeMSV3_2(getSession()->Order()->KdAuftragArt()(),
            getSession()->Order()->OrderLabel()(),
            atoi(koart),
            atoi(buchart),
            getSession()->Order()->OrderPeriodID());
    }
    else if (getSession()->Order() != NULL && getSession()->Order()->isProductAvailabilityRequest())
    {
        // do nothing
    }
    else
    {
        getSession()->OrderType(getSession()->Order()->KdAuftragArt(), request.SequenceNo);
    }
    pxOrderItem* orderitem = NULL;
    if (getSession()->isBulgaria())
    {
        if (request.PriceType == csc::types::PriceTypeEnum::HEALTHFUND_PRICE && !getSession()->Order()->Customer()->IsHealthFundAuthorized())
        {
            csc::base::ReturnStruct retVal;
            retVal.__set_ErrorMessage(getSession()->GetMessageText(CMSG_SDC_NO_PERMISSION_HEALTHFUND)());
            retVal.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_SDC_NO_PERMISSION_HEALTHFUND);
            _return.__set_RetValue(retVal);
            return;
        }
        if (request.PriceType == csc::types::PriceTypeEnum::RETAIL_PRICE && !getSession()->Order()->Customer()->Flags().IsRetailPermit())
        {
            csc::base::ReturnStruct retVal;
            retVal.__set_ErrorMessage(getSession()->GetMessageText(CMSG_SDC_NO_PERMISSION_RETAIL)());
            retVal.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_SDC_NO_PERMISSION_RETAIL);
            _return.__set_RetValue(retVal);
            return;
        }
        orderitem = getSession()->Order()->ItemList()->FindArticle(articleOrdered.ArticleNo, static_cast<PriceTypeEnum>(request.PriceType));
        if (orderitem != NULL)
        {
            if (orderitem->Open() == nSTATE_GOOD)
            {
                orderitem->OrderQuantity(orderitem->MengeBestellt() + request.QuantityOrdered, 0, 0);
            }
        }
    }

    if (orderitem == NULL)
    {
        if (request.__isset.PriceAep || request.__isset.PriceFree || request.__isset.DiscountPercentFree || request.__isset.QuantityRebateInKind)
        {
            orderitem = getSession()->NewOrderItem_13(
                articleOrdered.ArticleNo,
                request.QuantityOrdered,
                request.XmlOrderReference,
                request.XmlLineReference,
                request.AcceptInterBranchDelivery, request.AcceptRestDelivery, request.AcceptDispoDelivery, request.AcceptPartialDelivery,
                static_cast<PriceTypeEnum>(request.PriceType), request.PriceAep, request.PriceFree, request.DiscountPercentFree,
                request.QuantityRebateInKind, request.Batch.c_str(), request.FixBatch);
        }
        else
        {
            orderitem = getSession()->NewOrderItem_12(
                articleOrdered.ArticleNo,
                request.QuantityOrdered,
                request.XmlOrderReference,
                request.XmlLineReference,
                request.AcceptInterBranchDelivery, request.AcceptRestDelivery, request.AcceptDispoDelivery, request.AcceptPartialDelivery,
                static_cast<PriceTypeEnum>(request.PriceType), request.Batch.c_str(), request.FixBatch);
        }
    }

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (getSession()->isBulgaria())
    {
        if (orderitem == NULL && _return.RetValue.ErrorCode == csc::types::MessageCodeEnum::CMSG_ORD_CREDITLIMIT_EXHAUSTED)
        {
            getSession()->Order()->SetChangedToCashOrder();
            getSession()->Order()->SetOrderToCash();    //Neu: Ändern auf Barzahlung

            if (request.__isset.PriceAep || request.__isset.PriceFree || request.__isset.DiscountPercentFree || request.__isset.QuantityRebateInKind)
            {
                orderitem = getSession()->NewOrderItem_13(
                    articleOrdered.ArticleNo,
                    request.QuantityOrdered,
                    request.XmlOrderReference,
                    request.XmlLineReference,
                    request.AcceptInterBranchDelivery, request.AcceptRestDelivery, request.AcceptDispoDelivery, request.AcceptPartialDelivery,
                    static_cast<PriceTypeEnum>(request.PriceType), request.PriceAep, request.PriceFree, request.DiscountPercentFree,
                    request.QuantityRebateInKind);
            }
            else
            {
                orderitem = getSession()->NewOrderItem_12(
                    articleOrdered.ArticleNo,
                    request.QuantityOrdered,
                    request.XmlOrderReference,
                    request.XmlLineReference,
                    request.AcceptInterBranchDelivery, request.AcceptRestDelivery, request.AcceptDispoDelivery, request.AcceptPartialDelivery,
                    static_cast<PriceTypeEnum>(request.PriceType));
            }
        }
    }

    if (orderitem == NULL)
    {
        _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
        return;
    }

    _return.__set_OrderNo(orderitem->Order().KdAuftragNr());
    _return.__set_PositionNo(orderitem->PosNr());

    csc::order::TourInformation tourInfo = Helper::getPositionDeliveryInformation(orderitem, false);
    _return.__set_TourInfo(tourInfo);

    // set MSV3 request informations
    if (request.__isset.MSV3OrderID && request.__isset.MSV3OrderSupportID && request.__isset.MSV3RequestID && request.__isset.MSV3RequestSupportID)
    {
        orderitem->setMSV3OrderID(request.MSV3OrderID);
        orderitem->setMSV3OrderSupportID(request.MSV3OrderSupportID);
        orderitem->setMSV3RequestID(request.MSV3RequestID);
        orderitem->setMSV3RequestSupportID(request.MSV3RequestSupportID);
    }

    if (orderitem->MengeNachgeliefert() > 0)
    {
        if (getSession()->Order()->BatchSchreiben() > 0)
        {
            orderitem->CscBatchCheckOrderPos(request.QuantityRebateInKind, request.PositionText.c_str());
        }
    }
    else if (request.__isset.PositionText)    //Bemerkung für die Position setzen
    {
        orderitem->Bemerkungen(request.PositionText.c_str());
    }

    order::ArticleInformation articleDelivered;
    basar::VarString tmp;

    if (orderitem->SubstProposalArticleNo() > 0L)
    {
        // Parallel import - Substitution
        boost::shared_ptr<pxArticleCodes> pArtCode = boost::shared_ptr<pxArticleCodes>(orderitem->GetArticleCode(orderitem->SubstProposalArticleNo()));
        tmp = pArtCode->ArticleCode()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        articleDelivered.__set_ArticleCode(tmp);
        articleDelivered.__set_ArticleNo(orderitem->SubstProposalArticleNo());
    }
    else
    {
        articleDelivered.__set_ArticleNo(orderitem->ArtikelNr());
        tmp = orderitem->ArticleCode()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        articleDelivered.__set_ArticleCode(tmp);
        tmp = getSession()->ConvertPzn2Ean(orderitem->ArtikelNr(), 13)();    // TODO verify!!!
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        articleDelivered.__set_Ean(tmp);

        if (orderitem->ArtBase() != NULL && orderitem->ArtBase()->IsGoodState())
        {
            basar::Int16 TextKey = orderitem->ArtBase()->TextKey();
            if (TextKey > 0)
            {
                pxArticleText ptext(getSession().get(), TextKey);
                if (!ptext.Get(cDBGET_READONLY))
                {
                    tmp = ptext.Text()();
                    tmp.trim(basar::cmnutil::BString::FIRST_END);
                    articleDelivered.__set_ArticleText(tmp);
                }
            }
            tmp = orderitem->ArtBase()->Bezeichnung()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleDelivered.__set_ArticleName(tmp);

            tmp = orderitem->ArtBase()->ArtikelLangname()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleDelivered.__set_ArticleLongName(tmp);

            tmp = orderitem->ArtBase()->Einheit()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleDelivered.__set_ArticleUnit(tmp);

            tmp = orderitem->ArtBase()->Darreichform()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleDelivered.__set_ArticleHandout(tmp);

            std::stringstream s;
            s << orderitem->ArtBase()->CodeBlocage();
            tmp = s.str();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            _return.__set_CodeBlocage(tmp);
            articleDelivered.__set_CodeBlocage(tmp);

            if (orderitem->TotalIBTQuantity() > 0)
            {
                _return.__set_CodeBlocage("T");
                articleDelivered.__set_CodeBlocage("T");
            }
        }
        else
        {
            _return.__set_CodeBlocage("2");
            articleDelivered.__set_CodeBlocage("2");
        }
    }
    _return.__set_ArticleDelivered(articleDelivered);

    if (request.__isset.QuantityRebateInKind && request.QuantityRebateInKind > 0)
    {
        _return.__set_QuantityLack(request.QuantityOrdered + request.QuantityRebateInKind - orderitem->MengeGeliefert() - orderitem->TotalIBTQuantity() -
            orderitem->MengeNachgeliefert() - orderitem->MengeDisponiert());
    }
    else
    {
        _return.__set_QuantityLack(request.QuantityOrdered + orderitem->MengeNatra() - orderitem->MengeGeliefert() - orderitem->TotalIBTQuantity() -
            orderitem->MengeNachgeliefert() - orderitem->MengeDisponiert());
    }

    // 2017-11-14 Verbund möglich nicht als Defekt behandeln! (Probleme bei MSV3 mit doppelten Anteilen)
    if (orderitem->TotalIBTQuantity() == 0 && orderitem->MengeMoeglich() > 0)
    {
        _return.__set_QuantityLack(_return.QuantityLack - orderitem->MengeMoeglich());
    }

    if (_return.QuantityLack < 0)
        _return.__set_QuantityLack(0);

    _return.__set_QuantityInterBranch(orderitem->TotalIBTQuantity());
    _return.__set_QuantityInterBranchPossible(orderitem->MengeMoeglich()); // added, SH, 15.02.2017
    _return.__set_QuantityRestDelivery(orderitem->MengeNachgeliefert());
    _return.__set_QuantityDelivered(orderitem->MengeGeliefert());
    _return.__set_QuantityDispo(orderitem->MengeDisponiert());
    _return.__set_QuantityNatra(orderitem->MengeNatra());
    _return.__set_BranchNoIbt(getSession()->Order()->AuxFil());
    _return.__set_IbtQuantityAsNormal(false);
    _return.__set_RestDeliveryPossible(orderitem->IsRestDeliveryPossibleForArticle());

    // Ausweichartikel gebucht
    if (orderitem->IsQStateAlternate() || orderitem->IsReimportArtikel() || (orderitem->SubstProposalArticleNo() > 0L))
    {
        order::ArticleInformation articleOrderedAlter;
        articleOrderedAlter.__set_ArticleCode(request.ArticleCode);
        articleOrderedAlter.__set_ArticleNo(articleNo);
        articleOrderedAlter.__set_Ean(getSession()->ConvertPzn2Ean(articleNo, 13)());
        pxArticleInfo* ArtInfo = orderitem->ArticleInfoRequest(articleNo, orderitem->MengeBestaetigt());
        if (ArtInfo != NULL)
        {
            tmp = ArtInfo->ArtBase()->Bezeichnung()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleOrderedAlter.__set_ArticleName(tmp);

            tmp = ArtInfo->ArtBase()->ArtikelLangname()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleOrderedAlter.__set_ArticleLongName(tmp);

            tmp = ArtInfo->ArtBase()->Einheit()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleOrderedAlter.__set_ArticleUnit(tmp);

            tmp = ArtInfo->ArtBase()->Darreichform()();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleOrderedAlter.__set_ArticleHandout(tmp);

            std::stringstream s;
            s << ArtInfo->CodeBlocage();
            tmp = s.str();
            tmp.trim(basar::cmnutil::BString::FIRST_END);
            articleOrderedAlter.__set_CodeBlocage(tmp);

            if (getSession()->isFrance() || getSession()->isFrancePrewhole())
            {
                pxCountryCodes* CC = getSession()->CountryCodesInfo(getSession()->Order()->FilialNr(), articleOrderedAlter.CodeBlocage.c_str());
                if (CC != NULL)
                {
                    tmp = CC->SeraCode()();
                    tmp.trim(basar::cmnutil::BString::FIRST_END);
                    articleOrderedAlter.__set_SeraCode(tmp);

                    tmp = CC->XMLCode()();
                    tmp.trim(basar::cmnutil::BString::FIRST_END);
                    articleOrderedAlter.__set_XmlCode(tmp);

                    tmp = CC->XMLText()();
                    tmp.trim(basar::cmnutil::BString::FIRST_END);
                    articleOrderedAlter.__set_XmlText(tmp);
                    delete CC;
                }
            }

            articleOrderedAlter.__set_PricePharmacyPurchase(ArtInfo->PreisEKApo());
            articleOrderedAlter.__set_PriceCustomerPurchase(ArtInfo->PreisEKApo());
            articleOrderedAlter.__set_PricePharmacySell(ArtInfo->PreisVKApo());

            if (getSession()->isFrance() || getSession()->isFrancePrewhole())
            {
                nMoney lppr = orderitem->ReimbursementPrice(articleOrderedAlter.ArticleNo, '2');
                articleOrderedAlter.__set_PriceLppr(lppr);

                nMoney tfr = orderitem->ReimbursementPrice(articleOrderedAlter.ArticleNo, '1');
                articleOrderedAlter.__set_PriceTfr(tfr);
            }

        }
        _return.__set_ArticleOrdered(articleOrderedAlter);
    }

    // prices
    Helper::getPriceInformation(_return, orderitem);

    // quantities
    _return.__set_QuantityReserved(orderitem->MengeReserviert());

    // Batch
    _return.__set_Batch(orderitem->GetChargenNr());
    _return.__set_FixBatch(orderitem->IsFixBatch());
    _return.__set_ExpiryDate(orderitem->ArticleExpireDate());

    if (orderitem->PromotionNo() > 0)
    {
        _return.__set_PromotionNo(orderitem->PromotionNo());
        pxPromotions p(getSession().get(), orderitem->PromotionNo());
        _return.__set_PromotionName(p.PromotionName()());
    }

    if (orderitem->SubstProposalArticleNo() > 0L)
    {
        std::stringstream s;
        s << CMSG_ART_REIMPORT_PROPOSAL;
        _return.__set_LackReasonList(s.str());
    }

    char TEXT[100];
    memset(TEXT, 0, sizeof(TEXT));
    int errCode = orderitem->GetError(TEXT);
    if (errCode > 100000)
    {
        errCode /= 100;
    }
    csc::base::ReturnStruct retValue;
    retValue.__set_ErrorCode(static_cast<csc::types::MessageCodeEnum::type>(errCode));
    retValue.__set_ErrorMessage(TEXT);
    _return.__set_RetValue(retValue);

    // codes
    if (getSession()->isFrance() || getSession()->isFrancePrewhole())
    {
        if (_return.RetValue.ErrorCode != 0)
        {
            pxCountryCodes* CC = getSession()->CountryCodesInfo(getSession()->Order()->FilialNr(), articleDelivered.CodeBlocage.c_str());
            if (CC != NULL)
            {
                tmp = CC->SeraCode()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_SeraCode(tmp);
                articleDelivered.__set_SeraCode(tmp);

                tmp = CC->XMLCode()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_XmlCode(tmp);
                articleDelivered.__set_XmlCode(tmp);

                tmp = CC->XMLText()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_XmlText(tmp);
                articleDelivered.__set_XmlText(tmp);
                delete CC;
            }
        }
    }
    if (getSession()->Country() == "AU" || getSession()->isGermany())
    {
        basar::VarString xmlcode;
        xmlcode.format("%ld", _return.RetValue.ErrorCode);
        _return.__set_XmlCode(xmlcode);
        if (_return.RetValue.ErrorCode != 0)
        {
            pxCountryCodes* CC = getSession()->CountryCodesInfo(getSession()->Order()->FilialNr(), xmlcode.c_str(), (short)pxCountryCodes::CCT_XMLCODE);
            if (CC != NULL)
            {
                tmp = CC->SeraCode()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_SeraCode(tmp);

                tmp = CC->XMLText()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_XmlText(tmp);

                tmp = CC->InfoCode()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_LackReasonCountryCode(tmp);
                delete CC;
            }
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
struct find_posno
{
    find_posno(const long orderno, const long posno) :
        _orderno(orderno),
        _posno(posno)
    {
    }
    long _orderno;
    long _posno;
    bool operator()(const csc::order::OrderPositionResponse& response)
    {
        return (_orderno == response.OrderNo && _posno == response.PositionNo);
    }
};

void OrderHandler::updateProforma(csc::order::OrderPositionResponseList& responseList)
{
    pxOrderItemListIter iterator(*getSession()->Order()->ItemListProforma()); // define an iterator
    iterator += getSession()->Order()->FirstTransPos();
    pxOrderItem* item;

    while ((item = (pxOrderItem*) ++iterator) != NULL)
    {
        csc::order::OrderPositionResponseList::iterator it = std::find_if(responseList.begin(), responseList.end(),
            find_posno(item->KdAuftragNr(), item->PosNr()));
        if (it != responseList.end())
        {
            Helper::getPriceInformation(*it, item);
        }
        else if (item->IsSperreRabattManuell()) // TODO FN richtiges flag für automatisch gebuchte Natra-Position (rubber duck)???
        {
            csc::order::OrderPositionResponse pos;
            setItemResponseValues(pos, item);
            it = responseList.insert(it, pos);
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////
void OrderHandler::setItemResponseValues(csc::order::OrderPositionResponse& _return, pxOrderItem* orderitem)
{
    _return.__set_OrderNo(orderitem->Order().KdAuftragNr());
    _return.__set_PositionNo(orderitem->PosNr());

    csc::order::TourInformation tourInfo = Helper::getPositionDeliveryInformation(orderitem, false);
    _return.__set_TourInfo(tourInfo);

    order::ArticleInformation articleDelivered;
    basar::VarString tmp;

    articleDelivered.__set_ArticleNo(orderitem->ArtikelNr());
    tmp = orderitem->ArticleCode()();
    tmp.trim(basar::cmnutil::BString::FIRST_END);
    articleDelivered.__set_ArticleCode(tmp);
    tmp = getSession()->ConvertPzn2Ean(orderitem->ArtikelNr(), 13)();   // TODO verify!!!
    tmp.trim(basar::cmnutil::BString::FIRST_END);
    articleDelivered.__set_Ean(tmp);

    if (orderitem->ArtBase() != NULL && orderitem->ArtBase()->IsGoodState())
    {
        basar::Int16 TextKey = orderitem->ArtBase()->TextKey();
        if (TextKey > 0)
        {
            pxArticleText ptext(getSession().get(), TextKey);
            if (!ptext.Get(cDBGET_READONLY))
            {
                tmp = ptext.Text()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                articleDelivered.__set_ArticleText(tmp);
            }
        }
        tmp = orderitem->ArtBase()->Bezeichnung()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        articleDelivered.__set_ArticleName(tmp);

        tmp = orderitem->ArtBase()->ArtikelLangname()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        articleDelivered.__set_ArticleLongName(tmp);

        tmp = orderitem->ArtBase()->Einheit()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        articleDelivered.__set_ArticleUnit(tmp);

        tmp = orderitem->ArtBase()->Darreichform()();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        articleDelivered.__set_ArticleHandout(tmp);

        std::stringstream s;
        s << orderitem->ArtBase()->CodeBlocage();
        tmp = s.str();
        tmp.trim(basar::cmnutil::BString::FIRST_END);
        _return.__set_CodeBlocage(tmp);
        articleDelivered.__set_CodeBlocage(tmp);

        if (orderitem->TotalIBTQuantity() > 0)
        {
            _return.__set_CodeBlocage("T");
            articleDelivered.__set_CodeBlocage("T");
        }
    }
    else
    {
        _return.__set_CodeBlocage("2");
        articleDelivered.__set_CodeBlocage("2");
    }

    _return.__set_ArticleDelivered(articleDelivered);

    //if (request.__isset.QuantityRebateInKind && request.QuantityRebateInKind > 0)
    //{
    //  _return.__set_QuantityLack(request.QuantityOrdered + request.QuantityRebateInKind - orderitem->MengeGeliefert() - orderitem->TotalIBTQuantity() -
    //      orderitem->MengeNachgeliefert() - orderitem->MengeDisponiert());
    //}
    //else
    {
        _return.__set_QuantityLack(orderitem->MengeBestellt() + orderitem->MengeNatra() - orderitem->MengeGeliefert() - orderitem->TotalIBTQuantity() -
            orderitem->MengeNachgeliefert() - orderitem->MengeDisponiert());
    }

    // 2017-11-14 Verbund möglich nicht als Defekt behandeln! (Probleme bei MSV3 mit doppelten Anteilen)
    if (orderitem->TotalIBTQuantity() == 0 && orderitem->MengeMoeglich() > 0)
    {
        _return.__set_QuantityLack(_return.QuantityLack - orderitem->MengeMoeglich());
    }

    if (_return.QuantityLack < 0)
        _return.__set_QuantityLack(0);

    _return.__set_QuantityOrdered(orderitem->MengeBestellt());
    _return.__set_QuantityInterBranch(orderitem->TotalIBTQuantity());
    _return.__set_QuantityInterBranchPossible(orderitem->MengeMoeglich()); // added, SH, 15.02.2017
    _return.__set_QuantityRestDelivery(orderitem->MengeNachgeliefert());
    _return.__set_QuantityDelivered(orderitem->MengeGeliefert());
    _return.__set_QuantityDispo(orderitem->MengeDisponiert());
    _return.__set_QuantityNatra(orderitem->MengeNatra());
    _return.__set_BranchNoIbt(getSession()->Order()->AuxFil());
    _return.__set_IbtQuantityAsNormal(false);

    // Ausweichartikel gebucht
    //if (orderitem->IsQStateAlternate() || orderitem->IsReimportArtikel())
    //{
    //  order::ArticleInformation articleOrdered;
    //  articleOrdered.__set_ArticleCode(request.ArticleCode);
    //  articleOrdered.__set_ArticleNo(articleNo);
    //  articleOrdered.__set_Ean(getSession()->ConvertPzn2Ean(articleNo, 13)());
    //  pxArticleInfo* ArtInfo = orderitem->ArticleInfoRequest(articleNo, orderitem->MengeBestaetigt());
    //  if (ArtInfo != NULL)
    //  {
    //      tmp = ArtInfo->ArtBase()->Bezeichnung()();
    //      tmp.trim(basar::cmnutil::BString::FIRST_END);
    //      articleOrdered.__set_ArticleName(tmp);

    //      tmp = ArtInfo->ArtBase()->ArtikelLangname()();
    //      tmp.trim(basar::cmnutil::BString::FIRST_END);
    //      articleOrdered.__set_ArticleLongName(tmp);

    //      tmp = ArtInfo->ArtBase()->Einheit()();
    //      tmp.trim(basar::cmnutil::BString::FIRST_END);
    //      articleOrdered.__set_ArticleUnit(tmp);

    //      tmp = ArtInfo->ArtBase()->Darreichform()();
    //      tmp.trim(basar::cmnutil::BString::FIRST_END);
    //      articleOrdered.__set_ArticleHandout(tmp);
    //  }
    //  _return.__set_ArticleOrdered(articleOrdered);
    //}

    // prices
    Helper::getPriceInformation(_return, orderitem);

    // quantities
    _return.__set_QuantityReserved(orderitem->MengeReserviert());

    // Batch
    _return.__set_Batch(orderitem->GetChargenNr());
    _return.__set_FixBatch(orderitem->IsFixBatch());
    _return.__set_ExpiryDate(orderitem->ArticleExpireDate());

    char TEXT[100];
    memset(TEXT, 0, sizeof(TEXT));
    int errCode = orderitem->GetError(TEXT);
    if (errCode > 100000)
    {
        errCode /= 100;
    }
    csc::base::ReturnStruct retValue;
    retValue.__set_ErrorCode(static_cast<csc::types::MessageCodeEnum::type>(errCode));
    retValue.__set_ErrorMessage(TEXT);
    _return.__set_RetValue(retValue);

    // codes
    if (getSession()->isFrance() || getSession()->isFrancePrewhole())
    {
        if (_return.RetValue.ErrorCode != 0)
        {
            pxCountryCodes* CC = getSession()->CountryCodesInfo(getSession()->Order()->FilialNr(), _return.CodeBlocage.c_str());
            if (CC != NULL)
            {
                tmp = CC->SeraCode()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_SeraCode(tmp);

                tmp = CC->XMLCode()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_XmlCode(tmp);

                tmp = CC->XMLText()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_XmlText(tmp);
                delete CC;
            }
        }
    }
    if (getSession()->Country() == "AU" || getSession()->isGermany())
    {
        basar::VarString xmlcode;
        xmlcode.format("%ld", _return.RetValue.ErrorCode);
        _return.__set_XmlCode(xmlcode);
        if (_return.RetValue.ErrorCode != 0)
        {
            pxCountryCodes* CC = getSession()->CountryCodesInfo(getSession()->Order()->FilialNr(), xmlcode.c_str(), (short)pxCountryCodes::CCT_XMLCODE);
            if (CC != NULL)
            {
                tmp = CC->SeraCode()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_SeraCode(tmp);

                tmp = CC->XMLText()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_XmlText(tmp);

                tmp = CC->InfoCode()();
                tmp.trim(basar::cmnutil::BString::FIRST_END);
                _return.__set_LackReasonCountryCode(tmp);
                delete CC;
            }
        }
    }
}


} // namespace service
} // namespace csc
