#include "cscorderimportcsvformats.h"
#include "cscorderimportcsvcolumns.h"
#include <logger/loggerpool.h>
#include <boost/make_shared.hpp>

namespace libcsc {
namespace parameter {

	CSCOrderImportCSVFormats::CSCOrderImportCSVFormats()
{
		m_CSCOrderImportCSVColums = boost::make_shared<ICSCOrderImportCSVColumnsCollection>();
}

	CSCOrderImportCSVFormats::~CSCOrderImportCSVFormats()
{
}

const basar::Int32& CSCOrderImportCSVFormats::getCSCOrderImportFormatID() const
{
	return m_CSCOrderImportFormatID;
}

const basar::Int16& CSCOrderImportCSVFormats::getDataStartingLine() const
{
	return m_DataStartingLine;
}

const basar::Int16& CSCOrderImportCSVFormats::getPostponeOrder() const
{
	return m_PostponeOrder;
}

const basar::VarString& CSCOrderImportCSVFormats::getCSVFormatName() const
{
	return m_CSVFormatName;
}

const ICSCOrderImportCSVColumnsCollectionPtr CSCOrderImportCSVFormats::getCSCOrderImportCSVColums() const
{
	return m_CSCOrderImportCSVColums;
}

ICSCOrderImportCSVColumnsPtr CSCOrderImportCSVFormats::addCSCOrderImportCSVColums(	const basar::Int16& ColumnNo,
																					const basar::Int32& FieldNameId,
																					const basar::Int16& Grouping)
{
	CSCOrderImportCSVColumnsPtr CSVColumns = boost::make_shared<CSCOrderImportCSVColumns>();
	CSVColumns->setColumnNo(ColumnNo);
	CSVColumns->setFieldNameId(FieldNameId);
	CSVColumns->setCscOrderImportFormatId(this->getCSCOrderImportFormatID());
	CSVColumns->setGrouping(Grouping);
	m_CSCOrderImportCSVColums->push_back(CSVColumns);
	return CSVColumns;
}

bool CSCOrderImportCSVFormats::containsColumn(const basar::Int32& fieldNameId)
{
	ICSCOrderImportCSVColumnsCollection::const_iterator colIt = m_CSCOrderImportCSVColums->begin();
	while (colIt != m_CSCOrderImportCSVColums->end())
	{
		if (fieldNameId == (*colIt)->getFieldNameId())
		{
			return true;
		}
		++colIt;
	}
	return false;
}

void CSCOrderImportCSVFormats::setCSCOrderImportFormatID(const basar::Int32& CSCOrderImportFormatID)
{
	m_CSCOrderImportFormatID = CSCOrderImportFormatID;
}

void CSCOrderImportCSVFormats::setDataStartingLine(const basar::Int16& DataStartingLine)
{
	m_DataStartingLine = DataStartingLine;
}

void CSCOrderImportCSVFormats::setPostponeOrder(const basar::Int16& PostponeOrder)
{
	m_PostponeOrder = PostponeOrder;
}

void CSCOrderImportCSVFormats::setCSVFormatName(const basar::VarString& CSVFormatName)
{
	m_CSVFormatName = CSVFormatName;
}

bool CSCOrderImportCSVFormats::isInsertable() const
{
	return	m_CSCOrderImportFormatID.isUnset() &&

		m_DataStartingLine.isDirty() &&
		m_PostponeOrder.isDirty() &&
		m_CSVFormatName.isDirty();
}

bool CSCOrderImportCSVFormats::isUpdatable() const
{
	return	m_CSCOrderImportFormatID.isClean() &&

		m_DataStartingLine.isDirty() &&
		m_PostponeOrder.isDirty() &&
		m_CSVFormatName.isDirty();
}

bool CSCOrderImportCSVFormats::isClean() const
{
	return m_DataStartingLine.isClean() &&
		m_PostponeOrder.isClean() &&
		m_CSCOrderImportFormatID.isClean() &&
		m_CSVFormatName.isClean();
}

} // namespace parameter
} // namespace libcsc
