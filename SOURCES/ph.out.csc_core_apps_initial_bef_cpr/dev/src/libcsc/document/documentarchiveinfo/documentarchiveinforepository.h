#ifndef GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_REPOSITORY_H
#define GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_REPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasarcmnutil_bstring.h>
#include "documentarchiveinfoptr.h"
#include <parameter/ibranchparametergetterptr.h>
#include <types/documenttypeenum.inc>

namespace libcsc 
{
	namespace document 
	{
		class DocumentArchiveInfoRepository
		{
		public:
			DocumentArchiveInfoRepository();
			virtual ~DocumentArchiveInfoRepository();

			virtual void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);
			virtual void injectFindAccessor(persistence::IAccessorPtr accessor);
			virtual void injectFindbyGuidAccessor(persistence::IAccessorPtr accessor);
			virtual void injectInsertAccessor(persistence::IAccessorPtr accessor);
			virtual void injectUpdateAccessor(persistence::IAccessorPtr accessor);

			virtual DocumentArchiveInfoPtr createEmptyDocumentArchiveInfo() const;
			virtual DocumentArchiveInfoPtr findDocumentArchiveInfo(const basar::Int16 branchNo, const basar::Int32 customerNo, const DocumentTypeEnum documentType, const basar::VarString& documentNo, const basar::Int32 documentDate = 0) const;
			virtual DocumentArchiveInfoPtr findDocumentArchiveInfoByGuid(const basar::Int16 branchNo, const basar::Int32 customerNo, const basar::VarString& documentGUID) const;
			virtual void saveDocumentArchiveInfo(DocumentArchiveInfoPtr documentArchiveInfo) const;

			void injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter);

		protected:

		private:
			DocumentArchiveInfoRepository& operator=(const DocumentArchiveInfoRepository&);

			persistence::ITransactionFactoryPtr m_TransactionFactory;
			persistence::IAccessorPtr m_FindAccessor;
			persistence::IAccessorPtr m_FindByGuidAccessor;
			persistence::IAccessorPtr m_InsertAccessor;
			persistence::IAccessorPtr m_UpdateAccessor;
			parameter::IBranchParameterGetterPtr m_BranchParameterGetter;
		};
	} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_DOCUMENTARCHIVEINFO_REPOSITORY_H
