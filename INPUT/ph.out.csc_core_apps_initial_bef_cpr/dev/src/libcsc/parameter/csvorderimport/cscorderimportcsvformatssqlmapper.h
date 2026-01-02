#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FORMATS_SQLMAPPER_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FORMATS_SQLMAPPER_H

#include <parameter/csvorderimport/cscorderimportcsvformatsmapperbase.h>
#include <parameter/csvorderimport/icscorderimportcsvformatsptr.h>
#include <libbasardbsql_resultsetref.h>

namespace libcsc {
namespace parameter {

class CSCOrderImportCSVFormatsSQLMapper : public CSCOrderImportCSVFormatsMapperBase
{
public:
	CSCOrderImportCSVFormatsSQLMapper(CSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats, const basar::db::sql::ResultsetRef resultSet);
	virtual ~CSCOrderImportCSVFormatsSQLMapper();

	static const basar::VarString getSelectSQL();
	static const basar::VarString getUpdateSQL(const ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats);
	static const basar::VarString getInsertSQL(const ICSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats);
	static const basar::VarString getDeleteSQL( const basar::Int32& CSCOrderImportFormatID);


protected:
	virtual void doMap();

private:
	CSCOrderImportCSVFormatsSQLMapper(const CSCOrderImportCSVFormatsSQLMapper&);
	CSCOrderImportCSVFormatsSQLMapper & operator=(const CSCOrderImportCSVFormatsSQLMapper&);

	const basar::db::sql::ResultsetRef		m_ResultSet;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FORMATS_SQLMAPPER_H
