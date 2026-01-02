#include "cscorderimportfieldsmapperbase.h"
#include "cscorderimportfields.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace parameter {


CSCOrderImportFieldsMapperBase::CSCOrderImportFieldsMapperBase(CSCOrderImportFieldsPtr CSCOrderImportFields) :
	m_CSCOrderImportFields(CSCOrderImportFields)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderImportFieldsMapperBase::CSCOrderImportFieldsMapperBase()");
}

CSCOrderImportFieldsMapperBase::~CSCOrderImportFieldsMapperBase()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderImportFieldsMapperBase::~CSCOrderImportFieldsMapperBase()");
}

void CSCOrderImportFieldsMapperBase::map()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerParameter(), "CSCOrderImportFieldsMapperBase::map()");
	doMap();
}

void CSCOrderImportFieldsMapperBase::setFieldNameId( const basar::Int32& FieldNameId)
{
	m_CSCOrderImportFields->m_FieldNameId = FieldNameId;
	m_CSCOrderImportFields->m_FieldNameId.setClean();
}

void CSCOrderImportFieldsMapperBase::setImportFieldName( const basar::VarString& ImportFieldName)
{
	m_CSCOrderImportFields->m_ImportFieldName = ImportFieldName;
	m_CSCOrderImportFields->m_ImportFieldName.setClean();
}

void CSCOrderImportFieldsMapperBase::setDisplayName(const basar::VarString& DisplayName)
{
	m_CSCOrderImportFields->m_DisplayName = DisplayName;
	m_CSCOrderImportFields->m_DisplayName.setClean();
}

void CSCOrderImportFieldsMapperBase::setImportMandatory(const basar::Int16& ImportMandatory)
{
	m_CSCOrderImportFields->m_ImportMandatory = ImportMandatory;
	m_CSCOrderImportFields->m_ImportMandatory.setClean();
}

}
}