#include "documentprintinfomapperbase.h"
#include "documentprintinfo.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace document {

DocumentPrintInfoMapperBase::DocumentPrintInfoMapperBase(DocumentPrintInfoPtr documentPrintInfo) :
	m_DocumentPrintInfo(documentPrintInfo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoMapperBase::DocumentPrintInfoMapperBase()");
}

DocumentPrintInfoMapperBase::~DocumentPrintInfoMapperBase()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoMapperBase::~DocumentPrintInfoMapperBase()");
}

void DocumentPrintInfoMapperBase::map()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoMapperBase::map()");

	doMap();
}

void DocumentPrintInfoMapperBase::setBranchNo(const basar::Int16& branchNo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoMapperBase::setBranchNo()");

	m_DocumentPrintInfo->m_BranchNo = branchNo;
	m_DocumentPrintInfo->m_BranchNo.setClean();
}

void DocumentPrintInfoMapperBase::setCustomerNo(const basar::Int32& customerNo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoMapperBase::setCustomerNo()");

	m_DocumentPrintInfo->m_CustomerNo = customerNo;
	m_DocumentPrintInfo->m_CustomerNo.setClean();
}

void DocumentPrintInfoMapperBase::setDocumentType(const DocumentTypeEnum& documentType)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoMapperBase::setDocumentType()");

	m_DocumentPrintInfo->m_DocumentType = documentType;
	m_DocumentPrintInfo->m_DocumentType.setClean();
}

void DocumentPrintInfoMapperBase::setDocumentDate(const basar::Int32& documentDate)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoMapperBase::setDocumentDate()");

	m_DocumentPrintInfo->m_DocumentDate = documentDate;
	m_DocumentPrintInfo->m_DocumentDate.setClean();
}

void DocumentPrintInfoMapperBase::setDocumentNo(const basar::VarString& documentNo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoMapperBase::setDocumentNo()");

	m_DocumentPrintInfo->m_DocumentNo = documentNo;
	m_DocumentPrintInfo->m_DocumentNo.setClean();
}

void DocumentPrintInfoMapperBase::setClean()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentPrintInfoMapperBase::setClean()");

	m_DocumentPrintInfo->m_BranchNo.setClean();
	m_DocumentPrintInfo->m_CustomerNo.setClean();
	m_DocumentPrintInfo->m_DocumentType.setClean();
	m_DocumentPrintInfo->m_DocumentDate.setClean();
	m_DocumentPrintInfo->m_DocumentNo.setClean();
}

} // end namespace document
} // end namespace libcsc
