#ifndef GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_CSV_COLUMNS_H
#define GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_CSV_COLUMNS_H

#include <parameter/csvorderimport/icscorderimportcsvcolumns.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>

namespace libcsc {
namespace parameter {

class CSCOrderImportCSVColumns : public ICSCOrderImportCSVColumns
{
	friend class CSCOrderImportCSVColumnsMapperBase;

public:
	CSCOrderImportCSVColumns();
	virtual ~CSCOrderImportCSVColumns();

	const basar::Int16&			getColumnNo() const;
	const basar::Int32&			getFieldNameId() const;
	const basar::Int32&			getCscOrderImportFormatId() const;
	const basar::Int16&			getGrouping() const;


	void						setColumnNo(const basar::Int16& ColumnNo);
	void						setFieldNameId(const basar::Int32& FieldNameId);
	void						setCscOrderImportFormatId(const basar::Int32& CscOrderImportFormatId);
	void						setGrouping(const basar::Int16& Grouping);

	void						markForDeletion();
	bool						isMarkedForDeletion();

	bool						isInsertable() const;

private:
	libcsc::Int16						m_ColumnNo;
	libcsc::Int32						m_FieldNameId;
	libcsc::Int32						m_CscOrderImportFormatId;
	libcsc::Int16						m_Grouping;

	bool								m_DeletionFlag;
};

} // namespace parameter
} // namespace libcsc

#endif // GUARD_LIBCSC_PARAMETER_CSC_ORDER_IMPORT_CSV_COLUMNS_H
