/*
 * callbackcomponentmanager.hpp
 *
 *  Created on: 14.06.2016
 *  Author: sebastian.barth
 */

#ifndef CALLBACKCOMPONENTMANAGER_HPP
#define CALLBACKCOMPONENTMANAGER_HPP

#include "../icallbackcomponentmanager.hpp"
#include <callback/componentmanager/componentmanagerptr.h>
#include <persistence/connectionptr.h>

class pxSession;

class CallbackComponentManager : public ICallbackComponentManager
{
public:
    CallbackComponentManager();
    virtual ~CallbackComponentManager();

    static ICallbackComponentManagerPtr create(pxSession* session, libcsc::persistence::ConnectionPtr connection);

    virtual bool hasCallback(long const callbackNo, short const branchNo);
    virtual bool tryGetCallback(long const callbackNo, short const branchNo, libcsc::callback::domMod::ICallbackPtr& callback, libcsc::callback::domMod::CallbackPosCollectionPtr& callbackPos);
    virtual libcsc::base::IRunnablePtr getWriteNewCallbackCritPosUC(libcsc::callback::domMod::INewCallbackCritPosPtr const newCallbackCritPos);
    virtual libcsc::callback::domMod::CallbackDivisionCollectionPtr getCallbackDivisions(short const branchNo);
    virtual libcsc::callback::domMod::CallbackReasonCollectionPtr getCallbackReasons(short const branchNo, short const divisionNo);
    virtual libcsc::callback::domMod::CallbackStatusCollectionPtr getCallbackStatuses(short const branchNo);
    virtual libcsc::callback::domMod::CallbackCustomerCollectionPtr findCustomers(libcsc::callback::repo::FindCustomersRequestPtr const findCustomersRequest);
    virtual basar::Int32 getFindCustomersCount(libcsc::callback::repo::FindCustomersRequestPtr const findCustomersRequest);
    virtual libcsc::base::IRunnablePtr getWriteNewCallbackUC(libcsc::callback::domMod::INewCallbackPtr const newCallback);
    virtual libcsc::callback::domMod::CallbackOverviewCollectionPtr findCallbacks(libcsc::callback::repo::FindCallbacksRequestPtr const findCallbacksRequest);
    virtual basar::Int32 getFindCallbacksCount(libcsc::callback::repo::FindCallbacksRequestPtr const findCallbacksRequest);
    virtual void getGetCallbackDivisionAndReasonName(
        basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo, basar::VarString& divisionName, basar::VarString& reasonName);
    virtual bool isCallbackStatusVisibile(basar::Int16 const branchNo);

private:
    libcsc::callback::ComponentManagerPtr m_LibCscCallbackCM;
    pxSession* m_Session;
};

#endif // CALLBACKCOMPONENTMANAGER_HPP
