#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_REPOSITORY_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_REPOSITORY_H

#include "documentprintinfoptr.h"

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasarcmnutil_bstring.h>
#include <parameter/ibranchparametergetterptr.h>
#include <types/documenttypeenum.inc>

namespace libcsc {
namespace document {

class DocumentPrintInfoRepository
{
public:
	DocumentPrintInfoRepository();
	virtual ~DocumentPrintInfoRepository();

	virtual void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);
	virtual void injectInsertAccessor(persistence::IAccessorPtr accessor);
	virtual void injectFindAccessor(persistence::IAccessorPtr accessor);

	virtual DocumentPrintInfoPtr createEmptyDocumentPrintInfo() const;
	virtual void saveDocumentPrintInfo(DocumentPrintInfoPtr documentPrintInfo) const;
	virtual DocumentPrintInfoPtr findDocumentPrintInfo(const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum documentType, const basar::VarString & documentNo, const basar::Int32 documentDate = 0) const;

	void injectBranchParameterGetter( parameter::IBranchParameterGetterPtr parameterGetter );

protected:

private:
	DocumentPrintInfoRepository& operator=(const DocumentPrintInfoRepository &);

	persistence::ITransactionFactoryPtr  m_TransactionFactory;
	persistence::IAccessorPtr			 m_InsertAccessor;
	persistence::IAccessorPtr			 m_FindAccessor;
	parameter::IBranchParameterGetterPtr m_BranchParameterGetter;
};

} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTPRINTINFO_REPOSITORY_H
