#ifndef GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESCOMPONENTMANAGER_H
#define GUARD_LIBCSC_BLOCKEDARTICLES_BLOCKEDARTICLESCOMPONENTMANAGER_H

#include "blockedarticles/blockedarticlesrepositoryptr.h"
#include "blockedarticles/iblockedarticlesrepositoryptr.h"

#include <parameter/ibranchparametergetterptr.h>
#include <boost/enable_shared_from_this.hpp>
#include <persistence/itransactionfactory.h>
#include <persistence/connectionptr.h>
#include <persistence/iaccessorptr.h>

class pxSession;

namespace libcsc {
namespace blockedarticles {

	class BlockedArticlesComponentManager : public persistence::ITransactionFactory,
											public boost::enable_shared_from_this<BlockedArticlesComponentManager>
	{
	public:
		BlockedArticlesComponentManager();
		virtual ~BlockedArticlesComponentManager();

		void injectConnection(persistence::ConnectionPtr connection);
		void injectTransactionHandler(nDataBase * transactionHandler);
		void injectBranchParameterGetter(parameter::IBranchParameterGetterPtr parameterGetter);

		virtual libcsc::persistence::TransactionGuard	createTransaction() const;

		IBlockedArticlesRepositoryPtr		getBlockedArticlesRepository();

	private:
		BlockedArticlesComponentManager(const BlockedArticlesComponentManager &);
		BlockedArticlesComponentManager & operator=(const BlockedArticlesComponentManager &);

		persistence::IAccessorPtr					createAccessor();

		persistence::ConnectionPtr					m_Connection;
		nDataBase *									m_TransactionHandler;
		parameter::IBranchParameterGetterPtr		m_BranchParameterGetter;

		mutable IBlockedArticlesRepositoryPtr		m_BlockedArticlesRepository;
	};

} //returns
} //libcsc

#endif //GUARD_LIBCSC_RETURNS_RETURNSCOMPONENTMANAGER_H
