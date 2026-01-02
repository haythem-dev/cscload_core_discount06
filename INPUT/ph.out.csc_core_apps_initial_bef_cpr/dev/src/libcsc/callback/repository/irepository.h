/*
 * irepository.h
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#ifndef GUARD_LIBCSC_CALLBACK_IREPOSITORY_H
#define GUARD_LIBCSC_CALLBACK_IREPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasar_definitions.h>
#include "callback/domainmodule/callbackoverviewcollectionptr.h"
#include "callback/domainmodule/callbackposcollectionptr.h"
#include "callback/domainmodule/callbackcustomercollectionptr.h"
#include "callback/domainmodule/callbackdivisioncollectionptr.h"
#include "callback/domainmodule/callbackreasoncollectionptr.h"
#include "callback/domainmodule/callbackstatuscollectionptr.h"
#include "callback/domainmodule/icallbackptr.h"
#include "callback/domainmodule/icallbackcustomerptr.h"
#include "callback/domainmodule/icallbackitemptr.h"
#include "callback/domainmodule/icallbackreasonptr.h"
#include "callback/domainmodule/icritposptr.h"
#include "callback/domainmodule/icritptr.h"
#include "callback/repository/findcallbacksrequest.h"
#include "callback/repository/findcustomersrequest.h"

namespace libcsc {
namespace callback {
namespace repo {

class IRepository
{
public:
    virtual ~IRepository() {}

    virtual void injectDbName(basar::VarString const& dbName) = 0;
    virtual void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory) = 0;
    virtual void injectFindAccessor(persistence::IAccessorPtr accessor) = 0;
    virtual void injectInsertCritAccessor(persistence::IAccessorPtr accessor) = 0;
    virtual void injectInsertCritPosAccessor(persistence::IAccessorPtr accessor) = 0;
    virtual void injectInsertCallbackItemAccessor(persistence::IAccessorPtr accessor) = 0;
    virtual void injectUpdateCallbackItemAccessor(persistence::IAccessorPtr accessor) = 0;

    virtual bool hasCallback(basar::Int32 const callbackNo) const = 0;
    virtual bool tryGetCallback(basar::Int32 const callbackNo, domMod::ICallbackPtr& callback, domMod::CallbackPosCollectionPtr& callbackPos) const = 0;

    virtual void writeNewCritPos(basar::Int32 const callbackNo, basar::Int16 const statusNo, domMod::ICritPosPtr critPos) = 0;

    virtual domMod::CallbackDivisionCollectionPtr getDivisions(basar::Int16 const branchNo) const = 0;
    virtual domMod::CallbackReasonCollectionPtr getReasons(basar::Int16 const branchNo, basar::Int16 const divisionNo) const = 0;
    virtual domMod::CallbackStatusCollectionPtr getStatuses() const = 0;

    virtual domMod::CallbackCustomerCollectionPtr findCustomers(FindCustomersRequestPtr const findCustomersRequest) const = 0;
    virtual basar::Int32 getFindCustomersCount(FindCustomersRequestPtr const findCustomersRequest) const = 0;

    virtual domMod::ICallbackDivisionPtr findCallbackDivision(basar::Int16 const branchNo, basar::Int16 const divisionNo) const = 0;
    virtual domMod::ICallbackReasonPtr findCallbackReason(basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo) const = 0;
    virtual basar::Int32 writeNewCallback(domMod::ICallbackItemPtr callback, domMod::ICritPtr crit, domMod::ICritPosPtr critPos) = 0;
    virtual basar::VarString getCallbackMailingList(short const branchNo, short const divisionNo, short const reasonNo) const = 0;

    virtual domMod::ICallbackCustomerPtr findCustomer(basar::Int16 const branchNo, basar::Int32 const customerNo) const = 0;

    virtual basar::VarString findUserName(basar::Int16 const branchNo, basar::Int32 const uid) const = 0;

    virtual domMod::CallbackOverviewCollectionPtr findCallbacks(FindCallbacksRequestPtr const findCallbacksRequest) const = 0;
    virtual basar::Int32 getFindCallbacksCount(FindCallbacksRequestPtr const findCallbacksRequest) const = 0;
    virtual bool isCallbackStatusVisibile() const = 0;
};

} // end namespace repo
} // end namespace callback
} // end namespace libcsc

#endif // GUARD_LIBCSC_CALLBACK_IREPOSITORY_H
