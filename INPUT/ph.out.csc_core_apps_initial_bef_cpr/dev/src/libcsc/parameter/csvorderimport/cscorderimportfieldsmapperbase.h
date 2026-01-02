#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FIELDS_MAPPER_BASE_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FIELDS_MAPPER_BASE_H

#include <libbasar_definitions.h>
#include "cscorderimportfieldsptr.h"

namespace libcsc {
namespace parameter {

class CSCOrderImportFieldsMapperBase
{
public:
	CSCOrderImportFieldsMapperBase(CSCOrderImportFieldsPtr CSCOrderImportFields);

	void			map();
protected:
	virtual ~CSCOrderImportFieldsMapperBase();

	virtual void	doMap() = 0;

	void setFieldNameId( const basar::Int32& FieldNameId);
	void setImportFieldName( const basar::VarString& ImportFieldName);
	void setDisplayName(const basar::VarString& DisplayName);
	void setImportMandatory( const basar::Int16& ImportMandatory);

private:
	CSCOrderImportFieldsPtr m_CSCOrderImportFields;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FIELDS_MAPPER_BASE_H
