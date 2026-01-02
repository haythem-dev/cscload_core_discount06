/*
 * icallbackcomponentmanager.hpp
 *
 *  Created on: 14.06.2016
 *  Author: sebastian.barth
 */

#ifndef ICALLBACKCOMPONENTMANAGER_HPP
#define ICALLBACKCOMPONENTMANAGER_HPP

#include <base/irunnableptr.h>
#include <callback/domainmodule/icallbackptr.h>
#include <callback/domainmodule/inewcallbackptr.h>
#include <callback/domainmodule/inewcallbackcritposptr.h>
#include <callback/domainmodule/callbackoverviewcollectionptr.h>
#include <callback/domainmodule/callbackposcollectionptr.h>
#include <callback/domainmodule/callbackcustomercollectionptr.h>
#include <callback/domainmodule/callbackdivisioncollectionptr.h>
#include <callback/domainmodule/callbackreasoncollectionptr.h>
#include <callback/domainmodule/callbackstatuscollectionptr.h>
#include <callback/repository/findcallbacksrequest.h>
#include <callback/repository/findcustomersrequest.h>
#include <boost/shared_ptr.hpp>

class ICallbackComponentManager
{
public:
    virtual ~ICallbackComponentManager() {}

    virtual bool hasCallback(long const callbackNo, short const branchNo) = 0;
    virtual bool tryGetCallback(long const callbackNo, short const branchNo, libcsc::callback::domMod::ICallbackPtr& callback, libcsc::callback::domMod::CallbackPosCollectionPtr& callbackPos) = 0;
    virtual libcsc::base::IRunnablePtr getWriteNewCallbackCritPosUC(libcsc::callback::domMod::INewCallbackCritPosPtr const newCallbackCritPos) = 0;
    virtual libcsc::callback::domMod::CallbackDivisionCollectionPtr getCallbackDivisions(short const branchNo) = 0;
    virtual libcsc::callback::domMod::CallbackReasonCollectionPtr getCallbackReasons(short const branchNo, short const divisionNo) = 0;
    virtual libcsc::callback::domMod::CallbackStatusCollectionPtr getCallbackStatuses(short const branchNo) = 0;
    virtual libcsc::callback::domMod::CallbackCustomerCollectionPtr findCustomers(libcsc::callback::repo::FindCustomersRequestPtr const findCustomersRequest) = 0;
    virtual basar::Int32 getFindCustomersCount(libcsc::callback::repo::FindCustomersRequestPtr const findCustomersRequest) = 0;
    virtual libcsc::base::IRunnablePtr getWriteNewCallbackUC(libcsc::callback::domMod::INewCallbackPtr const newCallback) = 0;
    virtual libcsc::callback::domMod::CallbackOverviewCollectionPtr findCallbacks(libcsc::callback::repo::FindCallbacksRequestPtr const findCallbacksRequest) = 0;
    virtual basar::Int32 getFindCallbacksCount(libcsc::callback::repo::FindCallbacksRequestPtr const findCallbacksRequest) = 0;
    virtual void getGetCallbackDivisionAndReasonName(
        basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo, basar::VarString& divisionName, basar::VarString& reasonName) = 0;
    virtual bool isCallbackStatusVisibile(basar::Int16 const branchNo) = 0;
};

typedef boost::shared_ptr<ICallbackComponentManager> ICallbackComponentManagerPtr;

#endif // ICALLBACKCOMPONENTMANAGER_HPP
