#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FIELDS_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FIELDS_H

#include <parameter/csvorderimport/icscorderimportfields.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

namespace libcsc {
namespace parameter {

class CSCOrderImportFields : public ICSCOrderImportFields
{
	friend class CSCOrderImportFieldsMapperBase;

public:
	CSCOrderImportFields();
	virtual ~CSCOrderImportFields();

	virtual const basar::Int32&			getFieldNameId() const;
	virtual const basar::VarString&		getImportFieldName() const;
	virtual const basar::VarString&		getDisplayName() const;
	virtual const basar::Int16&			getImportMandatory() const;
	virtual       bool					isImportMandatory() const;

private:
	libcsc::Int32						m_FieldNameId;
	libcsc::VarString					m_ImportFieldName;
	libcsc::VarString					m_DisplayName;
	libcsc::Int16						m_ImportMandatory;
};

} // namespace parameter
} // namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FIELDS_H
