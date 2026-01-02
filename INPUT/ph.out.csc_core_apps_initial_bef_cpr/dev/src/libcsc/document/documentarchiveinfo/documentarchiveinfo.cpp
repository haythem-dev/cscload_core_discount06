#include "documentarchiveinfo.h"
#include <logger/loggerpool.h>

namespace libcsc {
namespace document {

DocumentArchiveInfo::DocumentArchiveInfo()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfo::DocumentArchiveInfo()");
}

DocumentArchiveInfo::~DocumentArchiveInfo()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfo::~DocumentArchiveInfo()");
}

const basar::Int16 & DocumentArchiveInfo::getBranchNo() const
{
	return m_BranchNo;
}

const basar::Int32 & DocumentArchiveInfo::getCustomerNo() const
{
	return m_CustomerNo;
}

const DocumentTypeEnum& DocumentArchiveInfo::getDocumentType() const
{
	return m_DocumentType;
}

const basar::VarString & DocumentArchiveInfo::getDocumentNo() const
{
	return m_DocumentNo;
}

const basar::Int32 & DocumentArchiveInfo::getDocumentDate() const
{
	return m_DocumentDate;
}

const basar::VarString & DocumentArchiveInfo::getDocumentId() const
{
	return m_DocumentId;
}

const basar::VarString & DocumentArchiveInfo::getDocumentLink() const
{
	return m_DocumentLink;
}

bool DocumentArchiveInfo::getSentViaMail() const
{
	return m_SentViaMail;
}

bool DocumentArchiveInfo::getSentViaFax() const
{
	return m_SentViaFax;
}


void DocumentArchiveInfo::setBranchNo(const basar::Int16 & branchNo)
{
	m_BranchNo = branchNo;
}

void DocumentArchiveInfo::setCustomerNo(const basar::Int32 & customerNo)
{
	m_CustomerNo = customerNo;
}

void DocumentArchiveInfo::setDocumentType(const DocumentTypeEnum& documentType)
{
	m_DocumentType = documentType;
}

void DocumentArchiveInfo::setDocumentNo(const basar::VarString & documentNo)
{
	m_DocumentNo = documentNo;
}

void DocumentArchiveInfo::setDocumentDate(const basar::Int32 & documentDate)
{
	m_DocumentDate = documentDate;
}

void DocumentArchiveInfo::setDocumentId(const basar::VarString & documentId)
{
	m_DocumentId = documentId;
}

void DocumentArchiveInfo::setDocumentLink(const basar::VarString & documentLink)
{
	m_DocumentLink = documentLink;
}

void DocumentArchiveInfo::setSentViaMail(const bool& sentViaMail)
{
	m_SentViaMail = sentViaMail;
}

void DocumentArchiveInfo::setSentViaFax(const bool& sentViaFax)
{
	m_SentViaFax = sentViaFax;
}

bool DocumentArchiveInfo::isClean()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfo::isClean()");
	return m_BranchNo.isClean() &&
			m_CustomerNo.isClean() &&
			m_DocumentType.isClean() &&
			m_DocumentNo.isClean() &&
			m_DocumentDate.isClean();
}

bool DocumentArchiveInfo::isDirty()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfo::isDirty()");
	return m_BranchNo.isDirty() &&
		m_CustomerNo.isDirty() &&
		m_DocumentType.isDirty() &&
		m_DocumentNo.isDirty() &&
		m_DocumentDate.isDirty() &&
		m_DocumentId.isDirty() &&
		m_DocumentLink.isDirty();
}

void DocumentArchiveInfo::setClean()
{
	LOG4CPLUS_TRACE_METHOD(libcsc::LoggerPool::getLoggerDocuments(), "DocumentArchiveInfo::setClean()");
}

} // namespace document
} // namespace libcsc
