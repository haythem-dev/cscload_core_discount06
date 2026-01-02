#include "cscordertypecomponentmanager.h"
#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <boost/make_shared.hpp>
#include <logger/loggerpool.h>
#include <cscordertype/repository/cscordertyperepositoryptr.h>
#include <cscordertype/repository/cscordertyperepository.h>
#include <persistence/itransactionfactoryptr.h>

namespace libcsc
{
namespace cscordertype
{

CSCOrderTypeComponentManager::CSCOrderTypeComponentManager()
{
}

CSCOrderTypeComponentManager::~CSCOrderTypeComponentManager()
{
}

void CSCOrderTypeComponentManager::injectConnection( persistence::ConnectionPtr connection )
{
    m_Connection = connection;
}

persistence::IAccessorPtr CSCOrderTypeComponentManager::createAccessor() const
{
    return persistence::IAccessorPtr( new persistence::Accessor( m_Connection->getDbSqlConnection() ) );
}

void CSCOrderTypeComponentManager::injectTransactionHandler( nDataBase * transHandler )
{
    m_TransactionHandler = transHandler;
}

ICSCOrderTypeRepositoryPtr CSCOrderTypeComponentManager::getCSCOrderTypeRepository()
{
	BLOG_TRACE_METHOD(LoggerPool::getLoggerParameter(), "CSCOrderTypeComponentManager::getCSCOrderTypeRepository()");

	if (NULL == m_CSCOrderTypeRepository.get())
	{
		m_CSCOrderTypeRepository = createCSCOrderTypeRepository();
	}
	return m_CSCOrderTypeRepository;
}

persistence::TransactionGuard CSCOrderTypeComponentManager::createTransaction() const
{
    return persistence::TransactionGuard( m_TransactionHandler );
}

ICSCOrderTypeRepositoryPtr CSCOrderTypeComponentManager::createCSCOrderTypeRepository()
{
    BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "CSCOrderTypeComponentManager::createCSCOrderTypeRepository()" );
	CSCOrderTypeRepositoryPtr repository = boost::make_shared<CSCOrderTypeRepository>();

//	CSCOrderTypeRepositoryPtr repository( new CSCOrderTypeRepository() );
    repository->injectAccessor( createAccessor() );
	repository->injectSelectCSCOrderTypeAccessor(createAccessor());
	repository->injectInsertCSCOrderTypeAccessor(createAccessor());
	repository->injectUpdateCSCOrderTypeAccessor(createAccessor());
	repository->injectDeleteCSCOrderTypeAccessor(createAccessor());
	repository->injectSelectCSCOrderTypeBatchConfigAccessor(createAccessor());
	repository->injectInsertCSCOrderTypeBatchConfigAccessor(createAccessor());
	repository->injectUpdateCSCOrderTypeBatchConfigAccessor(createAccessor());
	repository->injectDeleteCSCOrderTypeBatchConfigAccessor(createAccessor());
	repository->injectSelectCSCOrderTypeFlagTypeAccessor(createAccessor());
	repository->injectTransactionFactory(shared_from_this());
	return repository;
}

} // end namespace cscordertype
} // end namespace libcsc
