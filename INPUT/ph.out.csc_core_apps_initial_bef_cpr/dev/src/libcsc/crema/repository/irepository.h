/*
 * irepository.h
 *
 *  Created on: 05.07.2022
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CREMA_IREPOSITORY_H
#define GUARD_LIBCSC_CREMA_IREPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasar_definitions.h>
#include <crema/guidata/guidataptr.h>
#include <crema/maildata/maildataptr.h>
#include <crema/orderdata/orderdataptr.h>
#include <crema/usersuggestion/usersuggestionptr.h>
#include <crema/cremaorder/cremaordercollectionptr.h>
#include <crema/creditlimitdata/creditlimitdatacollectionptr.h>
#include <crema/reason/reasoncollectionptr.h>

namespace libcsc {
namespace crema {
namespace repo {

class IRepository
{
public:
    virtual ~IRepository() {}

    virtual void injectFindAccessor(persistence::IAccessorPtr accessor) = 0;
    virtual void injectInsertAccessor(persistence::IAccessorPtr accessor) = 0;
    virtual void injectUpdateAccessor(persistence::IAccessorPtr accessor) = 0;

    virtual GuiDataPtr findGuiData(const basar::Int16& branchNo, const basar::Int32& orderNo) = 0;

    virtual MailDataPtr findMailData(const basar::VarString& uuid) = 0;

    virtual ReasonCollectionPtr findReasons(
        const basar::Int32& country, const basar::Int32& language, const bool& unlock) = 0;

    virtual OrderDataPtr findOrderData(const basar::VarString& uuid) = 0;

    virtual UserSuggestionPtr findUserSuggestion(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::VarString& userName, const bool& byTime) = 0;

    virtual CremaOrderCollectionPtr findOpenCremaOrders(
        const basar::Int16& userLevel, const std::vector<basar::Int16>& relevantBranchNos) = 0;

    virtual CremaOrderCollectionPtr findFinishedTodayCremaOrders(const std::vector<basar::Int16>& relevantBranchNos) = 0;

    virtual void saveLastDecision(
        const basar::Int16& typeClose, const basar::Int32& reason, const basar::VarString& comment, const basar::VarString& user,
        const basar::Int16& branchNo, const basar::Int32& orderNo) = 0;

    virtual CreditLimitDataCollectionPtr findCreditLimitData(const basar::Int16& branchNo, const basar::Int32& orderNo) = 0;
};

} // end namespace repo
} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_IREPOSITORY_H
