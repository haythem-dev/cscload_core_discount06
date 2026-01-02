#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFOMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFOMAPPER_BASE_H

#include "documentprintinfoptr.h"
#include <libbasar_definitions.h>
#include <types/documenttypeenum.inc>

namespace libcsc {
namespace document {

class DocumentPrintInfoMapperBase
{
public:
	DocumentPrintInfoMapperBase(DocumentPrintInfoPtr documentPrintInfo);

	void	map();
protected:
	virtual ~DocumentPrintInfoMapperBase();

	virtual void	doMap() = 0;

	void	setBranchNo(const basar::Int16& branchNo);
	void	setCustomerNo(const basar::Int32& customerNo);
	void	setDocumentType(const DocumentTypeEnum& documentType);
	void	setDocumentDate(const basar::Int32& documentDate);
	void	setDocumentNo(const basar::VarString& documentNo);

	virtual void	setClean();

//private:
	DocumentPrintInfoPtr m_DocumentPrintInfo;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFOMAPPER_BASE_H
