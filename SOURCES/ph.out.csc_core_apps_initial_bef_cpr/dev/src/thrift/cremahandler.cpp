/*
 * cremahandler.cpp
 *
 *  Created on: 05.07.2022
 *  Author: sebastian.barth
 */

#include "cremahandler.h"

#include <boost/make_shared.hpp>
#include <logger/loggerpool.h>
#include <pxxmit.hpp>
#include <pxcstbas.hpp>
#include "cscservicehelper.h"

#include <crema/componentmanager/cremacomponentmanager.h>
#include <crema/repository/irepositoryptr.h>
#include <crema/repository/repository.h>
#include <crema/guidata/guidata.h>
#include <crema/maildata/maildata.h>
#include <crema/maildata/recipient.h>
#include <crema/reason/reason.h>
#include <crema/orderdata/orderdata.h>
#include <crema/usersuggestion/usersuggestion.h>
#include <crema/cremaorder/cremaorder.h>
#include <crema/creditlimitdata/creditlimitdata.h>
#include <types/messagecodeenum.inc>
#include <base/iint32result.h>
#include <base/irunnable.h>

namespace csc {
namespace service {

CremaHandler::CremaHandler()
{
}

CremaHandler::~CremaHandler()
{
}

void CremaHandler::processOpenCremaOrder(
    csc::crema::OpenCremaOrderResponse& _return,
    const ::csc::crema::OpenCremaOrderRequest& request)
{
    libcsc::crema::repo::IRepositoryPtr repo = getSession()->getCremaComponentManager()->getRepository();

    basar::Int32 orderNo;
    basar::Int16 branchNo;
    findOrderData(repo, request.Uuid, orderNo, branchNo);

    findGuiData(repo, branchNo, orderNo, _return);

    findMailData(repo, request.Uuid, _return);

    findReasons(repo, request.Country, request.Language, true, _return);

    findReasons(repo, request.Country, request.Language, false, _return);

    findApprovalData(orderNo, branchNo, _return);

    if (getSession()->isBulgaria())
    {
        findCreditLimitData(repo, branchNo, orderNo, _return);
    }
}

void CremaHandler::findGuiData(libcsc::crema::repo::IRepositoryPtr repo,
    const basar::Int16& branchNo, const basar::Int32& orderNo,
    csc::crema::OpenCremaOrderResponse& _return)
{
    libcsc::crema::GuiDataPtr result = repo->findGuiData(branchNo, orderNo);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    csc::crema::GuiData guiData;
    guiData.__set_BranchNo(result->getBranchNo());
    guiData.__set_Idf(result->getIdf());
    guiData.__set_CreditLimit(result->getCreditLimit().toFloat64());
    guiData.__set_Customer(result->getCustomer());
    guiData.__set_OrderID(result->getOrderID());
    guiData.__set_Place(result->getPlace());
    guiData.__set_PostalCode(result->getPostalCode());
    guiData.__set_Apothecary(result->getApothecary());
    guiData.__set_OrderAmount(result->getOrderAmount().toFloat64());
    guiData.__set_SumDebitside(result->getSumDebitside().toFloat64());
    guiData.__set_SumCreditside(result->getSumCreditside().toFloat64());
    guiData.__set_SumMonTurnover(result->getSumMonTurnover().toFloat64());
    guiData.__set_SumDayTurnover(result->getSumDayTurnover().toFloat64());
    guiData.__set_SumReturns(result->getSumReturns().toFloat64());
    guiData.__set_SumGoodsReceipt(result->getSumGoodsReceipt().toFloat64());
    guiData.__set_ChainNo(result->getChainNo());
    _return.__set_Gui(guiData);
}

void CremaHandler::findMailData(libcsc::crema::repo::IRepositoryPtr repo,
    const basar::VarString& uuid,
    csc::crema::OpenCremaOrderResponse& _return)
{
    libcsc::crema::MailDataPtr result = repo->findMailData(uuid);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        std::stringstream ss;
        ss << "CremaHandler::findMailData: no mail data found for uuid=" << uuid;
        BLOG_WARN(libcsc::LoggerPool::getLoggerCrema(), ss.str());
        return;
    }

    csc::crema::MailData mailData;
    mailData.__set_Sender(result->getSender());

