#include "returnannouncementpossqlmapper.h"
#include <logger/loggerpool.h>

#include <returns/returnannouncement/returnannouncementpos/returnannouncementpos.h>

namespace libcsc {
namespace returns {

	ReturnAnnouncementPosSQLMapper::ReturnAnnouncementPosSQLMapper(
		ReturnAnnouncementPosPtr returnAnnouncementPos,	const basar::db::sql::ResultsetRef resultSet)
		: ReturnAnnouncementPosMapperBase(returnAnnouncementPos), m_ResultSet(resultSet)
	{
	}

	ReturnAnnouncementPosSQLMapper::~ReturnAnnouncementPosSQLMapper()
	{
	}

	const basar::VarString ReturnAnnouncementPosSQLMapper::getSelectSQL(const basar::Int32 announcementHeadId)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementPosSQLMapper::getSelectSQL()");

		std::stringstream sql;

		sql <<
			"SELECT "
			"announcementheadid, "
			"posno, "
			"announcementposrefid, "
			"deliveryadviceno, "
			"deliveryadvicedate, "
			"deliveryadviceposno, "
			"returnreasoncode, "
			"returnqty, "
			"articleno, "
			"article_code, "
			"code_type, "
			"batch, "
			"expirydate "
			"FROM returnannouncementpos "
			"WHERE returnannouncementheadid=" << announcementHeadId << " "
			"ORDER BY posno ASC";

		BLOG_TRACE(LoggerPool::getLoggerReturns(), sql.str().c_str());

		return sql.str();
	}

	const basar::VarString ReturnAnnouncementPosSQLMapper::getInsertSQL(const ReturnAnnouncementPosPtr& position)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementPosSQLMapper::getInsertSQL()");

		std::stringstream sql;

		sql <<
			"INSERT INTO returnannouncementpos "
			"( "
				"announcementheadid, "
				"posno, "
				"announcementposrefid, "
				"deliveryadviceno, "
				"deliveryadvicedate, "
				"deliveryadviceposno, "
				"returnreasoncode, "
				"returnqty, "
				"articleno, "
				"article_code, "
				"code_type, "
				"batch, "
				"expirydate "
			" ) "
			"VALUES "
			"( "
				<<			position->getAnnouncementHeadId()			<< ", "
				<<			position->getPosNo()						<< ", "
				<<			position->getAnnouncementPosRefId()			<< ", "
				<< "'" <<	position->getDeliveryAdviceNo()				<< "', "
				<<			position->getDeliveryAdviceDate().getDate()	<< ", "
				<<			position->getDeliveryAdvicePosNo()			<< ", "
				<< "'" <<	position->getReturnReasonCode()				<< "', "
				<<			position->getReturnQty()					<< ", "
				<<			position->getArticleNo()					<< ", "
				<< "'" <<	position->getArticleCode()					<< "', "
				<<			position->getCodeType()						<< ", "
				<< "'" <<	position->getBatch()						<< "', "
				<<			position->getExpiryDate()					<< " "
			" );";

		BLOG_TRACE(LoggerPool::getLoggerReturns(), sql.str().c_str());

		return sql.str();
	}

	void ReturnAnnouncementPosSQLMapper::doMap()
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnannouncementPosSQLMapper::doMap()");

		if (m_ResultSet.isNull())
		{
			throw;
		}

		setAnnouncementHeadId(m_ResultSet.getInt32("announcementheadid"));
		setPosNo(m_ResultSet.getInt32("posno"));
		setAnnouncementPosRefId(m_ResultSet.getInt32("announcementposrefid"));
		setDeliveryAdviceNo(m_ResultSet.getString("deliveryadviceno"));
		setDeliveryAdviceDate(basar::Date(m_ResultSet.getInt32("deliveryadvicedate")));
		setDeliveryAdvicePosNo(m_ResultSet.getInt32("deliveryadviceposno"));
		setReturnReasonCode(m_ResultSet.getString("returnreasoncode"));
		setReturnQty(m_ResultSet.getInt32("returnqty"));
		setArticleNo(m_ResultSet.getInt32("articleno"));
		setArticleCode(m_ResultSet.getString("article_code"));
		setCodetype(m_ResultSet.getInt16("code_type"));
		setBatch(m_ResultSet.getString("batch"));
		setExpiryDate(m_ResultSet.getInt32("expirydate"));
	}

} //returns
} //libcsc
