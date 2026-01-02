#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FORMATS_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FORMATS_H

#include <parameter/csvorderimport/icscorderimportcsvformats.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>
#include "cscorderimportcsvcolumnsptr.h"

namespace libcsc {
namespace parameter {

class CSCOrderImportCSVFormats : public ICSCOrderImportCSVFormats
{
	friend class CSCOrderImportCSVFormatsMapperBase;
	friend class CSVOrderImportRepository;


public:
	CSCOrderImportCSVFormats();
	virtual ~CSCOrderImportCSVFormats();

	const basar::Int32&			getCSCOrderImportFormatID() const;
	const basar::Int16&			getDataStartingLine() const;
	const basar::Int16&			getPostponeOrder() const;
	const basar::VarString&		getCSVFormatName() const;
	const ICSCOrderImportCSVColumnsCollectionPtr getCSCOrderImportCSVColums() const;

	ICSCOrderImportCSVColumnsPtr addCSCOrderImportCSVColums(	const basar::Int16& ColumnNo,
																const basar::Int32& FieldNameId,
																const basar::Int16& Grouping);

	void						setCSCOrderImportFormatID(const basar::Int32& CSCOrderImportFormatID);
	void						setDataStartingLine(const basar::Int16& DataStartingLine);
	void						setPostponeOrder(const basar::Int16& PostponeOrder);
	void						setCSVFormatName(const basar::VarString& CSVFormatName);

	bool						containsColumn(const basar::Int32& fieldNameId);

	bool						isInsertable() const;
	bool						isUpdatable() const;
	bool						isClean() const;

private:
	libcsc::Int32						m_CSCOrderImportFormatID;
	libcsc::Int16						m_DataStartingLine;
	libcsc::Int16						m_PostponeOrder;
	libcsc::VarString					m_CSVFormatName;
	ICSCOrderImportCSVColumnsCollectionPtr m_CSCOrderImportCSVColums;
};

} // namespace parameter
} // namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_FORMATS_H
