#include "blockedarticlessqlmapper.h"
#include <logger/loggerpool.h>

#include <blockedarticles/blockedarticles.h>

namespace libcsc {
namespace blockedarticles {

	BlockedArticlesSqlMapper::BlockedArticlesSqlMapper(
		BlockedArticlesPtr blockedArticles, const basar::db::sql::ResultsetRef resultSet
	)
		: BlockedArticlesMapperBase(blockedArticles), m_ResultSet(resultSet)
	{
	}

	BlockedArticlesSqlMapper::BlockedArticlesSqlMapper(BlockedArticlesPtr blockedArticles)
		: BlockedArticlesMapperBase(blockedArticles)
	{
	}

	BlockedArticlesSqlMapper::~BlockedArticlesSqlMapper()
	{
	}

	const basar::VarString BlockedArticlesSqlMapper::getSelectSQL(const basar::VarString& dbName, const basar::Int16 branchNo, const basar::Int32 blockID)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "BlockedArticlesSqlMapper::getSelectSQL()");

		std::stringstream sql;

		sql <<
			"SELECT "
			"branchno, "
			"articleno, "
			"blockid, "
			"storagelocation, "
			"quantity, "
			"bookingtype, "
			"creationtime, "
			"creationdate, "
			"processeddate, "
			"processedtime "
			"FROM " << dbName << ":blockedarticles "
			"WHERE branchno=" << branchNo << " AND "
			"blockid= " << blockID <<
			"ORDER BY blockid";

		BLOG_TRACE(LoggerPool::getLoggerReturns(), sql.str().c_str());

		return sql.str();
	}

	const basar::VarString BlockedArticlesSqlMapper::getUpdateSQL(const basar::VarString& dbName, const BlockedArticlesPtr& blockedArticles)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "BlockedArticlesSqlMapper::getUpdateSQL()");

		std::stringstream sql;

		sql <<
			"UPDATE " << dbName << ":blockedarticles "
			"SET "
			"processeddate= " << blockedArticles->getProcessedDate() << ", "
			"processedtime= " << blockedArticles->getProcessedTime() << " "
			"WHERE branchno= " << blockedArticles->getBranchNo() << " AND "
			"articleno= " << blockedArticles->getArticleNo() << " AND "
			"blockid= " << blockedArticles->getBlockedID() << " AND "
			"storagelocation= '" << blockedArticles->getStorageLocation() << "';";

		BLOG_TRACE(LoggerPool::getLoggerReturns(), sql.str().c_str());

		return sql.str();
	}

	void BlockedArticlesSqlMapper::doMap()
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "BlockedArticlesSqlMapper::doMap()");

		if (m_ResultSet.isNull())
		{
			throw;
		}

		setBranchNo(m_ResultSet.getInt16("branchno"));
		setArticleNo(m_ResultSet.getInt32("articleno"));
		setBlockedID(m_ResultSet.getInt32("blockid"));
		setStorageLocation(m_ResultSet.getString("storagelocation"));
		setQuantity(m_ResultSet.getInt32("quantity"));
		setBookingType(m_ResultSet.getInt16("bookingtype"));
		setCreationTime(m_ResultSet.getInt32("creationtime"));
		setCreationDate(m_ResultSet.getInt32("creationdate"));
		setProcessedDate(m_ResultSet.getInt32("processeddate"));
		setProcessedTime(m_ResultSet.getInt32("processedtime"));
	}

} // namespace blockedarticles
} // namespace libcsc
