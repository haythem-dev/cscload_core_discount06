#include "returnannouncementheadsqlmapper.h"
#include <logger/loggerpool.h>

#include <returns/returnannouncement/returnannouncementhead/returnannouncementhead.h>

namespace libcsc {
namespace returns {

	ReturnAnnouncementHeadSqlMapper::ReturnAnnouncementHeadSqlMapper(
		ReturnAnnouncementHeadPtr returnAnnouncementHead, const basar::db::sql::ResultsetRef resultSet)
		: ReturnAnnouncementHeadMapperBase(returnAnnouncementHead), m_ResultSet(resultSet)
	{
	}

	ReturnAnnouncementHeadSqlMapper::ReturnAnnouncementHeadSqlMapper(ReturnAnnouncementHeadPtr returnAnnouncementHead)
		: ReturnAnnouncementHeadMapperBase(returnAnnouncementHead)
	{
	}

	ReturnAnnouncementHeadSqlMapper::~ReturnAnnouncementHeadSqlMapper()
	{
	}

	const basar::VarString ReturnAnnouncementHeadSqlMapper::getSelectSQL(const basar::Int32 announcementId)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementHeadSqlMapper::getSelectSQL()");

		std::stringstream sql;

		sql <<
			"SELECT "
			"announcementheadid, "
			"announcementid, "
			"acccheckresultcode, "
			"wholesalerreferenceid, "
			"documentid, "
			"tourid, "
			"tourdeparturedate, "
			"transferstatus "
			"FROM returnannouncementhead "
			"WHERE announcementid=" << announcementId << " "
			"ORDER BY announcementheadid";

		BLOG_TRACE(LoggerPool::getLoggerReturns(), sql.str().c_str());

		return sql.str();
	}

	const basar::VarString ReturnAnnouncementHeadSqlMapper::getInsertSQL(const ReturnAnnouncementHeadPtr& head)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementHeadSqlMapper::getInsertSQL()");

		std::stringstream sql;

		sql <<
			"INSERT INTO returnannouncementhead "
			"( "
				"announcementid, "
				"acccheckresultcode, "
				"wholesalerreferenceid, "
				"documentid, "
				"tourid, "
				"tourdeparturedate, "
				"transferstatus "
			" ) "
			"VALUES "
			"( "
				<<			head->getAnnouncementId()			<< ", "
				<< "'" <<	head->getAccCheckResultCode()		<< "', "
				<< "'" <<	head->getWholesalerReferenceId()	<< "', "
				<< "'" <<	head->getDocumentId()				<< "', "
				<< "'" <<	head->getTourId()					<< "', "
				<<			head->getTourDepartureDate()		<< ", "
				<<			head->getTransferStatus()			<< " "
			" );";

		BLOG_TRACE(LoggerPool::getLoggerReturns(), sql.str().c_str());

		return sql.str();
	}

	const basar::VarString ReturnAnnouncementHeadSqlMapper::getUpdateSQL(const ReturnAnnouncementHeadPtr& head)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementHeadSqlMapper::getInsertSQL()");

		std::stringstream sql;

		sql <<
			"UPDATE returnannouncementhead SET "
				"acccheckresultcode = '"	<< head->getAccCheckResultCode() << "', "
				"wholesalerreferenceid = '"	<< head->getWholesalerReferenceId() << "', "
				"documentid = '"			<< head->getDocumentId() << "', "
				"tourid = '"				<< head->getTourId() << "', "
				"tourdeparturedate = "		<< head->getTourDepartureDate() << ", "
				"transferstatus = "			<< head->getTransferStatus() << " "
			"WHERE announcementheadid = "	<< head->getAnnouncementHeadId();

		BLOG_TRACE(LoggerPool::getLoggerReturns(), sql.str().c_str());

		return sql.str();
	}

	void ReturnAnnouncementHeadSqlMapper::doMap()
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementHeadSqlMapper::doMap()");

		if (m_ResultSet.isNull())
		{
			throw;
		}

		setAnnouncementHeadId(m_ResultSet.getInt32("announcementheadid"));
		setAnnouncementId(m_ResultSet.getInt32("announcementid"));
		setAccCheckResultCode(m_ResultSet.getString("acccheckresultcode"));
		setWholesalerReferenceId(m_ResultSet.getString("wholesalerreferenceid"));
		setDocumentId(m_ResultSet.getString("documentid"));
		setTourId(m_ResultSet.getString("tourid"));
		setTourDepartureDate(m_ResultSet.getInt32("tourdeparturedate"));
		setTransferStatus(m_ResultSet.getInt16("transferstatus"));
	}

	//----------------------------------------------------------------------------------
	// Mapping after insert
	//----------------------------------------------------------------------------------
	void ReturnAnnouncementHeadSqlMapper::doMapSerial(const basar::Int32 id)
	{
		setAnnouncementHeadId(id);
	}

} //returns
} //libcsc
