#ifndef GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FIELDS_H
#define GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FIELDS_H

#include <libbasar_definitions.h>

namespace libcsc {
namespace parameter {

class ICSCOrderImportFields
{
public:
	virtual ~ICSCOrderImportFields() {}

	virtual const basar::Int32&			getFieldNameId() const = 0;
	virtual const basar::VarString&		getImportFieldName() const = 0;
	virtual const basar::VarString&		getDisplayName() const = 0;
	virtual const basar::Int16&			getImportMandatory() const = 0;
	virtual       bool					isImportMandatory() const = 0;
};

} // namespace parameter
} // namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FIELDS_H
