/*
 * callbackcomponentmanager.cpp
 *
 *  Created on: 14.06.2016
 *  Author: sebastian.barth
 */

#include "pxsess.hpp"
#include "impl/callbackcomponentmanager.hpp"
#include <boost/make_shared.hpp>
#include <logger/loggerpool.h>
#include <callback/componentmanager/componentmanager.h>
#include <callback/repository/irepository.h>
#include <callback/domainmodule/inewcallback.h>
#include <callback/domainmodule/inewcallbackcritpos.h>
#include <callback/domainmodule/icallbackdivision.h>
#include <callback/domainmodule/icallbackreason.h>
#include <callback/domainmodule/icallbackstatus.h>

CallbackComponentManager::CallbackComponentManager()
{
    m_LibCscCallbackCM = boost::make_shared<libcsc::callback::ComponentManager>();
}

CallbackComponentManager::~CallbackComponentManager()
{
}

ICallbackComponentManagerPtr CallbackComponentManager::create(pxSession* session, libcsc::persistence::ConnectionPtr connection)
{
    ICallbackComponentManagerPtr callbackComponentManagerPtr = boost::make_shared<CallbackComponentManager>();

    CallbackComponentManager* callbackComponentManager = dynamic_cast<CallbackComponentManager*>(callbackComponentManagerPtr.get());
    callbackComponentManager->m_Session = session;
    callbackComponentManager->m_LibCscCallbackCM->injectConnection(connection);
    callbackComponentManager->m_LibCscCallbackCM->injectTransactionHandler(session);

    return callbackComponentManagerPtr;
}

bool CallbackComponentManager::hasCallback(long const callbackNo, short const branchNo)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::hasCallback()");
    basar::VarString dbName = m_Session->getDatabaseName(branchNo);
    return m_LibCscCallbackCM->getRepository(dbName)->hasCallback(callbackNo);
}

bool CallbackComponentManager::tryGetCallback(long const callbackNo, short const branchNo, libcsc::callback::domMod::ICallbackPtr& callback, libcsc::callback::domMod::CallbackPosCollectionPtr& callbackPos)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::tryGetCallback()");
    basar::VarString dbName = m_Session->getDatabaseName(branchNo);
    return m_LibCscCallbackCM->getRepository(dbName)->tryGetCallback(callbackNo, callback, callbackPos);
}

libcsc::base::IRunnablePtr CallbackComponentManager::getWriteNewCallbackCritPosUC(libcsc::callback::domMod::INewCallbackCritPosPtr const newCallbackCritPos)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::getWriteNewCallbackCritPosUC()");
    basar::VarString dbName = m_Session->getDatabaseName(newCallbackCritPos->getBranchNo());
    return m_LibCscCallbackCM->getWriteNewCallbackCritPosUC(dbName, newCallbackCritPos);
}

libcsc::callback::domMod::CallbackDivisionCollectionPtr CallbackComponentManager::getCallbackDivisions(short const branchNo)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::getCallbackDivisions()");
    basar::VarString dbName = m_Session->getDatabaseName(branchNo);
    return m_LibCscCallbackCM->getRepository(dbName)->getDivisions(branchNo);
}

libcsc::callback::domMod::CallbackReasonCollectionPtr CallbackComponentManager::getCallbackReasons(short const branchNo, short const divisionNo)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::getCallbackReasons()");
    basar::VarString dbName = m_Session->getDatabaseName(branchNo);
    return m_LibCscCallbackCM->getRepository(dbName)->getReasons(branchNo, divisionNo);
}

libcsc::callback::domMod::CallbackStatusCollectionPtr CallbackComponentManager::getCallbackStatuses(short const branchNo)
{
	BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::getCallbackStatuses()");
	basar::VarString dbName = m_Session->getDatabaseName(branchNo);
    //return m_LibCscCallbackCM->getRepository(dbName)->getStatuses();
    return m_LibCscCallbackCM->getRepository(dbName)->getStatuses();
}

bool CallbackComponentManager::isCallbackStatusVisibile(basar::Int16 const branchNo)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::isCallbackStatusVisibile()");
	basar::VarString dbName = m_Session->getDatabaseName(branchNo);
	return m_LibCscCallbackCM->getRepository(dbName)->isCallbackStatusVisibile();
}

libcsc::callback::domMod::CallbackCustomerCollectionPtr CallbackComponentManager::findCustomers(libcsc::callback::repo::FindCustomersRequestPtr const findCustomersRequest)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::findCustomers()");
    basar::VarString dbName = m_Session->getDatabaseName(findCustomersRequest->BranchNo);
    return m_LibCscCallbackCM->getRepository(dbName)->findCustomers(findCustomersRequest);
}

basar::Int32 CallbackComponentManager::getFindCustomersCount(libcsc::callback::repo::FindCustomersRequestPtr const findCustomersRequest)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::getFindCustomersCount()");
    basar::VarString dbName = m_Session->getDatabaseName(findCustomersRequest->BranchNo);
    return m_LibCscCallbackCM->getRepository(dbName)->getFindCustomersCount(findCustomersRequest);
}

libcsc::base::IRunnablePtr CallbackComponentManager::getWriteNewCallbackUC(libcsc::callback::domMod::INewCallbackPtr const newCallback)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::getWriteNewCallbackUC()");
    basar::VarString dbName = m_Session->getDatabaseName(newCallback->getBranchNo());
	const basar::VarString& server = m_Session->getSmtpServer();
	short port = m_Session->getSmtpPort();
    return m_LibCscCallbackCM->getWriteNewCallbackUC(dbName, m_Session->CMsgStream(), 0, server, port, newCallback);
}

libcsc::callback::domMod::CallbackOverviewCollectionPtr CallbackComponentManager::findCallbacks(libcsc::callback::repo::FindCallbacksRequestPtr const findCallbacksRequest)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::findCallbacks()");
    basar::VarString dbName = m_Session->getDatabaseName(findCallbacksRequest->BranchNo);
    return m_LibCscCallbackCM->getRepository(dbName)->findCallbacks(findCallbacksRequest);
}

basar::Int32 CallbackComponentManager::getFindCallbacksCount(libcsc::callback::repo::FindCallbacksRequestPtr const findCallbacksRequest)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::getFindCallbacksCount()");
    basar::VarString dbName = m_Session->getDatabaseName(findCallbacksRequest->BranchNo);
    return m_LibCscCallbackCM->getRepository(dbName)->getFindCallbacksCount(findCallbacksRequest);
}

void CallbackComponentManager::getGetCallbackDivisionAndReasonName(
        basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo, basar::VarString& divisionName, basar::VarString& reasonName)
{
    BLOG_TRACE_METHOD(libcsc::LoggerPool::getLoggerSession(), "CallbackComponentManager::getGetCallbackDivisionAndReasonName()");
    basar::VarString dbName = m_Session->getDatabaseName(branchNo);
    m_LibCscCallbackCM->getGetCallbackDivisionAndReasonName(dbName, branchNo, divisionNo, reasonNo, divisionName, reasonName);
}
