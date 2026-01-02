/*
 * repository.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_REPOSITORY_H
#define GUARD_LIBCSC_CALLBACK_REPOSITORY_H

#include "callback/repository/irepository.h"
#include "callback/repository/irepositoryptr.h"
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
namespace callback {
namespace repo {

class Repository : public IRepository
{
public:
    virtual ~Repository();

    static IRepositoryPtr create(log4cplus::Logger const& logger);

    virtual void injectDbName(basar::VarString const& dbName);
    virtual void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);
    virtual void injectFindAccessor(persistence::IAccessorPtr accessor);
    virtual void injectInsertCritAccessor(persistence::IAccessorPtr accessor);
    virtual void injectInsertCritPosAccessor(persistence::IAccessorPtr accessor);
    virtual void injectInsertCallbackItemAccessor(persistence::IAccessorPtr accessor);
    virtual void injectUpdateCallbackItemAccessor(persistence::IAccessorPtr accessor);

    virtual bool hasCallback(basar::Int32 const callbackNo) const;
    virtual bool tryGetCallback(basar::Int32 const callbackNo, domMod::ICallbackPtr& callback, domMod::CallbackPosCollectionPtr& callbackPos) const;

    virtual void writeNewCritPos(basar::Int32 const callbackNo, basar::Int16 const statusNo, domMod::ICritPosPtr critPos);

    virtual domMod::CallbackDivisionCollectionPtr getDivisions(basar::Int16 const branchNo) const;
    virtual domMod::CallbackReasonCollectionPtr getReasons(basar::Int16 const branchNo, basar::Int16 const divisionNo) const;
    virtual domMod::CallbackStatusCollectionPtr getStatuses() const;

    virtual domMod::CallbackCustomerCollectionPtr findCustomers(FindCustomersRequestPtr const findCustomersRequest) const;
    virtual basar::Int32 getFindCustomersCount(FindCustomersRequestPtr const findCustomersRequest) const;

    virtual domMod::ICallbackDivisionPtr findCallbackDivision(basar::Int16 const branchNo, basar::Int16 const divisionNo) const;
    virtual domMod::ICallbackReasonPtr findCallbackReason(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo) const;
    virtual basar::Int32 writeNewCallback(domMod::ICallbackItemPtr callback, domMod::ICritPtr crit, domMod::ICritPosPtr critPos);
    virtual basar::VarString getCallbackMailingList(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo) const;

    virtual domMod::ICallbackCustomerPtr findCustomer(basar::Int16 const branchNo, basar::Int32 const customerNo) const;

    virtual basar::VarString findUserName(basar::Int16 const branchNo, basar::Int32 const uid) const;

    virtual domMod::CallbackOverviewCollectionPtr findCallbacks(FindCallbacksRequestPtr const findCallbacksRequest) const;
    virtual basar::Int32 getFindCallbacksCount(FindCallbacksRequestPtr const findCallbacksRequest) const;
	virtual bool isCallbackStatusVisibile() const;

protected:
    Repository(log4cplus::Logger const& logger);

private:
    Repository& operator=(const Repository&);

    domMod::ICallbackItemPtr findCallbackItem(basar::Int32 const callbackNo) const;
    basar::Int32 getNewCritPosNo(basar::Int32 const critNo, basar::VarString const& posTypeTag) const;
    basar::Int32 writeNewCritPos(domMod::ICritPosPtr critPos) const;
    basar::Int32 getNewCritNo() const;
    basar::Int32 writeNewCrit(domMod::ICritPtr crit) const;
    basar::Int32 getNewCallbackNo() const;
    basar::Int32 writeNewCallback(domMod::ICallbackItemPtr callbackItem) const;
    basar::Int32 getNewIndexFromSqlMax(basar::db::sql::ResultsetRef& resultset) const;
    void         updateCallbackStaus(domMod::ICallbackItemPtr callbackItem) const;

    static VarString const LockTagSet;
    static VarString const LockTagUnset;

    basar::VarString m_DbName;
    persistence::ITransactionFactoryPtr m_TransactionFactory;
    persistence::IAccessorPtr m_FindAccessor;
    persistence::IAccessorPtr m_InsertCritAccessor;
    persistence::IAccessorPtr m_InsertCritPosAccessor;
    persistence::IAccessorPtr m_InsertCallbackItemAccessor;
    persistence::IAccessorPtr m_UpdateCallbackItemAccessor;
    log4cplus::Logger const m_Logger;
};

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_REPOSITORY_H
