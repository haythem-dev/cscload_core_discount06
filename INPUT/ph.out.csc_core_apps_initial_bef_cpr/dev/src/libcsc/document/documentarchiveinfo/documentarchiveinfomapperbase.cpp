#include "documentarchiveinfomapperbase.h"
#include "documentarchiveinfo.h"
#include "logger/loggerpool.h"

namespace libcsc {
namespace document {

DocumentArchiveInfoMapperBase::DocumentArchiveInfoMapperBase(DocumentArchiveInfoPtr documentArchiveInfo) :
	m_DocumentArchiveInfo(documentArchiveInfo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::DocumentArchiveInfoMapperBase()");
}

DocumentArchiveInfoMapperBase::~DocumentArchiveInfoMapperBase()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::~DocumentArchiveInfoMapperBase()");
}

void DocumentArchiveInfoMapperBase::map()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::map()");

	doMap();
}

void DocumentArchiveInfoMapperBase::setBranchNo(const basar::Int16& branchNo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::setBranchNo()");

	m_DocumentArchiveInfo->m_BranchNo = branchNo;
	m_DocumentArchiveInfo->m_BranchNo.setClean();
}

void DocumentArchiveInfoMapperBase::setCustomerNo(const basar::Int32& customerNo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::setCustomerNo()");

	m_DocumentArchiveInfo->m_CustomerNo = customerNo;
	m_DocumentArchiveInfo->m_CustomerNo.setClean();
}

void DocumentArchiveInfoMapperBase::setDocumentType(const DocumentTypeEnum& documentType)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::setDocumentType()");

	m_DocumentArchiveInfo->m_DocumentType = documentType;
	m_DocumentArchiveInfo->m_DocumentType.setClean();
}

void DocumentArchiveInfoMapperBase::setDocumentNo(const basar::VarString& documentNo)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::setDocumentNo()");

	m_DocumentArchiveInfo->m_DocumentNo = documentNo;
	m_DocumentArchiveInfo->m_DocumentNo.setClean();
}

void DocumentArchiveInfoMapperBase::setDocumentDate(const basar::Int32& documentDate)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::setDocumentDate()");

	m_DocumentArchiveInfo->m_DocumentDate = documentDate;
	m_DocumentArchiveInfo->m_DocumentDate.setClean();
}

void DocumentArchiveInfoMapperBase::setDocumentId(const basar::VarString& documentId)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::setDocumentId()");

	m_DocumentArchiveInfo->m_DocumentId = documentId;
	m_DocumentArchiveInfo->m_DocumentId.setClean();
}

void DocumentArchiveInfoMapperBase::setDocumentLink(const basar::VarString& documentLink)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::setDocumentLink()");

	m_DocumentArchiveInfo->m_DocumentLink = documentLink;
	m_DocumentArchiveInfo->m_DocumentLink.setClean();
}

void DocumentArchiveInfoMapperBase::setSentViaMail(const bool sentViaMail)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::setSentViaMail()");

	m_DocumentArchiveInfo->m_SentViaMail = sentViaMail;
	m_DocumentArchiveInfo->m_SentViaMail.setClean();
}

void DocumentArchiveInfoMapperBase::setSentViaFax(const bool sentViaFax)
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::setSentViaFax()");

	m_DocumentArchiveInfo->m_SentViaFax = sentViaFax;
	m_DocumentArchiveInfo->m_SentViaFax.setClean();
}

void DocumentArchiveInfoMapperBase::setClean()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfoMapperBase::setClean()");

	m_DocumentArchiveInfo->m_BranchNo.setClean();
	m_DocumentArchiveInfo->m_CustomerNo.setClean();
	m_DocumentArchiveInfo->m_DocumentType.setClean();
	m_DocumentArchiveInfo->m_DocumentNo.setClean();
	m_DocumentArchiveInfo->m_DocumentDate.setClean();
	m_DocumentArchiveInfo->m_DocumentId.setClean();
	m_DocumentArchiveInfo->m_DocumentLink.setClean();
	m_DocumentArchiveInfo->m_SentViaMail.setClean();
	m_DocumentArchiveInfo->m_SentViaFax.setClean();
}

} // end namespace document
} // end namespace libcsc
