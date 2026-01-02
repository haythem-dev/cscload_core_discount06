#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_H

#include <datatypes/int16.h>
#include <datatypes/int32.h>
#include <datatypes/varstring.h>

#include <types/documenttypeenum.inc>


namespace libcsc {
namespace document {

typedef Property<DocumentTypeEnum> DocumentType;

class DocumentPrintInfo
{
	friend class DocumentPrintInfoMapperBase;
	friend class DocumentPrintInfoSQLMapper;

public:
	DocumentPrintInfo();
	virtual ~DocumentPrintInfo();

	virtual const basar::Int16 &		getBranchNo() const;
	virtual const basar::Int32 &		getCustomerNo() const;
	virtual const DocumentTypeEnum&		getDocumentType() const;
	virtual const basar::Int32 &		getDocumentDate() const;
	virtual const basar::VarString &	getDocumentNo() const;

	virtual void						setBranchNo(const basar::Int16 & branchNo);
	virtual void						setCustomerNo(const basar::Int32 & customerNo);
	virtual void						setDocumentType(const DocumentTypeEnum& documentType);
	virtual void						setDocumentDate(const basar::Int32 & documentDate);
	virtual void						setDocumentNo(const basar::VarString & documentNo);

	virtual bool						isClean();
	virtual bool						isDirty();
	virtual void						setClean();

protected:

private:
	libcsc::Int16						m_BranchNo;
	libcsc::Int32						m_CustomerNo;
	libcsc::document::DocumentType		m_DocumentType;
	libcsc::Int32						m_DocumentDate;
	libcsc::VarString					m_DocumentNo;
};

} // namespace document
} // namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_H
