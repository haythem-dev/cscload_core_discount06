#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_H

#include <datatypes/boolean.h>
#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

#include <types/documenttypeenum.inc>


namespace libcsc {
namespace document {

typedef Property<DocumentTypeEnum> DocumentType;

class DocumentArchiveInfo
{
	friend class DocumentArchiveInfoMapperBase;
	friend class DocumentArchiveInfoSQLMapper;

public:
	DocumentArchiveInfo();
	virtual ~DocumentArchiveInfo();

	virtual const basar::Int16 &		getBranchNo() const;
	virtual const basar::Int32 &		getCustomerNo() const;
	virtual const DocumentTypeEnum&		getDocumentType() const;
	virtual const basar::VarString &	getDocumentNo() const;
	virtual const basar::Int32 &		getDocumentDate() const;
	virtual const basar::VarString &	getDocumentId() const;
	virtual const basar::VarString &	getDocumentLink() const;
	virtual       bool					getSentViaMail() const;
	virtual       bool					getSentViaFax() const;

	virtual void						setBranchNo(const basar::Int16 & branchNo);
	virtual void						setCustomerNo(const basar::Int32 & customerNo);
	virtual void						setDocumentType(const DocumentTypeEnum& documentType);
	virtual void						setDocumentNo(const basar::VarString & documentNo);
	virtual void						setDocumentDate(const basar::Int32 & documentDate);
	virtual void						setDocumentId(const basar::VarString & documentId);
	virtual void						setDocumentLink(const basar::VarString & documentLink);
	virtual void						setSentViaMail(const bool& sentViaMail);
	virtual void						setSentViaFax(const bool& sentViaFax);

	virtual bool						isClean();
	virtual bool						isDirty();
	virtual void						setClean();

protected:

private:
	libcsc::Int16						m_BranchNo;
	libcsc::Int32						m_CustomerNo;
	libcsc::document::DocumentType		m_DocumentType;
	libcsc::VarString					m_DocumentNo;
	libcsc::Int32						m_DocumentDate;
	libcsc::VarString					m_DocumentId;
	libcsc::VarString					m_DocumentLink;
	libcsc::Bool						m_SentViaMail;
	libcsc::Bool						m_SentViaFax;
};

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_H
