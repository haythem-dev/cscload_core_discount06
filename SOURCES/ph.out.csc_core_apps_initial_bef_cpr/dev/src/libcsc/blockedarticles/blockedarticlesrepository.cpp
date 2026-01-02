#include "blockedarticlesrepository.h"

#include <blockedarticles/blockedarticles.h>
#include <blockedarticles/blockedarticlessqlmapper.h>

#include <parameter/branchparametergetter.h>
#include <persistence/iaccessor.h>
#include <persistence/itransactionfactory.h>
#include <exceptions/sqlduplicateexception.h>
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>


namespace libcsc {
namespace blockedarticles {

	BlockedArticlesRepository::BlockedArticlesRepository()
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "BlockedArticlesRepository::BlockedArticlesRepository()");
	}

	BlockedArticlesRepository::~BlockedArticlesRepository()
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "BlockedArticlesRepository::~BlockedArticlesRepository()");

		m_SelectBlockedArticlesAccessor.reset();
		m_UpdateAccessor.reset();
	}

	void BlockedArticlesRepository::injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "BlockedArticlesRepository::injectTransactionFactory()");
		m_TransactionFactory = transactionFactory;
	}

	void BlockedArticlesRepository::injectBlockedArticlesAccessor(persistence::IAccessorPtr accessor)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "BlockedArticlesRepository::injectReturnAnnouncementAccessor()");
		m_SelectBlockedArticlesAccessor = accessor;
	}

	void BlockedArticlesRepository::injectUpdateAccessor(persistence::IAccessorPtr accessor)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "BlockedArticlesRepository::injectUpdateAccessor()");
		m_UpdateAccessor = accessor;
	}

	void BlockedArticlesRepository::injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "BlockedArticlesRepository::injectBranchParameterGetter()");

		m_BranchParameterGetter = parameterGetter;
	}

	BlockedArticlesCollectionPtr BlockedArticlesRepository::findBlockedArticles(basar::Int16 branchNo, basar::Int32 blockID) const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "BlockedArticlesRepository::findBlockedArticles()");

		BlockedArticlesCollectionPtr blockedArticlesCollection = boost::make_shared<BlockedArticlesCollection>();

		basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(branchNo);
		if (dbName.empty())
		{
			return blockedArticlesCollection;
		}

		basar::db::sql::ResultsetRef resultSet = m_SelectBlockedArticlesAccessor->select(
			BlockedArticlesSqlMapper::getSelectSQL(dbName, branchNo, blockID)
		);

		while (resultSet.next())
		{
			BlockedArticlesPtr blockedArticle = boost::make_shared<BlockedArticles>();

			BlockedArticlesSqlMapper mapper(blockedArticle, resultSet);
			mapper.map();

			blockedArticlesCollection->push_back(blockedArticle);
		}

		return blockedArticlesCollection;
	}

	void BlockedArticlesRepository::saveBlockedArticle(const BlockedArticlesPtr& blockedArticles) const
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "BlockedArticlesRepository::saveBlockedArticle()");

		basar::VarString dbName = m_BranchParameterGetter->getDatabaseNameWarehouse(blockedArticles->getBranchNo());

		basar::db::sql::ExecuteReturnInfo retVal;
		retVal = m_UpdateAccessor->execute(BlockedArticlesSqlMapper::getUpdateSQL(dbName, blockedArticles), false);
	}

} // namespace blockedarticles
} // namespace libcsc
