#include "documentarchiveinfosqlmapper.h"
#include "documentarchiveinfo.h"
#include "documentarchiveinfoselectsqlparameterbinder.h"
#include "documentarchiveinfoselectbyguidsqlparameterbinder.h"
#include "documentarchiveinfoinsertsqlparameterbinder.h"
#include <logger/loggerpool.h>


namespace libcsc {
namespace document {

DocumentArchiveInfoSQLMapper::DocumentArchiveInfoSQLMapper(DocumentArchiveInfoPtr documentArchiveInfo, const basar::db::sql::ResultsetRef resultSet) :
	DocumentArchiveInfoMapperBase(documentArchiveInfo),
	m_ResultSet(resultSet)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::DocumentArchiveInfoSQLMapper()");
}

DocumentArchiveInfoSQLMapper::DocumentArchiveInfoSQLMapper(DocumentArchiveInfoPtr documentArchiveInfo) :
	DocumentArchiveInfoMapperBase(documentArchiveInfo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::DocumentArchiveInfoSQLMapper");
}

DocumentArchiveInfoSQLMapper::~DocumentArchiveInfoSQLMapper()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::~DocumentArchiveInfoSQLMapper()");
}

const basar::VarString DocumentArchiveInfoSQLMapper::getSelectSQL(const basar::VarString & dbName, const basar::Int32 documentDate)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::getSelectSQL()");
	std::stringstream sSql;

	sSql <<
		"SELECT "
		"branchno, "
		"customerno, "
		"documenttype, "
		"documentno, "
		"documentdate, "
		"documentid, "
		"documentlink, "
		"sentviafax, "
		"sentviamail "
		"FROM " << dbName << ":documentarchiveinfo "
		"WHERE "
		"branchno = ?"
		"and customerno = ?"
		"and documenttype = ?"
		"and documentno = ?";
	if (documentDate == 0)
	{
		sSql << " order by documentdate desc";
	}
	else
	{
		sSql << " and documentdate = ?";
	}

	return sSql.str();
}

void DocumentArchiveInfoSQLMapper::bindSelectSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum docType, const basar::VarString & documentNo, basar::Int32 documentDate )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::bindSelectSQL()");

	static basar::Int16 _branchNo = basar::Int16();
	static basar::Int32 _customerNo = basar::Int32();
	static basar::Int16 _documentType = basar::Int16();
	static basar::VarString _documentNo = basar::VarString();
	static basar::Int32 _documentDate = basar::Int32();

	_branchNo = branchNo;
	_customerNo = customerNo;
	_documentType = static_cast<basar::Int16>(docType);
	_documentNo = documentNo;
    _documentDate = documentDate;

	basar::UInt32 counter = 0;

	prepStmt.setInt16(counter++, _branchNo);
	prepStmt.setInt32(counter++, _customerNo);
	prepStmt.setInt16(counter++, _documentType);
	prepStmt.setString(counter++, _documentNo.c_str());
	if (documentDate != 0)
	{
		prepStmt.setInt32(counter++, _documentDate);
	}
}

const libcsc::persistence::ISqlParameterBinderPtr DocumentArchiveInfoSQLMapper::getSelectSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum docType, const basar::VarString & documentNo, const basar::Int32 documentDate )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::getSelectSqlParameterBinder()");
	return libcsc::persistence::ISqlParameterBinderPtr(new DocumentArchiveInfoSelectSqlParameterBinder( branchNo, customerNo, docType, documentNo, documentDate) );
}

const basar::VarString DocumentArchiveInfoSQLMapper::getSelectByGuidSQL(const basar::VarString & dbName)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::getSelectByGuidSQL()");
	std::stringstream sSql;

	sSql <<
		"SELECT "
		"branchno, "
		"customerno, "
		"documenttype, "
		"documentno, "
		"documentdate, "
		"documentid, "
		"documentlink, "
		"sentviafax, "
		"sentviamail "
		"FROM " << dbName << ":documentarchiveinfo "
		"WHERE "
		"branchno = ? "
		"and customerno = ? "
		"and documentid = ? ";

	return sSql.str();
}

void DocumentArchiveInfoSQLMapper::bindSelectByGuidSQL(basar::db::sql::PreparedStatementRef prepStmt, const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::VarString& documentId)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::bindSelectByGuidSQL()");
	static basar::Int16 _branchNo = basar::Int16();
	static basar::Int32 _customerNo = basar::Int32();
	static basar::VarString _documentId = basar::VarString();
	
	_branchNo = branchNo;
	_customerNo = customerNo;
	_documentId = documentId;

	basar::UInt32 counter = 0;

	prepStmt.setInt16(counter++, _branchNo);
	prepStmt.setInt32(counter++, _customerNo);
	prepStmt.setString(counter++, _documentId.c_str());
}

const libcsc::persistence::ISqlParameterBinderPtr DocumentArchiveInfoSQLMapper::getSelectByGuidSqlParameterBinder(const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::VarString& documentId)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::getSelectByGuidSqlParameterBinder()");
	return libcsc::persistence::ISqlParameterBinderPtr(new DocumentArchiveInfoSelectByGuidSqlParameterBinder(branchNo, customerNo, documentId));
}

