#include "transmissionresponsesqlmapper.h"
#include "transmissionresponse.h"
#include "transmissionresponseselectsqlparameterbinder.h"
#include "transmissionresponseselectbyintermalhashsqlparameterbinder.h"
#include "transmissionresponseinsertsqlparameterbinder.h"
#include "transmissionresponseupdatesqlparameterbinder.h"

namespace libcsc {
namespace msv3 {

TransmissionResponseSQLMapper::TransmissionResponseSQLMapper(TransmissionResponsePtr transmissionResponse, const basar::db::sql::ResultsetRef resultSet) :
	TransmissionResponseMapperBase(transmissionResponse),
	m_ResultSet(resultSet)
{
}

TransmissionResponseSQLMapper::TransmissionResponseSQLMapper(TransmissionResponsePtr transmissionResponse) :
	TransmissionResponseMapperBase(transmissionResponse)
{
}

TransmissionResponseSQLMapper::~TransmissionResponseSQLMapper()
{
}

//----------------------------------------------------------------------------------
// SELECT by transmission UUID
//----------------------------------------------------------------------------------
const basar::VarString TransmissionResponseSQLMapper::getSelectSQL()
{
	static basar::VarString sql;
	if (sql.empty())
	{
		sql =
		"SELECT "
			"id, "
			"request_id, "
			"support_id, "
			"branchno, "
			"customerno, "
			"is_offer, "
			"responseasxml, "
			"create_date, "
			"create_time, "
			"internalhash "
		"FROM "
			"orderresponses "
		"WHERE "
			"request_id = ?";
	}
	return sql;
}

void TransmissionResponseSQLMapper::bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::VarString& transmissionUuid)
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::VarString _transmissionUuid = basar::VarString();

	_transmissionUuid = transmissionUuid;

	basar::UInt32 counter = 0;

	prepStmt.setString(counter++, _transmissionUuid.c_str());
}

const libcsc::persistence::ISqlParameterBinderPtr TransmissionResponseSQLMapper::getSelectSqlParameterBinder(const basar::VarString& transmissionUuid)
{
	return libcsc::persistence::ISqlParameterBinderPtr(new TransmissionResponseSelectSqlParameterBinder(transmissionUuid));
}

//----------------------------------------------------------------------------------
// SELECT by internal hash
//----------------------------------------------------------------------------------

const basar::VarString TransmissionResponseSQLMapper::getSelectByInternalHashSQL()
{
	static basar::VarString sql;
	if (sql.empty())
	{
		sql =
			"SELECT "
			"id, "
			"request_id, "
			"support_id, "
			"branchno, "
			"customerno, "
			"is_offer, "
			"responseasxml, "
			"create_date, "
			"create_time, "
			"internalhash "
			"FROM "
			"orderresponses "
			"WHERE "
			"branchno = ? AND "
			"customerno = ? AND "
			"internalhash = ? AND "
			"((create_date = ? AND create_time >= ? ) OR (create_date > ? ))";
		// TODO FN Tageswechsel!!!
	}
	return sql;
}

void TransmissionResponseSQLMapper::bindSelectByInternalHashSQL(basar::db::sql::PreparedStatementRef prepStmt,
	const basar::Int16& branchNo,
	const basar::Int32& customerNo,
	const basar::VarString& internalHash,
	const basar::DateTime& checkFrom)
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::Int16 _branchNo = 0;
	static basar::Int32 _customerNo = 0;
	static basar::VarString _internalHash = basar::VarString();
	static basar::Int32 _creationDate = 0;
	static basar::Int32 _creationTime = 0;

	_branchNo = branchNo;
	_customerNo = customerNo;
	_internalHash = internalHash;
	_creationDate = checkFrom.getDate();
	_creationTime = checkFrom.getTime() / 1000;

	basar::UInt32 counter = 0;

	prepStmt.setInt16(counter++, _branchNo);
	prepStmt.setInt32(counter++, _customerNo);
	prepStmt.setString(counter++, _internalHash.c_str());
	prepStmt.setInt32(counter++, _creationDate);
	prepStmt.setInt32(counter++, _creationTime);
	prepStmt.setInt32(counter++, _creationDate);
}


const libcsc::persistence::ISqlParameterBinderPtr TransmissionResponseSQLMapper::getSelectByInternalHashSqlParameterBinder(
	const basar::Int16& branchNo,
	const basar::Int32& customerNo,
	const basar::VarString& internalHash,
	const basar::DateTime& checkFrom)
{
	return libcsc::persistence::ISqlParameterBinderPtr(new TransmissionResponseSelectByInternalHashSqlParameterBinder(branchNo, customerNo, internalHash, checkFrom));
}


//----------------------------------------------------------------------------------
// INSERT
//----------------------------------------------------------------------------------
const basar::VarString TransmissionResponseSQLMapper::getInsertSQL()
{
	static basar::VarString sql;
	if (sql.empty())
	{
		sql =
		"INSERT INTO orderresponses "
		"("
			"request_id, "
			"support_id, "
			"branchno, "
			"customerno, "
			"is_offer, "
			"responseasxml, "
			"create_date, "
			"create_time, "
			"internalhash "
			") "
		"VALUES "
		"("
			"?, "
			"?, "
			"?, "
			"?, "
			"?, "
			"?, "
			"?, "
			"?, "
			"? "
		")";
	}
	return sql;
}

