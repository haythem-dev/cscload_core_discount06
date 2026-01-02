#include "cscorderimportcsvcolumnsmapperbase.h"
#include "cscorderimportcsvcolumns.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace parameter {


CSCOrderImportCSVColumnsMapperBase::CSCOrderImportCSVColumnsMapperBase(CSCOrderImportCSVColumnsPtr CSCOrderImportCSVColumns):
	m_CSCOrderImportCSVColumns(CSCOrderImportCSVColumns)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderImportCSVColumnsMapperBase::CSCOrderImportCSVColumnsMapperBase()");
}

	CSCOrderImportCSVColumnsMapperBase::~CSCOrderImportCSVColumnsMapperBase()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderImportCSVColumnsMapperBase::~CSCOrderImportCSVColumnsMapperBase()");
}

void CSCOrderImportCSVColumnsMapperBase::map()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderImportCSVColumnsMapperBase::map()");
	doMap();
}

void CSCOrderImportCSVColumnsMapperBase::setColumnNo( const basar::Int16& ColumnNo)
{
	m_CSCOrderImportCSVColumns->m_ColumnNo = ColumnNo;
	m_CSCOrderImportCSVColumns->m_ColumnNo.setClean();
}

void CSCOrderImportCSVColumnsMapperBase::setFieldNameId(const basar::Int32& FieldNameId)
{
	m_CSCOrderImportCSVColumns->m_FieldNameId = FieldNameId;
	m_CSCOrderImportCSVColumns->m_FieldNameId.setClean();
}

void CSCOrderImportCSVColumnsMapperBase::setCscOrderImportFormatId(const basar::Int32& CscOrderImportFormatId)
{
	m_CSCOrderImportCSVColumns->m_CscOrderImportFormatId = CscOrderImportFormatId;
	m_CSCOrderImportCSVColumns->m_CscOrderImportFormatId.setClean();
}

void CSCOrderImportCSVColumnsMapperBase::setGrouping(const basar::Int16& Grouping)
{
	m_CSCOrderImportCSVColumns->m_Grouping = Grouping;
	m_CSCOrderImportCSVColumns->m_ColumnNo.setClean();
}


}
}