//----------------------------------------------------------------------------------
// INSERT
//----------------------------------------------------------------------------------
const basar::VarString DocumentArchiveInfoSQLMapper::getInsertSQL( const basar::VarString & dbName )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::getInsertSQL()");
	std::stringstream sSql;
	sSql <<
		"INSERT INTO " << dbName << ":documentarchiveinfo "
		"( "
			"branchno, "
			"customerno, "
			"documenttype, "
			"documentno, "
			"documentdate, "
			"documentid, "
			"documentlink, "
			"sentviafax, "
			"sentviamail "
		") "
		"VALUES "
		"( "
			"?, "
			"?, "
			"?, "
			"?, "
			"?, "
			"?, "
			"?, "
			"?, "
			"?"
		" )";
	return sSql.str();
}

void DocumentArchiveInfoSQLMapper::bindInsertSQL(basar::db::sql::PreparedStatementRef prepStmt, const DocumentArchiveInfoPtr documentArchiveInfo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::bindInsertSQL()");
	// Prepared statement setters take a reference and only move the address to the client sdk layer.
	// We have to take sure, variables are still existent at that moment execute() ist called!

	static basar::Int16		branchNo = 0;
	static basar::Int32		customerNo = 0;
	static basar::Int16		documentType = 0;
	static basar::VarString	documentNo = basar::VarString();
	static basar::Int32		documentDate = 0;
	static basar::VarString	documentId = basar::VarString();
	static basar::VarString	documentLink = basar::VarString();
	static basar::Int16		sentViaFax = 0;
	static basar::Int16		sentViaMail = 0;

	branchNo		= documentArchiveInfo->getBranchNo();
	customerNo		= documentArchiveInfo->getCustomerNo();
	documentType	= static_cast<basar::Int16>(documentArchiveInfo->getDocumentType());
	documentNo		= documentArchiveInfo->getDocumentNo();
	documentDate	= documentArchiveInfo->getDocumentDate();
	documentId		= documentArchiveInfo->getDocumentId();
	documentLink	= documentArchiveInfo->getDocumentLink();
	sentViaFax		= documentArchiveInfo->getSentViaFax() ? 1 : 0;
	sentViaMail		= documentArchiveInfo->getSentViaMail() ? 1 : 0;

	basar::UInt32 counter = 0;

	prepStmt.setInt16	(counter++, branchNo);
	prepStmt.setInt32	(counter++, customerNo);
	prepStmt.setInt16	(counter++, documentType);
	prepStmt.setString	(counter++, documentNo.c_str());
	prepStmt.setInt32	(counter++, documentDate);
	prepStmt.setString	(counter++, documentId.c_str());
	prepStmt.setString	(counter++, documentLink.c_str());
	prepStmt.setInt16	(counter++, sentViaFax);
	prepStmt.setInt16	(counter++, sentViaMail);
}

const libcsc::persistence::ISqlParameterBinderPtr DocumentArchiveInfoSQLMapper::getInsertSqlParameterBinder(const DocumentArchiveInfoPtr documentArchiveInfo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::getInsertSqlParameterBinder()");
	return libcsc::persistence::ISqlParameterBinderPtr(new DocumentArchiveInfoInsertSqlParameterBinder(documentArchiveInfo));
}

//----------------------------------------------------------------------------------
// UPDATE
//----------------------------------------------------------------------------------
const basar::VarString DocumentArchiveInfoSQLMapper::getUpdateSQL( const basar::VarString & dbName , const DocumentArchiveInfoPtr documentArchiveInfo )
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::getUpdateSQL()");
	std::stringstream sSql;
	sSql <<
		"UPDATE " << dbName << ":documentarchiveinfo SET documentlink = '" << documentArchiveInfo->getDocumentLink() <<"' ";
	
	if( documentArchiveInfo->m_DocumentId.isDirty() )
	{
		sSql << ", documentid = '" << documentArchiveInfo->getDocumentId() << "' ";
	}
	if (documentArchiveInfo->m_SentViaFax.isDirty())
	{
		sSql << ", sentviafax = " << (documentArchiveInfo->getSentViaFax() ? "1 " : "0 ");
	}
	if (documentArchiveInfo->m_SentViaMail.isDirty())
	{
		sSql << ", sentviamail = " << (documentArchiveInfo->getSentViaMail() ? "1 " : "0 ");
	}

	sSql << "WHERE branchno = " << documentArchiveInfo->getBranchNo() << " and customerno = " << documentArchiveInfo->getCustomerNo() <<
			" and documenttype = " << documentArchiveInfo->getDocumentType() << " and documentno = '" << documentArchiveInfo->getDocumentNo() << "' and documentdate = " << documentArchiveInfo->getDocumentDate() ;
	return sSql.str();
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void DocumentArchiveInfoSQLMapper::doMap()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoSQLMapper::doMap()");
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setBranchNo			( m_ResultSet.getInt16("branchno") );
	setCustomerNo		( m_ResultSet.getInt32("customerno") );
	setDocumentType		( static_cast<DocumentTypeEnum>(m_ResultSet.getInt16("documenttype")) );
	setDocumentNo		( m_ResultSet.getString("documentno") );
	setDocumentDate		( m_ResultSet.getInt32("documentdate") );
	setDocumentId		( m_ResultSet.getString("documentid") );
	setDocumentLink		( m_ResultSet.getString("documentlink") );
	setSentViaFax		( m_ResultSet.getInt16("sentviafax") == 1 );
	setSentViaMail		( m_ResultSet.getInt16("sentviamail") == 1 );
}

} // end namespace document
} // end namespace libcsc
