#include "returnannouncementsqlmapper.h"
#include <logger/loggerpool.h>

#include <returns/returnannouncement/returnannouncement.h>

namespace libcsc {
namespace returns {

	ReturnAnnouncementSqlMapper::ReturnAnnouncementSqlMapper(
		ReturnAnnouncementPtr returnAnnouncement, const basar::db::sql::ResultsetRef resultSet)
		: ReturnAnnouncementMapperBase(returnAnnouncement), m_ResultSet(resultSet)
	{

	}

	ReturnAnnouncementSqlMapper::ReturnAnnouncementSqlMapper(ReturnAnnouncementPtr returnAnnouncement)
		: ReturnAnnouncementMapperBase(returnAnnouncement)
	{

	}

	ReturnAnnouncementSqlMapper::~ReturnAnnouncementSqlMapper()
	{

	}

	const basar::VarString ReturnAnnouncementSqlMapper::getSelectSQL(const basar::Int32 announcementId)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementSqlMapper::getSelectSQL()");

		std::stringstream sql;

		sql <<
			"SELECT "
			"announcementid, "
			"branchno, "
			"customerno, "
			"announcementguid, "
			"announcementsupportid, "
			"announcementdate, "
			"announcementtime, "
			"containswrongpickeditem, "
			"localcourt, "
			"companyregistrationno, "
			"vatidentificationno, "
			"taxidentificationno, "
			"nameofbank, "
			"bic, "
			"iban "
			"FROM returnannouncement "
			"WHERE announcementid=" << announcementId << " "
			"ORDER BY announcementid";

		BLOG_TRACE(LoggerPool::getLoggerReturns(), sql.str().c_str());

		return sql.str();
	}

	const basar::VarString ReturnAnnouncementSqlMapper::getInsertSQL(const ReturnAnnouncementPtr& returnAnnouncement)
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementSqlMapper::getInsertSQL()");

		std::stringstream sql;

		sql <<
			"INSERT INTO returnannouncement "
			"( "
				"branchno, "
				"customerno, "
				"announcementguid, "
				"announcementsupportid, "
				"announcementdate, "
				"announcementtime, "
				"containswrongpickeditem, "
				"localcourt, "
				"companyregistrationno, "
				"vatidentificationno, "
				"taxidentificationno, "
				"nameofbank, "
				"bic, "
				"iban "
			") "
			"VALUES "
			"( "
				<<			returnAnnouncement->getBranchNo()					<< ", "
				<<			returnAnnouncement->getCustomerNo()					<< ", "
				<< "'" <<	returnAnnouncement->getAnnouncementGuid()			<< "', "
				<<			returnAnnouncement->getAnnouncementSupportId()		<< ", "
				<<			returnAnnouncement->getAnnouncementDate()			<< ", "
				<<			returnAnnouncement->getAnnouncementTime()			<< ", "
				<<			returnAnnouncement->getContainsWrongPickedItem()	<< ", "
				<< "'" <<	returnAnnouncement->getLocalCourt()					<< "', "
				<< "'" <<	returnAnnouncement->getCompanyRegistrationNo()		<< "', "
				<< "'" <<	returnAnnouncement->getVatIdentificationNo()		<< "', "
				<< "'" <<	returnAnnouncement->getTaxIdentificationNo()		<< "', "
				<< "'" <<	returnAnnouncement->getNameOfBank()					<< "', "
				<< "'" <<	returnAnnouncement->getBIC()						<< "', "
				<< "'" <<	returnAnnouncement->getIBAN()						<< "' "
			");";

		BLOG_TRACE(LoggerPool::getLoggerReturns(), sql.str().c_str());

		return sql.str();
	}

	void ReturnAnnouncementSqlMapper::doMap()
	{
		LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerReturns(), "ReturnAnnouncementSqlMapper::doMap()");

		if (m_ResultSet.isNull())
		{
			throw;
		}

		setAnnouncementId(m_ResultSet.getInt32("announcementid"));
		setBranchNo(m_ResultSet.getInt16("branchno"));
		setCustomerNo(m_ResultSet.getInt32("customerno"));
		setAnnouncementGuid(m_ResultSet.getString("announcementguid"));
		setAnnouncementSupportId(m_ResultSet.getInt32("announcementsupportid"));
		setAnnouncementDate(m_ResultSet.getInt32("announcementdate"));
		setAnnouncementTime(m_ResultSet.getInt32("announcementtime"));
		setContainsWrongPickedItem(m_ResultSet.getInt16("containswrongpickeditem"));
		setLocalCourt(m_ResultSet.getString("localcourt"));
		setCompanyRegistrationNo(m_ResultSet.getString("companyregistrationno"));
		setVatIdentificationNo(m_ResultSet.getString("vatidentificationno"));
		setTaxIdentificationNo(m_ResultSet.getString("taxidentificationno"));
		setNameOfBank(m_ResultSet.getString("nameofbank"));
		setBIC(m_ResultSet.getString("bic"));
		setIBAN(m_ResultSet.getString("iban"));
	}

	//----------------------------------------------------------------------------------
	// Mapping after insert
	//----------------------------------------------------------------------------------
	void ReturnAnnouncementSqlMapper::doMapSerial(const basar::Int32 id)
	{
		setAnnouncementId(id);
	}


} // namespace returns
} // namespace libcsc
