#ifndef GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_REPOSITORY_H
#define GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_REPOSITORY_H

#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasarcmnutil_bstring.h>
#include "narcoticarchiveptr.h"
#include <parameter/ibranchparametergetterptr.h>
#include <types/documenttypeenum.inc>

namespace libcsc 
{
	namespace document 
	{

		class NarcoticArchiveRepository
		{
		public:
			NarcoticArchiveRepository();
			virtual ~NarcoticArchiveRepository();

			virtual void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);
			virtual void injectFindAccessor(persistence::IAccessorPtr accessor);
			virtual void injectFindByContributionVoucherNoAccessor(persistence::IAccessorPtr accessor);
			virtual void injectInsertAccessor(persistence::IAccessorPtr accessor);
			virtual void injectUpdateAccessor(persistence::IAccessorPtr accessor);

			virtual NarcoticArchivePtr createEmptyNarcoticArchive() const;
			virtual NarcoticArchivePtr findNarcoticArchive(const basar::Int16 branchNo, const basar::Int32 customerSupplierNo, const basar::Int32 transactionDate) const;
			virtual NarcoticArchivePtr findNarcoticArchiveByContributionVoucherNo(const basar::Int16 branchNo, const basar::Int32 contributionVoucherNo) const;
			virtual void updateAcknowledgementStatusSQL(NarcoticArchivePtr narcoticArchivePtr) const;

			void injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter);

		protected:

		private:
			NarcoticArchiveRepository& operator=(const NarcoticArchiveRepository&);

			persistence::ITransactionFactoryPtr m_TransactionFactory;
			persistence::IAccessorPtr m_FindAccessor;
			persistence::IAccessorPtr m_FindByContributionVoucherNoAccessor;
			persistence::IAccessorPtr m_InsertAccessor;
			persistence::IAccessorPtr m_UpdateAccessor;
			parameter::IBranchParameterGetterPtr m_BranchParameterGetter;
		};

	} // end namespace document
} // end namespace libcsc

#endif // GUARD_LIBCSC_DOCUMENT_NARCOTICARCHIVE_REPOSITORY_H
