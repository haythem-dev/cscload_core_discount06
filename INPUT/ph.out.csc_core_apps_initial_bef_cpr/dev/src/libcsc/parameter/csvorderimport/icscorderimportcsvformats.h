#ifndef GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FORMATS_H
#define GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FORMATS_H

#include <libbasar_definitions.h>

#include <parameter/csvorderimport/icscorderimportcsvcolumnsptr.h>

namespace libcsc {
namespace parameter {

class ICSCOrderImportCSVFormats
{
public:
	virtual ~ICSCOrderImportCSVFormats() {}

	virtual const basar::Int32&			getCSCOrderImportFormatID() const = 0;
	virtual const basar::Int16&			getDataStartingLine() const = 0;
	virtual const basar::Int16&			getPostponeOrder() const = 0;
	virtual const basar::VarString&		getCSVFormatName() const = 0;
	virtual const ICSCOrderImportCSVColumnsCollectionPtr getCSCOrderImportCSVColums() const = 0;

	virtual ICSCOrderImportCSVColumnsPtr addCSCOrderImportCSVColums(	const basar::Int16& ColumnNo,
																		const basar::Int32& FieldNameId,
																		const basar::Int16& Grouping) = 0;
	virtual bool						containsColumn(const basar::Int32& fieldNameId) = 0;
	
	virtual void						setCSCOrderImportFormatID(const basar::Int32& CSCOrderImportFormatID) = 0;
	virtual void						setDataStartingLine(const basar::Int16& DataStartingLine) = 0;
	virtual void						setPostponeOrder(const basar::Int16& PostponeOrder) = 0;
	virtual void						setCSVFormatName(const basar::VarString& ordeCSVFormatNamerType) = 0;

	virtual bool						isInsertable() const = 0;
	virtual bool						isUpdatable() const = 0;
	virtual bool						isClean() const = 0;
//	virtual bool						operator < (const ICSCOrderImportCSVFormats& rhs) const = 0;

};

} // namespace parameter
} // namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_I_CSC_ORDER_IMPORT_FORMATS_H
