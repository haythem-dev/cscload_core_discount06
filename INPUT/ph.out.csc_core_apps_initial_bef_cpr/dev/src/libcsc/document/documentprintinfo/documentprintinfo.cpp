#include "documentprintinfo.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace document {

DocumentPrintInfo::DocumentPrintInfo()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfo::DocumentPrintInfo()");
}

DocumentPrintInfo::~DocumentPrintInfo()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfo::~DocumentPrintInfo()");
}

const basar::Int16 & DocumentPrintInfo::getBranchNo() const
{
	return m_BranchNo;
}

const basar::Int32 & DocumentPrintInfo::getCustomerNo() const
{
	return m_CustomerNo;
}

const DocumentTypeEnum& DocumentPrintInfo::getDocumentType() const
{
	return m_DocumentType;
}

const basar::Int32 & DocumentPrintInfo::getDocumentDate() const
{
	return m_DocumentDate;
}

const basar::VarString & DocumentPrintInfo::getDocumentNo() const
{
	return m_DocumentNo;
}

void DocumentPrintInfo::setBranchNo(const basar::Int16 & branchNo)
{
	m_BranchNo = branchNo;
}

void DocumentPrintInfo::setCustomerNo(const basar::Int32 & customerNo)
{
	m_CustomerNo = customerNo;
}

void DocumentPrintInfo::setDocumentType(const DocumentTypeEnum& documentType)
{
	m_DocumentType = documentType;
}

void DocumentPrintInfo::setDocumentDate(const basar::Int32 & documentDate)
{
	m_DocumentDate = documentDate;
}

void DocumentPrintInfo::setDocumentNo(const basar::VarString & documentNo)
{
	m_DocumentNo = documentNo;
}

bool DocumentPrintInfo::isClean()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfo::isClean()");
	return m_BranchNo.isClean() &&
		m_CustomerNo.isClean() &&
		m_DocumentType.isClean() &&
		m_DocumentDate.isClean() &&
		m_DocumentNo.isClean();
}

bool DocumentPrintInfo::isDirty()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfo::isDirty()");
	return m_BranchNo.isDirty() &&
		m_CustomerNo.isDirty() &&
		m_DocumentType.isDirty() &&
		m_DocumentDate.isDirty() &&
		m_DocumentNo.isDirty();
}

void DocumentPrintInfo::setClean()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfo::setClean()");
}

} // namespace document
} // namespace libcsc
