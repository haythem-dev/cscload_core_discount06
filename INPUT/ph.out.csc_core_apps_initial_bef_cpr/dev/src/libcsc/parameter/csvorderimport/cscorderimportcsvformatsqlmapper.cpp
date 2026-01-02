#include "cscorderimportcsvformatssqlmapper.h"
#include "cscorderimportcsvformats.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace parameter {

CSCOrderImportCSVFormatsSQLMapper::CSCOrderImportCSVFormatsSQLMapper(CSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats, const basar::db::sql::ResultsetRef resultSet) :
	CSCOrderImportCSVFormatsMapperBase(CSCOrderImportCSVFormats),
	m_ResultSet(resultSet)
{
}

CSCOrderImportCSVFormatsSQLMapper::~CSCOrderImportCSVFormatsSQLMapper()
{
}

const basar::VarString CSCOrderImportCSVFormatsSQLMapper::getSelectSQL()
{
	std::stringstream sSql;

	sSql << "SELECT "
		"csvformatname, "
		"datastartingline, "
		"postponeorder, "
		"cscorderimportformatid "
		"FROM "
		"cscorderimportcsvformats "
		"ORDER BY csvformatname ";

	BLOG_TRACE(LoggerPool::getLoggerParameter(), sSql.str());
	return sSql.str();
}

const basar::VarString CSCOrderImportCSVFormatsSQLMapper::getUpdateSQL(const ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats)
{
	std::stringstream sSql;

	sSql << "UPDATE "
		"cscorderimportcsvformats SET "
		"csvformatname = '" << CSCOrderImportCSVFormats->getCSVFormatName() << "', " <<
		"datastartingline = " << CSCOrderImportCSVFormats->getDataStartingLine() << ", " <<
		"postponeorder = " << CSCOrderImportCSVFormats->getPostponeOrder() <<
		" WHERE cscorderimportformatid = " << CSCOrderImportCSVFormats->getCSCOrderImportFormatID();
	BLOG_TRACE(LoggerPool::getLoggerParameter(), sSql.str());
	return sSql.str();
}

const basar::VarString CSCOrderImportCSVFormatsSQLMapper::getInsertSQL( const ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats)
{
	std::stringstream sSql;
	
	sSql << "INSERT INTO cscorderimportcsvformats "
		" (csvformatname, datastartingline, postponeorder ) "
		" VALUES ( " 
		"'" << CSCOrderImportCSVFormats->getCSVFormatName() << "', "
		<< CSCOrderImportCSVFormats->getDataStartingLine() << ", " 
		<< CSCOrderImportCSVFormats->getPostponeOrder() << ")";
	BLOG_TRACE(LoggerPool::getLoggerParameter(), sSql.str());
	return sSql.str();
}

const basar::VarString CSCOrderImportCSVFormatsSQLMapper::getDeleteSQL( const basar::Int32& CSCOrderImportFormatID)
{
	std::stringstream sSql;
	sSql << "DELETE FROM cscorderimportcsvformats WHERE cscorderimportformatid = " << CSCOrderImportFormatID;
	BLOG_TRACE(LoggerPool::getLoggerParameter(), sSql.str());
	return sSql.str();
}
//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void CSCOrderImportCSVFormatsSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setCSCOrderImportFormatID( m_ResultSet.getInt32("CSCOrderImportFormatID"));

	setDataStartingLine(m_ResultSet.getInt16("DataStartingLine"));
	setPostponeOrder( m_ResultSet.getInt16("PostponeOrder"));
	setCSVFormatName( m_ResultSet.getString("CSVFormatName"));

}

}
}