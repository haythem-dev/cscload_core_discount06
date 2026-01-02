#include "cscorderimportcsvcolumns.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace parameter {

CSCOrderImportCSVColumns::CSCOrderImportCSVColumns()
{
	m_DeletionFlag = false;
}

CSCOrderImportCSVColumns::~CSCOrderImportCSVColumns()
{
}

//Get-Methods
const basar::Int16& CSCOrderImportCSVColumns::getColumnNo() const
{
	return m_ColumnNo;
}

const basar::Int32& CSCOrderImportCSVColumns::getFieldNameId() const
{
	return m_FieldNameId;
}

const basar::Int32& CSCOrderImportCSVColumns::getCscOrderImportFormatId() const
{
	return m_CscOrderImportFormatId;
}

const basar::Int16& CSCOrderImportCSVColumns::getGrouping() const
{
	return m_Grouping;
}


//Set-Methods
void CSCOrderImportCSVColumns::setColumnNo(const basar::Int16& ColumnNo)
{
	m_ColumnNo = ColumnNo;
}

void CSCOrderImportCSVColumns::setFieldNameId(const basar::Int32& FieldNameId)
{
	m_FieldNameId = FieldNameId;
}

void CSCOrderImportCSVColumns::setCscOrderImportFormatId(const basar::Int32& CscOrderImportFormatId)
{
	m_CscOrderImportFormatId = CscOrderImportFormatId;
}

void CSCOrderImportCSVColumns::setGrouping(const basar::Int16& Grouping)
{
	m_Grouping = Grouping;
}

//Internals
void CSCOrderImportCSVColumns::markForDeletion()
{
	m_DeletionFlag = true;
}
bool CSCOrderImportCSVColumns::isMarkedForDeletion()
{
	return m_DeletionFlag;
}

bool CSCOrderImportCSVColumns::isInsertable() const
{
	return	m_ColumnNo.isDirty() &&

		m_CscOrderImportFormatId.isDirty() &&
		m_FieldNameId.isDirty();
}

} // namespace parameter
} // namespace libcsc