    mailData.__set_Recipient_List(csc::crema::RecipientList());
    libcsc::crema::RecipientCollection::const_iterator it = result->getRecipients()->begin();
    while (it != result->getRecipients()->end())
    {
        csc::crema::Recipient recipient;
        recipient.__set_EmailType(static_cast<csc::types::CremaEmailTypeEnum::type>((*it)->getEmailType()));
        recipient.__set_Address((*it)->getAddress());
        mailData.Recipient_List.push_back(recipient);
        ++it;
    }
    _return.__set_Mail(mailData);
}

void CremaHandler::findReasons(libcsc::crema::repo::IRepositoryPtr repo,
    const basar::Int32& country, const basar::Int32& language, bool unlock,
    csc::crema::OpenCremaOrderResponse& _return)
{
    libcsc::crema::ReasonCollectionPtr result = repo->findReasons(country, language, unlock);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    std::vector<std::string> reasonsList;
    libcsc::crema::ReasonCollection::const_iterator it = result->begin();

    while (it != result->end())
    {
        reasonsList.push_back((*it)->getReason());
        ++it;
    }

    csc::crema::Reasons reasons;

    reasons.__set_Reasons_List(reasonsList);
    if (unlock)
    {
        _return.__set_UnlockReasons(reasons);
    }
    else
    {
        _return.__set_CancelReasons(reasons);
    }
}

Order::ApprovalType CremaHandler::findReasonId(libcsc::crema::repo::IRepositoryPtr repo,
    const basar::Int32& country, const basar::Int32& language, bool unlock,
    const basar::VarString& reasonText)
{
    libcsc::crema::ReasonCollectionPtr result = repo->findReasons(country, language, unlock);

    if (result == NULL)
    {
        return Order::NOT_DEFINED;
    }
    basar::Int32 reasonId = 0;
    libcsc::crema::ReasonCollection::const_iterator it = result->begin();

    while (it != result->end())
    {
        if ((*it)->getReason() == reasonText)
        {
            reasonId = (*it)->getId();
            break;
        }
        ++it;
    }

    return static_cast<Order::ApprovalType>(reasonId);
}

void CremaHandler::findOrderData(libcsc::crema::repo::IRepositoryPtr repo, const basar::VarString& uuid,
    basar::Int32& orderNo, basar::Int16& branchNo)
{
    libcsc::crema::OrderDataPtr result = repo->findOrderData(uuid);

    if (result == NULL)
    {
        orderNo = 0;
        branchNo = 0;
        return;
    }

    orderNo = result->getOrderID();
    branchNo = result->getBranchNo();
}

void CremaHandler::processUserSuggestion(
    csc::crema::UserSuggestionResponse& _return,
    const ::csc::crema::UserSuggestionRequest& request)
{
    libcsc::crema::repo::IRepositoryPtr repo = getSession()->getCremaComponentManager()->getRepository();

    libcsc::crema::UserSuggestionPtr result = repo->findUserSuggestion(
        request.BranchNo, request.CustomerNo, request.UserName, request.ByTime);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_Choice(result->getChoice());
    _return.__set_ChoiceReason(result->getChoiceReason());
    _return.__set_ChoiceComment(result->getChoiceComment());
}

void CremaHandler::processOpenCremaOrders(
    csc::crema::OpenCremaOrdersResponse& _return,
    const ::csc::crema::OpenCremaOrdersRequest& request)
{
    libcsc::crema::repo::IRepositoryPtr repo = getSession()->getCremaComponentManager()->getRepository();

    libcsc::crema::CremaOrderCollectionPtr result = repo->findOpenCremaOrders(
        request.UserLevel, request.RelevantBranchNos);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_Order_List(csc::crema::CremaOrderList());
    libcsc::crema::CremaOrderCollection::const_iterator it = result->begin();
    while (it != result->end())
    {
        csc::crema::CremaOrder cremaOrder;
        setCommonCremaOrderValues(cremaOrder, it->get());
        cremaOrder.__set_Guid((*it)->getGuid());
        cremaOrder.__set_SendDate(csc::service::Helper::getCscDateFromIntDate((*it)->getSendDate()));
        cremaOrder.__set_Url((*it)->getUrl());
        _return.Order_List.push_back(cremaOrder);
        ++it;
    }
}

void CremaHandler::processFinishedTodayCremaOrders(
    csc::crema::FinishedTodayCremaOrdersResponse& _return,
    const ::csc::crema::FinishedTodayCremaOrdersRequest& request)
{
    libcsc::crema::repo::IRepositoryPtr repo = getSession()->getCremaComponentManager()->getRepository();

    libcsc::crema::CremaOrderCollectionPtr result = repo->findFinishedTodayCremaOrders(
        request.RelevantBranchNos);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }

