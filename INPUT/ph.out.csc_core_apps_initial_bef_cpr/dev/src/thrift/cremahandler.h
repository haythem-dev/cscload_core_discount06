/*
 * cremahandler.h
 *
 *  Created on: 05.07.2022
 *  Author: sebastian.barth
 */

#ifndef GUARD_CSC_SERVICE_CREMAHANDLER_H
#define GUARD_CSC_SERVICE_CREMAHANDLER_H

#include <libbasar_definitions.h>
#include <pxordertransmitptr.h>
#include <pxorder.hpp>
#include <pxorddef.h>
#include <crema/repository/irepositoryptr.h>

#include "crema_types.h"
#include "csclibtothrifthandlerbase.h"

namespace libcsc {
namespace crema {
class CremaOrder;
}
}

namespace csc {
namespace service {

class CremaHandler : public CscLibToThriftHandlerBase
{
public:
    CremaHandler();
    virtual ~CremaHandler();

    void processOpenCremaOrder(
        csc::crema::OpenCremaOrderResponse& _return,
        const ::csc::crema::OpenCremaOrderRequest& request);

    void processUserSuggestion(
        csc::crema::UserSuggestionResponse& _return,
        const ::csc::crema::UserSuggestionRequest& request);

    void processOpenCremaOrders(
        csc::crema::OpenCremaOrdersResponse& _return,
        const ::csc::crema::OpenCremaOrdersRequest& request);

    void processFinishedTodayCremaOrders(
        csc::crema::FinishedTodayCremaOrdersResponse& _return,
        const ::csc::crema::FinishedTodayCremaOrdersRequest& request);

    void processLastDecision(
        csc::crema::LastDecisionResponse& _return,
        const ::csc::crema::LastDecisionRequest& request);

    void processFinishOrder(
        csc::crema::FinishOrderResponse& _return,
        const ::csc::crema::FinishOrderRequest& request);

private:
    std::string blogException(basar::Exception const& ex, std::string const& methodName);

    void findOrderData(libcsc::crema::repo::IRepositoryPtr repo, const basar::VarString& uuid, basar::Int32& orderNo, basar::Int16& branchNo);

    void findGuiData(libcsc::crema::repo::IRepositoryPtr repo,
        const basar::Int16& branchNo, const basar::Int32& orderNo,
        csc::crema::OpenCremaOrderResponse& _return);

    void findMailData(libcsc::crema::repo::IRepositoryPtr repo,
        const basar::VarString& uuid,
        csc::crema::OpenCremaOrderResponse& _return);

    void findReasons(libcsc::crema::repo::IRepositoryPtr repo,
        const basar::Int32& country, const basar::Int32& language, bool unlock,
        csc::crema::OpenCremaOrderResponse& _return);

    Order::ApprovalType findReasonId(libcsc::crema::repo::IRepositoryPtr repo,
        const basar::Int32& country, const basar::Int32& language, bool unlock,
        const basar::VarString& reasonText);

    void findApprovalData(const basar::Int32& orderNo, const basar::Int16& branchNo,
        csc::crema::OpenCremaOrderResponse& _return);

    void setCommonCremaOrderValues(csc::crema::CremaOrder& cremaOrder, libcsc::crema::CremaOrder* values);

    csc::base::ReturnStruct openOrder(const ::csc::crema::FinishOrderRequest& request);

    bool closeOrderDebtLimit(const ::csc::crema::FinishOrderRequest& request);

    bool cancelOrderDebtLimit(const ::csc::crema::FinishOrderRequest& request);

    bool closeCancelOrder(const ::csc::crema::FinishOrderRequest& request, Order::CloseType closetype);

    void findCreditLimitData(libcsc::crema::repo::IRepositoryPtr repo,
        const basar::Int16& branchNo, const basar::Int32& orderNo,
        csc::crema::OpenCremaOrderResponse& _return);
};

} // namespace service
} // namespace csc

#endif // GUARD_CSC_SERVICE_CREMAHANDLER_H
