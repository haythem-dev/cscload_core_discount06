#ifndef GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESREPOSITORY_H
#define GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESREPOSITORY_H

#include "iblockedarticlesrepository.h"

#include <parameter/ibranchparametergetterptr.h>
#include <persistence/iaccessorptr.h>
#include <persistence/itransactionfactoryptr.h>
#include <libbasar_definitions.h>

#include <blockedarticles/blockedarticlesptr.h>

namespace basar {
	namespace db {
		namespace sql {
			class ResultsetRef;
		}
	}
}

namespace libcsc {
namespace blockedarticles {

	class BlockedArticlesRepository : public IBlockedArticlesRepository
	{
	public:
		BlockedArticlesRepository();
		virtual ~BlockedArticlesRepository();

		virtual void injectTransactionFactory(persistence::ITransactionFactoryPtr transactionFactory);

		virtual void injectBlockedArticlesAccessor(persistence::IAccessorPtr accessor);
		virtual void injectUpdateAccessor(persistence::IAccessorPtr accessor);
		void injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter);

		virtual BlockedArticlesCollectionPtr findBlockedArticles(basar::Int16 branchNo, basar::Int32 blockID) const;

		virtual void saveBlockedArticle(const BlockedArticlesPtr& blockedArticles) const;

	private:
		persistence::ITransactionFactoryPtr		m_TransactionFactory;
		persistence::IAccessorPtr				m_SelectBlockedArticlesAccessor;
		persistence::IAccessorPtr				m_UpdateAccessor;

		parameter::IBranchParameterGetterPtr	m_BranchParameterGetter;
	};

} // namespace blockedarticles
} // namespace libcsc

#endif // GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESREPOSITORY_H
