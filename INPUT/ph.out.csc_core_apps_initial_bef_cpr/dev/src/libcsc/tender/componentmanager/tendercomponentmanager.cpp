#include "tendercomponentmanager.h"
#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <logger/loggerpool.h>

#include "tender/repository/tenderrepository.h"

namespace libcsc
{
namespace tender
{

TenderComponentManager::TenderComponentManager()
{
}

TenderComponentManager::~TenderComponentManager()
{
}

void TenderComponentManager::injectConnection( persistence::ConnectionPtr connection )
{
    m_Connection = connection;
}

persistence::IAccessorPtr TenderComponentManager::createAccessor()
{
    return persistence::IAccessorPtr( new persistence::Accessor( m_Connection->getDbSqlConnection() ) );
}

void TenderComponentManager::injectTransactionHandler (nDataBase * transHandler)
{
    m_TransactionHandler = transHandler;
}

void TenderComponentManager::injectBatchParameterGetter(parameter::IBranchParameterGetterPtr branchParameterGetter)
{
	m_BranchParameterGetter = branchParameterGetter;
}

persistence::TransactionGuard TenderComponentManager::createTransaction() const
{
    return persistence::TransactionGuard(m_TransactionHandler);
}

TenderRepositoryPtr TenderComponentManager::createTenderRepository()
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerInfrastructure(), "TenderComponentManager::createTenderRepository()" );

    TenderRepositoryPtr repository( new TenderRepository() );
    repository->injectAccessor( createAccessor() );
	repository->injectBranchParameterGetter( m_BranchParameterGetter );
    return repository;
}


} // end namespace ibt
} // end namespace libcsc
