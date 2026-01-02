#ifndef GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_CSV_COLUMNS_H
#define GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_CSV_COLUMNS_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace parameter {

class ICSCOrderImportCSVColumns
{
public:
	virtual ~ICSCOrderImportCSVColumns() {}

	virtual const basar::Int16&			getColumnNo() const = 0;
	virtual const basar::Int32&			getFieldNameId() const = 0;
	virtual const basar::Int32&			getCscOrderImportFormatId() const = 0;
	virtual const basar::Int16&			getGrouping() const = 0;

	virtual void						setColumnNo(const basar::Int16& ColumnNo) = 0;
	virtual void						setFieldNameId(const basar::Int32& FieldNameId) = 0;
	virtual void						setCscOrderImportFormatId(const basar::Int32& CscOrderImportFormatId) = 0;
	virtual void						setGrouping(const basar::Int16& Grouping) = 0;

	virtual void						markForDeletion() = 0;
	virtual bool						isMarkedForDeletion() = 0;

	virtual bool						isInsertable() const = 0;
};

} // namespace parameter
} // namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_CSV_COLUMNS_H
