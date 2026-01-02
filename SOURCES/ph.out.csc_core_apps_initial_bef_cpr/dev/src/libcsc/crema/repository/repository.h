/*
 * repository.h
 *
 *  Created on: 05.07.2022
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CREMA_REPOSITORY_H
#define GUARD_LIBCSC_CREMA_REPOSITORY_H

#include "crema/repository/irepository.h"
#include "crema/repository/irepositoryptr.h"
#include <libbasarcmnutil_bstring.h>
#include <libbasardbsql_resultsetref.h>
#include "datatypes/varstring.h"
#include "logger/loggerpool.h"

namespace basar {
namespace db {
namespace sql {
class ResultsetRef;
} } }

namespace libcsc {
namespace crema {
namespace repo {

class Repository : public IRepository
{
public:
    virtual ~Repository();

    static IRepositoryPtr create(log4cplus::Logger const& logger);

    virtual void injectFindAccessor(persistence::IAccessorPtr accessor);
    virtual void injectInsertAccessor(persistence::IAccessorPtr accessor);
    virtual void injectUpdateAccessor(persistence::IAccessorPtr accessor);

    virtual GuiDataPtr findGuiData(const basar::Int16& branchNo, const basar::Int32& orderNo);

    virtual MailDataPtr findMailData(const basar::VarString& uuid);

    virtual ReasonCollectionPtr findReasons(
        const basar::Int32& country, const basar::Int32& language, const bool& unlock);

    virtual OrderDataPtr findOrderData(const basar::VarString& uuid);

    virtual UserSuggestionPtr findUserSuggestion(
        const basar::Int16& branchNo, const basar::Int32& customerNo, const basar::VarString& userName, const bool& byTime);

    virtual CremaOrderCollectionPtr findOpenCremaOrders(
        const basar::Int16& userLevel, const std::vector<basar::Int16>& relevantBranchNos);

    virtual CremaOrderCollectionPtr findFinishedTodayCremaOrders(const std::vector<basar::Int16>& relevantBranchNos);

    virtual void saveLastDecision(
        const basar::Int16& typeClose, const basar::Int32& reason, const basar::VarString& comment, const basar::VarString& user,
        const basar::Int16& branchNo, const basar::Int32& orderNo);
    virtual CreditLimitDataCollectionPtr findCreditLimitData(const basar::Int16& branchNo, const basar::Int32& orderNo);

protected:
    Repository(log4cplus::Logger const& logger);

private:
    Repository& operator=(const Repository&);

    basar::VarString m_DbName;
    persistence::ITransactionFactoryPtr m_TransactionFactory;
    persistence::IAccessorPtr m_FindAccessor;
    persistence::IAccessorPtr m_InsertAccessor;
    persistence::IAccessorPtr m_UpdateAccessor;
    log4cplus::Logger const m_Logger;
};

} // end namespace repo
} // end namespace crema
} // end namespace libcsc

#endif // GUARD_LIBCSC_CREMA_REPOSITORY_H
