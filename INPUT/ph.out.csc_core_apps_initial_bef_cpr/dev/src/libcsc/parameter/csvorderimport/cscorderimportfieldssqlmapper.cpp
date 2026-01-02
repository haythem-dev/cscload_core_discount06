#include "cscorderimportfieldssqlmapper.h"
#include "cscorderimportfields.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace parameter {

CSCOrderImportFieldsSQLMapper::CSCOrderImportFieldsSQLMapper(CSCOrderImportFieldsPtr CSCOrderImportFields, const basar::db::sql::ResultsetRef resultSet) :
	CSCOrderImportFieldsMapperBase(CSCOrderImportFields),
	m_ResultSet(resultSet)
{
}

CSCOrderImportFieldsSQLMapper::~CSCOrderImportFieldsSQLMapper()
{
}


const basar::VarString CSCOrderImportFieldsSQLMapper::getSelectSQL()
{
	std::stringstream sSql;
	sSql <<
		"SELECT "
			"fieldnameid, "
			"importfieldname, "
			"displayname, "
			"importmandatory "
		"FROM cscorderimportfields " ;

	BLOG_TRACE(LoggerPool::getLoggerParameter(), sSql.str());
	return sSql.str();
}

//----------------------------------------------------------------------------------
// Mapping from database
//----------------------------------------------------------------------------------
void CSCOrderImportFieldsSQLMapper::doMap()
{
	if( m_ResultSet.isNull() )
	{
		throw;
	}

	setFieldNameId		( m_ResultSet.getInt32("FieldNameId"));
	setImportFieldName	( m_ResultSet.getString("ImportFieldName"));
	setDisplayName		( m_ResultSet.getString("DisplayName"));
	setImportMandatory	( m_ResultSet.getInt16("ImportMandatory"));
}

}
}
