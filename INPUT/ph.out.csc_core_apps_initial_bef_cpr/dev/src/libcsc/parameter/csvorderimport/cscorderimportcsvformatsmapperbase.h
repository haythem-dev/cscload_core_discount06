#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FORMATS_MAPPER_BASE_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FORMATS_MAPPER_BASE_H

#include <libbasar_definitions.h>
#include "cscorderimportcsvformatsptr.h"

namespace libcsc {
namespace parameter {

class CSCOrderImportCSVFormatsMapperBase
{
public:
	CSCOrderImportCSVFormatsMapperBase(CSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats);

	void			map();
protected:
	virtual ~CSCOrderImportCSVFormatsMapperBase();

	virtual void	doMap() = 0;

	void setCSCOrderImportFormatID(const basar::Int32& CSCOrderImportFormatID);
	void setDataStartingLine(const basar::Int16& DataStartingLine);
	void setPostponeOrder(const basar::Int16& PostponeOrder);
	void setCSVFormatName(const basar::VarString& CSVFormatName);

private:
	CSCOrderImportCSVFormatsPtr m_CSCOrderImportCSVFormats;
};

} // end namespace parameter
} // end namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FORMATS_MAPPER_BASE_H
