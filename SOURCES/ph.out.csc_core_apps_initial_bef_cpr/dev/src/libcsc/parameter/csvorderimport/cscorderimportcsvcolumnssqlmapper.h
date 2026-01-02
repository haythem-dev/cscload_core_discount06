#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_CSV_COLUMNS_SQLMAPPER_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_CSV_COLUMNS_SQLMAPPER_H

#include "cscorderimportcsvcolumnsmapperbase.h"
#include "icscorderimportcsvcolumnsptr.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace parameter {

class CSCOrderImportCSVColumnsSQLMapper : public CSCOrderImportCSVColumnsMapperBase
{
public:
	CSCOrderImportCSVColumnsSQLMapper(CSCOrderImportCSVColumnsPtr CSCOrderImportCSVColumns, const basar::db::sql::ResultsetRef resultSet);
	virtual ~CSCOrderImportCSVColumnsSQLMapper();

	static const basar::VarString getSelectSQLByCscOrderImportFormatId(const basar::Int32 CscOrderImportFormatId);
	static const basar::VarString getInsertSQL(const ICSCOrderImportCSVColumnsPtr CSCOrderImportCSVColumns);
	static const basar::VarString getDeleteSQLByKey(const basar::Int16 ColumnNo, const basar::Int32 CscOrderImportFormatId);
	static const basar::VarString getDeleteSQLByCscOrderImportFormatId( const basar::Int32 CscOrderImportFormatId);


protected:
	virtual void doMap();

private:
	CSCOrderImportCSVColumnsSQLMapper(const CSCOrderImportCSVColumnsSQLMapper&);
	CSCOrderImportCSVColumnsSQLMapper & operator=(const CSCOrderImportCSVColumnsSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace paramater
} // end namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_CSV_COLUMNS_SQLMAPPER_H
