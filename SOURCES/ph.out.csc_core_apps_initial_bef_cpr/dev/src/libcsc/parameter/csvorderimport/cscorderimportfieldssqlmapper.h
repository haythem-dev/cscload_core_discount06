#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FIELDS_SQLMAPPER_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FIELDS_SQLMAPPER_H

#include "cscorderimportfieldsmapperbase.h"
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace parameter {

class CSCOrderImportFieldsSQLMapper : public CSCOrderImportFieldsMapperBase
{
public:
	CSCOrderImportFieldsSQLMapper(CSCOrderImportFieldsPtr CSCOrderImportFields, const basar::db::sql::ResultsetRef resultSet);
	virtual ~CSCOrderImportFieldsSQLMapper();

	static const basar::VarString getSelectSQL();
protected:
	virtual void doMap();

private:
	CSCOrderImportFieldsSQLMapper(const CSCOrderImportFieldsSQLMapper&);
	CSCOrderImportFieldsSQLMapper & operator=(const CSCOrderImportFieldsSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FIELDS_SQLMAPPER_H
