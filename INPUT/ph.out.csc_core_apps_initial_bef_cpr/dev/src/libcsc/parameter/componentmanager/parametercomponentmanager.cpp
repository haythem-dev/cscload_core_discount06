#include <parameter/componentmanager/parametercomponentmanager.h>

#include <parameter/csvorderimport/csvorderimportrepositoryptr.h>
#include <parameter/csvorderimport/csvorderimportrepository.h>

#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>
#include <parameter/branchparametergetter.h>


namespace libcsc {
namespace parameter {

ParameterComponentManager::ParameterComponentManager()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "ParameterComponentManager::ParameterComponentManager()" );
}

ParameterComponentManager::~ParameterComponentManager()
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "ParameterComponentManager::~ParameterComponentManager()" );
}

void ParameterComponentManager::injectConnection( persistence::ConnectionPtr connection )
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "ParameterComponentManager::injectConnection()" );

	m_Connection = connection;
}

void ParameterComponentManager::injectTransactionHandler (nDataBase * transHandler)
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "ParameterComponentManager::injectTransactionHandler()" );

	m_TransactionHandler = transHandler;
}

libcsc::persistence::TransactionGuard ParameterComponentManager::createTransaction() const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "ParameterComponentManager::createTransaction()" );

	return persistence::TransactionGuard( m_TransactionHandler );
}


ICSVOrderImportRepositoryPtr ParameterComponentManager::getCSVOrderImportRepository() const
{
	BLOG_TRACE_METHOD(LoggerPool::getLoggerParameter(), "ParameterComponentManager::getCSVOrderImportRepository()");

	if (NULL == m_CSVOrderImportRepository.get())
	{
		m_CSVOrderImportRepository = createCSVOrderImportRepository();
	}
	return m_CSVOrderImportRepository;
}

persistence::IAccessorPtr ParameterComponentManager::createAccessor() const
{
	BLOG_TRACE_METHOD( LoggerPool::getLoggerParameter(), "ParameterComponentManager::createAccessor()" );
	return persistence::IAccessorPtr( new persistence::Accessor( m_Connection->getDbSqlConnection() ) );
}

ICSVOrderImportRepositoryPtr ParameterComponentManager::createCSVOrderImportRepository() const
{
	CSVOrderImportRepositoryPtr repo = boost::make_shared<CSVOrderImportRepository>();
	repo->injectSelectCSCOrderImportCSVFieldsAccessor(createAccessor());
	repo->injectSelectCSCOrderImportCSVFormatsAccessor(createAccessor());
	repo->injectInsertCSCOrderImportCSVFormatsAccessor(createAccessor());
	repo->injectUpdateCSCOrderImportCSVFormatsAccessor(createAccessor());
	repo->injectDeleteCSCOrderImportCSVFormatsAccessor(createAccessor());
	repo->injectSelectCSCOrderImportCSVColumnsAccessor(createAccessor());
	repo->injectInsertCSCOrderImportCSVColumnsAccessor(createAccessor());
	repo->injectDeleteCSCOrderImportCSVColumnsAccessor(createAccessor());
	return repo;
}

} // end namespace parameter
} // end namespace libcsc
