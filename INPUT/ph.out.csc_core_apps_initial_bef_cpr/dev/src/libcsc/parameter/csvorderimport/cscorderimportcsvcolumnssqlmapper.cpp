#include "cscorderimportcsvcolumnssqlmapper.h"
#include "cscorderimportcsvcolumns.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace parameter {

CSCOrderImportCSVColumnsSQLMapper::CSCOrderImportCSVColumnsSQLMapper(CSCOrderImportCSVColumnsPtr CSCOrderImportCSVColumns, const basar::db::sql::ResultsetRef resultSet) :
	CSCOrderImportCSVColumnsMapperBase(CSCOrderImportCSVColumns),
	m_ResultSet(resultSet)
{
}

CSCOrderImportCSVColumnsSQLMapper::~CSCOrderImportCSVColumnsSQLMapper()
{
}

const basar::VarString CSCOrderImportCSVColumnsSQLMapper::getSelectSQLByCscOrderImportFormatId(const basar::Int32 CscOrderImportFormatId)
{
	std::stringstream sSql;

	sSql << "SELECT "
		"columnno, "
		"fieldnameid, "
		"cscorderimportformatid, "
		"grouping "
		"FROM "
		"cscorderimportcsvcolumns "
		"WHERE cscorderimportformatid = " << CscOrderImportFormatId <<
		" ORDER BY columnno";

	BLOG_TRACE(LoggerPool::getLoggerParameter(), sSql.str());
	return sSql.str();

}

const basar::VarString CSCOrderImportCSVColumnsSQLMapper::getInsertSQL(const ICSCOrderImportCSVColumnsPtr CSCOrderImportCSVColumns)
{
	std::stringstream sSql;
	
	sSql << "INSERT INTO cscorderimportcsvcolumns "
		" (columnno, fieldnameid, cscorderimportformatid, grouping ) "
		" VALUES ( '" << CSCOrderImportCSVColumns->getColumnNo() << "', "
		<< CSCOrderImportCSVColumns->getFieldNameId() << ", "
		<< CSCOrderImportCSVColumns->getCscOrderImportFormatId() << ", "
		<< CSCOrderImportCSVColumns->getGrouping() << ")";
	BLOG_TRACE(LoggerPool::getLoggerParameter(), sSql.str());
	return sSql.str();

}

const basar::VarString CSCOrderImportCSVColumnsSQLMapper::getDeleteSQLByKey(const basar::Int16 ColumnNo, const basar::Int32 CscOrderImportFormatId)
{
	std::stringstream sSql;
	sSql << "DELETE FROM cscorderimportcsvcolumns WHERE columnno = " << ColumnNo << "and cscorderimportformatid = " << CscOrderImportFormatId;
	BLOG_TRACE(LoggerPool::getLoggerParameter(), sSql.str());
	return sSql.str();

}

const basar::VarString CSCOrderImportCSVColumnsSQLMapper::getDeleteSQLByCscOrderImportFormatId( const basar::Int32 CscOrderImportFormatId)
{
	std::stringstream sSql;
	sSql << "DELETE FROM cscorderimportcsvcolumns WHERE cscorderimportformatid = " << CscOrderImportFormatId;
	BLOG_TRACE(LoggerPool::getLoggerParameter(), sSql.str());
	return sSql.str();
}


void CSCOrderImportCSVColumnsSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setColumnNo( m_ResultSet.getInt16("ColumnNo"));
	setFieldNameId(m_ResultSet.getInt32("FieldNameId"));
	setCscOrderImportFormatId(m_ResultSet.getInt32("CscOrderImportFormatId"));
	setGrouping(m_ResultSet.getInt16("Grouping"));
}


}
}