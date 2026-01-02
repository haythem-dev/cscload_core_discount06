#include "cscorderimportfields.h"

namespace libcsc {
namespace parameter {

CSCOrderImportFields::CSCOrderImportFields()
{
}

CSCOrderImportFields::~CSCOrderImportFields()
{
}

const basar::Int32& CSCOrderImportFields::getFieldNameId() const
{
	return m_FieldNameId;
}

const basar::VarString& CSCOrderImportFields::getImportFieldName() const
{
	return m_ImportFieldName;
}

const basar::VarString& CSCOrderImportFields::getDisplayName() const
{
	return m_DisplayName;
}

const basar::Int16& CSCOrderImportFields::getImportMandatory() const
{
	return m_ImportMandatory;
}

bool CSCOrderImportFields::isImportMandatory() const
{
	return (1 == m_ImportMandatory);
}

} // namespace parameter
} // namespace libcsc
