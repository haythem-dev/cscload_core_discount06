#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFOMAPPER_BASE_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFOMAPPER_BASE_H

#include <libbasar_definitions.h>
#include "documentarchiveinfoptr.h"
#include <types/documenttypeenum.inc>

namespace libcsc {
namespace document {

class DocumentArchiveInfoMapperBase
{
public:
	DocumentArchiveInfoMapperBase(DocumentArchiveInfoPtr documentArchiveInfo);

	void			map();
protected:
	virtual ~DocumentArchiveInfoMapperBase();

	virtual void	doMap() = 0;

	void	setBranchNo(const basar::Int16& branchNo);
	void	setCustomerNo(const basar::Int32& customerNo);
	void	setDocumentType(const DocumentTypeEnum& documentType);
	void	setDocumentNo(const basar::VarString& documentNo);
	void	setDocumentDate(const basar::Int32& documentDate);
	void	setDocumentId(const basar::VarString& documentId);
	void	setDocumentLink(const basar::VarString& documentLink);
	void	setSentViaMail(const bool sentViaMail);
	void	setSentViaFax(const bool sentViaFax);

	virtual void	setClean();
//private:
	DocumentArchiveInfoPtr m_DocumentArchiveInfo;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFOMAPPER_BASE_H