void TransmissionResponseSQLMapper::bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, const TransmissionResponsePtr transmissionResponse)
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::VarString transmissionUuid = basar::VarString();
	static basar::Int32 supportId = 0;
	static basar::Int16 branchNo = 0;
	static basar::Int32 customerNo = 0;
	static basar::Int16 isOffer = 0;
	static basar::VarString xmlResponse = basar::VarString();
	static basar::Int32 creationDate = 0;
	static basar::Int32 creationTime = 0;
	static basar::VarString internalHash = basar::VarString();

	transmissionUuid	= transmissionResponse->getTransmissionGuid();
	supportId			= transmissionResponse->getTransmissionSupportId();
	branchNo			= transmissionResponse->getBranchNo();
	customerNo			= transmissionResponse->getCustomerNo();
	isOffer				= transmissionResponse->getIsOffer();
	xmlResponse			= transmissionResponse->getResponseAsXml();
	creationDate		= transmissionResponse->getCreationDate();
	creationTime		= transmissionResponse->getCreationTime();
	internalHash		= transmissionResponse->getInternalHash();

	basar::UInt32 counter = 0;

	prepStmt.setString	(counter++, transmissionUuid.c_str());
	prepStmt.setInt32	(counter++, supportId);
	prepStmt.setInt16	(counter++, branchNo);
	prepStmt.setInt32	(counter++, customerNo);
	prepStmt.setInt16	(counter++, isOffer);
	prepStmt.setString	(counter++, xmlResponse.c_str());
	prepStmt.setInt32	(counter++, creationDate);
	prepStmt.setInt32	(counter++, creationTime);
	prepStmt.setString	(counter++, internalHash.c_str());
}

const libcsc::persistence::ISqlParameterBinderPtr TransmissionResponseSQLMapper::getInsertSqlParameterBinder(const TransmissionResponsePtr transmissionResponse)
{
	return libcsc::persistence::ISqlParameterBinderPtr(new TransmissionResponseInsertSqlParameterBinder(transmissionResponse));
}


//----------------------------------------------------------------------------------
// UPDATE
//----------------------------------------------------------------------------------
const basar::VarString TransmissionResponseSQLMapper::getUpdateSQL()
{
	static basar::VarString sql;
	if (sql.empty())
	{
		sql =
		"UPDATE orderresponses SET "
			"request_id = ?, "
			"support_id = ?, "
			"branchno = ?, "
			"customerno = ?, "
			"is_offer = ?, "
			"responseasxml = ?, "
			"create_date = ?, "
			"create_time = ?, "
			"internalhash = ? "
		"WHERE "
			"id = ?";
	}
	return sql;
}

void TransmissionResponseSQLMapper::bindUpdateSQL(basar::db::sql::PreparedStatementRef prepStmt, const TransmissionResponsePtr transmissionResponse)
{
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!
	static basar::VarString transmissionUuid = basar::VarString();
	static basar::Int32 supportId = 0;
	static basar::Int16 branchNo = 0;
	static basar::Int32 customerNo = 0;
	static basar::Int16 isOffer = 0;
	static basar::VarString xmlResponse = basar::VarString();
	static basar::Int32 creationDate = 0;
	static basar::Int32 creationTime = 0;
	static basar::VarString internalHash = basar::VarString();
	static basar::Int32 id = 0;


	transmissionUuid	= transmissionResponse->getTransmissionGuid();
	supportId			= transmissionResponse->getTransmissionSupportId();
	branchNo			= transmissionResponse->getBranchNo();
	customerNo			= transmissionResponse->getCustomerNo();
	isOffer				= transmissionResponse->getIsOffer();
	xmlResponse			= transmissionResponse->getResponseAsXml();
	creationDate		= transmissionResponse->getCreationDate();
	creationTime		= transmissionResponse->getCreationTime();
	internalHash		= transmissionResponse->getInternalHash();
	id					= transmissionResponse->getId();

	basar::UInt32 counter = 0;

	prepStmt.setString	(counter++, transmissionUuid.c_str());
	prepStmt.setInt32	(counter++, supportId);
	prepStmt.setInt16	(counter++, branchNo);
	prepStmt.setInt32	(counter++, customerNo);
	prepStmt.setInt16	(counter++, isOffer);
	prepStmt.setString	(counter++, xmlResponse.c_str());
	prepStmt.setInt32	(counter++, creationDate);
	prepStmt.setInt32	(counter++, creationTime);
	prepStmt.setString	(counter++, internalHash.c_str());
	prepStmt.setInt32	(counter++, id);
}

const libcsc::persistence::ISqlParameterBinderPtr TransmissionResponseSQLMapper::getUpdateSqlParameterBinder(const TransmissionResponsePtr transmissionResponse)
{
	return libcsc::persistence::ISqlParameterBinderPtr(new TransmissionResponseUpdateSqlParameterBinder(transmissionResponse));
}


//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void TransmissionResponseSQLMapper::doMap()
{
	// TODO: check ResultSet
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setTransmissionId			(m_ResultSet.getInt32("id"));
	setTransmissionGuid			(m_ResultSet.getString("request_id"));
	setTransmissionSupportId	(m_ResultSet.getInt32("support_id"));
	setBranchNo					(m_ResultSet.getInt16("branchno"));
	setCustomerNo				(m_ResultSet.getInt32("customerno"));
	setIsOffer					(m_ResultSet.getInt16("is_offer"));
	setResponseAsXml			(m_ResultSet.getString("responseasxml"));
	setCreationDate				(m_ResultSet.getInt32("create_date"));
	setCreationTime				(m_ResultSet.getInt32("create_time"));
	setInternalHash				(m_ResultSet.getString("internalhash"));
}

//----------------------------------------------------------------------------------
// Mapping after insert
//----------------------------------------------------------------------------------
void TransmissionResponseSQLMapper::doMapSerial(const basar::Int32& id)
{
	setTransmissionId(id);
	setClean();
}


} // end namespace msv3
} // end namespace libcsc