    _return.__set_Order_List(csc::crema::CremaOrderList());
    libcsc::crema::CremaOrderCollection::const_iterator it = result->begin();
    while (it != result->end())
    {
        csc::crema::CremaOrder cremaOrder;
        setCommonCremaOrderValues(cremaOrder, it->get());
        cremaOrder.__set_ReleaseUser((*it)->getReleaseUser());
        cremaOrder.__set_ReleaseReason((*it)->getReleaseReason());
        cremaOrder.__set_ReleaseComment((*it)->getReleaseComment());
        _return.Order_List.push_back(cremaOrder);
        ++it;
    }
}

void CremaHandler::setCommonCremaOrderValues(csc::crema::CremaOrder& cremaOrder, libcsc::crema::CremaOrder* values)
{
    cremaOrder.__set_OrderNo(values->getOrderNo());
    cremaOrder.__set_BranchNo(values->getBranchNo());
    cremaOrder.__set_OrderValue(values->getOrderValue().toFloat64());
    cremaOrder.__set_CustomerNo(values->getCustomerNo());
    cremaOrder.__set_Pharmacy(values->getPharmacy());
    cremaOrder.__set_Place(values->getPlace());
    cremaOrder.__set_ChainNo(values->getChainNo());
}

void CremaHandler::findApprovalData(const basar::Int32& orderNo, const basar::Int16& branchNo,
    csc::crema::OpenCremaOrderResponse& _return)
{
    short approvalMax = 0;
    short approvalCancel = 0;
    short approvalClose = 0;

    getSession()->Order()->GetReleaseApprovalValues(orderNo, branchNo, approvalMax, approvalCancel, approvalClose);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (!(getSession()->Order()->IsGoodState()))
    {
        return;
    }

    csc::crema::ApprovalData approvalData;
    approvalData.__set_ApprovalMax(approvalMax);
    approvalData.__set_ApprovalClose(approvalClose);
    approvalData.__set_ApprovalCancel(approvalCancel);
    _return.__set_Approval(approvalData);
}

void CremaHandler::processLastDecision(
    csc::crema::LastDecisionResponse& _return,
    const ::csc::crema::LastDecisionRequest& request)
{
    libcsc::crema::repo::IRepositoryPtr repo = getSession()->getCremaComponentManager()->getRepository();

    repo->saveLastDecision(
        request.TypeClose, request.Reason, request.Comment, request.User, request.BranchNo, request.OrderNo);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
}

void CremaHandler::processFinishOrder(
    csc::crema::FinishOrderResponse& _return,
    const ::csc::crema::FinishOrderRequest& request)
{
    csc::base::ReturnStruct retValue = openOrder(request);
    if (retValue.__isset.ErrorCode)
    {
        _return.__set_RetValue(retValue);
        return;
    }

    // remember values here as they could be away after close/cancel
    basar::Int16 branchNo = getSession()->Order()->Customer()->Vertriebszentrum();
    basar::Int32 orderNo = getSession()->Order()->KdAuftragNr();

    bool res;
    if (request.TypeClose == csc::types::CremaCloseEnum::CloseOrder)
    {
        res = closeOrderDebtLimit(request);
    }
    else
    {
        res = cancelOrderDebtLimit(request);
    }

    if (res)
    {
        getSession()->Order()->DeleteCremaMail(orderNo, branchNo);
    }

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));
}

csc::base::ReturnStruct CremaHandler::openOrder(const ::csc::crema::FinishOrderRequest& request)
{
    getSession()->Reset();
    getSession()->SetTransmissionType(pxOrderTransmit::tDCT_Serial);

    getSession()->NewOrder(request.OrderId);
    if (getSession()->Order() == NULL)
    {
        csc::base::ReturnStruct retVal;
        retVal.__set_ErrorCode(csc::types::MessageCodeEnum::CMSG_ORD_NOTFOUND);
        return retVal;
    }
    getSession()->Order()->OpenOrder(cDBOPEN_INSERT);

    if (!(getSession()->Order()->IsGoodState()))
    {
        return Helper::getReturnStructFromError(*getSession());
    }
    return csc::base::ReturnStruct();
}

bool CremaHandler::closeOrderDebtLimit(const ::csc::crema::FinishOrderRequest& request)
{
    if (!closeCancelOrder(request, Order::CLOSE))
    {
        return false;
    }

    nDate today;
    if (getSession()->Order()->DatumAuslieferung() <= today)    //Tour ist bei verzögerter Auslieferung bereits korrekt SR-16030276
    {
        getSession()->Order()->SetNextValidRouteNormal((nString)"000000"); //immer nächste gültige Tour
    }

    getSession()->Order()->Close(Order::EntryClosed, Order::cClose_UnConditional);

    return getSession()->Order()->IsGoodState();
}

