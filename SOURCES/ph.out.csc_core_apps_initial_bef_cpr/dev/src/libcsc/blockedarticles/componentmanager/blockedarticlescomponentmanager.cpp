#include "blockedarticlescomponentmanager.h"

#include "blockedarticles/blockedarticlesrepository.h"

#include <persistence/accessor.h>
#include <persistence/connection.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>
#include "pxsess.hpp"
#include "pxparameter.hpp"

namespace libcsc {
namespace blockedarticles {

	BlockedArticlesComponentManager::BlockedArticlesComponentManager()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "BlockedArticlesComponentManager::BlockedArticlesComponentManager()");
	}

	BlockedArticlesComponentManager::~BlockedArticlesComponentManager()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "BlockedArticlesComponentManager::~BlockedArticlesComponentManager()");
	}

	void BlockedArticlesComponentManager::injectConnection(persistence::ConnectionPtr connection)
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "BlockedArticlesComponentManager::injectConnection()");

		m_Connection = connection;
	}

	void BlockedArticlesComponentManager::injectTransactionHandler(nDataBase * transactionHandler)
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "BlockedArticlesComponentManager::injectTransactionHandler()");

		m_TransactionHandler = transactionHandler;
	}

	void BlockedArticlesComponentManager::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "BlockedArticlesComponentManager::injectBranchParameterGetter()");

		m_BranchParameterGetter = parameterGetter;
	}

	libcsc::persistence::TransactionGuard BlockedArticlesComponentManager::createTransaction() const
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "BlockedArticlesComponentManager::createTransaction()");

		return persistence::TransactionGuard(m_TransactionHandler);
	}

	IBlockedArticlesRepositoryPtr BlockedArticlesComponentManager::getBlockedArticlesRepository()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "BlockedArticlesComponentManager::getBlockedArticlesRepository()");

		if (NULL == m_BlockedArticlesRepository.get())
		{
			BlockedArticlesRepositoryPtr repository = boost::make_shared<BlockedArticlesRepository>();
			repository->injectTransactionFactory(shared_from_this());
			repository->injectUpdateAccessor(createAccessor());
			repository->injectBlockedArticlesAccessor(createAccessor());
			repository->injectBranchParameterGetter(m_BranchParameterGetter);

			m_BlockedArticlesRepository = repository;
		}

		return m_BlockedArticlesRepository;
	}

	persistence::IAccessorPtr BlockedArticlesComponentManager::createAccessor()
	{
		BLOG_TRACE_METHOD(LoggerPool::getLoggerInfrastructure(), "BlockedArticlesComponentManager::createAccessor()");

		return persistence::IAccessorPtr(new persistence::Accessor(m_Connection->getDbSqlConnection()));
	}

} //blockedarticles
} //libcsc
