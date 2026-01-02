#include "cscorderimportcsvformatsmapperbase.h"
#include "cscorderimportcsvformats.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace parameter {


CSCOrderImportCSVFormatsMapperBase::CSCOrderImportCSVFormatsMapperBase(CSCOrderImportCSVFormatsPtr CSCOrderImportCSVFormats) :
	m_CSCOrderImportCSVFormats(CSCOrderImportCSVFormats)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerInfrastructure(), "CSCOrderImportCSVFormatsMapperBase::CSCOrderImportCSVFormatsMapperBase()");
}

CSCOrderImportCSVFormatsMapperBase::~CSCOrderImportCSVFormatsMapperBase()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerInfrastructure(), "CSCOrderImportCSVFormatsMapperBase::~CSCOrderImportCSVFormatsMapperBase()");
}

void CSCOrderImportCSVFormatsMapperBase::map()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerInfrastructure(), "CSCOrderImportCSVFormatsMapperBase::map()");
	doMap();
}
void CSCOrderImportCSVFormatsMapperBase::setCSCOrderImportFormatID(const basar::Int32& CSCOrderImportFormatID)
{
	m_CSCOrderImportCSVFormats->m_CSCOrderImportFormatID = CSCOrderImportFormatID;
	m_CSCOrderImportCSVFormats->m_CSCOrderImportFormatID.setClean();
}

void CSCOrderImportCSVFormatsMapperBase::setDataStartingLine(const basar::Int16& DataStartingLine)
{
	m_CSCOrderImportCSVFormats->m_DataStartingLine = DataStartingLine;
	m_CSCOrderImportCSVFormats->m_DataStartingLine.setClean();
}

void CSCOrderImportCSVFormatsMapperBase::setPostponeOrder(const basar::Int16& PostponeOrder)
{
	m_CSCOrderImportCSVFormats->m_PostponeOrder = PostponeOrder;
	m_CSCOrderImportCSVFormats->m_PostponeOrder.setClean();
}

void CSCOrderImportCSVFormatsMapperBase::setCSVFormatName(const basar::VarString& CSVFormatName)
{
	m_CSCOrderImportCSVFormats->m_CSVFormatName = CSVFormatName;
	m_CSCOrderImportCSVFormats->m_CSVFormatName.setClean();
}

}
}