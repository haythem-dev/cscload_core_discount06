/*
 * componentmanager.cpp
 *
 *  Created on: 26.04.2016
 *  Author: sebastian.barth
 */

#include "componentmanager.h"
#include <persistence/accessor.h>
#include <persistence/connection.h>
#include "logger/loggerpool.h"
#include "callback/domainmodule/newcallbackdm.h"
#include "callback/domainmodule/newcallbackcritposdm.h"
#include "callback/domainmodule/callbackdivisiondm.h"
#include "callback/domainmodule/callbackreasondm.h"
#include "callback/domainmodule/callbackstatusdm.h"
#include "callback/repository/repository.h"
#include "callback/usecase/writenewcallbackcritposuc.h"
#include "callback/usecase/writenewcallbackuc.h"
#include <boost/make_shared.hpp>
#include "util/messagetxtresource.h"

namespace libcsc {
namespace callback {

ComponentManager::ComponentManager()
{
}

ComponentManager::~ComponentManager()
{
}

void ComponentManager::injectConnection(persistence::ConnectionPtr connection)
{
    m_Connection = connection;
}

persistence::IAccessorPtr ComponentManager::createAccessor()
{
    return boost::make_shared<persistence::Accessor>(persistence::Accessor(m_Connection->getDbSqlConnection()));
}

repo::IRepositoryPtr ComponentManager::getRepository(basar::VarString const& dbName)
{
    return createRepository(dbName);
}

repo::IRepositoryPtr ComponentManager::createRepository(basar::VarString const& dbName)
{
    repo::IRepositoryPtr repository = repo::Repository::create(LoggerPool::getLoggerCallback());
    repository->injectFindAccessor(createAccessor());
    repository->injectDbName(dbName);

    return repository;
}

libcsc::persistence::TransactionGuard ComponentManager::createTransaction() const
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerCallback(), "callback::ComponentManager::createTransaction()");

    return persistence::TransactionGuard( m_TransactionHandler );
}

void ComponentManager::injectTransactionHandler(nDataBase* transHandler)
{
    BLOG_TRACE_METHOD(LoggerPool::getLoggerCallback(), "callback::ComponentManager::injectTransactionHandler()");

    m_TransactionHandler = transHandler;
}

libcsc::base::IRunnablePtr ComponentManager::getWriteNewCallbackCritPosUC(basar::VarString const& dbName, domMod::INewCallbackCritPosPtr const newCallbackCritPos)
{
    repo::IRepositoryPtr repository = repo::Repository::create(LoggerPool::getLoggerCallback());
    repository->injectDbName(dbName);
    repository->injectInsertCritPosAccessor(createAccessor());
    repository->injectUpdateCallbackItemAccessor(createAccessor());
    repository->injectFindAccessor(createAccessor());
    repository->injectTransactionFactory(shared_from_this());
    uc::WriteNewCallbackCritPosUCPtr writeNewCallbackCritPosUC = boost::make_shared<uc::WriteNewCallbackCritPosUC>(uc::WriteNewCallbackCritPosUC());
    writeNewCallbackCritPosUC->injectRepository(repository);
    writeNewCallbackCritPosUC->setNewCritPos(newCallbackCritPos);

    return writeNewCallbackCritPosUC;
}

libcsc::base::IRunnablePtr ComponentManager::getWriteNewCallbackUC(basar::VarString const& dbName, std::ifstream* msgStream, int languageCode, 
	const basar::VarString& smtpServer, const short smtpPort, domMod::INewCallbackPtr const newCallback)
{
    uc::WriteNewCallbackUCPtr writeNewCallbackUC = boost::make_shared<uc::WriteNewCallbackUC>(uc::WriteNewCallbackUC());

    repo::IRepositoryPtr repository = repo::Repository::create(LoggerPool::getLoggerCallback());
    repository->injectDbName(dbName);
    repository->injectFindAccessor(createAccessor());
    repository->injectInsertCritAccessor(createAccessor());
    repository->injectInsertCritPosAccessor(createAccessor());
    repository->injectInsertCallbackItemAccessor(createAccessor());
    repository->injectUpdateCallbackItemAccessor(createAccessor());
    repository->injectTransactionFactory(shared_from_this());
    writeNewCallbackUC->injectRepository(repository);

    util::MessageTxtResource msgTxtResource;
    msgTxtResource.injectMsgStream(msgStream);
    msgTxtResource.setLanguageCode(languageCode);
    util::IStringResourcePtr stringResource = boost::make_shared<util::MessageTxtResource>(msgTxtResource);
    writeNewCallbackUC->injectStringResource(stringResource);
	writeNewCallbackUC->injectSmptServer(smtpServer, smtpPort);

    writeNewCallbackUC->setNewCallback(newCallback);

    return writeNewCallbackUC;
}

void ComponentManager::getGetCallbackDivisionAndReasonName(basar::VarString const& dbName,
        basar::Int16 const branchNo, basar::Int16 const divisionNo, basar::Int16 const reasonNo, basar::VarString& divisionName, basar::VarString& reasonName)
{
    repo::IRepositoryPtr repository = getRepository(dbName);

    libcsc::callback::domMod::ICallbackDivisionPtr division = repository->findCallbackDivision(branchNo, divisionNo);
    divisionName = division->getDivisionName();

    libcsc::callback::domMod::ICallbackReasonPtr reason = repository->findCallbackReason(branchNo, divisionNo, reasonNo);
    reasonName = reason->getReasonName();
}

} // end namespace callback
} // end namespace libcsc
