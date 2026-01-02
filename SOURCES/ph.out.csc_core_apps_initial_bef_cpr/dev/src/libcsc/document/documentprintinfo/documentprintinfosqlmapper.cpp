#include "documentprintinfosqlmapper.h"
#include "documentprintinfo.h"
#include "documentprintinfoinsertsqlparameterbinder.h"
#include "documentprintinfoselectsqlparameterbinder.h"
#include <logger/loggerpool.h>


namespace libcsc {
namespace document {

DocumentPrintInfoSQLMapper::DocumentPrintInfoSQLMapper(DocumentPrintInfoPtr documentPrintInfo, const basar::db::sql::ResultsetRef resultSet) :
	DocumentPrintInfoMapperBase(documentPrintInfo),
	m_ResultSet(resultSet)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoSQLMapper::DocumentPrintInfoSQLMapper()");
}

DocumentPrintInfoSQLMapper::DocumentPrintInfoSQLMapper(DocumentPrintInfoPtr documentPrintInfo) :
	DocumentPrintInfoMapperBase(documentPrintInfo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoSQLMapper::DocumentPrintInfoSQLMapper");
}

DocumentPrintInfoSQLMapper::~DocumentPrintInfoSQLMapper()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoSQLMapper::~DocumentPrintInfoSQLMapper()");
}

//----------------------------------------------------------------------------------
// INSERT
//----------------------------------------------------------------------------------
const basar::VarString DocumentPrintInfoSQLMapper::getInsertSQL( const basar::VarString & dbName )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoSQLMapper::getInsertSQL()");
	std::stringstream sSql;
	sSql <<
		"INSERT INTO " << dbName << ":documentprintinfo "
		"( "
			"branchno, "
			"customerno, "
			"documenttype, "
			"documentdate, "
			"documentno "
		") "
		"VALUES "
		"( "
			"?, "
			"?, "
			"?, "
			"?, "
			"?"
			" )";

	return sSql.str();
}

void DocumentPrintInfoSQLMapper::bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, const DocumentPrintInfoPtr documentPrintInfo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoSQLMapper::bindInsertSQL()");
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!

	static basar::Int16		branchNo = 0;
	static basar::Int32		customerNo = 0;
	static basar::Int16		documentType = 0;
	static basar::Int32		documentDate = 0;
	static basar::VarString	documentNo = basar::VarString();

	branchNo		= documentPrintInfo->getBranchNo();
	customerNo		= documentPrintInfo->getCustomerNo();
	documentType	= static_cast<basar::Int16>(documentPrintInfo->getDocumentType());
	documentDate	= documentPrintInfo->getDocumentDate();
	documentNo		= documentPrintInfo->getDocumentNo();

	basar::UInt32 counter = 0;

	prepStmt.setInt16	(counter++, branchNo);
	prepStmt.setInt32	(counter++, customerNo);
	prepStmt.setInt16	(counter++, documentType);
	prepStmt.setInt32	(counter++, documentDate);
	prepStmt.setString	(counter++, documentNo.c_str());
}

const libcsc::persistence::ISqlParameterBinderPtr DocumentPrintInfoSQLMapper::getInsertSqlParameterBinder(const DocumentPrintInfoPtr documentPrintInfo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoSQLMapper::getInsertSqlParameterBinder()");
	return libcsc::persistence::ISqlParameterBinderPtr(new DocumentPrintInfoInsertSqlParameterBinder(documentPrintInfo));
}

//----------------------------------------------------------------------------------
// SELECT
//----------------------------------------------------------------------------------
const basar::VarString DocumentPrintInfoSQLMapper::getSelectSQL(const basar::VarString & dbName)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoSQLMapper::getSelectSQL()");
	std::stringstream sSql;
	sSql <<
		"SELECT branchno, customerno, documenttype, documentdate, documentno FROM " << dbName << ":documentprintinfo "
		"WHERE "
		"branchno = ? "
		"AND customerno = ? "
		"AND documenttype = ? "
		"AND documentdate = ? "
		"AND documentno = ?;";

	return sSql.str();
}

void DocumentPrintInfoSQLMapper::bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum docType,
	basar::Int32 documentDate, const basar::VarString & documentNo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoSQLMapper::bindSelectSQL()");
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!

	static basar::Int16		_branchNo = 0;
	static basar::Int32		_customerNo = 0;
	static basar::Int16		_documentType = 0;
	static basar::Int32		_documentDate = 0;
	static basar::VarString	_documentNo = basar::VarString();

	_branchNo = branchNo;
	_customerNo = customerNo;
	_documentType = static_cast<basar::Int16>(docType);
	_documentDate = documentDate;
	_documentNo = documentNo;

	basar::UInt32 counter = 0;

	prepStmt.setInt16(counter++, _branchNo);
	prepStmt.setInt32(counter++, _customerNo);
	prepStmt.setInt16(counter++, _documentType);
	prepStmt.setInt32(counter++, _documentDate);
	prepStmt.setString(counter++, _documentNo.c_str());
}

const libcsc::persistence::ISqlParameterBinderPtr DocumentPrintInfoSQLMapper::getSelectSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum documentType,
	const basar::Int32 documentDate, const basar::VarString & documentNo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoSQLMapper::getSelectSqlParameterBinder()");
	return libcsc::persistence::ISqlParameterBinderPtr(new DocumentPrintInfoSelectSqlParameterBinder(branchNo, customerNo, documentType, documentDate, documentNo));
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void DocumentPrintInfoSQLMapper::doMap()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoSQLMapper::doMap()");
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo( m_ResultSet.getInt16("branchno") );
	setCustomerNo( m_ResultSet.getInt32("customerno") );
	setDocumentType( static_cast<DocumentTypeEnum>(m_ResultSet.getInt16("documenttype")) );
	setDocumentDate( m_ResultSet.getInt32("documentdate") );
	setDocumentNo( m_ResultSet.getString("documentno") );
}

} // end namespace document
} // end namespace libcsc
