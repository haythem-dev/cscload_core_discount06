#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_CSV_COLUMNS_MAPPER_BASE_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_CSV_COLUMNS_MAPPER_BASE_H

#include <libbasar_definitions.h>
#include "cscorderimportcsvcolumnsptr.h"

namespace libcsc {
namespace parameter {

class CSCOrderImportCSVColumnsMapperBase
{
public:
	CSCOrderImportCSVColumnsMapperBase(CSCOrderImportCSVColumnsPtr CSCOrderImportCSVColumns);

	void			map();
protected:
	virtual ~CSCOrderImportCSVColumnsMapperBase();

	virtual void	doMap() = 0;

	void setColumnNo( const basar::Int16& ColumnNo);
	void setFieldNameId(const basar::Int32& FieldNameId);
	void setCscOrderImportFormatId(const basar::Int32& CscOrderImportFormatId);
	void setGrouping(const basar::Int16& Grouping);

private:
	CSCOrderImportCSVColumnsPtr m_CSCOrderImportCSVColumns;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_CSV_COLUMNS_MAPPER_BASE_H