bool CremaHandler::cancelOrderDebtLimit(const ::csc::crema::FinishOrderRequest& request)
{
    if (!closeCancelOrder(request, Order::CANCEL))
    {
        return false;
    }

    return getSession()->CancelTransmission() == 0 ? true : false;
}

bool CremaHandler::closeCancelOrder(const ::csc::crema::FinishOrderRequest& request, Order::CloseType closetype)
{
    getSession()->Order()->ClearError();
    getSession()->Order()->ClearProblemClearance();

    nString reason = request.Reason.c_str();
    nString comment = request.Comment.c_str();
    nString user = request.User.c_str();
    nString guid = request.Guid.c_str();
    nString url = request.Url.c_str();
    Order::ApprovalType approvalType = Order::NOT_DEFINED;

    if (getSession()->isBulgaria() && closetype == Order::CLOSE)
    {
        libcsc::crema::repo::IRepositoryPtr repo = getSession()->getCremaComponentManager()->getRepository();
        approvalType = findReasonId(repo, 2, 1, true, request.Reason.c_str());
    }

    getSession()->Order()->SetReleaseInfos(reason, comment, user, closetype, guid, url, approvalType);

    // In case of cash approval in Bulgaria order paymen type is set to cash 
    if (getSession()->isBulgaria() && closetype == Order::CLOSE && approvalType == Order::CASH)
    {
        getSession()->Order()->SetOrderToCash();
    }
    if (getSession()->Order()->IsCremaReleased())
    {
        getSession()->Order()->SetNoDebtLimitCheck();
        return true;
    }

    // No error, but fill data for application above

    // Werte merken, die nach erfolgreichem Zurückstellen wieder gesetzt werden ...
    getSession()->Order()->RevertCancelDebtLimitSumDayTurnOver();
    const int lackreason = getSession()->Order()->ErrorNumber();
    nString msg = getSession()->Order()->ErrorString();

    getSession()->Order()->ClearError();

    // Auftrag darf nicht in IE stehen bleiben, sondern muss wieder zurückgestellt werden (DF) !!!
    getSession()->Order()->SetProblemClearance();
    getSession()->Order()->SetEventCode(pxEventReason::CremaVotingInProcess);
    getSession()->Order()->Close(Order::EntryDeferred);

    if (getSession()->Order()->IsGoodState() && (lackreason != 0))
    {
        getSession()->Order()->ExternalError(nMessage(msg), lackreason);
    }
    return false;
}

void CremaHandler::findCreditLimitData(
    libcsc::crema::repo::IRepositoryPtr repo,
    const basar::Int16& branchNo, const basar::Int32& orderNo,
    csc::crema::OpenCremaOrderResponse& _return)
{
    libcsc::crema::CreditLimitDataCollectionPtr result = repo->findCreditLimitData(branchNo, orderNo);

    _return.__set_RetValue(Helper::getReturnStructFromError(*getSession()));

    if (result == NULL)
    {
        return;
    }
    _return.__set_CreditLimits(csc::crema::CreditLimitDataList());
    libcsc::crema::CreditLimitDataCollection::const_iterator it = result->begin();

    while (it != result->end())
    {
        csc::crema::CreditLimitData creditLimitData;
        creditLimitData.__set_CreditLimit((*it)->getCreditLimit().toFloat64());
        creditLimitData.__set_SumDebitside((*it)->getSumDebitside().toFloat64());
        creditLimitData.__set_SumCreditside((*it)->getSumCreditside().toFloat64());
        creditLimitData.__set_SumMonTurnover((*it)->getSumMonTurnover().toFloat64());
        creditLimitData.__set_SumDayTurnover((*it)->getSumDayTurnover().toFloat64());
        creditLimitData.__set_SumReturns((*it)->getSumReturns().toFloat64());
        creditLimitData.__set_SumGoodsReceipt((*it)->getSumGoodsReceipt().toFloat64());
        creditLimitData.__set_LimitType((*it)->getLimitType());
        creditLimitData.__set_IsChain((*it)->getIsChain());
        _return.CreditLimits.push_back(creditLimitData);
        ++it;
    }
}

std::string CremaHandler::blogException(basar::Exception const& ex, std::string const& methodName)
{
    std::stringstream ss;
    ss << "CremaHandler::" << methodName << "() exception: " << ex.what() << std::endl << ex.stackTrace();
    BLOG_ERROR(libcsc::LoggerPool::getLoggerCrema(), ss.str());
    return ss.str();
}

} // namespace service
} // namespace csc
